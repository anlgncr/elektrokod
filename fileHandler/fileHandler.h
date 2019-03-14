#ifndef fileHandler_h
#define fileHandler_h

#include "Arduino.h"
#include "ROM.h"
#include "RAM.h"

#define SECTOR_SIZE 110
#define DATA_START_ADD 0x2000
#define MAX_FILE_COUNT 512
#define MEMORY_SIZE 1024*64

#define LAST_SECTOR 0xFF
#define FREE_SECTOR 0x00

class fileHandler
{
	public:	
		fileHandler(){}
		
		typedef struct{
			char name[10];
			uint16_t fileIndex;
			uint16_t startSector;
			uint16_t size;
		}FILE;
		

		bool openFile(char name, FILE* file) //isimler şimdilik tek karakterden oluşuyor.!
		{	
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++)
			{
				FILE* currentFile = (FILE*)(i * sizeof(FILE));	
				char karakter = ROM::read(currentFile);
				
				if(karakter == name){
					file->fileIndex = i;
					file->startSector = ROM::read16(&currentFile->startSector);
					file->size = ROM::read16(&currentFile->size);
					return true;
				}
			}

			//"name" adında bir dosya yok. Boş bir slot ara
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++){
				FILE* currentFile = (FILE*)(i * sizeof(FILE));
				
				uint16_t startSector = ROM::read16(&currentFile->startSector);
				if(startSector == 0){
					file->fileIndex = i;
					file->startSector = findFreeSector(DATA_START_ADD);
					file->size = 0;
					
					ROM::write(&currentFile->name, name);
					ROM::write16(&currentFile->startSector, file->startSector);
					ROM::write16(file->startSector, 0xFF);
					return true;
				}
			}
			
			Serial.println("Wtf !");
			return false;
		}
		
		bool writeFile(FILE* file, uint8_t* data, uint16_t length){
			uint16_t currentSize = file->size;
			//uint16_t sectorCount = (currentSize / SECTOR_SIZE);
			
			uint16_t currentSector = file->startSector;
			uint16_t dataSectorCount = (length / SECTOR_SIZE);
			uint8_t remaningData = length % SECTOR_SIZE;
			
			uint16_t sectorIndex = 0;
			if(dataSectorCount > 0){
				for(sectorIndex = 0; sectorIndex < dataSectorCount; sectorIndex++){
					ROM::writeArray(currentSector + 2, data + sectorIndex * SECTOR_SIZE, SECTOR_SIZE);
				
					uint16_t nextSector = ROM::read16(currentSector);
					if(nextSector == LAST_SECTOR){
						nextSector = findFreeSector(currentSector + (SECTOR_SIZE + 2));
						if(!nextSector)
							return false;
						
						ROM::write16(currentSector, nextSector);
						ROM::write16(nextSector, LAST_SECTOR);
					}
					currentSector = nextSector;
				}
			}
			
			ROM::writeArray(currentSector + 2, data + sectorIndex * SECTOR_SIZE, remaningData);
			ROM::write16(file->size, length);
			
			uint16_t nextSector = ROM::read16(currentSector);
			if(nextSector != LAST_SECTOR){
				ROM::write16(currentSector, LAST_SECTOR);

				do{
					currentSector = nextSector;
					nextSector = ROM::read16(currentSector);
					ROM::write16(currentSector, FREE_SECTOR);	
				}
				while(nextSector != LAST_SECTOR);
				
				ROM::write16(nextSector, FREE_SECTOR);		
			}
			
			
			Serial.println("Write operation is complete");
			return true;
		}
	
	private:
		void readBlock(uint8_t* address, uint8_t* buf){
			ROM::readArray(address, buf, SECTOR_SIZE);
		}
		
		uint16_t findFreeSector(uint16_t startAdd){
			for(uint16_t address=startAdd; address<=MEMORY_SIZE-1; address+=(SECTOR_SIZE + 2)){
				uint16_t linkAdd = ROM::read16(address);
				if(linkAdd == 0){
					return address;
				}
			}
		
			uint16_t remainingSectors = startAdd - DATA_START_ADD;
			for(uint16_t address = DATA_START_ADD; address<=(DATA_START_ADD + remainingSectors - 1); address+=(SECTOR_SIZE + 2)){
				uint16_t linkAdd = ROM::read16(address);
				if(linkAdd == 0){
					Serial.println("Rollovered...!");
					return address;
				}
			}
			
			Serial.println("shit");
			return 0;
		}
};
#endif
