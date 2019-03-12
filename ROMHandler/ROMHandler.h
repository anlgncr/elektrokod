#ifndef ROMHandler_h
#define ROMHandler_h

#include "Arduino.h"
#include "ROM.h"
#include "RAM.h"

#define ID_SECTION_SIZE 2048
#define ID_SECTION_ADD 0x02

class ROMHandler{
	private:
		
		ROMHandler(){
			
		}
		
		uint16_t* allocate(uint16_t id, uint16_t length){
			
		}
		
		
	public:
};
#endif
