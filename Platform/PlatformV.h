#ifndef PlatformV_h
#define PlatformV_h
#include "arduino.h"
#include "Shape.h"
#include "RAM.h"
#include "Player.h"

class PlatformV : public Shape{
	public:
		Player *player;
		uint8_t leftHit = false;
		uint8_t rightHit = false;
		
		PlatformV(uint8_t width, uint8_t height): Shape(0, width, height){
			//drawRectangle(0,0,width, height);
			fill();
		};
		
		void setPlayer(Player* my_player){
			player = my_player;
		}
		
		void onUpdate(){
			if(isDrawing()){
				if(player != NULL){
					uint8_t hit;
					
					hit = hitTest(player->getLeftSensor());
					if(hit){
						if(!leftHit){
							setId(4);
							player->onCollisonEnter(this);
							leftHit = true;
						}
					}else{
						if(leftHit){
							setId(4);
							player->onCollisonExit(this);
							leftHit = false;
						}
					}	
					
					hit = hitTest(player->getRightSensor());
					if(hit){
						if(!rightHit){
							setId(3);
							player->onCollisonEnter(this);
							rightHit = true;
						}
					}else{
						if(rightHit){
							setId(3);
							player->onCollisonExit(this);
							rightHit = false;
						}
					}									
				}
			}
		};
		
		void onAdded(){}


	private:
};

#endif