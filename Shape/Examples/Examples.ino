#include <Setup.h>

Shape newShape(1, 16, 16);
void setup() {
  Setup();
  scene.addChild(&newShape);
  newShape.putPixel(1,1);
  newShape.putPixel(16,1);
  newShape.putPixel(1,16);
  newShape.putPixel(16,16);
}

void loop() {
  // put your main code here, to run repeatedly:
  updater.update();
}