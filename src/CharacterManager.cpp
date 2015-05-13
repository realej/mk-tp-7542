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

void CharacterManager::solveMovesBeignHint(DamageObject* actualObj, DamageObject* nextObj){

	Character* character1;

	Character* character2;

	if (actualObj->isCharacter()){
		character1 = dynamic_cast<Character*>(actualObj);
	}

	if (nextObj->isCharacter()){
		character2 = dynamic_cast<Character*>(nextObj);
	}

	//GOLPES CHARACTER 1
	if (character1->getMovement() == PUNCHING_HIGH_MOVEMENT || character1->getMovement() == HIGH_KICK_MOVEMENT
			|| character1->getMovement() == AIR_PUNCH_MOVEMENT){
		character2->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
	}
	else if (character1->getMovement() == PUNCHING_LOW_MOVEMENT || character1->getMovement() == LOW_KICK_MOVEMENT
			|| character1->getMovement() == DUCK_HIGH_KICK_MOVEMENT || character1->getMovement() == DUCK_LOW_KICK_MOVEMENT
			|| character1->getMovement() == PUNCHING_DUCK_MOVEMENT || character1->getMovement() == PUNCHING_HIGH_MOVEMENT ){
		character2->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
	}
	else if (character1->getMovement() == UNDER_KICK_MOVEMENT){
		character2->setMovement(BEING_HINT_FALLING_UNDER_KICK_MOVEMENT);
	}

	else if (character1->getMovement() == SUPER_KICK_MOVEMENT || character1->getMovement() == AIR_HIGH_kICK_MOVEMENT
			|| character1->getMovement() == AIR_LOW_kICK_MOVEMENT){
		character2->setMovement(HINT_FLYING_MOVEMENT);
	}

	else if (character1->getMovement() == UPPERCUT_MOVEMENT){
		character2->setMovement(HINT_FLYING_UPPER_MOVEMENT);
	}

	//GOLPES CHARACTER 2
	if (character2->getMovement() == PUNCHING_HIGH_MOVEMENT || character2->getMovement() == HIGH_KICK_MOVEMENT
			|| character2->getMovement() == AIR_PUNCH_MOVEMENT){
		character1->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
	}
	else if (character2->getMovement() == PUNCHING_LOW_MOVEMENT || character2->getMovement() == LOW_KICK_MOVEMENT
			|| character2->getMovement() == DUCK_HIGH_KICK_MOVEMENT || character2->getMovement() == DUCK_LOW_KICK_MOVEMENT
			|| character2->getMovement() == PUNCHING_DUCK_MOVEMENT || character2->getMovement() == PUNCHING_HIGH_MOVEMENT ){
		character1->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
	}
	else if (character2->getMovement() == UNDER_KICK_MOVEMENT){
		character1->setMovement(BEING_HINT_FALLING_UNDER_KICK_MOVEMENT);
	}

	else if (character2->getMovement() == SUPER_KICK_MOVEMENT || character2->getMovement() == AIR_HIGH_kICK_MOVEMENT
			|| character2->getMovement() == AIR_LOW_kICK_MOVEMENT){
		character1->setMovement(HINT_FLYING_MOVEMENT);
	}

	else if (character2->getMovement() == UPPERCUT_MOVEMENT){
		character1->setMovement(HINT_FLYING_UPPER_MOVEMENT);
	}

}

