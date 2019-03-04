#ifndef Camera_h
#define Camera_h
#include "arduino.h"
#include "DisplayObject.h"
#include "RAM.h"
#include "Tween.h"

class Camera : public DisplayObject{
	public:
		Tween newTween, newTween2, alignTween;
		DisplayObject* target;
		
		Camera(uint8_t childSize): DisplayObject(childSize), newTween(SPIMEM), newTween2(SPIMEM), alignTween(SMEM){
			target = NULL;
			//alignTween.setAnimation(EASE_OUT);
			//setName("camera");
		}
		
		int16_t offSetX = 15;
		void onUpdate(){
			if(target){
				setXY(-target->getX() + offSetX, -target->getY() + 30);
			}
		}
		
		void alignLeft(){
			if(alignTween.getEndVal() != 15 ){
				alignTween.start(&offSetX, offSetX, 15, 2000);
				Manager::updater.add(&alignTween);
			}
		}
		
		void alignRight(){
			if(alignTween.getEndVal() != 83 ){
				alignTween.start(&offSetX, offSetX, 83, 2500);
				Manager::updater.add(&alignTween);
			}
		}
		
		void onAdded(){
			
		}
		
		void onRemoved(){
			
		}
		
		void follow(DisplayObject* my_target){
			target = my_target;
			moveTo(-target->getX() + 30, -target->getY() + 28, 50);
		}
		
		void onButtonDown(uint8_t button){
			//moveTo(128, 64, 5000);
		}
		
		void onButtonUp(uint8_t button){
			
		}
		
		void onButtonLongDown(uint8_t button){
			//moveTo(0,0,1000);
		}
		
		void moveTo(int16_t x, int16_t y, uint32_t time){
			if(newTween.isFinished()){
				newTween.start(getXRef(), getX(), x, time);
				Manager::updater.add(&newTween);
			}
			if(newTween2.isFinished()){
				newTween2.start(getYRef(), getY(), y, time);
				Manager::updater.add(&newTween2);
			}
		}
		
	private:
};

#endif