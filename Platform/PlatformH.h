#ifndef PlatformH_h
#define PlatformH_h
#include "arduino.h"
#include "Shape.h"
#include "RAM.h"
#include "Player.h"

class PlatformH : public Shape{
	public:
		Player *player;
		uint8_t bottomHit = false;
		uint8_t topHit = false;
		
		PlatformH(uint8_t width, uint8_t height): Shape(0, width, height){
			//drawRectangle(0,0,width, height);
			fill();
		};
		
		void setPlayer(Player* my_player){
			player = my_player;
		}
		
		void onUpdate(){
			if(player != NULL){
				uint8_t hit;
				
				hit = hitTest(player->getBottomSensor());
				if(hit){
					if(!bottomHit){
						setId(1);
						player->onCollisonEnter(this);
						bottomHit = true;
					}
				}else{
					if(bottomHit){
						setId(1);
						player->onCollisonExit(this);
						bottomHit = false;
					}
				}	
				
				hit = hitTest(player->getTopSensor());
				if(hit){
					if(!topHit){
						setId(2);
						player->onCollisonEnter(this);
						topHit = true;
					}
				}else{
					if(topHit){
						setId(2);
						player->onCollisonExit(this);
						topHit = false;
					}
				}									
			}
		};
		
		void onAdded(){}


	private:
};

#endif