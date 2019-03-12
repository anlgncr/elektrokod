#include "ROM.h"

void setup() {

  Serial.begin(115200);
 
  uint8_t* adres = 120;
  uint8_t zero[1024] = {};
  
  for(uint16_t i=0; i<64; i++){
    ROM::writeArray(i, zero, 1024);
    Serial.println("One page write is done..!");
  }
  Serial.println("All pages write are done..!");
  
  for(uint16_t i=0; i<64; i++){
    ROM::readArray(i, zero, 1024);

    for(uint16_t j=0; j<64; j++){
      Serial.println(zero[j]);
    }
    Serial.println("One page read is done");
  }
   Serial.println("All pages read are done..!");
}

void loop() {
 

}