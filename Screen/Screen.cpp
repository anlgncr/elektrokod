#include "Screen.h"

Screen::Screen(){
	//buf = (uint8_t(*)[COLS])RAM::malloc(ROWS * COLS);
	SPI.begin();
	spiSetting =  SPISettings(16000000, MSBFIRST, SPI_MODE0);
	pinMode(6, OUTPUT);
	
	reset();
};

void Screen::reset(){
	sendCommand(DISP_NOOP);
	sendCommand2Byte(CMD_LOCK, 0x10);
	//sendCommand(ENTIRE_DISP_ON);
	sendCommand(RAM_CONTENT);
	sendCommand2Byte(MEM_ADD_MODE, PAGE_ADD_MODE);
	sendCommand(DISP_START_LINE | 0x00);
	sendCommand2Byte(DISP_CLOCK, 0xF0);
	sendCommand(SCAN_DIR_NORMAL);
	sendCommand(NORMAL_DIP);
	sendCommand2Byte(CONTRAST, 50);
	sendCommand2Byte(0xD5, 0xF0);//Frekans ve Divide

	writeBuffer();
	sendCommand(DISP_ON);
}

void Screen::setInverse(uint8_t value){
	if(value)
		sendCommand(INVERSE_DISP);
	else
		sendCommand(NORMAL_DIP);
}

void Screen::setBrightness(uint8_t value){
	sendCommand2Byte(CONTRAST, value);
}

void Screen::sleep(){
	sendCommand(DISP_OFF);
}

void Screen::wakeUp(){
	sendCommand(DISP_ON);
}

void Screen::writeBuffer(){
	sendCommand2Byte(LCOL_START_ADD, HCOL_START_ADD);
	
	for(uint8_t rows = 0; rows < ROWS; rows++){	
		sendCommand(PAGE_START_ADD | rows);
		
		SPI.beginTransaction(spiSetting);
		PORTD |= 1<<6;
		PORTC &= DECODER_MASK;
		PORTC |= CS_SCREEN;
		for(uint8_t cols = 0; cols < COLS; cols++){
			SPI.transfer(buf[rows][cols]);
		}
		SPI.endTransaction();	
	}
}

void Screen::clearBuffer(){
	for(uint8_t rows = 0; rows < ROWS; rows++){	
		for(uint8_t cols = 0; cols < COLS; cols++){
			buf[rows][cols] = 0x00;
		}
	}
}

void Screen::sendCommand(uint8_t cmd){
	PORTD &= ~(1<<6);
	send(cmd);
}

void Screen::sendCommand2Byte(uint8_t cmd1, uint8_t cmd2){
	SPI.beginTransaction(SPISettings(spiSetting));
	PORTD &= ~(1<<6);
	PORTC &= DECODER_MASK;
	PORTC |= CS_SCREEN;
	
	SPI.transfer(cmd1);
	SPI.transfer(cmd2);
	
	SPI.endTransaction();
}

void Screen::sendDataArray(uint8_t *data, uint16_t length){
	/*SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
	PORTD |= 1<<6;
	PORTC &= DECODER_MASK;
	PORTC |= CS_SCREEN;

	for(uint16_t i=0; i<length; i++){
		SPI.transfer(data[i]);
	}
	
	SPI.endTransaction();*/
}

void Screen::sendData(uint8_t data){
	//digitalWrite(6, HIGH);
	PORTD |= 1<<6;
	send(data);
}

void Screen::send(uint8_t data){
	SPI.beginTransaction(spiSetting);
	PORTC &= DECODER_MASK;
	PORTC |= CS_SCREEN;
	
	PORTC &= DECODER_MASK | 3;
	
	SPI.transfer(data);
	
	SPI.endTransaction();
}

uint8_t Screen::testDraw(DisplayObject* dispObj){
	my_object.image = dispObj->getImage();	
	if(!my_object.image)
		return 0;
	
	my_object.memory = dispObj->getMemory();
	my_object.width = dispObj->getCanvasWidth();
	my_object.height = dispObj->getCanvasHeight();

	my_object.x = dispObj->getGlobalX();
	my_object.y = dispObj->getGlobalY();
	
	if((my_object.x + my_object.width) <= 0){ return 0; }
	if(my_object.x >= COLS){ return 0; }
	
	if(my_object.height == 0){ return 0; } // TO DO: yüksekliği 0 ile 8 arasında olanların yüksekliği 8 e ayarlanacak
	if((int)(my_object.y + my_object.height) <= 0){ return 0; }
	if(my_object.y >= ROWS*8){ return 0; }	
	if(my_object.height < 8) { my_object.height = 8; }
	my_object.dispObj = dispObj;
	
	return 1;
}	

