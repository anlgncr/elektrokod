#include "ROM.h"
#include "RAM.h"
#include "fileHandler.h"

#define READ_TIMEOUT 1000

fileHandler myFileHandler;

typedef enum {NONE, OKAY = 'O', WRITE = 'W', READ_FILE = 'F', READ_DIRECTORY = 'D', REMOVE = 'R'} commands;
commands command = NONE;

typedef enum {COMMAND, TRANSMIT, RECEIVE} serialStat;
serialStat status = COMMAND;

uint8_t* incomingData;
void setup() {
  Serial.begin(115200);
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
			else if(command == WRITE || command == REMOVE){
				status = RECEIVE;
				readStartTime = millis();
				dataPtr = 0;
			}
			else if(command == READ_DIRECTORY){
				readStartTime = millis();
				status = TRANSMIT;
				dataPtr = 0;
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
					status = COMMAND;
					dataPtr = 0;
					dataInfo = 0;
					//Serial.println("Cihaz komut bekliyor...");
				}
			}
		}
		else if(command == REMOVE){
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
				//if(myFileHandler.removeFileByIndex(dataInfo)){
					Serial.print('O');//OK
				/*}
				else{
					Serial.print('N');//NO OK
				}*/
				status = COMMAND;
			}
		}
	}
	else if(status == TRANSMIT)	
	{
		if(command == READ_DIRECTORY){
			uint16_t count = myFileHandler.getFileCount();
			char upper = count >> 8;
			char lower = count;
			Serial.print(lower);
			Serial.print(upper);
			myFileHandler.readDirectoryOut();
			status = COMMAND;
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
