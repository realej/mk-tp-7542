/*
 * Sprite.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/Sprite.h"

Sprite::Sprite() {
    this->spriteId = "";
    this->spriteWidth = 0;
    this->spriteHeight = 0;
    this->currentFrame = 0;
    this->framesAmount = 0;

}

Sprite::Sprite(std::string id, std::string spritePath, SDL_Renderer* m_pRenderer, int w, int h, int framesAmount) {
	if (!TextureManager::Instance()->load(spritePath, id, m_pRenderer)) {
		cout << "error con el load";
	}
	this->spriteId = id;
	this->spriteWidth = w;
	this->spriteHeight = h;
	this->framesAmount = framesAmount;
	this->currentFrame = 0;
}

Sprite::Sprite(std::string id, std::string spritePath, SDL_Renderer* m_pRenderer, int w, int h, int framesAmount, bool isAltPlayer, AlternativeColor* altColor) {
	if (!TextureManager::Instance()->load(spritePath, id, m_pRenderer, isAltPlayer, altColor)) {
		cout << "error con el load";
	}
	this->spriteId = id;
	this->spriteWidth = w;
	this->spriteHeight = h;
	this->framesAmount = framesAmount;
	this->currentFrame = 0;
}

std::string Sprite::getSpriteId() {
	return this->spriteId;
}

int Sprite::getSpriteWidth() {
	return this->spriteWidth;
}

int Sprite::getSpriteHeight() {
	return this->spriteHeight;
}


int Sprite::getNextForwardingFrame() {
	if (this->currentFrame >= this->framesAmount) {
		this->currentFrame=0;
	}
	return this->currentFrame++;
}

int Sprite::getNextFrameWithLimit(){
	if (currentFrame < framesAmount-1) {
		return currentFrame++;
	} else {
		return currentFrame;
	}
}

int Sprite::getNextFrameWithLimitAndShowFrame(int frameToShow){
	if (currentFrame < framesAmount-1) {
		return currentFrame++;
	} else {
		return frameToShow;
	}
}

int Sprite::getNextFrameWithLimitAndLoop(int loopMovement, int timesLoop){

	if (currentFrame < framesAmount-1) {
		return currentFrame++;
	} else {
		if (!isLooped){
			currentFrame = currentFrame - loopMovement;
			timeLooped = timeLooped +1;
			if (timeLooped == timesLoop){
				isLooped = true;
			}
		}
		return currentFrame;
	}
}

int Sprite::getNextFrameWithLimitAndLoop(int loopMovement, int frameToLoop, int timesLoop){

	if (isLooped) {
		if (currentFrame < framesAmount - 1) {
			return currentFrame++;
		}
		else return currentFrame;
	} else {
		if (currentFrame < frameToLoop - 1) {
			return currentFrame++;
		} else {
			if (!isLooped) {
				currentFrame = currentFrame - loopMovement;
				timeLooped = timeLooped + 1;
				if (timeLooped == timesLoop) {
					isLooped = true;
				}
			}
			return currentFrame;
		}
	}
}

int Sprite::getNextBackwardingFrame() {
	return (framesAmount - getNextForwardingFrame()-1);
}

void Sprite::refresh(){
	this->currentFrame = 0;
}

int Sprite::getCurrentFrame(){
	return this->currentFrame;
}

int Sprite::getFramesAmount(){
	return this->framesAmount;
}

Sprite::~Sprite() {
}


