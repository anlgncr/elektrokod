#ifndef Watch_h
#define Watch_h
#include "arduino.h"
#include "DS3231.h"
#include "DisplayObject.h"
#include "Sprite.h"
#include "MovieClip.h"
#include "Shape.h"
#include "Tween.h"
#include "numbers.h"

#define DIGITAL 0
#define ANALOG 1
#define CHAR_WIDTH 23
#define COLON_WIDTH 7
#define AKREP_WIDTH 15
#define YELKOVAN_WIDTH 25
#define SANIYE_WIDTH 25

uint8_t* colonImageArray[] = {(uint8_t*)colonBmp, NULL};
uint8_t* numbers[] = {	(uint8_t*)zero, (uint8_t*)one, (uint8_t*)two, (uint8_t*)three, (uint8_t*)four,
						(uint8_t*)five, (uint8_t*)six, (uint8_t*)seven, (uint8_t*)eight, (uint8_t*)nine };

class Watch : public DisplayObject{
	public:
		Watch() : 	DisplayObject(10),
					tens1(0, numbers, 10, 1), tens0(0, numbers, 10, 1), 
					ones1(0, numbers, 10, 1), ones0(0, numbers, 10, 1), 
					digitalContainer(10), analogContainer(5),
					akrep(0, 40, 40), yelkovan(0, 50, 50), saniye(0, 50, 50), indicator(0,46, 5),
					newTween(SPIMEM), colon(0, colonImageArray, 2, 1)
		{
			
			digitalContainer.setXY(13, 12);		
			addChild(&digitalContainer);			
			digitalContainer.addChild(&tens1);
			digitalContainer.addChild(&tens0);
			digitalContainer.addChild(&ones1);
			digitalContainer.addChild(&ones0);
			digitalContainer.addChild(&colon);
			
			tens0.setX(tens1.getX() + CHAR_WIDTH);
			colon.setXY(tens0.getX() + CHAR_WIDTH + 3, 4);
			colon.play();
			ones1.setX(colon.getX() + COLON_WIDTH + 3);
			ones0.setX(ones1.getX() + CHAR_WIDTH);
			
			analogContainer.setX((128 - 63) / 2);
			analogContainer.setImage((uint8_t*)frameBmp);
			
			akrep.setXY(12,12);
			yelkovan.setXY(7,7);
			saniye.setXY(7,7);
			analogContainer.addChild(&akrep);
			analogContainer.addChild(&yelkovan);
			analogContainer.addChild(&saniye);
			
			newTween.setAnimation(EASE_OUT_ELASTIC);
			indicator.setY(45);
			digitalContainer.addChild(&indicator); 

			for(uint8_t i=0; i<5; i++)
				indicator.drawLine(0, i, 45, i);
		}
		
		void onAdded(){
			my_watch.getTime(&my_dt);
			updateClock();
			colon.play();
			indicator.setVisibility(false);
			set = false;
		}
		
		void onRemoved(){
			colon.gotoAndStop(0);
		}
		
		void onButtonDown(uint8_t button){
			if(set){
				if(button == CODE_G)
					increaseTime();
				else if(button == CODE_E)
					decreaseTime();
				else if(button == CODE_H)
					selectHours();
				else if(button == CODE_F)
					selectMinutes();
				else if(button == CODE_A)
					setTime();
				else if(button == CODE_C)
					cancel();
			}
			else if(button == CODE_D){
				toggle();
			}
		}
		
		void onButtonLongDown(uint8_t button){
			if(button == CODE_E)
				setMode();
		}

		void setMode(){
			if(!set){ 									//Eğer ayarlama modu kapalıysa
				setType(DIGITAL); 						//Digitale geç
				set = true;
				indicator.setVisibility(true);
				colon.gotoAndStop(0); 					//İki nokta animasyonunu durdur
				selectHours();							//Saat kısmını seç
			}
		}
		
		void setType(uint8_t value){
			if(value == DIGITAL){
				analogContainer.remove();
				addChild(&digitalContainer);
				type = DIGITAL;
			}
			else{
				digitalContainer.remove();
				addChild(&analogContainer);
				type = ANALOG;
			}
			onAdded();
		}
		
