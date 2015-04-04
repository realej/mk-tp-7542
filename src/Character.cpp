/*
 * Character.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Character.h"
#include "../headers/TextureManager.h"
#include <SDL.h>
#include <string>
#include <sstream>
#include <iostream>

Character::Character() {
	// TODO Auto-generated constructor stub

}

Character::Character(int width, int height, int zindex, std::string orientation) {
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->orientation = orientation;
}

Character::Character(std::string name, int width, int height, int zindex, std::string orientation) {
	this->name = name;
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->orientation = orientation;
}

bool Character::load(SDL_Renderer* render) {

	std::string path_img_sc = "images/scorpion_fighting_stance/sfsGIF.gif";
	return (TextureManager::Instance()->load(path_img_sc, "scorpion", render));
}

void Character::render(SDL_Renderer* render) {
	TextureManager::Instance()->draw("scorpion", 0, 0, this->width, this->height, render, SDL_FLIP_NONE);
}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

