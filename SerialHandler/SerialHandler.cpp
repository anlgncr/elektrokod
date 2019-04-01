#include "SerialHandler.h"

SerialHandler::SerialHandler(){	
	readStartTime = 0;
	cmd = NOOP;
	status = COMMAND;
	incomingData = (uint8_t*)RAM::malloc(112);	
}

void SerialHandler::flushBuffer(){
	while(Serial.available()){
		Serial.read();
	}
}

void SerialHandler::processByte(const char data)
{
	static uint16_t dataPtr = 0;
	static uint16_t dataLength = 0;
	
	if(status != COMMAND){
		if(millis() > readStartTime + READ_TIMEOUT){
			status = COMMAND;
		}
	}
	
	//--------------------------------------------->COMMAND
	if(status == COMMAND)
	{	
		if(cmd == NOOP){
			cmd = data;
		}
		else if(data == '\n')
		{
			if(cmd == OKAY){
				Serial.println(F("OK"));
				cmd = NOOP;
			}
			else if(cmd == HEY){
				Serial.println(F("Merhaba..."));
				cmd = NOOP;
			}
			else if(cmd == FORMAT){
				myFileHandler.formatMemory();
				Serial.println(F("Format tamamlandi."));
				cmd = NOOP;
			}
			else if(cmd == GET_FILE_COUNT){
				Serial.println(myFileHandler.getFileCount());
				cmd = NOOP;
			}
			else if(cmd == GET_FREE_SECTOR_COUNT){
				uint16_t sectorCount = myFileHandler.getFreeSectorCount();
				uint8_t data[2] = {sectorCount, sectorCount >> 8};
				Serial.write(data, 2);
				cmd = NOOP;
			}
			else if(cmd == WRITE_SECTOR || cmd == READ_SECTOR 	|| cmd == GET_FILE_ATTRIBUTE || 
					cmd == REMOVE_FILE 	|| cmd == NEW_FILE		|| cmd == RESIZE)
			{
				readStartTime = millis();
				status = RECEIVE;
				dataPtr = 0;
				dataLength = 0;
			}
			else if(cmd == READ_DIRECTORY){
				readStartTime = millis();
				status = TRANSMIT;
			}
			else{ cmd = NOOP; }					
		}
		else{ cmd = data; }	
	}//--------------------------------------------> RECEIVE
    else if(status == RECEIVE)
	{
		readStartTime = millis();
		if(dataPtr == 0){
			dataLength = data;
			dataLength <<= 8;
			dataPtr++;
		}
		else if(dataPtr == 1){
			dataLength |= data;
			dataPtr++;
		}
		else if((dataPtr - 2) < dataLength){
			RAM::write(&incomingData[dataPtr - 2], data);
			dataPtr++;
		}
		else{ 
			status = COMMAND;

			if(cmd == WRITE_SECTOR){
				uint16_t currentSector = RAM::read16(incomingData);
				uint16_t length = RAM::read16(incomingData + 2);
				uint8_t isThisLastSector = RAM::read(incomingData + 4);
				
				uint16_t nextSector = myFileHandler.writeSector(incomingData + 5, currentSector, length, isThisLastSector);
				uint8_t data[2] = { (uint8_t)nextSector, (uint8_t)(nextSector >> 8) };
				Serial.write(data, 2);
			}
			else if(cmd == READ_SECTOR){
				uint16_t currentSector = RAM::read16(incomingData);
				uint16_t length = RAM::read16(incomingData + 2);
				
				uint16_t nextSector = myFileHandler.readSector(incomingData, currentSector, length);
				for(uint8_t i=0; i<length; i++){
					Serial.write(RAM::read(&incomingData[i]));
				}
				uint8_t data[2] = { (uint8_t)nextSector, (uint8_t)(nextSector >> 8) };
				Serial.write(data, 2);
			}
			else if(cmd == NEW_FILE){
				char name[10];
				RAM::readArray(incomingData, name, 10);
				FileHandler::FILE newFile;
				uint8_t result = myFileHandler.createFile(name, &newFile);
				if(result == 'Y'){
					name[0] = 'Y';
					name[1] = newFile.fileAddress;
					name[2] = newFile.fileAddress >> 8;
					Serial.write(name, 3);
				}
				else if(result == 'S'){ Serial.print('S'); }
				else{ Serial.print('N'); }
			}
			else if(cmd == REMOVE_FILE){
				uint16_t fileIndex = RAM::read16(incomingData);
				if(myFileHandler.removeFileByIndex(fileIndex)){
					Serial.print('O');//OK
				}
				else{ Serial.print('N'); }//NO OK	
			}
			else if(cmd == RESIZE){
				uint16_t fileIndex = RAM::read16(incomingData);
				uint16_t fileSize = RAM::read16(incomingData + 2);
				
				FileHandler::FILE newFile = {};
				myFileHandler.getFileByIndex(fileIndex, &newFile);
				myFileHandler.setFileSize(&newFile, fileSize);
				uint8_t data[2] = {(uint8_t)newFile.size, (uint8_t)(newFile.size >> 8)};
				Serial.write(data, 2);
			}
			else if(cmd == GET_FILE_ATTRIBUTE){
				uint16_t fileIndex = RAM::read16(incomingData);
				FileHandler::FILE newFile = {};
				myFileHandler.getFileByIndex(fileIndex, &newFile);
				Serial.write((uint8_t*)&newFile, 16);
			}
		}
	}//-------------------------------------------> TRANSMIT*/
	else if(status == TRANSMIT)	
	{
		if(cmd == READ_DIRECTORY){
			uint16_t fileCount = myFileHandler.readDirectory(incomingData);
			Serial.write((byte)fileCount);
			Serial.write((byte)(fileCount >> 8));
			
			RAM::startSeqRead(incomingData);
			for(int i=0; i<fileCount * sizeof(FileHandler::FILE); i++){
				Serial.write(RAM::readNext());
			}
			RAM::endSeqRead();
			status = COMMAND;
		}
		
	}
}