		void selectHours(){
			selected_side = 1;
			moveIndicator(tens1.getX());
		}
		
		void selectMinutes(){
			selected_side = 0;
			moveIndicator(ones1.getX());
		}
		
		void setTime(){
			my_watch.setTime(my_dt.hours, my_dt.minutes, 0);
			cancel();
		}
		
		void cancel(){
			onAdded();
			indicator.setVisibility(false);
		}
		
		void onUpdate()
		{
			if(set){
				newTween.update();
			}
			else{
				my_watch.getTime(&my_dt);
				
				if(type == DIGITAL){
					if(my_dt.minutes == 0){
						tens1.gotoAndStop(my_dt.hours / 10);
						tens0.gotoAndStop(my_dt.hours % 10);
					}
					if(my_dt.seconds == 0){
						ones1.gotoAndStop(my_dt.minutes / 10);
						ones0.gotoAndStop(my_dt.minutes % 10);
					}
				}
				else if(type == ANALOG){
					if(my_dt.seconds == 0){
						drawAkrep();	
						drawYelkovan();
					}
					drawSaniye();
				}
			}
		}
		
		void toggle(){
			if(type == DIGITAL)
				setType(ANALOG);
			else
				setType(DIGITAL);
		}
		
		void increaseTime()
		{
			if(selected_side == 1){
				if(my_dt.hours >= 23){
					my_dt.hours = 0;
				}
				else{
					my_dt.hours++;
				}
			}
			else{
				if(my_dt.minutes >= 59){
					my_dt.minutes = 0;
				}
				else{
					my_dt.minutes++;
				}
			}
			updateClock();
			
		}
		
		void decreaseTime(){
			if(selected_side == 1){
				if(my_dt.hours <= 0){
					my_dt.hours = 23;
				}
				else{
					my_dt.hours--;
				}		
			}
			else{
				if(my_dt.minutes <= 0){
					my_dt.minutes = 59;
				}
				else{
					my_dt.minutes--;
				}
			}
			updateClock();
		}
		
						
	private:
		uint8_t type = DIGITAL;
		uint8_t set = false;
		uint8_t selected_side = 1;
		DS3231 my_watch;
		DS3231::dateTime my_dt;
		Sprite digitalContainer, analogContainer;
		Shape akrep, yelkovan, saniye, indicator;
		MovieClip tens1, tens0, ones1, ones0, colon;
		Tween newTween;
		
		void updateClock(){
			if(type == ANALOG){
				drawAkrep();
				drawYelkovan();
			}
			else{
				tens1.gotoAndStop(my_dt.hours / 10);
				tens0.gotoAndStop(my_dt.hours % 10);
				ones1.gotoAndStop(my_dt.minutes / 10);
				ones0.gotoAndStop(my_dt.minutes % 10);
			}	
		}
		
		void drawSaniye(){
			int16_t degree = ((float)my_dt.seconds / 60) * 360;
			draw(&saniye, SANIYE_WIDTH, 24, degree);
		}
		
		void drawYelkovan(){
			int16_t degree = ((float)my_dt.minutes / 60) * 360;
			draw(&yelkovan, YELKOVAN_WIDTH, 24, degree);
		}
		
		void drawAkrep(){
			int16_t degree = ((float)(my_dt.hours % 12) / 12) * 360 + ((float)my_dt.minutes / 60) * 30;
			draw(&akrep, AKREP_WIDTH, 19, degree);
		}
		
		void draw(Shape* my_object, uint8_t width, uint8_t pos, int16_t degree){
			if(degree < 180){
				degree-=180;
				degree = abs(degree);
			}
			else if(degree >= 180){
				degree-=180;
				degree = 360 - degree;
			}
				
			float radian = ((float)degree / 180) * PI;
			int16_t x1 = round(sin(radian) * width) + pos;
			int16_t y1 = round(cos(radian) * width) + pos;
			my_object->clear();
			my_object->drawLine(pos, pos, x1, y1);
		}
		
		void moveIndicator(int16_t x){
			newTween.start(indicator.getXRef(), indicator.getX(), x, 250);
		}
};
#endif