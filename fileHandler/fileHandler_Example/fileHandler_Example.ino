#include "fileHandler.h"

fileHandler handler; 
fileHandler::FILE myFile;

void yaz(){
  Serial.println("");
  Serial.print("Directory index : ");
  Serial.println(myFile.fileAddress / sizeof(fileHandler::FILE));
  Serial.print("Start sector address : ");
  Serial.println(myFile.startSector);
  Serial.print("Size : ");
  Serial.println(myFile.size);
  Serial.println("----------------");
}

void setup() {
  
  Serial.begin(115200);
  
  //handler.formatMemory();

  
  handler.createFile("anil", &myFile);
  handler.createFile("onur", &myFile);
  handler.createFile("ebru", &myFile);
  handler.createFile("tugce", &myFile);
  handler.createFile("file1", &myFile);
  handler.createFile("file2", &myFile);
  handler.createFile("file3", &myFile);
  handler.createFile("file4", &myFile);
  handler.createFile("file5", &myFile);
  handler.createFile("file6", &myFile);
  handler.createFile("file7", &myFile);
  handler.createFile("file8", &myFile);
  handler.createFile("file9", &myFile);
  handler.createFile("file10", &myFile);

   /*Serial.println("DIRECTORY TABLE");
  for(uint16_t i=0; i<32; i++){
    if(i % 16 == 0)
      Serial.println("-------------");
      
    Serial.println(ROM::read(i));
    
  }

  /*handler.getFile("anil", &myFile);
  handler.removeFile(&myFile);
  yaz();*/

  /* Serial.println("DIRECTORY TABLE");
  for(uint16_t i=0; i<32; i++){
    if(i % 16 == 0)
      Serial.println("-------------");
      
    Serial.println(ROM::read(i));
    
  }
  
*/
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
