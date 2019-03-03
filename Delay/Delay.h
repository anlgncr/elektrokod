#ifndef Delay_h
#define Delay_h
#include "arduino.h"
#include "RAM.h"
#include "Updatable.h"

class Delay : public Updatable{
	public:
		Delay();
		
		typedef void (*fPtr)(Delay*);
		void start(fPtr, uint32_t);
		uint8_t update();
		
		void setRepeatCount(uint16_t);
		void setFinished(uint8_t);
		void setOnFinish(fPtr);
		void setOnRepeat(fPtr);
		void setId(uint8_t);
		
		uint8_t getRepeatCount();
		uint32_t getInitTime();
		uint32_t getTotalTime();
		uint8_t isFinished();
		uint8_t getId();
		
	private:
		struct object{
			uint8_t id;
			fPtr onFinish;
			fPtr onRepeat;
			uint8_t finished;
			uint16_t repeat_count;
			uint16_t repeat_size;
			uint32_t init_time;
			uint32_t total_time;
		};
		object *my_object;
		void repeat();
		void setRepeatSize(uint16_t);
		void setTotalTime(uint32_t);
		void setInitTime(uint32_t);
		uint16_t getRepeatSize();
		fPtr getOnRepeat();
		fPtr getOnFinish();
};
#endif