#ifndef DisplayObject_h
#define DisplayObject_h
#include "arduino.h"
#include "RAM.h"
#include "Updatable.h"
#include "Button.h"
#include "EventNames.h"
#define NAME_MAX_LENGTH 15

#define COLLIDER_RECTANGLE 0
#define COLLIDER_CIRCLE 1

class DisplayObject : public Updatable{
	public:
		DisplayObject(uint8_t);
		typedef void(*eventFunction)(DisplayObject*);
		
		void dispatchEvent(uint8_t);
		void dispatchEvent(uint8_t, uint8_t);
		void dispatchEventAll(uint8_t, uint8_t);
		void addEventListener(uint8_t, eventFunction);
		void removeEventListener(uint8_t);
		
		virtual void onDelay(){};
		virtual void onAdded(){};
		virtual void onRemoved(){};
		virtual void onButtonDown(uint8_t){};
		virtual void onButtonUp(uint8_t){};
		virtual void onButtonLongDown(uint8_t){};
		//virtual void lateUpdate(){};
		
		uint8_t hitTest(DisplayObject*);
		uint16_t distanceTo(DisplayObject*);
		
		void setId(uint16_t);
		void setName(char*);
		void addChild(DisplayObject*);
		void removeChild(DisplayObject*);
		void remove();
		void leaveParent();
		void setImage(uint8_t*);
		void setX(int16_t); 
		void setY(int16_t);
		void setXY(int16_t, int16_t);
		void setWidth(uint16_t);
		void setHeight(uint16_t);
		void setWidthHeight(uint16_t, uint16_t);
		void setGlobalX(int16_t); 
		void setGlobalY(int16_t);
		void setVisibility(uint8_t);
		void setMemory(uint8_t);
		void setDrawing(uint8_t);
		void setCollider(uint8_t);
		void setFlipped(uint8_t);
		void setDelayTime(uint32_t);
		void setDelayStartTime(uint32_t);
		void setDelaying(uint8_t);
		void setChildIndex(DisplayObject*, uint8_t);
		
		uint16_t getId();
		void getName(char*, uint8_t);
		DisplayObject* getParent();
		DisplayObject* contains(DisplayObject*);
		DisplayObject* getChildAt(uint8_t);
		uint8_t* getImage();
		int16_t getX();
		int16_t getY();
		uint16_t getWidth();
		uint16_t getHeight();
		uint8_t getCanvasWidth();
		uint8_t getCanvasHeight();
		int16_t* getXRef();
		int16_t* getYRef();
		int16_t getGlobalX();
		int16_t getGlobalY();
		uint8_t isVisible();
		uint8_t getChildCount();
		uint8_t getChildSize();
		uint8_t getMemory();
		uint8_t isDrawing();
		uint8_t getCollider();
		uint8_t isFlipped();
		uint32_t getDelayTime();
		uint32_t getDelayStartTime();
		uint8_t isDelaying();
		uint8_t getIndex();
		void writeInfo();
		
		void applyChildChanges();
		
	private:
		struct eventObject{
			eventFunction function;
			uint8_t event;
		};
		
		struct object{
			uint16_t id;
			char* name;
			DisplayObject *parent;
			DisplayObject **children;
			uint8_t *image;
			int16_t x;
			int16_t y;
			uint16_t height;
			uint16_t width;
			int16_t globalX;
			int16_t globalY;
			int8_t flipped;
			uint8_t index;
			uint8_t childSize;
			uint8_t childCount;
			uint8_t visibility;
			uint8_t memory;
			uint8_t drawing;
			eventObject **events;
			uint8_t eventSize;
			uint8_t eventCount;
			uint8_t collider;
			uint32_t delayStartTime;
			uint32_t delayTime;
			uint8_t isDelaying;
			uint8_t childIndexChanged;
			uint8_t childRemoved;
		};
		object *my_object;
		
		void copyObject(object*, object*);
		void loadObject(object*, object*);
		void disposeChild();
		uint16_t getRadius();
		
		void updateEvent(uint8_t, uint8_t);
		
		void setChildIndexChanged(uint8_t);
		uint8_t getChildIndexChanged();
		
		void setChildRemoved(uint8_t);
		uint8_t getChildRemoved();
		
		void setParent(DisplayObject*);
		void setChildAt(uint8_t, DisplayObject*);
		void setChildCount(uint8_t);
		void setIndex(uint8_t);
		
		void setEvent(eventObject*, uint8_t);
		void setEventFunction(eventObject*, eventFunction);	
		void setEventAt(uint8_t, eventObject*);
		void setEventSize(uint8_t);
		void setEventCount(uint8_t);
		void disposeEvent();
		
		uint8_t getEvent(eventObject*);
		eventFunction getEventFunction(eventObject*);
		eventObject* getEventAt(uint8_t);
		uint8_t getEventSize();
		uint8_t getEventCount(); 
};

#endif