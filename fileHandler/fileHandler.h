#ifndef fileHandler_h
#define fileHandler_h

#include "Arduino.h"
#include "ROM.h"
#include "RAM.h"

#define SECTOR_SIZE 110
#define DATA_START_ADD 0x2000
#define MAX_FILE_COUNT 512
#define ROM_MEMORY_SIZE 65535

#define LAST_SECTOR 0xFF
#define FREE_SECTOR 0x00
#define NAME_SIZE 10 //Don't change this value

class fileHandler
{
	public:	
		fileHandler(){}
		
		typedef struct{
			char name[NAME_SIZE];
			uint16_t fileAddress;
			uint16_t startSector;
			uint16_t size;
		}FILE;
		
		bool compareName(char* name1, char* name2){
			for(uint8_t i=0; i<NAME_SIZE; i++){
				if(name1[i] == name2[i]){
					if(name1[i] == '\0'){
						return true;
					}
				}
				else{
					return false;
				}
			}
			return true;
		}

		bool getFile(char* fileName, FILE* file)
		{	
			if(fileName[0] == '\0')
				return false;
			
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++)
			{
				FILE* currentFile = (FILE*)(i * sizeof(FILE));	
				char name[NAME_SIZE];
				ROM::readArray(&currentFile->name, name, NAME_SIZE);
				
				if(compareName(name, fileName)){
					file->fileAddress = i * sizeof(FILE);
					file->startSector = ROM::read16(&currentFile->startSector);
					file->size = ROM::read16(&currentFile->size);
					return true;
				}
			}
			return false;
		}
		
		bool createFile(char* fileName, FILE* file)
		{
			if(fileName[0] == '\0')
				return false;
			
			if(getFile(fileName, file)){
				return true;
			}
		
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++){
				uint16_t fileAddress = i * sizeof(FILE);
				FILE* currentFile = (FILE*)(fileAddress);
				
				uint16_t startSector = ROM::read16(&currentFile->startSector);
				if(startSector == 0){
					file->fileAddress = fileAddress;
					file->startSector = findFreeSector(DATA_START_ADD);
					file->size = 0;
					
					FILE tempFile = {};
					for(uint8_t i=0; i<NAME_SIZE; i++){
						tempFile.name[i] = fileName[i];
						
						if(fileName[i] == '\0'){
							break;
						}
					}
					tempFile.fileAddress = fileAddress;
					tempFile.startSector = file->startSector;
					tempFile.size = 0;
					
					ROM::writeArray((uint8_t*)fileAddress, (uint8_t*)&tempFile, sizeof(FILE));
					ROM::write16(file->startSector, 0xFF);
					//Serial.println("New file has been created");
					return true;
				}
			}
			//Serial.println("There is no empty place!");
			return false;
		}
		
		uint8_t getNameLength(char* fileName){
			uint8_t length = 0;
			for(uint8_t i=0; i<NAME_SIZE; i++){
				if(fileName[i] == '\0'){
					return length;
				}
				else{
					length++;
				}
			}
			return length;
		}
		
		bool writeFile(FILE* file, uint8_t* data, uint16_t length)
		{
			uint16_t currentSector = file->startSector; // Dosya yazımına başlanacak ilk sektor
			if(!currentSector)
				return false;
			
			uint16_t sectorCount = (length / SECTOR_SIZE); // Verinin yazılıcağı sektor sayısı
			uint8_t remaningData = length % SECTOR_SIZE; // Son sektore yazılacak veri miktarı
			
			uint16_t sectorIndex = 0;
			if(sectorCount > 0){
				for(sectorIndex = 0; sectorIndex < sectorCount; sectorIndex++){
					ROM::writeArray(currentSector + 2, data + sectorIndex * SECTOR_SIZE, SECTOR_SIZE);//Sektorun ilk 2 byte'ında sıradaki sektorun adresi var
				
					if(!(sectorIndex == (sectorCount - 1) && remaningData == 0))
					{	
						uint16_t nextSector = ROM::read16(currentSector);
						if(nextSector == LAST_SECTOR){
							nextSector = findFreeSector(currentSector + (SECTOR_SIZE + 2));
							if(!nextSector)
								return false;
								
							ROM::write16(currentSector, nextSector);//Şimdiki sektorun ilk 2 byte'ı sıradaki sektoru göstersin
							ROM::write16(nextSector, LAST_SECTOR);//Sıradaki sektoru şimdilik son sektor olarak işaretle
						}
						currentSector = nextSector;
					}
				}
			}
			ROM::writeArray(currentSector + 2, data + sectorIndex * SECTOR_SIZE, remaningData);
			
			file->size = length;
			FILE *currentFile = file->fileAddress;
			ROM::write16(&currentFile->size, length);
			
			//Eğer veri önceki veriden daha az sektor kaplıyor ise diğer sektorleri serbest bırak
			uint16_t nextSector = ROM::read16(currentSector);
			if(nextSector != LAST_SECTOR){
				ROM::write16(currentSector, LAST_SECTOR);
				do{
					currentSector = nextSector;
					nextSector = ROM::read16(currentSector);
					ROM::write16(currentSector, FREE_SECTOR);	
				}
				while(nextSector != LAST_SECTOR);
			}
			//Serial.println("Write operation is complete");
			return true;
		}
		
		void readFile(FILE* file, uint8_t* data, uint16_t length)
		{
			uint16_t currentSector = file->startSector;
			if(!currentSector)
				return;
		
			uint16_t currentSize = file->size;
			if(length > currentSize){
				length = currentSize;
			}
			
			uint16_t sectorCount = (length / SECTOR_SIZE);
			uint8_t remaningData = length % SECTOR_SIZE;
			uint16_t sectorIndex = 0;
			if(sectorCount > 0){
				for(sectorIndex = 0; sectorIndex < sectorCount; sectorIndex++){
					ROM::readArray(currentSector + 2, data + sectorIndex * SECTOR_SIZE, SECTOR_SIZE);
					currentSector = ROM::read16(currentSector);
				}
			}
			ROM::readArray(currentSector + 2, data + sectorIndex * SECTOR_SIZE, remaningData);
		}
		
		bool removeFile(FILE* file){
			uint16_t currentSector = file->startSector;
			if(!currentSector)
				return false;
			
			uint16_t nextSector;
			do{
				nextSector = ROM::read16(currentSector);
				ROM::write16(currentSector, FREE_SECTOR);
				currentSector = nextSector;
			}
			while(nextSector != LAST_SECTOR);
			
			FILE emptyFile = {};		
			ROM::writeArray((uint8_t*)file->fileAddress, (uint8_t*)&emptyFile, sizeof(FILE));
			
			*file = {};
			//Serial.println("File has been deleted");
			return true;
		}
		
		void formatMemory(){
			FILE emptyFile = {};	
			
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++){
				ROM::writeArray((uint8_t*)(i * sizeof(FILE)), (uint8_t*)&emptyFile, sizeof(FILE));
			}
	
			for(uint32_t i=DATA_START_ADD; i<ROM_MEMORY_SIZE; i+=(SECTOR_SIZE + 2)){
				ROM::write16(i, FREE_SECTOR);	
			}
		}
	
	private:
		void readBlock(uint8_t* address, uint8_t* buf){
			ROM::readArray(address, buf, SECTOR_SIZE);
		}
		
		uint16_t findFreeSector(uint16_t startAdd){
			if(startAdd < DATA_START_ADD)
				startAdd = DATA_START_ADD;
			
			for(uint32_t address=startAdd; address<ROM_MEMORY_SIZE; address+=(SECTOR_SIZE + 2)){
				uint16_t nextAdd = ROM::read16(address);
				if(nextAdd == 0){
					return address;
				}
			}
		
			uint16_t remainingSectors = startAdd - DATA_START_ADD;
			for(uint32_t address = DATA_START_ADD; address<(DATA_START_ADD + remainingSectors); address+=(SECTOR_SIZE + 2)){
				uint16_t nextAdd = ROM::read16(address);
				if(nextAdd == 0){
					//Serial.println("Rollovered...!");
					return address;
				}
			}
			return 0;
		}
};
#endif
