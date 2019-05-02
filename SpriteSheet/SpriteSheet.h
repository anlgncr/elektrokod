#ifndef SpriteSheet_h
#define SpriteSheet_h
#include "Sprite.h"

class SpriteSheet : public Sprite{
	public:
		SpriteSheet();
		Sprite* getSprite(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	
	
	private:
};

#endif