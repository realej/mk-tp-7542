/*
 * GameGui.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/GameGUI.h"

GameGUI* GameGUI::gameGui = NULL;
GameGUI* GameGUI::getInstance() {
	if (!gameGui) {
		gameGui = new GameGUI();
		return gameGui;
	} else {
		return gameGui;
	}
}

void GameGUI::clean(){
	delete this->stage;
	delete this->window;
	this->vCollitionable.clear();
}

void GameGUI::setWindow(Window* window) {
	this->window = window;
}

void GameGUI::setStage(Stage* stage) {
	this->stage = stage;
}

void GameGUI::setCharacters(vector<Character*> characters) {
	this->characters = characters;
}

void GameGUI::setLayers(vector<Layer*> layers) {
	this->layers = layers;
}

void GameGUI::setFight(Fight* fight) {
	this->fight = fight;
}

vector<Character*> GameGUI::getCharacters() {
	return this->characters;
}

vector<Layer*> GameGUI::getLayers() {
	return this->layers;
}

Window* GameGUI::getWindow() {
	return this->window;
}

Stage* GameGUI::getStage() {
	return this->stage;
}

Fight* GameGUI::getFight() {
	return this->fight;
}


void GameGUI::setVisualEffects(vector<VisualEffect*> visualEffects) {
	this->visualEffects = visualEffects;
}
