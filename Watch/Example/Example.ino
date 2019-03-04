#include "Setup.h"
#include "Watch.h"

Watch newWatch;

void setup(){
	Setup();
	scene.addChild(&newWatch);	
}

void loop(){
	updater.update();
}