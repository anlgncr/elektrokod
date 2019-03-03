#include "Tween.h"

Tween::Tween(uint8_t memory){
	my_object = (object*)RAM::malloc(sizeof(object));
	if(my_object){
		setMemory(memory);
		setRepeatCount(1);
		setFinished(true);
	}
}

void Tween::start(int16_t* variable, int16_t init_value, int16_t end_value, uint32_t total_time){
	//If timer register overflows then do not add my_tween
	if((millis() + total_time) < total_time)
		return;
	
	if(my_object){
		setVariable(variable);
        setInitVal(init_value);
		setEndVal(end_value);
		setInitTime(millis());
		setTotalTime(total_time);
		setFinished(false);
		
		if(getMemory() == SPIMEM){
			setVariableVal(variable, init_value);
		}
		else{
			*variable = init_value;
		}
	}
}

uint8_t Tween::update(){
	
	if(isFinished())
		return false;
	
	int16_t *my_var = getVariable();
	if(!my_var)
		return true;
	
	uint32_t elapsed_time = 0;
	elapsed_time = millis() - getInitTime();
	
	uint32_t total_time = getTotalTime();
	uint8_t memory = getMemory();
	
	if(elapsed_time >= total_time){
		elapsed_time = total_time;
				
		if(memory == SPIMEM){
			setVariableVal(my_var, getEndVal());
		}
		else{
			*my_var = getEndVal();
		}
	
		if(isReversing())
		{	
			int16_t temp = getInitVal();
			setInitVal(getEndVal());
			setEndVal(temp);
		}
		
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
			
			setFinished(true);
			return false;
		}
	}
	else{
		int16_t init_value = getInitVal();
		int16_t value = getEndVal() - init_value;
		float ratio = (float)elapsed_time / (float)getTotalTime();
		
		float cal_ratio = 1;
		switch(getAnimation()){
			case LINEAR: 					cal_ratio = linear(ratio); 				break;
			case EASE_IN: 					cal_ratio = easeIn(ratio); 				break;
			case EASE_OUT: 					cal_ratio = easeOut(ratio); 			break;
			case EASE_IN_BOUNCE: 			cal_ratio = easeInBounce(ratio); 		break;
			case EASE_OUT_BOUNCE: 			cal_ratio = easeOutBounce(ratio); 		break;
			case EASE_IN_BACK: 				cal_ratio = easeInBack(ratio); 			break;
			case EASE_OUT_BACK: 			cal_ratio = easeOutBack(ratio); 		break;
			case EASE_IN_ELASTIC: 			cal_ratio = easeInElastic(ratio); 		break;
			case EASE_OUT_ELASTIC: 			cal_ratio = easeOutElastic(ratio); 		break;
			case EASE_IN_OUT: 				cal_ratio = easeInOut(ratio); 			break;
			case EASE_OUT_IN: 				cal_ratio = easeOutIn(ratio); 			break;
			case EASE_OUT_IN_ELASTIC: 		cal_ratio = easeOutInElastic(ratio); 	break;
			case EASE_IN_OUT_ELASTIC: 		cal_ratio = easeInOutElastic(ratio); 	break;
		}
		int16_t result = init_value + round(value * cal_ratio);
		if(memory == SPIMEM){
			setVariableVal(my_var, result);
		}
		else{
			*my_var = result;
		}
	}
	return true;
}

void Tween::repeat(){
	fPtr function = getOnRepeat();
	if(function)
		function(this);
	
	setInitTime(millis());
}

//-------------------------------------- SETTER -->

void Tween::setVariable(int16_t* var){
	RAM::writePtr(&my_object->variable, var);
}

void Tween::setTotalTime(uint32_t time){
	RAM::write32(&my_object->total_time, time);
}

void Tween::setMemory(uint8_t value){
	RAM::write(&my_object->memory, value);
}

void Tween::setAnimation(uint8_t value){
	value = constrain(value, 0, NUMBER_OF_FUNCTION);
	RAM::write(&my_object->animation, value);
}

void Tween::setVariableVal(int16_t* var, int16_t value){
	RAM::write16(var, value);
}

void Tween::setFinished(uint8_t value){
	RAM::write(&my_object->finished, value);
}

void Tween::setReverse(uint8_t value){
	RAM::write(&my_object->reverse, value);
}

/*void Tween::setRepeating(uint8_t value){
	RAM::write(&my_object->repeating, value);
}

uint8_t Tween::isRepeating(){
	return RAM::read(&my_object->repeating);
}*/

void Tween::setRepeatCount(uint16_t value){
	RAM::write16(&my_object->repeat_count, value);
}

void Tween::setInitTime(uint32_t value){
	RAM::write32(&my_object->init_time, value);
}

