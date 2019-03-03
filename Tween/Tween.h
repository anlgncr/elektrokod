#ifndef Tween_h
#define Tween_h
#include "arduino.h"
#include "RAM.h"
#include "Updatable.h"

#define LINEAR 0
#define EASE_IN 1
#define EASE_OUT 2
#define EASE_IN_BOUNCE 3
#define EASE_OUT_BOUNCE 4
#define EASE_IN_BACK 5
#define EASE_OUT_BACK 6
#define EASE_IN_ELASTIC 7 
#define EASE_OUT_ELASTIC 8
#define EASE_IN_OUT 9
#define EASE_OUT_IN 10
#define EASE_OUT_IN_ELASTIC 11 
#define EASE_IN_OUT_ELASTIC 12
#define NUMBER_OF_FUNCTION 12

class Tween : public Updatable{
	public:
		Tween(uint8_t);
		
		uint8_t update();
		void start(int16_t*, int16_t, int16_t, uint32_t);
		
		typedef void (*fPtr)(Tween*); 
		fPtr getOnFinish();
		fPtr getOnRepeat();
		int16_t* getVariable();
		int16_t getInitVal();
		int16_t getEndVal();
		uint32_t getInitTime();
		uint32_t getTotalTime();
		uint8_t getRepeatCount();
		uint8_t isReversing();
		uint8_t getAnimation();
		uint8_t getMemory();
		uint8_t isFinished();
		
		void setMemory(uint8_t);
		void setAnimation(uint8_t);
		void setOnFinish(fPtr);
		void setOnRepeat(fPtr);
		void setRepeatCount(uint16_t);
		void setReverse(uint8_t);
		void setFinished(uint8_t);
		void setId(uint8_t);
	
	private:
		struct object{
			uint8_t id;
			int16_t* variable;
			int16_t init_value;
			int16_t end_value;
			uint32_t init_time;
			uint32_t total_time;
			uint16_t repeat_count;
			//uint8_t repeating;
			uint8_t animation;
			fPtr onFinish;
			fPtr onRepeat;
			uint8_t finished;
			uint8_t memory;
			uint8_t reverse;
		};
		object *my_object;

		void repeat();
		
		void setVariable(int16_t*);
		void setInitVal(int16_t);
		void setEndVal(int16_t);
		void setTotalTime(uint32_t);
		void setVariableVal(int16_t*, int16_t);
		void setInitTime(uint32_t);
		//uint8_t isRepeating();
		//void setRepeating(uint8_t);
		
		typedef float(Tween::*tweenFunction)(float);
		float easeCombination(tweenFunction, tweenFunction, float);
		float linear(float); 			
		float easeIn(float); 			
		float easeOut(float); 		
		float easeInBounce(float); 	
		float easeOutBounce(float); 	
		float easeInBack(float); 		
		float easeOutBack(float); 	
		float easeInElastic(float); 	
		float easeOutElastic(float); 	
		float easeInOut(float); 		
		float easeOutIn(float); 		
		float easeOutInElastic(float);
		float easeInOutElastic(float);
};
#endif