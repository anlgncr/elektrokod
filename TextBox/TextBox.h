#ifndef TextBox_h
#define TextBox_h
#include "arduino.h"
#include "DisplayObject.h"
#include "RAM.h"
#include "ASCII.h"
#include "MovieClip.h"

#define TYPE_8 0
#define TYPE_16 1
#define TYPE_24 2
#define TYPE_32 3

const uint8_t cursor[] PROGMEM = {1,1, 0xFF};

class TextBox : public DisplayObject{
	
	public:
		TextBox(uint8_t, uint8_t, uint8_t, uint8_t);
		
		uint8_t update();
		void write(char*);
		void setTextSource(uint8_t);
		void setCursor(uint8_t);
		void clear();
		
		uint8_t getRowCount();
	
	private:
	struct object{
		uint8_t textSource;
		uint8_t *textIndex;
		uint8_t *imageIndex;
		uint8_t textType;
		uint8_t charWidth;
	};
	object *my_object;
	
	void getType();
	uint8_t getWidth();
	
	MovieClip* cursor_clip;
	uint8_t *cursor_images[2] = {(uint8_t*)cursor, NULL};
	void moveCursor(uint8_t, uint8_t);
	
	uint16_t getTextIndex();
	uint8_t* getImageIndex();
	uint8_t getTextSource();
	void setTextType(uint8_t);
	uint8_t getCharWidth();
	uint8_t getTextType();
	void setTextIndex(uint16_t);
	void setImageIndex(uint8_t*);
};

#endif