#include <Sprite.h>
#include <RAM.h>

Sprite my_sprite, s1, s2;
Drawable* shape;

void setup() {
  Serial.begin(9600);
  RAM::init();

  my_sprite.create(NULL, 100, 23, 24);
  shape = &my_sprite;  
  shape->setName("The God");
   
  s1.create(NULL, 20, 100, 200);
  s1.setName("Adem");
  
  s2.create(NULL, 20, 100, 200);
  s2.setName("Havva");

  my_sprite.addChild(&s1);
  s1.addChild(&s2);
  
  my_sprite.writeInfo();

  s1.writeInfo();
  s2.writeInfo();  
}

void loop() {

}