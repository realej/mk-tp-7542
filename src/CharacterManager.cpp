/*
 * CharacterManager.cpp
 *
 *  Created on: 12/5/2015
 *      Author: mauro
 */

#include "../headers/CharacterManager.h"

CharacterManager* CharacterManager::cm_pInstance = 0;

CharacterManager::CharacterManager() {
	// TODO Auto-generated constructor stub

}

CharacterManager* CharacterManager::Instance() {
	if (!cm_pInstance) {
		cm_pInstance = new CharacterManager();
		return cm_pInstance;
	} else {
		return cm_pInstance;
	}
}


void CharacterManager::solveMovesBeignHint(){

	Character* character2 = GameGUI::getInstance()->getCharacters().at(1);
	character2->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);

}

void pushCharacter(Character* character1, Character* character2, bool pushChar1, bool pushChar2, bool rightOrientation) {

	//si los 2 se empujan
	if (pushChar1 && pushChar2) {
		if (rightOrientation) { //la ultima orientacion seteada es la del character 1
			character1->walkLeft();
			character2->walkRight();
		} else {
			character1->walkRight();
			character2->walkLeft();
		}
	}

	//Char2 empujando al 1
	else if (pushChar1) {
		if (rightOrientation) {
			character1->setPositionX(character1->getPositionX() + FRONTAL_LAYER_SPEED/2 * character1->getRatioX());
			character2->setPositionX(character1->posXBox - character2->widthBox * 2);
		} else {
			character1->setPositionX(character1->getPositionX() - FRONTAL_LAYER_SPEED/2 * character1->getRatioX());
			character2->setPositionX((character1->posXBox + character1->widthBox) - character2->widthBox );
		}

	//Char1 empujando al 2
	} else if (pushChar2) {
		if (rightOrientation) {
			character2->setPositionX(character2->getPositionX() + FRONTAL_LAYER_SPEED/2 * character2->getRatioX());
			character1->setPositionX(character2->posXBox - character1->widthBox * 2);
		}else {
			character2->setPositionX(character2->getPositionX() - FRONTAL_LAYER_SPEED/2 * character2->getRatioX());
			character1->setPositionX((character2->posXBox + character2->widthBox) - character1->widthBox);
		}
	}
}

bool isHitting(Character* character){
	return ( character->getMovement() == PUNCHING_HIGH_MOVEMENT ||
			character->getMovement() == HIGH_KICK_MOVEMENT ||
			character->getMovement() == LOW_KICK_MOVEMENT ||
			character->getMovement() == DUCK_LOW_KICK_MOVEMENT ||
			character->getMovement() == DUCK_HIGH_KICK_MOVEMENT ||
			character->getMovement() == UPPERCUT_MOVEMENT ||
			character->getMovement() == PUNCHING_DUCK_MOVEMENT ||
			character->getMovement() == AIR_HIGH_kICK_MOVEMENT ||
			character->getMovement() == AIR_LOW_kICK_MOVEMENT ||
			character->getMovement() == UNDER_KICK_MOVEMENT ||
			character->getMovement() == AIR_PUNCH_MOVEMENT ||
			character->getMovement() == PUNCHING_LOW_MOVEMENT ||
			character->getMovement() == SUPER_KICK_MOVEMENT ||
			character->getMovement() == FIRE_MOVEMENT ||
			character->getMovement() == SPECIAL_MOVEMENT ||
			character->getMovement() == SWEEP_MOVEMENT );
}


