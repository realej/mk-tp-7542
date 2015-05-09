/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Constants.h"
#include "Sprite.h"
#include "InputControl.h"
#include <string>
#include "SDLObjectGUI.h"
#include <SDL.h>
#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;


class Character : public SDLObjectGUI {
private:
	std::string name;
	int zindex;
	bool isRightOriented;
	float yGround;
	std::string movement;
	std::map<std::string,Sprite*> characterSprites;
	SDL_Renderer* renderer; //TODO: review
	bool isJumping;
	bool isWalkingRight;
	bool isWalkingLeft;
	bool isJumpingRight;
	bool isJumpingLeft;
	bool isDucking;
	bool isPunchingHigh;
	bool isPunchingLow;
	bool isPunchingDuck;
	bool isPunchingAnUppercut;
	bool isKickingLow;
	bool isKickingHigh;
	bool isKickingDuckHigh;
	bool isKickingDuckLow;
	bool isKickingSuper;

public:
	Character();
	virtual bool load(SDL_Renderer* );
	void render(SDL_Renderer* render);
	virtual ~Character();
	Character(const LoaderParams* pParams, bool isRightOriented);
	virtual void draw();
	virtual void update();
	virtual void clean();
	int getWidth();
	int getPosX();
	float getYGround();
	bool reachedWindowLeftLimit();
	bool reachedWindowRightLimit();
	float getPosXUL();
	//Movement & position methods
	void jump();
	void jumpRight();
	void jumpLeft();
	void walkRight();
	void walkLeft();
	void refreshFrames();
	std::string getMovement();
	void setMovement(std::string movement);
	bool isTouchingGround(float positionY);
	bool shouldMoveForward();
	void clearMovementsFlags();
	bool isMovingRight();
	bool isMovingLeft();
	std::string getName();
};

#endif /* CHARACTER_H_ */
