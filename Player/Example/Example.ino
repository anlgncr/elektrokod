#include "Manager.h"
#include "Player.h"
#include "Camera.h"
#include "PlatformH.h"
#include "PlatformV.h"

Manager my_manager;
Player player(10);
Camera newCam(100);
Sprite f(0);

void setup(){
	//Serial.begin(115200); 
  f.setImage((uint8_t*)female);
  f.setXY(120,-50);
  
  Manager::scene.addChild(&newCam);
  newCam.addChild(&f);
  newCam.addChild(&player);
	
	player.setXY(0, 0);

	
	newCam.follow(&player);
	player.setCamera(&newCam);

  PlatformH *plat = new PlatformH(250, 3);
  plat->setName("c");
  plat->setY(50);
  plat->setX(-50);
  newCam.addChild(plat);
  plat->setPlayer(&player);

}

void loop(){
  my_manager.run();
}