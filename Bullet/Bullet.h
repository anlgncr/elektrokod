#ifndef Bullet_h
#define Bullet_h
#include "arduino.h"
#include "Shape.h"
#include "RAM.h"

class Bullet : public Shape{
	public:
		Bullet(): Shape(0, 2, 2){
			drawSquare(0,0,2);
		};
		
		uint8_t onUpdate(){
			move();
		};
		
		void onAdded(){
			setDelaying(true);
			analogWrite(BUZZER, 10);
			setDelayTime(10);
		}
		
		void onDelay(){
			digitalWrite(BUZZER, LOW);
			setDelaying(false);
		}
		
		void onRemoved(){
			setFlipped(false);
			digitalWrite(BUZZER, LOW);
			setDelaying(false);
		}
		
		void move(){
		
			if(isFlipped())
				setX(getX() - 4);
			else
				setX(getX() + 4);
				
			int16_t globalX = getGlobalX();
			
			if(globalX > 127 || globalX < 0)
				remove();
		
		}
		
		void setDirection(uint8_t value){
			setFlipped(value);
		}


	private:
};

#endif