/*
 * LayerManager.cpp
 *
 *  Created on: 9/4/2015
 *      Author: julian
 */

#include "../headers/LayerManager.h"

LayerManager* LayerManager::lm_pInstance = NULL;

LayerManager* LayerManager::Instance() {
	if (!lm_pInstance) {
		lm_pInstance = new LayerManager();
		return lm_pInstance;
	} else {
		return lm_pInstance;
	}
}

void LayerManager::clean() {

}

LayerManager::LayerManager() {
	this->offSceneFrontalLayer = 0;
	this->speedFirstLayer = 0;
	this->stage = NULL;
	this->window = NULL;

}

void LayerManager::updateSpeedLayers(Layer* layer) {
	layer->setLayerSpeed(this->speedFirstLayer, this->offSceneFrontalLayer);
}

void LayerManager::updateOffScene(Layer* layer) {
	float windowSize = GameGUI::getInstance()->getWindow()->getWidth();
	layer->setLayerOffScene(windowSize);
}

void LayerManager::setOffSceneFrontalLayer() {
	float windowSize = this->window->getWidth();
	Layer* layer;
	unsigned int size = this->layers.size();

	layer = this->layers[size - 1];
	layer->setLayerOffScene(windowSize);
	this->offSceneFrontalLayer = layer->getLayerOffScene();
}

void LayerManager::setSpeedFrontalLayer() {
	Layer* layer;
	unsigned int size = this->layers.size();
	layer = this->layers[size - 1];
	layer->setLayerSpeed(FRONTAL_LAYER_SPEED, this->offSceneFrontalLayer);
	this->speedFirstLayer = layer->getLayerSpeed();
}

void LayerManager::centerFrontalLayer() {
	Layer* layer;
	unsigned int size = this->layers.size();
	layer = this->layers[size - 1];
	layer->setPositionX( - layer->getLayerOffScene());

}

void LayerManager::centerLayers( Layer* layer) {
	layer->setPositionX( - layer->getLayerOffScene());
}

void LayerManager::init() {

	this->layers = GameGUI::getInstance()->getLayers();
	this->characters = GameGUI::getInstance()->getCharacters();
	this->stage = GameGUI::getInstance()->getStage();
	this->window = GameGUI::getInstance()->getWindow();

	setOffSceneFrontalLayer();
	setSpeedFrontalLayer();
	centerFrontalLayer();

	Layer* layerAux;
	int numberOfLayers = this->layers.size();
	//std::cout << numberOfLayers << endl;
	for(int i = numberOfLayers - 2 ; i >= 0  ; i--) {
		layerAux = this->layers[i];
		updateOffScene(layerAux);
		updateSpeedLayers(layerAux);
		centerLayers(layerAux);
	}
}

//border true = derecho
//border false = izquierdo
bool LayerManager::layerReachedStageLimit(int windowWidth, bool border) {

	Layer* frontalLayer = this->layers[this->layers.size() - 1 ];
	float frontalLayerOffset = frontalLayer->getScrollingOffset();

	//Derecho || Izquierdo
	if (( frontalLayerOffset < ( - frontalLayer->getWidth() / 2 + windowWidth / 2 )) &&  ( border ) )
		return true;
	else if (
			( frontalLayerOffset > (  frontalLayer->getWidth() / 2 - windowWidth / 2 ))  && (!border)){
		return true;
	}
	return false;
}

void LayerManager::refresh() {

	bool refresh = false;
	int orientation = 1;
	bool rightOrientation = false;
	bool leftOrientation = false;
	//int passiveCharacter = -1;
	int standingCharacter = -1;
	Character* passiveCharacter;



	for (unsigned int i = 0; i < this->characters.size() ; i++) {

		if ( i == 0) passiveCharacter = this->characters[1];
		else passiveCharacter = this->characters[0];

		bool isCharMovingRight = this->characters[i]->isMovingRight();
		bool isCharMovingLeft = this->characters[i]->isMovingLeft();
		int posXCharacter = this->characters[i]->getPosXUL();
		int windowWidth = this->window->width;
		int characterWidth = this->characters[i]->getWidth();

		if ( ( (windowWidth - (posXCharacter + characterWidth )) < WINDOW_MARGIN -14) && !layerReachedStageLimit( windowWidth, true) && isCharMovingRight && !passiveCharacter->reachedWindowLeftLimit() ) {
			refresh = true;
			rightOrientation = true;
			orientation = 1;
		}
		else if  (( posXCharacter < WINDOW_MARGIN -14) && !layerReachedStageLimit( windowWidth, false) && isCharMovingLeft && !passiveCharacter->reachedWindowRightLimit())  {
			refresh = true;
			leftOrientation = true;
			orientation = -1;
		}
		else {
			standingCharacter = i;
		}

	}

	if (rightOrientation && leftOrientation) refresh = false; //Si hay un personaje en cada esquina no muevo la cámara
	for(unsigned int index=0; index < this->layers.size(); ++index) {
		this->layers[index]->setNeedRefresh(refresh);
		this->layers[index]->setOrientation(orientation);
	}

	if (refresh == true && standingCharacter != -1 ) {
		this->characters[standingCharacter]->setFixPosXStandingCharacter( orientation );
	}

}