void Screen::draw(){ // draw after testDraw!!
	
	uint8_t flipped = my_object.dispObj->isFlipped();
	uint8_t maskType = my_object.dispObj->getMaskType();
	
	uint8_t image_start_col, image_end_col, buffer_start_col;
	
	if(my_object.x < 0){
		buffer_start_col = 0;
		
		if((my_object.x + my_object.width) > COLS){
			image_start_col = abs(my_object.x);
			image_end_col = COLS - my_object.x; // Soldan, sağdan taşıyor
		}
		else{// Soldan taşıyor
			if(flipped){
				image_start_col = 0;
				image_end_col = my_object.width + my_object.x;
			}
			else{
				image_start_col = abs(my_object.x);
				image_end_col = my_object.width;
			}
		}
	}
	else{
		buffer_start_col = my_object.x;
		
		if(my_object.x + my_object.width > COLS) // Sağdan taşıyor
		{
			if(flipped){
				image_start_col = my_object.width - COLS + my_object.x;
				image_end_col = my_object.width;
			}
			else{
				image_start_col = 0;
				image_end_col = COLS - my_object.x;
			}
		}
		else{ // Taşma yok
			image_start_col = 0;
			image_end_col = my_object.width;
		}
	}
	
	int16_t buffer_start_row, buffer_end_row, image_start_row;
	uint8_t image_shift;
	
	if(my_object.y < 0){
		image_shift = 8 - abs(my_object.y) % 8;
		image_start_row = abs(my_object.y) / 8;
		buffer_start_row = -1;
		
		if((int)(my_object.y + my_object.height) > ROWS*8){
			buffer_end_row = ROWS; // Alttan üstten taşıyor
		}
		else{
			buffer_end_row = (my_object.y / 8 - 1) + (my_object.height / 8); // Üstten taşıyor
		}
	}
	else{
		image_shift = abs(my_object.y) % 8;
		image_start_row = 0;
		buffer_start_row = my_object.y / 8;
		
		if((int)(my_object.y + my_object.height) > ROWS*8){
			buffer_end_row = ROWS; // Alttan taşıyor
		}
		else{
			buffer_end_row = (my_object.y / 8) + (my_object.height / 8); // Taşma yok
		}
	}
	
	uint8_t visible_width = image_end_col - image_start_col;
	uint8_t temp_image[visible_width];
	uint8_t image_start_row_copy = image_start_row;
	
	uint8_t(*image_array)[my_object.width];
	
	OVERDRAW:
	image_start_row = image_start_row_copy;
	if(maskType == IMAGE_NO_MASK || maskType == IMAGE_AUTO_MASK){
		image_array = (uint8_t(*)[my_object.width])(my_object.image + 4);
	}
	else if(maskType == IMAGE_SELF_MASK){
		image_array = (uint8_t(*)[my_object.width])(my_object.image + 4 + my_object.width * (my_object.height / 8));
	}
	else{ //IMAGE_EXTERNAL_MASK
		image_array = (uint8_t(*)[my_object.width])my_object.dispObj->getExternalMask();
		maskType = IMAGE_SELF_MASK;
	}

	for(int16_t rows = buffer_start_row; rows < buffer_end_row; rows++)
	{
		uint8_t *imageCurAdd = &image_array[image_start_row][image_start_col];
		if(flipped){
			if(my_object.memory == SPIMEM)
				RAM::readArrayReverse(imageCurAdd, temp_image, visible_width);
			else if(my_object.memory == PGMEM)
				readArrayPgmReverse(imageCurAdd, temp_image, visible_width);	
		}
		else{
			if(my_object.memory == SPIMEM)
				RAM::readArray(imageCurAdd, temp_image, visible_width);
			else if(my_object.memory == PGMEM)
				readArrayPgm(imageCurAdd, temp_image, visible_width);		
		}
		
		if(maskType == IMAGE_NO_MASK){
			if(rows >= 0){	
				for(uint8_t i=0; i<visible_width; i++){
					buf[rows][buffer_start_col + i] |= (temp_image[i] << image_shift);
				}
			}
			uint8_t lowerRow = rows + 1;
			if(lowerRow < ROWS && image_shift){	
				for(uint8_t i=0; i<visible_width; i++){
					buf[lowerRow][buffer_start_col + i] |= (temp_image[i] >> (8 - image_shift));
				}
			}
		}
		else if(maskType == IMAGE_SELF_MASK)
		{		
			if(rows >= 0){	
				for(uint8_t i=0; i<visible_width; i++){
					uint8_t image_mask = (buf[rows][buffer_start_col + i] & (0xFF >> (8 - image_shift))); 
					buf[rows][buffer_start_col + i] &= (temp_image[i] << image_shift) | image_mask;
				}
			}
			uint8_t lowerRow = rows + 1;
			if(lowerRow < ROWS && image_shift){	
				for(uint8_t i=0; i<visible_width; i++){
					uint8_t image_mask = (buf[lowerRow][buffer_start_col + i] & (0xFF << image_shift)); 
					buf[lowerRow][buffer_start_col + i] &= (temp_image[i] >> (8 - image_shift)) | image_mask;
				}
			}
		}
		else{//IMAGE_AUTO_MASK
			if(rows >= 0){	
				for(uint8_t i=0; i<visible_width; i++){
					uint8_t image_mask = (buf[rows][buffer_start_col + i] & (0xFF >> (8 - image_shift))); 
					buf[rows][buffer_start_col + i] = (temp_image[i] << image_shift) | image_mask;
				}
			}
			uint8_t lowerRow = rows + 1;
			if(lowerRow < ROWS && image_shift){	
				for(uint8_t i=0; i<visible_width; i++){
					uint8_t image_mask = (buf[lowerRow][buffer_start_col + i] & (0xFF << image_shift)); 
					buf[lowerRow][buffer_start_col + i] = (temp_image[i] >> (8 - image_shift)) | image_mask;
				}
			}
		}
		image_start_row++;
	}
	
	if(maskType == IMAGE_SELF_MASK){
		maskType = IMAGE_NO_MASK;
		goto OVERDRAW;
	}
}

void Screen::readArrayPgm(uint8_t *address, uint8_t *data, uint16_t length){
	for(uint16_t i=0; i<length; i++){
		data[i] = pgm_read_byte(&address[i]);
	}
}

void Screen::readArrayPgmReverse(uint8_t *address, uint8_t *data, uint16_t length){
	for(uint16_t i=0; i<length; i++){
		data[i] = pgm_read_byte(&address[length - 1 - i]);
	}
}



























