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
			uint16_t fileAddress;
			uint16_t startSector;
			uint16_t size;
		}FILE;
		

		bool getFile(char name, FILE* file) //isimler şimdilik tek karakterden oluşuyor.!
		{	
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++)
			{
				FILE* currentFile = i * sizeof(FILE);	
				char karakter = ROM::read(currentFile);
				
				if(karakter == name){
					file->name[0] = name;
					file->fileAddress = i * sizeof(FILE);
					file->startSector = ROM::read16(&currentFile->startSector);
					file->size = ROM::read16(&currentFile->size);
					return true;
				}
			}

			//"name" adında bir dosya yok. Boş bir sektor ara ve dosyayı oluştur
			for(uint16_t i=0; i<MAX_FILE_COUNT; i++){
				FILE* currentFile = i * sizeof(FILE);
				
				uint16_t startSector = ROM::read16(&currentFile->startSector);
				if(startSector == 0){
					file->name[0] = name;
					file->fileAddress = i * sizeof(FILE);
					file->startSector = findFreeSector(DATA_START_ADD);
					file->size = 0;
					
					ROM::write(&currentFile->name, name);
					ROM::write16(&currentFile->startSector, file->startSector);
					ROM::write16(file->startSector, 0xFF);
					ROM::write16(file->size, 0x00);
					
					//Serial.println("New file has been created");
					return true;
				}
			}
			//Serial.println("There is no empty place!");
			return false;
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
				
					if(!(sectorIndex == (sectorCount - 1) && remaningData == 0)){
						uint16_t nextSector = findFreeSector(currentSector + (SECTOR_SIZE + 2));
						if(!nextSector)
							return false;
							
						ROM::write16(currentSector, nextSector);//Şimdiki sektorun ilk 2 byte'ı sıradaki sektoru göstersin
						ROM::write16(nextSector, LAST_SECTOR);//Sıradaki sektoru şimdilik son sektor olarak işaretle
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
			
			FILE* currentFile = file->fileAddress;
			ROM::write(&currentFile->name[0], 0x00);
			ROM::write16(&currentFile->startSector, 0x00);
			ROM::write16(&currentFile->size, 0);
			
			file->startSector = 0;
			file->size = 0;
			//Serial.println("File has been deleted");
			return true;
		}
	
	private:
		void readBlock(uint8_t* address, uint8_t* buf){
			ROM::readArray(address, buf, SECTOR_SIZE);
		}
		
		uint16_t findFreeSector(uint16_t startAdd){
			if(startAdd < DATA_START_ADD)
				startAdd = DATA_START_ADD;
			
			for(uint16_t address=startAdd; address<=MEMORY_SIZE-1; address+=(SECTOR_SIZE + 2)){
				uint16_t nextAdd = ROM::read16(address);
				if(nextAdd == 0){
					return address;
				}
			}
		
			uint16_t remainingSectors = startAdd - DATA_START_ADD;
			for(uint16_t address = DATA_START_ADD; address<=(DATA_START_ADD + remainingSectors - 1); address+=(SECTOR_SIZE + 2)){
				uint16_t nextAdd = ROM::read16(address);
				if(nextAdd == 0){
					//Serial.println("Rollovered...!");
					return address;
				}
			}
			//Serial.println("shit");
			return 0;
		}
};
#endif
