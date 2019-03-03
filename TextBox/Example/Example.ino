#include "Setup.h"

TextBox myText(1, 128, 8, TYPE_8);
const char yazi[] PROGMEM = "Serial port is being>listened...>Baud rate is 115200>>";

void setup(){
	Serial.begin(115200);
	Setup();
	
	scene.addChild(&myText);
	myText.setCursor(true);
  
	myText.setTextSource(PGMEM);
	myText.write((char*)yazi);
	myText.setTextSource(SMEM);
}

void loop(){
  if(Serial.available()){
    char a[2];
    a[0] = Serial.read();
    a[1] = '\0';
    myText.write(a);
  }
  updater.update();
}