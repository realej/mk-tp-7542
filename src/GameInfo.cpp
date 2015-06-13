/*
 * GameInfo.cpp
 *
 *  Created on: 23/4/2015
 *      Author: julian
 */

#include "../headers/GameInfo.h"

GameInfo::GameInfo(const LoaderParams* pParams, vector<Character*> characters) :
		SDLObjectGUI(pParams) {
	this->characters = characters;
	bgColor = {204, 0, 0, 150};
	frontColor = {0, 0, 204, 255};
	barWidth = ((pParams->getWidth() * 0.9) - (WINDOW_MARGIN * 2)) / 2;
	this->percent = 0.0f;
	this->fightAnimationTimer = 40;
	TTF_Init();
	this->initAnimation = true;
	this->showFightAnimation = true;
	this->msTime = 100000.0f;
	this->idTimer = "";
	this->roundCompleted = false;
	this->currentRound = 1;
	this->roundTriggered = false;
	this->roundOneCompleted = false;
	this->roundTwoCompleted = false;
	this->roundThreeCompleted = false;
	this->characterOneWins = 0;
	this->characterTwoWins = 0;
}

bool GameInfo::load() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();

	// carga de textos personajes

	SDL_Color textColor = {255, 255, 255};
	TTF_Font* font = TTF_OpenFont( "fonts/MK4.ttf", 28 );

	return (TextureManager::Instance()->loadFromRenderedText( this->textureID, characters[0]->getName(), textColor, font, render ));
}

void GameInfo::loadTextTimer() {
	//libero timer anterior
	TextureManager::Instance()->unload(this->textureID + this->idTimer);

	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 200 );

	//Timer
	SDL_Color timerColor = {227, 188, 119};
	std::stringstream timeText;
    timeText.str( "" );
    timeText << (int)((msTime - timer.getTicks()) / 1000.f);
    this->idTimer = timeText.str();
	TextureManager::Instance()->loadFromRenderedText( this->textureID, idTimer, timerColor, font, render);
	TTF_CloseFont(font);
}

bool GameInfo::load(SDL_Renderer* r) {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 100 );
	string name = "";
	string round1 = "ROUND 1";
	string round2 = "ROUND 2";
	string round3 = "ROUND 3";

	//Timer
	loadTextTimer();

	SDL_Color playerColor = {255, 255, 255};
	SDL_Color roundColor = {255, 255, 255};

	//jugador 1
	name = this->characters[0]->getName();
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, name, playerColor, font, render);

	//jugador 2
	name = this->characters[1]->getName();
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, name, playerColor, font, render);

	//Round 1
	std::transform(round1.begin(), round1.end(), round1.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, round1, roundColor, font, render);

	//Round 2
	std::transform(round2.begin(), round2.end(), round2.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, round2, roundColor, font, render);

	//Round 3
	std::transform(round3.begin(), round3.end(), round3.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, round3, roundColor, font, render);

	//fightRed sprite
	TextureManager::Instance()->load(FIGHT_IMAGE_SPRITE, "fightSprite", r);
	//fightYellow sprite
	TextureManager::Instance()->load(FIGHT2_IMAGE_SPRITE, "fight2Sprite", r);

	TTF_CloseFont(font);
	return true;
}


