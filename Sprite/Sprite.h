#ifndef Sprite_h
#define Sprite_h
#include "arduino.h"
#include "DisplayObject.h"
#include "RAM.h"

class Sprite : public DisplayObject{
	public:
		Sprite(uint8_t childSize) : DisplayObject(childSize){
			
		};
		
		Sprite() : DisplayObject(0){
			
		};
		
		uint8_t update(){
			
		};

		
	private:
};

#endif