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
	
	Manager::button_code = my_button->getCode();
	Manager::scene.dispatchEventAll(button_event, Manager::button_code);
}

Manager::Manager():
	button_A(BUTTON_A,buttonListener),
	button_B(BUTTON_B,buttonListener),
	button_C(BUTTON_C,buttonListener),
	button_D(BUTTON_D,buttonListener),
	button_E(BUTTON_E,buttonListener),
	button_F(BUTTON_F,buttonListener),
	button_G(BUTTON_G,buttonListener),
	button_H(BUTTON_H,buttonListener),
	button_X(BUTTON_X,buttonListener),
	button_Y(BUTTON_Y,buttonListener)
{		   
	pinMode(CHARGE_STATUS_PIN, INPUT);
	pinMode(BUZZER, OUTPUT);
	button_Y.setInputType(PARALEL_INPUT);
	button_X.setInputType(PARALEL_INPUT);
	
	updater.add(&button_A);
	updater.add(&button_B);
	updater.add(&button_C);
	updater.add(&button_D);
	updater.add(&button_E);
	updater.add(&button_F);
	updater.add(&button_G);
	updater.add(&button_H);
	updater.add(&button_X);
	updater.add(&button_Y);
	updater.add(&scene);
}

void Manager::run(){
	
	for(uint8_t i=0; i<scene.getChildCount(); i++){
		updateDisplayObjects(scene.getChildAt(i));
	}
	scene.applyChildChanges();
	
	updater.update();
}

void Manager::updateDisplayObjects(DisplayObject* child){
	if(child == NULL)
		return;

	child->setGlobalX(child->getParent()->getGlobalX() + child->getX());
	child->setGlobalY(child->getParent()->getGlobalY() + child->getY());
	child->update();
				
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




