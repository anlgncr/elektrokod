#ifndef Scene_h
#define Scene_h
#include "arduino.h"
#include "DisplayObject.h"
#include "Updatable.h"
#include "RAM.h"
#include "Screen.h"
#include "EventNames.h"
#include "TextBox.h"

class Scene : public DisplayObject{
	
	uint8_t autoBrightness = true;
	
	public:
		Scene(uint8_t childSize) : DisplayObject(childSize){
			pinMode(A2, INPUT);
			
		}
				
		void onUpdate(){
			myScreen.clearBuffer();
			updateChild(this);
			myScreen.writeBuffer();
			adjustBrightness();
		}
		
		void updateChild(DisplayObject* child){
			if(child == NULL)
				return;
	
			if(child->isVisible()){
				if(myScreen.testDraw(child)){
					myScreen.draw();
				}
				
				if(child->getChildCount() > 0){
					for(uint8_t i=0; i<child->getChildCount(); i++){					
						updateChild(child->getChildAt(i));
					}
				}
			}
		}
		
		void setInverse(uint8_t value){
			myScreen.setInverse(value);
		}
		
		void adjustBrightness(){
			if(autoBrightness){
				uint16_t lightVal = analogRead(A2);
				uint8_t brightness = map(lightVal, 0, 1023, 0, 255);
				myScreen.setBrightness(255-brightness);
				//Serial.println(255-brightness);
			}
		}
		
		uint8_t inverse = true;
		void onButtonDown(uint8_t button){
			if(button == CODE_Y){
				setInverse(inverse);
				inverse = !inverse;
			}
		}
		
		void sleep(){
			myScreen.sleep();
		}
		
		void wakeUp(){
			myScreen.wakeUp();
		}
		
	private:
		Screen myScreen;
		
};

#endif