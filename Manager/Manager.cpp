#include "Manager.h"

Updater Manager::updater(100);
Scene Manager::scene(100);
FileHandler Manager::fileHandler;
uint8_t* Manager::charset;

uint8_t Manager::button_code = 0;
uint32_t Manager::processTime = 0;

uint32_t Manager::getProcessTime(){
	return processTime;
}

uint8_t Manager::getBrightness(){
	uint8_t brightness = map(analogRead(A2), 0, 1023, 0, 255);
	return (255 - brightness);
}

void Manager::buttonListener(Button* my_button){ 
	uint8_t button_event;
	if(my_button->buttonUp())
		button_event = BUTTON_UP;
	else if(my_button->buttonDown())
		button_event = BUTTON_DOWN;
	else if(my_button->buttonLongDown())
		button_event = BUTTON_LONG_DOWN;
	else
		return;
	
	EventArgs e;
	e.setSender(&scene);
	e.setEventName(button_event);
	e.setData(my_button->getCode());
	scene.dispatchEventAll(&e);
}

Manager::Manager():
	button_A(BUTTON_A,buttonListener),button_B(BUTTON_B,buttonListener),
	button_C(BUTTON_C,buttonListener),button_D(BUTTON_D,buttonListener),
	button_E(BUTTON_E,buttonListener),button_F(BUTTON_F,buttonListener),
	button_G(BUTTON_G,buttonListener),button_H(BUTTON_H,buttonListener),
	button_X(BUTTON_X,buttonListener),button_Y(BUTTON_Y,buttonListener)
{		  
	SPI.begin();
	
	pinMode(LIGHT_SENSOR, INPUT);
	pinMode(CHARGE_STATUS_PIN, INPUT);
	pinMode(BUZZER_PIN, OUTPUT);
	spiSetting = SPISettings(16000000, MSBFIRST, SPI_MODE0);
	
	button_X.setInputType(PARALEL_INPUT);
	button_Y.setInputType(PARALEL_INPUT);
	
	run();
}

void Manager::begin(){
	Serial.begin(115200);
	
	FileHandler::FILE newFile;
	if(Manager::fileHandler.getFile("c.bmp", &newFile)){	
		charset = RAM::malloc(newFile.size);
		fileHandler.fileToSpiRam(&newFile, charset, newFile.size);
		charset += 5; // width + height + mask
	}
}

void Manager::run(){
	while(Serial.available())
		serialHandler.processByte(Serial.read());
	
	static uint32_t lastMillis = 0;
	
	updateButtons();
	updater.update();
	
	scene.onUpdate();
	scene.applyChildChanges();
	for(uint8_t i=0; i<scene.getChildCount(); i++){
		updateDisplayObjects(scene.getChildAt(i));
	}
	processTime = millis() - lastMillis;
	lastMillis = millis();
}

void Manager::updateDisplayObjects(DisplayObject* child){
	if(child == NULL)
		return;

	child->setGlobalX(child->getParent()->getGlobalX() + child->getX());
	child->setGlobalY(child->getParent()->getGlobalY() + child->getY());
	child->onUpdate();
				
	if(child->isDelaying()){
		if(millis() > (child->getDelayStartTime() + child->getDelayTime())){
			child->onDelay();
			child->setDelayStartTime(millis());	
		}
	}
	
	if(child->getChildCount() > 0){
		child->applyChildChanges();
		for(uint8_t i=0; i<child->getChildCount(); i++){					
			updateDisplayObjects(child->getChildAt(i));
		}
	}
}

void Manager::updateButtons(){	
	uint8_t data;
	
	SPI.beginTransaction(spiSetting);
	PORTC &= DECODER_MASK;
	PORTC |= CS_BUTTON;
	data = SPI.transfer(0);
	SPI.endTransaction();
	
	button_A.update(data);
	button_B.update(data);
	button_C.update(data);
	button_D.update(data);
	button_E.update(data);
	button_F.update(data);
	button_G.update(data);
	button_H.update(data);
	
	data = PINB & PARALEL_BUTTON_MASK;
	button_X.update(data);
	button_Y.update(data);
}

uint8_t Manager::isButtonDown(uint8_t code){
	switch(code){
		case CODE_A	: return button_A.isDown();
		case CODE_B : return button_B.isDown();
		case CODE_C : return button_C.isDown();
		case CODE_D : return button_D.isDown();
		case CODE_E : return button_E.isDown();
		case CODE_F : return button_F.isDown();
		case CODE_G : return button_G.isDown();
		case CODE_H : return button_H.isDown();
		case CODE_X : return button_X.isDown();
		case CODE_Y : return button_Y.isDown();
	}
	return false;
}




