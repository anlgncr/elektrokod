#ifndef MovieClip_h
#define MovieClip_h
#include "arduino.h"
#include "DisplayObject.h"
#include "RAM.h"

class MovieClip : public DisplayObject{
	public:
		MovieClip(uint8_t, uint8_t**, uint8_t, uint8_t);
		
		void onUpdate();
		
		void play();
		void playFor(uint8_t);
		void playOnce();
		void gotoAndPlay(uint8_t);
		void stop();
		void gotoAndStop(uint8_t);
		void nextFrame();
		void prevFrame();
		void setFirstAndLastFrame(uint8_t, uint8_t);
		void setFPS(uint8_t);
		
		uint8_t isPlaying();
		uint8_t getFPS();
		uint8_t getFrameCount();
		uint8_t getCurrentFrame();
		uint8_t getRepeatCount();
		uint8_t getFirstFrame();
		uint8_t getLastFrame();
	
	private:
		struct object{
			uint8_t FPS;
			uint8_t frameCount;
			uint8_t repeatCount;
			uint8_t currentFrame;
			uint8_t isPlaying;
			uint8_t **images;
			uint32_t *frameChangeTimes;
			uint32_t passedTime;	
			uint8_t firstFrame;
			uint8_t lastFrame;
		};
		object *my_object;
		
		void getType();
		
		void copyObject(object*, object*);
		void loadObject(object*, object*);
		void playMovie();
		uint32_t getPassedTime();
		uint8_t** getImages();
		
		uint32_t getFrameChangeTime(uint8_t);
		void setRepeatCount(uint8_t);
		void setPassedTime(uint32_t);
		void setPlaying(uint8_t);
		void setCurrentFrame(uint8_t);
};

#endif