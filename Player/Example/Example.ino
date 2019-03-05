#include "Manager.h"
#include "Player.h"
#include "Camera.h"
#include "PlatformH.h"
#include "PlatformV.h"

Manager my_manager;
Player player(10);
Camera newCam(100);
Sprite f;
TextBox info(0, 110, 3, TYPE_8);

void setup(){
  Manager::scene.addChild(&info);
  info.setX(24);
  
	//Serial.begin(9600); 
  f.setImage((uint8_t*)female);
  f.setXY(120,-50);
  f.setMaskType(IMAGE_AUTO_MASK);
  
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
  info.clear();

  char buf[20];
  sprintf(buf, "Sahne :%02d>", Manager::scene.getChildCount());
  info.write(buf);

  sprintf(buf, "Cam index :%02d>", newCam.getIndex());
  info.write(buf);

  sprintf(buf, "score index :%02d", player.fpsText.getIndex());
  info.write(buf);
  
}


