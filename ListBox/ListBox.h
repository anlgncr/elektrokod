#ifndef ListBox_h
#define ListBox_h
#include "arduino.h"
#include "DisplayObject.h"
#include "TextBox.h"
#include "Tween.h"

const uint8_t indicatorBmp[] PROGMEM = {8, 1, 0x1C, 0x1C, 0x1C, 0x7F, 0x3E, 0x1C, 0x08, 0x00};


class ListBox : public DisplayObject{
	
	Sprite indicator;
	Tween indicatorTween;
	Tween listTextTween;
	int8_t index = 0;
	int8_t indexSize = 0;
	
	public:
	TextBox listText;
		ListBox(uint8_t width, uint8_t rowCount) : 
			DisplayObject(1), listText(1, width, rowCount, TYPE_8), 
			indicator(0), indicatorTween(SPIMEM), listTextTween(SPIMEM)
		{	
			addChild(&listText);
			listText.setX(12);
			listText.addChild(&indicator);
			indicator.setX(-12);
			indicator.setImage((uint8_t*)indicatorBmp);
			indicatorTween.setAnimation(EASE_OUT);
			listTextTween.setAnimation(EASE_OUT);
			
			//listText.setCursor(true);
			//indexSize=11;
		};
		
		void onUpdate(){
			
		};
		
		void onButtonUp(uint8_t button){
			
		}
			
		void onButtonDown(uint8_t button)
		{	
			if(button == CODE_A){
				if(listTextTween.isFinished()){
					if(index < indexSize - 1){
						int16_t y = indicator.getGlobalY();
						
						if((y + 8) >= 64 && indicatorTween.isFinished()){
							listTextTween.start(listText.getYRef(), listText.getY(), listText.getY()-8 , 100);
							updater.add(&listTextTween);
						}
						
						index++;
						indicatorTween.start(indicator.getYRef(), indicator.getY(), index*8 , 100);
						updater.add(&indicatorTween);
					}	
				}
			}
			else if(button == CODE_C){
				if(listTextTween.isFinished()){
					if(index > 0){
						int16_t y = indicator.getGlobalY();
						
						if((y - 8) < 0 && indicatorTween.isFinished()){
							listTextTween.start(listText.getYRef(), listText.getY(), listText.getY()+8 , 100);
							updater.add(&listTextTween);
						}
						
						index--;
						indicatorTween.start(indicator.getYRef(), indicator.getY(), index*8 , 100);
						updater.add(&indicatorTween);
					}
				}
			}
		}
		
		void add(char *text){
			uint8_t maxSize = listText.getRowCount();
			if(indexSize < maxSize){
				indexSize++;
				listText.write(text);
				if(indexSize != maxSize){
					char newLine[] = ">";
					listText.write(newLine);
				}
			}
		}
		
		uint8_t getIndex(){
			return index;
		}
			
		void onButtonLongDown(uint8_t button){}

		
	private:
};

#endif