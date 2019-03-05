#ifndef Player_h
#define Player_h
#include "arduino.h"
#include "DisplayObject.h"
#include "RAM.h"
#include "Bullet.h"
#include "MovieClip.h"
#include "Camera.h"
#include "TextBox.h"
#include "character_images.h"

uint8_t* movieBmp[14] = {	(uint8_t*)idle1, (uint8_t*)idle2, (uint8_t*)idle1, 
							(uint8_t*)run1, (uint8_t*)run2, (uint8_t*)run3, (uint8_t*)run2, 
							(uint8_t*)falling, 
							(uint8_t*)fire, 
							(uint8_t*)run_fire1,(uint8_t*)run_fire2,(uint8_t*)run_fire3,(uint8_t*)run_fire2, 
							(uint8_t*)falling_fire
						};

class Player : public DisplayObject
{
	public:
		Camera *camera;
		TextBox score, fpsText;
		MovieClip mega;
		typedef enum{null, idle1, run, run_fire, fire, falling, falling_fire } animations;
		animations animation = null;
		
		Shape sensorTop, sensorBottom, sensorRight, sensorLeft;
		
		int16_t x, y;
		uint8_t left, right, down, up, left2, right2;
		
		uint8_t leftBlock = false, rightBlock = false;

		float speedY = 0, speedX = 0;
		float gravity = 0.1;
		//float friction = 0.08;
		uint8_t grounded = false;
		uint32_t processTime;
		
		Player(uint8_t childSize): 	DisplayObject(childSize), mega(0, movieBmp, 14, 8), 
									sensorBottom(0, 17, 3), sensorTop(0, 17, 3),
									sensorRight(0, 3, 24), sensorLeft(0, 3, 24),
									score(0, 18, 3, TYPE_8), fpsText(0, 18, 1, TYPE_8)
		{
			setDelayTime(500);
			setDelaying(true);
			mega.setMaskType(IMAGE_AUTO_MASK);
			
			Manager::scene.addChild(&fpsText);
			Manager::scene.addChild(&score);
			processTime = millis();
	
			pinMode(3, OUTPUT);
			//setName("player");
			setWidth(24);
			setHeight(24);
			
			score.setX(110);
			
			addChild(&mega);			
			playAnimation(idle1);
			
			
			
			sensorBottom.drawRectangle(0,0,17,3);
			sensorTop.drawRectangle(0,0,17,3);
			sensorBottom.setXY(7,24);
			sensorTop.setXY(7,-2);
			addChild(&sensorBottom);
			addChild(&sensorTop);
			
			sensorRight.drawRectangle(0,0,3,24);
			sensorLeft.drawRectangle(0,0,3,24);
			sensorRight.setX(23);
			sensorLeft.setX(4);
			addChild(&sensorRight);
			addChild(&sensorLeft);
			
			sensorLeft.setVisibility(false);
			sensorRight.setVisibility(false);
			sensorTop.setVisibility(false);
			sensorBottom.setVisibility(false);
		}
		
		void setCamera(Camera *my_camera){
			camera = my_camera;
		}
				
		void onAdded(){
			Manager::scene.setChildIndex(&fpsText, Manager::scene.getChildCount()- 1);
			Manager::scene.setChildIndex(&score, Manager::scene.getChildCount() - 1);
		}	
		
		void onDelay(){
			char text_buffer[4];
			sprintf(text_buffer, "%03d", fps);
			//fpsText.clear();
			fpsText.write(text_buffer);
			
			if(getY() > 128){
				setXY(100,-50);
				x = 100; y = -50;
				lastX = x;
			}
		}
		
		uint8_t fps;
		void onUpdate(){
			processTime = millis() - processTime;
			fps = 1000 / processTime;
			processTime = millis();
			move();
				
			if(grounded){
				speedY = 0;	
				speedX -= speedX * 0.09;
			}
			else{
				speedY += gravity;
				if(speedY > 3){
					speedY = 3;
				}
				y += round(speedY); 
				setY(y);
				speedX -= speedX * 0.02;
			}
			
			if(leftBlock){
				if(speedX < 0){
					speedX = 0;
				}
			}
			if(rightBlock){
				if(speedX > 0)
					speedX = 0;
			}
			
			x += round(speedX);
			setX(x);
		}
		
