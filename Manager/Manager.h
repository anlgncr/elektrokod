#ifndef Manager_h
#define Manager_h
#include <Arduino.h>
#include <RAM.h>
#include <ROM.h>
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

#define CHARGE_STATUS_PIN 2
#define SWITCH_PIN 8
#define SMD_BUTTON_PIN 9
#define BUZZER 3

class Manager{

	public:
		static Updater updater;
		static Scene scene;
		static uint8_t button_code;
		static void buttonListener(Button*);
		
		Manager();
		void run();
		uint8_t update();
	
	private:
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
};

#endif