void Tween::setInitVal(int16_t value){
	RAM::write16(&my_object->init_value, value);
}

void Tween::setEndVal(int16_t value){
	RAM::write16(&my_object->end_value, value);
}

void Tween::setOnFinish(fPtr onFinish){
	RAM::writePtr(&my_object->onFinish, (void*)onFinish);
}

void Tween::setOnRepeat(fPtr onRepeat){
	RAM::writePtr(&my_object->onRepeat, (void*)onRepeat);
}

//-------------------------------------- GETTER -->

uint8_t Tween::getMemory(){
	return RAM::read(&my_object->memory);
}

uint8_t Tween::getAnimation(){
	return RAM::read(&my_object->animation);
}

Tween::fPtr Tween::getOnRepeat(){
	return (fPtr)RAM::readPtr(&my_object->onRepeat);
}

Tween::fPtr Tween::getOnFinish(){
	return (fPtr)RAM::readPtr(&my_object->onFinish);
}

uint8_t Tween::getRepeatCount(){
	return RAM::read(&my_object->repeat_count);
}

uint8_t Tween::isReversing(){
	return RAM::read(&my_object->reverse);
}

int16_t* Tween::getVariable(){
	return (int16_t*)RAM::readPtr(&my_object->variable);
}

int16_t Tween::getInitVal(){
	return RAM::read16(&my_object->init_value);
}

int16_t Tween::getEndVal(){
	return RAM::read16(&my_object->end_value);
}

uint32_t Tween::getInitTime(){
	return RAM::read32(&my_object->init_time);
}

uint32_t Tween::getTotalTime(){
	return RAM::read32(&my_object->total_time);
}

uint8_t Tween::isFinished(){
	return RAM::read(&my_object->finished);
}


/* Methods for transition */

float Tween::linear(float ratio){
	return ratio;
}

float Tween::easeIn(float ratio){
  return ratio * ratio * ratio;
}

float Tween::easeOut(float ratio){
  float invRatio = ratio - 1;
  return invRatio * invRatio * invRatio +1; 
}

float Tween::easeInElastic(float ratio){
	if(ratio == 1 || ratio ==0)
		return ratio;
	else{
		float p = 0.3;
		float s = p/4.0;
		float invRatio = ratio - 1;
		return -1.0 * pow(2.0, 10.0 * invRatio) * sin((invRatio-s)*(2.0* 3.14)/p);
	}
}

float Tween::easeOutBounce(float ratio){
	float s= 7.5625;
	float p= 2.75;
	float l;
	if (ratio < (1.0/p)){
		l = s * pow(ratio, 2);
	}
	else{
		if (ratio < (2.0/p)){
			ratio -= 1.5/p;
			l = s * pow(ratio, 2) + 0.75;
		}
		else{
			if (ratio < 2.5/p){
				ratio -= 2.25/p;
				l = s * pow(ratio, 2) + 0.9375;
			}
			else{
				ratio -= 2.625/p;
				l =  s * pow(ratio, 2) + 0.984375;
			}
		}
	}
	return l;
}

float Tween::easeInBack(float ratio){
	float s = 1.70158;
	return pow(ratio, 2) * ((s + 1.0)*ratio - s);
}
		
float Tween::easeOutBack(float ratio){
	float invRatio = ratio - 1.0;            
	float s = 1.70158;
	return pow(invRatio, 2) * ((s + 1.0)*invRatio + s) + 1.0;
}

float Tween::easeOutElastic(float ratio){
	if (ratio == 0 || ratio == 1) return ratio;
	else{
		float p = 0.3;
		float s = p/4.0;                
		return pow(2.0, -10.0*ratio) * sin((ratio-s)*(2.0*3.14)/p) + 1;                
	}            
}      	

float Tween::easeInOut(float ratio){
	return easeCombination(&Tween::easeIn, &Tween::easeOut, ratio);
} 

float Tween::easeOutIn(float ratio){
	return easeCombination(&Tween::easeOut, &Tween::easeIn, ratio);
} 

float Tween::easeInBounce(float ratio){
	return 1.0 - easeOutBounce(1.0 - ratio);
}

float Tween::easeInOutElastic(float ratio){
	return easeCombination(&Tween::easeInElastic, &Tween::easeOutElastic, ratio);
} 

float Tween::easeOutInElastic(float ratio){
	return easeCombination(&Tween::easeOutElastic, &Tween::easeInElastic, ratio);
}

float Tween::easeCombination(tweenFunction init_function, tweenFunction end_function, float ratio){
	if (ratio < 0.5) {
		return 0.5 * (this->*init_function)(ratio * 2.0);
	}
	else {
		return 0.5 * (this->*end_function)((ratio - 0.5) * 2.0) + 0.5;
	}	
}







