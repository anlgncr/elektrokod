#include "Delay.h"
// SETONREPEAT KULLAN !!!!
Delay::Delay(){
	my_object = (object*)RAM::malloc(sizeof(object));
	if(my_object){
		setRepeatCount(1);
	}
}

void Delay::start(fPtr function, uint32_t total_time){
	//If timer register overflows then do not add my_tween
	if((millis() + total_time) < total_time)
		return;
	
	if(my_object){
		setRepeatSize(getRepeatCount());
		setInitTime(millis());
		setTotalTime(total_time);
		setOnFinish(function);
		setFinished(false);
	}
}

uint8_t Delay::update(){
	if(isFinished())
		return false;
		
	if((millis() - getInitTime()) >= getTotalTime()){
		uint16_t repeat_count = getRepeatCount();
		if(repeat_count > 1){
			repeat();
			setRepeatCount(repeat_count - 1);
		}
		else if(repeat_count == 0){
			repeat();
		}
		else{
			fPtr function = getOnFinish();
			if(function){
				function(this);
			}
			
			setRepeatCount(getRepeatSize());
			setFinished(true);
			return false;
		}
	}
	
	return true;
}

void Delay::repeat(){
	fPtr function = getOnRepeat();
	if(function)
		function(this);
	
	setInitTime(millis());
}

//--------------------- SETTER -->

void Delay::setTotalTime(uint32_t time){
	RAM::write32(&my_object->total_time, time);
}

void Delay::setRepeatCount(uint16_t value){
	RAM::write16(&my_object->repeat_count, value);
}

void Delay::setRepeatSize(uint16_t value){
	RAM::write16(&my_object->repeat_size, value);
}

void Delay::setFinished(uint8_t value){
	RAM::write(&my_object->finished, value);
}

void Delay::setInitTime(uint32_t value){
	RAM::write32(&my_object->init_time, value);
}

void Delay::setOnFinish(fPtr onFinish){
	RAM::writePtr(&my_object->onFinish, (void*)onFinish);
}

void Delay::setOnRepeat(fPtr onRepeat){
	RAM::writePtr(&my_object->onRepeat, (void*)onRepeat);
}

void Delay::setId(uint8_t id){
	RAM::write(&my_object->id, id);
}

//--------------------- GETTER -->

Delay::fPtr Delay::getOnRepeat(){
	return (fPtr)RAM::readPtr(&my_object->onRepeat);
}

Delay::fPtr Delay::getOnFinish(){
	return (fPtr)RAM::readPtr(&my_object->onFinish);
}

uint8_t Delay::getRepeatCount(){
	return RAM::read(&my_object->repeat_count);
}

uint16_t Delay::getRepeatSize(){
	return RAM::read(&my_object->repeat_size);
}

uint8_t Delay::getId(){
	return RAM::read(&my_object->id);
}

uint32_t Delay::getInitTime(){
	return RAM::read32(&my_object->init_time);
}

uint32_t Delay::getTotalTime(){
	return RAM::read32(&my_object->total_time);
}

uint8_t Delay::isFinished(){
	return RAM::read(&my_object->finished);
}



