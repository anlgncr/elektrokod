#include "Sprite.h"
#include "Manager.h"

Sprite::Sprite() : DisplayObject(0){  }
Sprite::Sprite(uint8_t childSize) : DisplayObject(childSize){  }

bool Sprite::drawFromFile(char* fileName){
	FileHandler::FILE newFile;
	if(Manager::fileHandler.getFile(fileName, &newFile))
	{		
		uint8_t data[5];
		Manager::fileHandler.fileToSram(&newFile, data, 5);

		uint16_t width = Convert::toUInt16(&data[1]);
		uint16_t height = Convert::toUInt16(&data[3]);
	
		if(height != 0 && width != 0){
			uint16_t rowCount = height / 8;
			rowCount += (height % 8 == 0)? 0 : 1;
			
			uint8_t* image = RAM::malloc(newFile.size);
			Manager::fileHandler.fileToSpiRam(&newFile, image, newFile.size);
			setMaskType(data[0]);
			setImage(image + 1);
			setMemory(SPIMEM);
			return true;
		}
	}
	setMemory(PGMEM);
	setImage((uint8_t*)noImage);
	return false;
}

void Sprite::drawFromProgmem(uint8_t* image){
	setImage(image);
	setMemory(PGMEM);
}

void Sprite::draw(uint8_t* image){
	setImage(image);
	setMemory(SMEM);
}

uint8_t Sprite::update(){
	
}

