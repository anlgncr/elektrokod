#ifndef Manager_h
#define Manager_h
#include <Arduino.h>
#include <RAM.h>
#include <ROM.h>
#include <EventArgs.h>
#include <DisplayObject.h>
#include <Updater.h>
#include <Scene.h>
#include <Sprite.h>
#include <MovieClip.h>
#include <TextBox.h>
#include <Shape.h>
#include <Button.h>
#include <Delay.h>
#include <Tween.h>
#include <EventNames.h>
#include <FileHandler.h>
#include <SerialHandler.h>


#define CS_BUTTON 0
#define PARALEL_BUTTON_MASK 0x03

#define CHARGE_STATUS_PIN 2
#define SWITCH_PIN 8
#define SMD_BUTTON_PIN 9
#define BUZZER_PIN 3
#define LIGHT_SENSOR A2

class Manager{
	public:
		static Updater updater;
		static Scene scene;
		static FileHandler fileHandler;
		static uint8_t* charset;
		static uint8_t button_code;
		static void buttonListener(Button*);
		static uint32_t processTime;
		static uint32_t getProcessTime();
		static uint8_t getBrightness();
		
		Manager();
		void run();
		void begin();
		uint8_t isButtonDown(uint8_t);
	
	private:
		SPISettings spiSetting;
		SerialHandler serialHandler;
		Button button_A;
		Button button_B;
		Button button_C;
		Button button_D;
		Button button_E;
		Button button_F;
		Button button_G;
		Button button_H;
		Button button_X;
		Button button_Y;
		
		
		void updateDisplayObjects(DisplayObject*);
		void updateButtons();
};

#endif