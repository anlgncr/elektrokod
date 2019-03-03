#include <RAM.h>


void setup() {
  Serial.begin(9600);
  RAM::init();

  byte *x = (byte*)RAM::malloc(20);
  byte a[20] = {255,0,3,4,5,6,7,8,9,0,11,22,33,55,66,77,88,99,100};
  RAM::writeArray(x,a, 20);

  byte b[20];

  RAM::readArray(x,b,20);

  for(byte i=0; i<20; i++)
   Serial.println(b[i]);

}

void loop() {
  // put your main code here, to run repeatedly:

}