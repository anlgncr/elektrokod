#include "Manager.h"

Updater Manager::updater(100);
Scene Manager::scene(100);
uint8_t Manager::button_code = 0;

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
	
	button_code = my_button->getCode();
	scene.setEventInfo(button_code);
	scene.dispatchEventAll(button_event);
}

Manager::Manager():
	button_A(BUTTON_A,buttonListener),button_B(BUTTON_B,buttonListener),
	button_C(BUTTON_C,buttonListener),button_D(BUTTON_D,buttonListener),
	button_E(BUTTON_E,buttonListener),button_F(BUTTON_F,buttonListener),
	button_G(BUTTON_G,buttonListener),button_H(BUTTON_H,buttonListener),
	button_X(BUTTON_X,buttonListener),button_Y(BUTTON_Y,buttonListener)
{		  
	SPI.begin();
	pinMode(CHARGE_STATUS_PIN, INPUT);
	pinMode(BUZZER_PIN, OUTPUT);
	spiSetting = SPISettings(16000000, MSBFIRST, SPI_MODE0);
	
	button_X.setInputType(PARALEL_INPUT);
	button_Y.setInputType(PARALEL_INPUT);
}

void Manager::run(){
	updateButtons();
	updater.update();
	
	for(uint8_t i=0; i<scene.getChildCount(); i++){
		updateDisplayObjects(scene.getChildAt(i));
	}
	scene.applyChildChanges();
	scene.onUpdate();
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
		for(uint8_t i=0; i<child->getChildCount(); i++){					
			updateDisplayObjects(child->getChildAt(i));
		}
		child->applyChildChanges();
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
}




