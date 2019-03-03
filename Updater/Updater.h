#ifndef Updater_h
#define Updater_h
#include "Arduino.h"
#include "Updatable.h"
#include "RAM.h"

class Updater{
	public:
		Updater(uint16_t);
		void update();
		void add(Updatable*);
		void addMulti(uint8_t, ...);
		void remove(Updatable*);
		
		uint16_t getCount();
	
	private:
		/*struct object{ // SAVE 4 byte here!
			Updatable** updatables;
			uint16_t size;
			uint16_t count;
		};
		object* my_object;*/
		
		Updatable** objects;
		uint16_t size = 0;
		uint16_t count = 0;
		
		void dispose();
		Updatable* getObject(uint16_t);
		void setObject(uint16_t, Updatable*);
};

#endif