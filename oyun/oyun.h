#ifndef Player_h
#define Player_h
#include "arduino.h"
#include "DisplayObject.h"
#include "RAM.h"
#include "MovieClip.h"
#include "TextBox.h"
#include "Sprite.h"

const uint8_t mega[] PROGMEM = { 25, 3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x18, 0x04, 0x82, 0x42, 0x23, 0xA5, 0xB9,
	0x2A, 0xAC, 0x28, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x18, 0x04,
	0x44, 0xC2, 0xE3, 0x04, 0x0B, 0x10, 0x14, 0x15, 0x15, 0x14, 0xE9, 0xC4, 0x47, 0x04, 0x18, 0xE0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xA1, 0xA2, 0x92, 0x9A, 0x85, 0x83, 0x82, 0xE4, 0x14, 0x08,
	0x94, 0xE4, 0x82, 0x83, 0x85, 0x9A, 0x92, 0xA2, 0xA1, 0xC0, 0x00
	//mask
	/*0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01,
	0x03, 0x07, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x07,
	0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x07, 0x1F, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xBE, 0x9E, 0x9E, 0x84, 0x80, 0x80, 0xE0, 0xF0, 0xF8,
	0xF0, 0xE0, 0x80, 0x80, 0x84, 0x9E, 0x9E, 0xBE, 0xBF, 0xFF, 0xFF*/
};

const uint8_t mega_mask[] PROGMEM = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01,
	0x03, 0x07, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x07,
	0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x07, 0x1F, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xBE, 0x9E, 0x9E, 0x84, 0x80, 0x80, 0xE0, 0xF0, 0xF8,
	0xF0, 0xE0, 0x80, 0x80, 0x84, 0x9E, 0x9E, 0xBE, 0xBF, 0xFF, 0xFF
};

class oyun : public DisplayObject
{
	Sprite karakter;
	TextBox fpsText;
	TextBox messageText;
	public:
		uint32_t processTime;
		
		oyun(uint8_t childSize): DisplayObject(childSize), karakter(0), fpsText(0, 18, 1, TYPE_8), messageText(0, 18, 1, TYPE_8){
			
			//setImage((uint8_t*)background);
			
			setDelayTime(250);
			setDelaying(true);
			Manager::scene.addChild(&fpsText);
			Manager::scene.addChild(&messageText);
			messageText.setY(8);;
			processTime = millis();
			
			karakter.setImage((uint8_t*)mega);
			karakter.setExternalMask((uint8_t*)mega_mask);
			karakter.setMaskType(IMAGE_EXTERNAL_MASK);
			karakter.setXY(60,30);
			addChild(&karakter);
			
			pinMode(7, OUTPUT);
		}
		
		void onAdded(){}	
		void onRemoved(){ right = left = up = down = false;}
		
		
		void onDelay(){
			char text_buffer[4];
			sprintf(text_buffer, "%03d", fps);
			//fpsText.clear();
			fpsText.write(text_buffer);
			
			sprintf(text_buffer, "%03d", getIndex());
			messageText.write(text_buffer);
			
			byte a = !digitalRead(7);
			digitalWrite(7, a);
		}
		
		uint8_t fps;
		void onUpdate(){
			processTime = millis() - processTime;
			fps = 1000 / processTime;
			processTime = millis();
			
			
			if(right){
				karakter.setX(karakter.getX()+1);
			}
			else if(left){
				karakter.setX(karakter.getX()-1);
			}
			
			if(up){
				karakter.setY(karakter.getY()-1);
			}
			else if(down){
				karakter.setY(karakter.getY()+1);
			}
		}
		
	private:
			bool right,left,up,down;
			
			uint8_t index = 4;
			void onButtonDown(uint8_t button){
				if(button == CODE_F){
					right = true;
					karakter.setFlipped(false);
				}
				else if(button == CODE_H){
					left = true;
					karakter.setFlipped(true);
				}
				
				if(button == CODE_E){
					down = true;
				}
				else if(button == CODE_G){
					up = true;
				}
				
				if(button == CODE_A){
					index --;
					getParent()->setChildIndex(this, index);
				}
				else if(button == CODE_C){
					index++;
					getParent()->setChildIndex(this, index);
				}
				
				if(button == CODE_B){
					//remove();
				}
			}
			
			void onButtonUp(uint8_t button){
				if(button == CODE_F){
					right = false;
					karakter.setFlipped(false);
				}
				else if(button == CODE_H){
					left = false;
					karakter.setFlipped(true);
				}
				
				if(button == CODE_E){
					down = false;
				}
				else if(button == CODE_G){
					up = false;
				}
				
			}
			void onButtonLongDown(uint8_t button){}
};

#endif