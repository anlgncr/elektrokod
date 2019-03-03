#include "Updater.h"

Updater::Updater(uint16_t my_size){
	size = my_size;
	objects = (Updatable**)RAM::malloc(size * sizeof(Updatable*));
}

void Updater::update(){
	uint8_t disposePool = false;
	for(uint16_t i=0; i<count; i++)
	{
		Updatable *object = getObject(i);
		if(object == NULL){
			disposePool = true;
		}
		else{
			if(!object->update()){
				setObject(i, NULL);
				disposePool = true;
			}
		}
	}
	
	if(disposePool)
		dispose();
}

void Updater::addMulti(uint8_t num_args, ...){
	/*va_list ap;

	va_start(ap, num_args);
	for(uint8_t i = 0; i < num_args; i++) {
	  Updatable* a = va_arg(ap, Updatable*);
	  add(a);
	}
	va_end(ap);*/
}

void Updater::add(Updatable* object){
	if(!object || count >= size)
		return;
	
	for(uint16_t i=0; i<count; i++){
		if(object == getObject(i)){
			return;
		}
	}
	setObject(count++, object);
}

void Updater::remove(Updatable* object){
	for(uint16_t i=0; i<count; i++){
		if(getObject(i) == object){
			setObject(i, NULL);
			dispose();
			return;
		}
	}
}

void Updater::dispose(){
	uint16_t index = 0;
	for(uint16_t i=0; i<count; i++){
		Updatable *object = getObject(i);
		if(object != NULL){
			if(index != i){
				setObject(index, object);
				setObject(i, NULL);
			}
			index++;
		}
	}
	count = index;
}

uint16_t Updater::getCount(){
	return count;
}

Updatable* Updater::getObject(uint16_t index){
	return (Updatable*)RAM::readPtr(&objects[index]);
}

void Updater::setObject(uint16_t index, Updatable* object){
	RAM::writePtr(&objects[index], (void*)object);
}