void CharacterManager::solveMovesBeignHint(DamageObject* actualObj, DamageObject* nextObj){

	Character* character1;

	Character* character2;

	if (actualObj->isCharacter()){
		character1 = dynamic_cast<Character*>(actualObj);
	}

	if (nextObj->isCharacter()){
		character2 = dynamic_cast<Character*>(nextObj);
	}

	//character1->beingPushed = false;
	//character2->beingPushed = false;

	if ((actualObj->isCharacter()) && (nextObj->isCharacter())){
		//GOLPES CHARACTER 1

		if (character2->getMovement() == LAZY_MOVEMENT && isHitting(character1) && MKGame::Instance()->isFinishimMoment ){
			character2->setMovement(FALLING_MOVEMENT);
			character2->setCurrentSprite();
			character2->isFalling = true;
			character1->completeMovementAndChangeVictory = true;
//			character1->completeMovemenAndChangeToVictory();
//			character1->setMovement(VICTORY_MOVEMENT);
//			character1->setCurrentSprite();
//			character1->isVictory = true;
		}

		else if ((character1->getMovement() == PUNCHING_HIGH_MOVEMENT ) && character2->getMovement() != BLOCK_MOVEMENT && character2->getMovement() != DUCK_BLOCK_MOVEMENT){
			character2->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
			character1->talk("punchHit",1);
			//GameGUI::getInstance()->visualEffects[0]->animateToasty();
		}

		else if ( (character1->getMovement() == HIGH_KICK_MOVEMENT || character1->getMovement() == AIR_PUNCH_MOVEMENT) &&
				character2->getMovement() != BLOCK_MOVEMENT && character2->getMovement() != DUCK_BLOCK_MOVEMENT){
			character2->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
			character1->talk("punchHit");

		}

		else if ((character1->getMovement() == PUNCHING_LOW_MOVEMENT || character1->getMovement() == LOW_KICK_MOVEMENT)
				 && character2->getMovement() != BLOCK_MOVEMENT && character2->getMovement() != DUCK_BLOCK_MOVEMENT){
			character2->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
			character1->talk("punchHit");
		}
		else if ((character1->getMovement() == DUCK_HIGH_KICK_MOVEMENT || character1->getMovement() == DUCK_LOW_KICK_MOVEMENT
				|| character1->getMovement() == PUNCHING_DUCK_MOVEMENT)
					&& character2->getMovement() != DUCK_BLOCK_MOVEMENT){
			character2->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
			character1->talk("punchHit");
		}
		else if (character1->getMovement() == UNDER_KICK_MOVEMENT  && character2->getMovement() != DUCK_BLOCK_MOVEMENT){
			character2->setMovement(BEING_HINT_FALLING_UNDER_KICK_MOVEMENT);
			character1->talk("uppercut");
		}

		else if ((character1->getMovement() == SUPER_KICK_MOVEMENT || character1->getMovement() == AIR_HIGH_kICK_MOVEMENT
				|| character1->getMovement() == AIR_LOW_kICK_MOVEMENT) && character2->getMovement() != BLOCK_MOVEMENT){
			character2->setMovement(HINT_FLYING_MOVEMENT);

			character1->talk("uppercut");
		}

		else if (character1->getMovement() == UPPERCUT_MOVEMENT && character2->getMovement() != BLOCK_MOVEMENT && character2->getMovement() != DUCK_BLOCK_MOVEMENT){

			character2->setMovement(HINT_FLYING_UPPER_MOVEMENT);
			character1->talk("uppercut");
			int random = rand() % 10;
			if (random == 0)  {
				character1->talk("toasty");
				GameGUI::getInstance()->visualEffects[0]->animateToasty();
			}

		}

		else if (character1->getMovement() == SWEEP_MOVEMENT && character2->getMovement() != DUCK_BLOCK_MOVEMENT && character2->getMovement() != SWEEP_MOVEMENT){
			character2->setMovement(HINT_FLYING_MOVEMENT);
			character1->clearMovementsFlags();
			SoundManager::Instance()->playSound("gancho", 0);
		}

		//GOLPES CHARACTER 2

		if (character1->getMovement() == LAZY_MOVEMENT && isHitting(character2) && MKGame::Instance()->isFinishimMoment ){
			character1->setMovement(FALLING_MOVEMENT);
			character1->setCurrentSprite();
			character1->isFalling = true;
			character1->completeMovementAndChangeVictory = true;
//			character2->setMovement(VICTORY_MOVEMENT);
//			character2->setCurrentSprite();
//			character2->isVictory = true;
		}


		else if ((character2->getMovement() == PUNCHING_HIGH_MOVEMENT ) && character1->getMovement() != BLOCK_MOVEMENT  && character1->getMovement() != DUCK_BLOCK_MOVEMENT){
			character1->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
			character2->talk("punchHit",1);
			//GameGUI::getInstance()->visualEffects[1]->animateToasty();
		}
		else if (( character2->getMovement() == HIGH_KICK_MOVEMENT
				|| character2->getMovement() == AIR_PUNCH_MOVEMENT) && character1->getMovement() != BLOCK_MOVEMENT  && character1->getMovement() != DUCK_BLOCK_MOVEMENT){
			character1->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
			character2->talk("punchHit");
		}
		else if ((character2->getMovement() == PUNCHING_LOW_MOVEMENT || character2->getMovement() == LOW_KICK_MOVEMENT
				) && character1->getMovement() != BLOCK_MOVEMENT && character1->getMovement() != DUCK_BLOCK_MOVEMENT){
			character1->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
			character2->talk("punchHit");
		}
		else if ((character2->getMovement() == DUCK_HIGH_KICK_MOVEMENT || character2->getMovement() == DUCK_LOW_KICK_MOVEMENT
				|| character2->getMovement() == PUNCHING_DUCK_MOVEMENT) && character1->getMovement() != DUCK_BLOCK_MOVEMENT) {
			character1->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
			character2->talk("punchHit");
		}
		else if (character2->getMovement() == UNDER_KICK_MOVEMENT && character1->getMovement() != DUCK_BLOCK_MOVEMENT){
			character1->setMovement(BEING_HINT_FALLING_UNDER_KICK_MOVEMENT);
			character2->talk("punchHit");
		}

		else if ((character2->getMovement() == SUPER_KICK_MOVEMENT || character2->getMovement() == AIR_HIGH_kICK_MOVEMENT
				|| character2->getMovement() == AIR_LOW_kICK_MOVEMENT) && character1->getMovement() != BLOCK_MOVEMENT){
			character1->setMovement(HINT_FLYING_MOVEMENT);
			character2->talk("uppercut");
		}

		else if (character2->getMovement() == UPPERCUT_MOVEMENT && character1->getMovement() != BLOCK_MOVEMENT && character1->getMovement() != DUCK_BLOCK_MOVEMENT){
			character1->setMovement(HINT_FLYING_UPPER_MOVEMENT);
			character2->talk("uppercut");

			int random = rand() % 10;
			if (random == 0)  {
				GameGUI::getInstance()->visualEffects[0]->animateToasty();
				character1->talk("toasty");
			}
		}

		else if (character2->getMovement() == SWEEP_MOVEMENT && character1->getMovement() != DUCK_BLOCK_MOVEMENT && character1->getMovement() != SWEEP_MOVEMENT){
				character1->setMovement(HINT_FLYING_MOVEMENT);
				character2->clearMovementsFlags();
				SoundManager::Instance()->playSound("gancho", 0);
		}

		bool rightOrientation = false;
		bool pushChar1 = false;
		//DON'T OVERLAP LOGIC FOR CHARACTER 2
		float windowWidth = GameGUI::getInstance()->getWindow()->getWidth();
		//FOR WALKING
		if ( character2->getMovement() == WALKING_LEFT_MOVEMENT && !character2->getIsRightOriented() ) {
			character1->beingPushed = true;
			// stop walking
			if (character1->posXBox > WINDOW_MARGIN * character1->getRatioX()) {
				pushChar1 = true;
				rightOrientation = false;
			} else {
				character2->setPositionX((character1->posXBox + character1->widthBox) - character2->widthBox);
			}
		}

		if (character2->getMovement() == WALKING_RIGHT_MOVEMENT && character2->getIsRightOriented()) {
			character1->beingPushed = true;
			if (character1->posXBox + character1->widthBox < (windowWidth - WINDOW_MARGIN ) * character1->getRatioX()) {
				pushChar1 = true;
				rightOrientation = true;
			} else {
				character2->setPositionX(character1->posXBox - character2->widthBox * 2);
			}

		}


	//FOR JUMPING
		//	float windowWidth = GameGUI::getInstance()->getWindow()->getWidth();
			float posYCharacter1 = character1->posYBox;
			float posXCharacter1 = character1->posYBox;
			float widthCharacter1 = character1->widthBox;

			float posYCharacter2 = character2->posYBox;
			float posXCharacter2 = character2->posYBox;
			float widthCharacter2 = character2->widthBox;
			if ( character2->getMovement() == JUMPING_LEFT_MOVEMENT && !character2->getIsRightOriented() ) {
				character1->beingPushed = true;
				//TODO: review if the jump is too close
				if ( ((posYCharacter1 - posYCharacter2) < 30*character2->getRatioY())) {
					if ((posXCharacter2 - posXCharacter1 < widthCharacter1) && (character2->jumpVel < 0)){
						character2->smoothOffsetX = widthCharacter2;
						character2->smoothOrientation = 1;
					}
				}
			}

			if ( character2->getMovement() == JUMPING_RIGHT_MOVEMENT && character2->getIsRightOriented() ) {
				character1->beingPushed = true;
				if ( ((posYCharacter1 - posYCharacter2)  < 30*character2->getRatioY())) {
					if (posXCharacter1 - posXCharacter2 < widthCharacter1 && (character2->jumpVel < 0)) {
						character2->smoothOffsetX = character2->widthBox;
						character2->smoothOrientation = -1;
					}
				}
			}


		//FOR AIR KICKING
		if ( character2->getIsKickingAirLowLeft() && !character2->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			character2->setPositionX(character1->posXBox);
			character2->talk("punchHit");
		}

		if ( character2->getIsKickingAirLowRight() && character2->getIsRightOriented() ) {
			character2->setPositionX(character1->posXBox - character1->widthBox*2);
			character2->talk("punchHit");
		}


		//FOR AIR PUNCHING
		if ( character2->getIsAirPunchingLeft() && !character2->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			character2->setPositionX(character1->posXBox);
			character2->talk("punchHit");
		}

		if ( character2->getIsAirPunchingRight() && character2->getIsRightOriented() ) {
			character2->setPositionX(character1->posXBox - character1->widthBox*2);
			character2->talk("punchHit");
		}
		bool pushChar2 = false;

		//----------------------------------------------------------------------------------------------
		//DON'T OVERLAP LOGIC FOR CHARACTER 1
		//FOR WALKING
			if ( character1->getMovement() == WALKING_LEFT_MOVEMENT && !character1->getIsRightOriented() ) {
				character2->beingPushed = true;
				// stop walking
				if (character2->posXBox > WINDOW_MARGIN * character2->getRatioX()) {
					pushChar2 = true;
					rightOrientation = false;

				} else {
					character1->setPositionX((character2->posXBox + character2->widthBox) - character1->widthBox);
				}
			}

			if (character1->getMovement() == WALKING_RIGHT_MOVEMENT && character1->getIsRightOriented()) {
				character2->beingPushed = true;
				if (character2->posXBox + character2->widthBox < (windowWidth - WINDOW_MARGIN ) * character2->getRatioX()) {
					pushChar2 = true;
					rightOrientation = true;

				} else {
					character1->setPositionX(character2->posXBox - character1->widthBox * 2);
				}

			}


			pushCharacter(character1,character2, pushChar1,pushChar2,rightOrientation);

			//FOR JUMPING
			if ( character1->getMovement() == JUMPING_LEFT_MOVEMENT && !character1->getIsRightOriented() ) {
				//TODO: review if the jump is too close
				character2->beingPushed = true;
				if ( ((posYCharacter2- posYCharacter1) < 30*character1->getRatioY())) {
					if ((posXCharacter1 - posXCharacter2 < widthCharacter2) && (character1->jumpVel < 0)) {
						character1->smoothOffsetX = character1->widthBox;
						character1->smoothOrientation = 1;
					}
				}
			}

			if ( character1->getMovement() == JUMPING_RIGHT_MOVEMENT && character1->getIsRightOriented() ) {
				character2->beingPushed = true;
				if ( ((character2->posYBox - character1->posYBox) < 30*character1->getRatioY())) {
					if (posXCharacter2 - posXCharacter1 < widthCharacter2 && (character1->jumpVel < 0)) {
						character1->smoothOffsetX = character1->widthBox;
						character1->smoothOrientation = -1;
					}
				}
			}


		//FOR AIR KICKING
		if ( character1->getIsKickingAirLowLeft() && !character1->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			character1->setPositionX(character2->posXBox);
			character1->talk("punchHit");
		}

		if ( character1->getIsKickingAirLowRight() && character1->getIsRightOriented() ) {
			character1->setPositionX(character2->posXBox - character2->widthBox*2);
			character1->talk("punchHit");
		}


		//FOR AIR PUNCHING
		if ( character1->getIsAirPunchingLeft() && !character1->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			character1->setPositionX(character2->posXBox);
			character1->talk("punchHit");
		}

		if ( character1->getIsAirPunchingRight() && character1->getIsRightOriented() ) {
			character1->setPositionX(character2->posXBox - character2->widthBox*2);
			character1->talk("punchHit");
		}

	}
}

//Distancia en el eje x entre los personajes (en UL)
//Se toma como distancia el espacio entre el fin de una box y el comienzo de la otra.
float CharacterManager::getCharacterDistance() {
	Character* character1 = GameGUI::getInstance()->getCharacters().at(0);
	Character* character2 = GameGUI::getInstance()->getCharacters().at(1);
	return fabs( character1->getPosXUL() - character2->getPosXUL() ) - character1->getWidthBoxUL();
}
