#ifndef Sprite_h
#define Sprite_h
#include "arduino.h"
#include "DisplayObject.h"
#include "RAM.h"

class Sprite : public DisplayObject{
	public:
		Sprite() : DisplayObject(0){
			
		}
		
		Sprite(uint8_t childSize) : DisplayObject(childSize){
			
		}
		
		Sprite(uint8_t* image, uint8_t childSize, uint8_t memory) : DisplayObject(childSize){
			setImage(image);
		}
		
		uint8_t update(){
			
		}

		
	private:
};

#endif