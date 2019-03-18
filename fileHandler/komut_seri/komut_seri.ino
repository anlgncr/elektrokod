#include "ROM.h"
#include "RAM.h"
#include "fileHandler.h"

#define READ_TIMEOUT 1000
#define READ_DIRECTORY 'D'
#define READ_FILE 'F'

fileHandler myFileHandler;

typedef enum {NONE, OKAY = 'O', WRITE = 'W', READ = 'R', DELETE = 'D'} commands;
commands command = NONE;

typedef enum {COMMAND, TRANSMIT, RECEIVE} serialStat;
serialStat status = COMMAND;

uint8_t* incomingData;
void setup() {
  Serial.begin(9600);
  incomingData = (uint8_t*)RAM::malloc(512);
}


uint32_t readStartTime = 0;

void processByte(const char data)
{
	static uint16_t dataPtr = 0;
	static uint16_t dataInfo = 0;
	
	if(status != COMMAND){
		if(millis() > readStartTime + READ_TIMEOUT){
			status = COMMAND;
		}
	}
	
	if(status == COMMAND)
	{
		if(command == NONE){
			command = data;
		}
		else if(data == '\n')
		{
			if(command == OKAY){
				Serial.print("OK");
				command = NONE;
			}
			else if(command == WRITE){
				status = RECEIVE;
				readStartTime = millis();
				dataPtr = 0;
				//Serial.println("Cihaz yazma modunda...");
			}
			else if(command == READ){
				readStartTime = millis();
				status = TRANSMIT;
				dataPtr = 0;
				//Serial.println("Cihaz okuma modunda...");
			}
			else if(command == DELETE){
				readStartTime = millis();
				status = RECEIVE;
				dataPtr = 0;
				//Serial.println("Silme işlemi seçildi");
			}
			else{
				command = NONE;
			}					
		}
		else{
			command = data;
		}
	}
    else if(status == RECEIVE)
	{
		readStartTime = millis();
		
		if(command == WRITE){
			if(dataPtr == 0){
				dataInfo = data;
				dataInfo <<= 8;
				dataPtr++;
			}
			else if(dataPtr == 1){
				dataInfo |= data;
				//Serial.println(data);
				dataPtr++;
			}
			else{
				if((dataPtr - 2) < dataInfo){
					RAM::write(&incomingData[dataPtr - 2], data);
					dataPtr++;
					//Serial.println("Data is being written...");
				}
				else{
					writeToROM();
					status = COMMAND;
					dataPtr = 0;
					Serial.println("Yazma islemi tamam!");
					dataInfo = 0;
					//Serial.println("Cihaz komut bekliyor...");
				}
			}
		}
		else if(command == DELETE){
			if(dataPtr == 0){
				dataInfo = data;
				dataInfo <<= 8;
				dataPtr++;
			}
			else if(dataPtr == 1){
				dataInfo |= data;
				dataPtr++;
			}
			else{
				if(myFileHandler.removeFileByIndex(dataInfo)){
					Serial.print('O');//OK
				}
				else{
					Serial.print('N');//NO OK
				}
				command = NONE;
				status = COMMAND;
			}
		}
	}
	else if(status == TRANSMIT)	
	{
		if(command == READ){
			if(data == READ_DIRECTORY){
				uint16_t count = myFileHandler.getFileCount();
				char upper = count >> 8;
				char lower = count;
				Serial.print(lower);
				Serial.print(upper);
				myFileHandler.readDirectoryOut();
			}
		}
	}
}


void readFromROM(uint16_t length){
	
}

void loop() {
	while(Serial.available()){
		processByte(Serial.read()); 
	}
}
