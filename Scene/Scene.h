#ifndef Scene_h
#define Scene_h
#include "arduino.h"
#include "DisplayObject.h"
#include "RAM.h"
#include "Screen.h"

class Manager;
class Scene : public DisplayObject{
	public:
		Scene(uint8_t childSize);
				
		void onUpdate();
		void updateChild(DisplayObject* child);
		
		void setInverse(uint8_t value);
		void adjustBrightness();
		
		void onButtonDown(uint8_t button);
		
		void sleep();
		void wakeUp();
		
	private:
		Screen myScreen;
		uint8_t inverse = true;
		uint8_t sleeping = false;
		uint8_t autoBrightness = true;
		
};

#endif