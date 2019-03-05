#include "TextBox.h"
#include "MovieClip.h"

TextBox::TextBox(uint8_t childSize, uint8_t width, uint8_t rowCount, uint8_t type) : DisplayObject(childSize + 1){
	uint8_t text_type;
	uint8_t *image = (uint8_t*)RAM::malloc(width * rowCount + 2);
	if(!image)
		return;
	
	RAM::write(&image[0], width);
	RAM::write(&image[1], rowCount);
	
	setMemory(SPIMEM);
	setImage(image);
	setMaskType(IMAGE_AUTO_MASK);
	
	my_object = (object*)RAM::malloc(sizeof(object));
	if(my_object){
		setTextSource(SMEM);
		setTextType(type);
		setImageIndex(&image[2]);	
	}
}

void TextBox::write(char *text){
	A:
	uint8_t row_width = getCanvasWidth(); // Satır genişliği (pixel)
	uint8_t char_width = getCharWidth() + 1; // Bir karakterin genişliği (pixel) + boşluk
	uint8_t row_char_count = row_width / char_width; // Bir satırda olabilecek azami karakter sayısı
	uint8_t row_remaining_space = row_width % char_width; // Satırın sonunda artan boşluk
	
	uint8_t row_count = getCanvasHeight(); // Toplam satır sayısı
	uint16_t char_count = getTextIndex(); // Toplam karakter sayısı
	uint8_t *image = getImageIndex(); // görüntü dizisinin kaldığı son index
	uint8_t start_col = char_count % row_char_count; // Son yazının kaldığı sütun
	uint8_t start_row = char_count / row_char_count; // Son yazının bittiği satır
	
	if(start_row >= row_count){
		//return;
		clear();
		goto A;
	}
	
	uint8_t nextChar;
	uint8_t current_row, current_col;

	for(current_row = start_row; current_row < row_count; current_row++)
	{
		for(current_col = start_col; current_col < row_char_count; current_col++)
		{
			if(getTextSource() == SMEM)
				nextChar = *(text++);
			else
				nextChar = pgm_read_byte(text++);
			
			if(nextChar == '\0'){
				setTextIndex(char_count);
				setImageIndex(image);
				moveCursor(current_row * 8, current_col * char_width);
				//Serial.println("end of the text");
				return;
			}
			else if(nextChar == '>'){
				uint8_t space_width = row_width - (current_col * char_width);
				char_count += space_width / char_width;
				
				for(uint8_t i=0; i<space_width; i++){
					RAM::write(image++, 0x00);
				}
				current_col = row_char_count; 
				break;
			}
			else{
				if(nextChar > 127)
					nextChar = 128;
				
				for(uint8_t curData = 0; curData < char_width - 1; curData++){
					RAM::write(image++, pgm_read_byte(&ASCII[nextChar - 0x20][curData]));
				}
				RAM::write(image++, 0x00);
			}
			char_count++;
		}
		
		if(nextChar != '>'){
			for(uint8_t i=0; i<row_remaining_space; i++){
				RAM::write(image++, 0x00);
			}
		}
		start_col = 0;
	}
	
	setTextIndex(char_count);
	setImageIndex(image);
	moveCursor((current_row - 1) * 8, current_col * char_width);
}

void TextBox::setCursor(uint8_t value){
	if(cursor_clip == NULL){
		cursor_clip = new MovieClip(0, cursor_images, 2, 2);
	}
	
	if(value){
		addChild(cursor_clip);
		cursor_clip->play();
	}
	else{
		cursor_clip->gotoAndStop(0);
		removeChild(cursor_clip);
	}
}

void TextBox::clear(){
	uint8_t* image_address = &getImage()[2];
	uint16_t col_size = (uint16_t)getImageIndex() - (uint16_t)image_address;
	RAM::writeLoop(image_address, 0, col_size);
	setTextIndex(0);
	setImageIndex(image_address);
	moveCursor(0, 0);
}

void TextBox::moveCursor(uint8_t row, uint8_t col){
	if(cursor_clip != NULL){
		cursor_clip->setX(col);
		cursor_clip->setY(row);
	}
}

void TextBox::setTextSource(uint8_t source){
	RAM::write(&my_object->textSource, source);
}

uint8_t TextBox::getTextSource(){
	return RAM::read(&my_object->textSource);
}

void TextBox::setTextType(uint8_t type){
	RAM::write(&my_object->textType, type);
	uint8_t charWidth;
	switch(type){
		case TYPE_8: charWidth = 5; break;
		case TYPE_16:  charWidth = 11; break;
		case TYPE_24:  charWidth = 13; break;
		case TYPE_32:  charWidth = 18; break;
		default: charWidth = 5;
	}
	RAM::write(&my_object->charWidth, charWidth);
}

uint8_t TextBox::getCharWidth(){
	return RAM::read(&my_object->charWidth);
}

uint8_t TextBox::getTextType(){
	return RAM::read(&my_object->textType);
}

void TextBox::setTextIndex(uint16_t index){
	RAM::write16(&my_object->textIndex, index);
}

void TextBox::setImageIndex(uint8_t *index){
	RAM::writePtr(&my_object->imageIndex, index);
}

uint16_t TextBox::getTextIndex(){
	return RAM::read16(&my_object->textIndex);
}

uint8_t TextBox::getRowCount(){
	return getCanvasHeight();
}

uint8_t* TextBox::getImageIndex(){
	return (uint8_t*)RAM::readPtr(&my_object->imageIndex);
}






