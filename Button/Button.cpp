#include "Button.h"

Button::Button(uint8_t button_pin, fPtr onChanged){
	SPI.begin();
	
	my_object = (object*)RAM::malloc(sizeof(object));
	if(my_object){
		object new_button = {};
		new_button.pin = button_pin;                                          
		new_button.preLongPressed = true;
		new_button.up = true;
		new_button.longPressedTime = 500;
		new_button.onChanged = onChanged;
		copyObject(&new_button, my_object);
	}
}

bool Button::buttonDown(){
	if(RAM::read(&my_object->pushed)){
		RAM::write(&my_object->pushed, false);
		return true;
	}
	return false;
}

bool Button::buttonLongDown(){
	if(RAM::read(&my_object->longPressed)){
		RAM::write(&my_object->longPressed, false);
		return true;
	}
	return false;
}

bool Button::buttonUp(){
	if(RAM::read(&my_object->released)){
		RAM::write(&my_object->released, false);
		return true;
	}
	return false;
}

void Button::statusChanged(){
	fPtr onChanged = (fPtr)RAM::readPtr(&my_object->onChanged);
	if(onChanged != NULL)
		onChanged(this);
}

void Button::update(uint8_t data)
{	
	if(data & getPin())
	{
		RAM::write32(&my_object->down_lastTime, millis());
		if(RAM::read(&my_object->up) && (millis() - RAM::read32(&my_object->up_lastTime)) > DEBOUNCE_TIME){
			RAM::write(&my_object->up, false);
			RAM::write(&my_object->down, true);
			RAM::write(&my_object->pushed, true);
			statusChanged();
		}
	}	
	else
	{
		RAM::write32(&my_object->up_lastTime, millis());
		if(RAM::read(&my_object->down) && (millis() - RAM::read32(&my_object->down_lastTime)) > DEBOUNCE_TIME){
			RAM::write(&my_object->up, true);
			RAM::write(&my_object->down, false);
			RAM::write(&my_object->released, true);
			RAM::write(&my_object->preLongPressed, true);
			statusChanged();
		}
	}
	
	if(RAM::read(&my_object->preLongPressed) && (millis() - RAM::read32(&my_object->up_lastTime)) > RAM::read32(&my_object->longPressedTime)){
		RAM::write(&my_object->preLongPressed, false);
		RAM::write(&my_object->longPressed, true);
		statusChanged();
	}
}

uint8_t Button::isDown(){
	return RAM::read(&my_object->down);
}

uint8_t Button::getPin(){
	return RAM::read(&my_object->pin);
}

void Button::setInputType(uint8_t type){
	RAM::write(&my_object->inputType, type);
	if(type == PARALEL_INPUT){
		pinMode(7 + getPin(), INPUT);
	}
}
uint8_t Button::getInputType(){
	return RAM::read(&my_object->inputType);
}

uint8_t Button::getCode(){
	uint8_t inputType = getInputType();
	uint8_t code;
	
	if(inputType == SPI_INPUT){
		switch(getPin()){
			case BUTTON_H: code = CODE_H; break;
			case BUTTON_G: code = CODE_G; break;
			case BUTTON_F: code = CODE_F; break;
			case BUTTON_E: code = CODE_E; break;
			case BUTTON_D: code = CODE_D; break;
			case BUTTON_C: code = CODE_C; break;
			case BUTTON_B: code = CODE_B; break;
		    case BUTTON_A: code = CODE_A; break;
		}
	}
	else if(inputType == PARALEL_INPUT){
		switch(getPin()){
			case BUTTON_Y: code = CODE_Y; break;
		    case BUTTON_X: code = CODE_X; break;
		}
	}
	return code;
}

void Button::copyObject(object* obj1, object* obj2){ //obj1 is to be copied
	RAM::writeArray(obj2, obj1, sizeof(object));
}

void Button::loadObject(object* obj1, object* obj2){ //obj1 is to be loaded
	RAM::readArray(obj2, obj1, sizeof(object));
}





