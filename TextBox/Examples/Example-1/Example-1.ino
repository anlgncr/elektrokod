#include "Manager.h"
Manager manager;
TextBox myText;

void setup(){
  manager.begin();

  myText.create(128, 8);
  Manager::scene.addChild(&myText);
  if(!myText.writeFromFile("a.h")){
     myText.write("Dosya yok!");
  }
}

void loop(){
  manager.run();
}