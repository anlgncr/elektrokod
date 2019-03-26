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
		
		
		uint16_t getFileCount(){
			uint16_t fileCount = 0;
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++)
			{
				FILE* currentFile = (FILE*)(i * sizeof(FILE));	
				uint16_t startSector = ROM::read16(&currentFile->startSector);
				
				if(startSector != 0){
					fileCount++;
				}
			}
			return fileCount;
		}
		
		uint16_t readDirectory(uint8_t* data){
			int fileCount = 0;
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++)
			{
				FILE* currentFile = (FILE*)(i * sizeof(FILE));	
				uint16_t startSector = ROM::read16(&currentFile->startSector);
				
				if(startSector != 0){
					ROM::copyToSpiRam(currentFile, data + fileCount * sizeof(FILE), sizeof(FILE));
					fileCount++;
				}
			}
			return fileCount;
		}
		
		void fileToSpiRam(FILE* file, uint8_t* data, uint16_t length){
			readFile(file, data, length, 2);
		}
		
		void fileToSram(FILE* file, uint8_t* data, uint16_t length){
			readFile(file, data, length, 1);
		}
		
		uint16_t readSector(uint8_t* data, uint16_t sectorAddress, uint16_t length){
			if(!sectorAddress || length < 1){
				return 0;
			}
			ROM::copyToSpiRam(sectorAddress + 2, data, length);
			return ROM::read16(sectorAddress);//next sector
		}
		
		uint16_t writeSector(uint8_t* data, uint16_t currentSector, uint16_t length, uint8_t sector){
			if(currentSector < DATA_START_ADD || length < 1){
				return 255;
			}
			ROM::copyFromSpiRam(currentSector + 2, data, length);
			
			if(sector == LAST_SECTOR){
				freeSectors(currentSector);
				return LAST_SECTOR;			
			}
			else{
				uint16_t nextSector = ROM::read16(currentSector);
				if(nextSector == LAST_SECTOR){
					nextSector = findFreeSector(DATA_START_ADD);
					ROM::write16(currentSector, nextSector);
					ROM::write16(nextSector, LAST_SECTOR);
				}
				return nextSector;
			}
		}

		bool getFile(char* fileName, FILE* file){	
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
		
		bool getFileByIndex(uint16_t fileIndex, FILE* file){
			if(fileIndex >= MAX_FILE_COUNT){
				return false;
			}
			
			uint8_t* fileAddress = fileIndex * sizeof(FILE);
			
			ROM::readArray(fileAddress, file, sizeof(FILE));
			return true;
		}
		
		void setFileSize(FILE* file, uint16_t size){
			FILE* currentFile = (FILE*)(file->fileAddress);
			ROM::write16(&currentFile->size, size);
		}
		
		bool createFile(char* fileName, FILE* file){
			if(fileName[0] == '\0' || getFile(fileName, file))
				return false;
			
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
					ROM::write16(file->startSector, LAST_SECTOR);
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
		
		bool writeFile(FILE* file, uint8_t* data, uint16_t length){
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
			freeSectors(currentSector);
			//Serial.println("Write operation is complete");
			return true;
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
		
		bool removeFileByIndex(uint16_t fileIndex){
			if(fileIndex >= MAX_FILE_COUNT){
				return false;
			}
			
			FILE file;
			FILE* currentFile = (FILE*)(fileIndex * sizeof(FILE));
			
			ROM::readArray(currentFile, &file, sizeof(FILE));
			return removeFile(&file);
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
		
		bool readFile(FILE* file, uint8_t* data, uint16_t length, uint8_t memory){
			uint16_t currentSector = file->startSector;
			if(!currentSector)
				return false;
		
			uint16_t currentSize = file->size;
			if(length > currentSize){
				length = currentSize;
			}
			
			uint16_t sectorCount = (length / SECTOR_SIZE);
			uint8_t remaningData = length % SECTOR_SIZE;
			uint16_t sectorIndex = 0;
			if(sectorCount > 0){
				for(sectorIndex = 0; sectorIndex < sectorCount; sectorIndex++){
					if(memory == 1){
						ROM::readArray(currentSector + 2, data + sectorIndex * SECTOR_SIZE, SECTOR_SIZE);
					}
					else if(memory == 2){
						ROM::copyToSpiRam(currentSector + 2, data + sectorIndex * SECTOR_SIZE, SECTOR_SIZE);
					}
					currentSector = ROM::read16(currentSector);
				}
			}
			if(memory == 1){
				ROM::readArray(currentSector + 2, data + sectorIndex * SECTOR_SIZE, remaningData);
			}
			else if(memory == 2){
				ROM::copyToSpiRam(currentSector + 2, data + sectorIndex * SECTOR_SIZE, remaningData);
			}
			return true;
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
		
		void freeSectors(uint16_t currentSector){
			
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
		}
};
#endif