		int16_t lastX = 0;
		enum {goingLeft, goingRight} lastXDir;
		void move(){
			if(grounded){
				if(left){
					int16_t x = getX();
					if(lastXDir == goingRight){
						lastX = x;
					}
					mega.setFlipped(true);
					
					if(x - lastX < -40){
						camera->alignRight();
						lastX = x;
					}
					lastXDir = goingLeft;
				}
				else if(right){
					int16_t x = getX();
					if(lastXDir == goingLeft){
						lastX = x;
					}
					mega.setFlipped(false);
					
					if(x - lastX > 40){
						camera->alignLeft();
						lastX = x;
					}
					lastXDir = goingRight;
				}
				
				if(left && left2 && !leftBlock){
					speedX = -1;
					playAnimation(run_fire);
					fireGun();
				}
				else if(right && left2 && !rightBlock){
					speedX = 1;
					playAnimation(run_fire);
					fireGun();
				}
				else if(left){
					if(!leftBlock){
						speedX = -1;
						playAnimation(run);
					}else{
						playAnimation(idle1);
					}
				}
				else if(right){
					if(!rightBlock){
						speedX = 1;
						playAnimation(run);
					}else{
						playAnimation(idle1);
					}
				}
				else if(left2){
					fireGun();
					playAnimation(fire);
				}
				else{
					playAnimation(idle1);
				}
			}
			else{
				if(right){
					speedX = 1;
				}
				else if(left){
					speedX = -1;
				}
				
				if(left2){
					fireGun();
					playAnimation(falling_fire);
				}
				else{
					playAnimation(falling);
				}
			}
		}
		
		uint8_t isBlocked(){
			return (leftBlock || rightBlock);
		}
		
		void jump(){
			if(grounded){
				grounded = false;
				speedY = -2;
				setY(y);
			}
		}
		
		void playAnimation(animations anim){
			if(anim == animation)
				return;
			
			if(anim == idle1){
				mega.setFPS(1);
				mega.setFirstAndLastFrame(0, 1);
				mega.gotoAndPlay(0);
			}
			else if(anim == falling_fire){
				mega.gotoAndStop(13);
			}
			else if(anim == run_fire){
				mega.setFPS(8);
				mega.setFirstAndLastFrame(9, 12);
				mega.gotoAndPlay(9);;
			}
			else if(anim == run){
				mega.setFPS(8);
				mega.setFirstAndLastFrame(3, 6);
				mega.gotoAndPlay(3);
			}
			else if(anim == falling){
				mega.gotoAndStop(7);
			}
			else if(anim == fire){
				mega.gotoAndStop(8);
			}
			animation = anim;
		}
		
		void onCollisonEnter(DisplayObject* object)
		{
			if(object->getId() == 1){ // Bottom sensor
				if(speedY >= 0 && !grounded){ // Eğer karakter aşağıya gidiyorsa
					grounded = true;
					y = object->getY() - 24;
					setY(y);
				}
			}
			else if(object->getId() == 2){ // Top sensor
				if(speedY <= 0)
					speedY = 0;
			}
			else if(object->getId() == 3){ // Right sensor
				rightBlock = true;
			}
			else if(object->getId() == 4){ // Left sensor
				leftBlock = true;
			}
		}
		
		void onCollisonExit(DisplayObject* object)
		{	
			if(object->getId() == 1){ // Bottom sensor
				grounded = false;
			}
			else if(object->getId() == 2){ // Top sensor
				
			}
			else if(object->getId() == 3){ // Right sensor
				rightBlock = false;
			}
			else if(object->getId() == 4){ // Left sensor
				leftBlock = false;
			}
		}
		
		
		DisplayObject* getBottomSensor(){
			return &sensorBottom;
		}
		
		DisplayObject* getTopSensor(){
			return &sensorTop;
		}
		
		DisplayObject* getLeftSensor(){
			return &sensorLeft;
		}
		
		DisplayObject* getRightSensor(){
			return &sensorRight;
		}
		
	private:
		Bullet b1, b2, b3, b4, b5;
		Bullet* bullet_array[5] = {&b1, &b2, &b3, &b4, &b5}; 
		uint8_t bullet_index = 0;
		
		unsigned long nextFireTime = 0;
			void fireGun(){
				if(millis() > nextFireTime)
				{
					Bullet *my_bullet = bullet_array[bullet_index];
					getParent()->addChild(my_bullet);
					if(mega.isFlipped()){
						my_bullet->setX(getX() - 2);
						my_bullet->setDirection(true);
					}
					else{
						my_bullet->setX(getX() + 31);
					}
					
					my_bullet->setY(getY() + 10);
					
					bullet_index ++;
					if(bullet_index > 4)
						bullet_index = 0;
					
					nextFireTime = millis() + 125;
				}
			}
			
			void setButtonStatus(uint8_t button, uint8_t value){
				if(button == CODE_H){
					left = value;
				}
				else if(button == CODE_F){
					right = value;
				}
				
				if(button == CODE_G){
					up = value;
				}
				else if(button == CODE_E){
					down = value;
				}
				
				if(button == CODE_D){
					left2 = value;
				}
				if(button == CODE_B){
					right2 = value;
				}
			}
			
			void onButtonUp(uint8_t button){
				setButtonStatus(button, false);
			}
			
			void onButtonDown(uint8_t button){
				setButtonStatus(button, true);
				
				if(button == CODE_A){
					jump();
				}
			}
			
			void onButtonLongDown(uint8_t button){}
};

#endif