void GameInfo::HealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* pRender, int player) {
	   Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	   SDL_Color old;
	   SDL_GetRenderDrawColor(pRender, &old.r, &old.g, &old.g, &old.a);
	   SDL_Rect bgrect = { x, y, w, h };
	   SDL_SetRenderDrawColor(pRender, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	   SDL_SetRenderDrawBlendMode(pRender, SDL_BLENDMODE_BLEND);
	   SDL_RenderFillRect(pRender, &bgrect);
	   SDL_SetRenderDrawColor(pRender, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	   int pw = (int)((float)w * Percent);
	   int px;
	   if (player == 0) {
		   px = x;
	   } else {
		   px = x + (w - pw);
	   }

	   SDL_Rect fgrect = { px, y, pw, h };
	   SDL_RenderFillRect(pRender, &fgrect);
       SDL_SetRenderDrawColor( pRender, 227, 188, 119, 0xFF );
       SDL_RenderDrawRect( pRender, &bgrect );
	   SDL_SetRenderDrawColor(pRender, 0x00, 0x00, 0x00, 0xFF );
}

void GameInfo::animation() {
	if (this->percent < 1.0f && this->initAnimation) {
		this->percent += 0.05f;
	} else {
		this->initAnimation = false;
	}
	if (this->fightAnimationTimer > 0 && this->showFightAnimation){
		this->fightAnimationTimer -= 1;
	} else {
		//this->fightAnimationTimer = 40;
		this->showFightAnimation = false;
		if (!this->roundTriggered) {
			this->timerStart();
			MKGame::Instance()->setAllowPlayerMovements(true);
			this->roundTriggered=true;
		}
	}
}

void GameInfo::time() {
	if (this->timer.getTicks() > 99000.f ) {
		this->timer.stop();
		this->timer.start();
	}
	loadTextTimer();
}


void GameInfo::update() {
	animation();
	time();
	if (this->characters[0]->getEnergy() <= 0.0f || this->characters[1]->getEnergy() <= 0.0f) {
		if (this->characters[0]->getEnergy() <= 0.0f) {
			this->characterOneWins += 1;
			FILE_LOG(logDEBUG) <<"############ RESULT: " << this->characters[1]->getName() << "Wins #############";
		} else {
			this->characterTwoWins += 1;
			FILE_LOG(logDEBUG) << "############ RESULT: " << this->characters[0]->getName() << " Wins #############";
		}
		if (this->characterOneWins == 2 || this->characterTwoWins == 2) {
			//finish him logic
			MKGame::Instance()->setOnReset();
		}
		//MKGame::Instance()->setOnReset();
		if (!this->roundOneCompleted) {
			this->roundOneCompleted = true;
		} else if (!this->roundTwoCompleted) {
			this->roundTwoCompleted = true;
		} else if (!this->roundThreeCompleted) {
			MKGame::Instance()->setOnReset();
		}
		this->percent = 0.0f;
		this->fightAnimationTimer = 40;
		this->initAnimation = true;
		this->showFightAnimation = true;
		this->roundTriggered=false;
		MKGame::Instance()->setAllowPlayerMovements(false);
		this->characters[0]->setEnergy(1.0f);
		this->characters[1]->setEnergy(1.0f);
		this->characters[0]->setPositionX(GameGUI::getInstance()->getWindow()->widthPx / 4 - this->characters[0]->getWidth() * this->characters[0]->getRatioX()/2);
		this->characters[1]->setPositionX((GameGUI::getInstance()->getWindow()->widthPx / 4)*3 -  this->characters[1]->getWidth() * this->characters[1]->getRatioX()/2);
		SDL_Delay(1000);
	}
}

void GameInfo::clean() {
	delete this->pParams;
	this->timer.stop();
	TTF_Quit();
}

void GameInfo::draw() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();

	//timer
	string id = this->textureID + this->idTimer;
	int width = WINDOW_MARGIN * 3;
	int x = (pParams->getWidth()/2 - width/2);
	int y = this->height * 0.1;
	int height = 15;
	TextureManager::Instance()->draw( id, x, y, width, height, render);

	string name = "";
	string round1 = "ROUND 1";
	string round2 = "ROUND 2";
	string round3 = "ROUND 3";
	float energy = 0.0f;

	//jugador 1
	name = this->characters[0]->getName();
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->draw( this->textureID + name, WINDOW_MARGIN, 0, barWidth/2, 10, render );
	energy = this->characters[0]->getEnergy();
	if (this->initAnimation) HealthBar(positionX * ratioX, 35, barWidth * ratioX, 20, percent, frontColor, bgColor, render, 0 );
	else HealthBar(positionX * ratioX, 35, barWidth * ratioX, 20, energy, frontColor, bgColor, render, 0 );

	//jugador 2
	name = this->characters[1]->getName();
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->draw(this->textureID + name, pParams->getWidth() - barWidth/2 - WINDOW_MARGIN,0,barWidth/2, 10, render);
	energy = this->characters[1]->getEnergy();
	if (this->initAnimation) {
		HealthBar((this->width - WINDOW_MARGIN - barWidth) * ratioX, 35, barWidth * ratioX, 20, percent, frontColor, bgColor, render, 1);
	} else HealthBar((this->width - WINDOW_MARGIN - barWidth) * ratioX, 35, barWidth * ratioX, 20, energy, frontColor, bgColor, render, 1);

	//round 1
	float roundWidth = barWidth/2;
	float roundHeight = 15;
	if (this->initAnimation) {
		if (!this->roundOneCompleted) {
			std::transform(round1.begin(), round1.end(), round1.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID + round1, pParams->getWidth()/2 - roundWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - roundHeight, roundWidth, roundHeight, render);
		} else if (!this->roundTwoCompleted) {
			std::transform(round2.begin(), round2.end(), round2.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID + round2, pParams->getWidth()/2 - roundWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - roundHeight, roundWidth, roundHeight, render);

		} else if (!this->roundThreeCompleted) {
			std::transform(round3.begin(), round3.end(), round3.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID + round3, pParams->getWidth()/2 - roundWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - roundHeight, roundWidth, roundHeight, render);
		}
	}

	if (!this->initAnimation && this->showFightAnimation) {
		if ( (this->fightAnimationTimer % 2) == 0){
			TextureManager::Instance()->draw("fightSprite", pParams->getWidth()/2 - roundWidth/2,
							GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - roundHeight, roundWidth, roundHeight, render);
		} else {
			TextureManager::Instance()->draw("fight2Sprite", pParams->getWidth()/2 - roundWidth/2,
										GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - roundHeight, roundWidth, roundHeight, render);
		}

	}
}

void GameInfo::timerStart() {
	this->timer.start();
}

void GameInfo::timerStop() {
	this->timer.stop();
}

void GameInfo::timerPause() {
	this->timer.pause();
}

bool GameInfo::isRoundTriggered() {
	return this->isRoundTriggered();
}
