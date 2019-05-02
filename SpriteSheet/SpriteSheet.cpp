#include "SpriteSheet.h"

SpriteSheet::SpriteSheet() : Sprite(){ }


Sprite* SpriteSheet::getSprite(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
	Sprite* new_sprite = new Sprite;
	
	if(sheet.getImage())
	{
		uint16_t sheetWidth = getCanvasWidth();
		uint16_t sheetHeight = getCanvasHeight();
		
		if(!((x + width) > sheetWidth))
		{
			if(!((y + height) > sheetHeight))
			{
				uint16_t sheetRowCount = height / 8;
				rowCount += (height % 8 == 0)? 0 : 1;
				
				uint16_t rowCount = height / 8;
				rowCount += (height % 8 == 0)? 0 : 1;
				
				uint16_t currentRow =  y / 8;
				uint8_t image_shift = y % 8;
				
				uint8_t* new_image = RAM::malloc(width * rowCount);
				uint8_t* sheetImage = &sheet.getImage()[4];
				
				/*for(uint16_t row = currentRow; row < currentRow + rowCount; row++)
				{
					uint8_t imageCol = (row * sheetWidth) + x + sheetImage;
					for(uint16_t col = 0; col < width; col++)
					{
						uint8_t data = RAM::read(imageCol + col);
						data >>= image_shift;
					}
					
					uint8_t lowerRow = row + 1;
					if(lowerRow < sheetRowCount && image_shift){	
						for(uint16_t col = 0; col < width; col++)
						{
							uint8_t data = RAM::read(imageCol + col);
							data >>= image_shift;
						}
					}
				}*/
			}
		}
	}
	new_sprite->setMemory(PGMEM);
	new_sprite->setImage(noImage);
	return new_sprite;	
}