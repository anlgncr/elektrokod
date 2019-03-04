#include "Setup.h"
#include "ListBox.h"

ListBox myList(120, 12);

void setup() {
  Serial.begin(115200);
  Setup();

  scene.addChild(&myList);
  myList.add("Ocak");
  myList.add("Subat");
  myList.add("Mart");
  myList.add("Nisan");
  myList.add("Mayis");
  myList.add("Haziran");
  myList.add("Temmuz");
  myList.add("Agustos");
  myList.add("Eylul");
  myList.add("Ekim");
  myList.add("Kasim");
  myList.add("Aralik");
  
}

void loop() {
  //Serial.println(myList.getIndex());
  updater.update();

}