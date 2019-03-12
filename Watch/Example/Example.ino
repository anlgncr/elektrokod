#include "Manager.h"
#include "Watch.h"

Watch newWatch;
Manager manager;

void setup(){
	Manager::scene.addChild(&newWatch);	
}

void loop(){
	manager.run();
}