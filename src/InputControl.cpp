/*
 * InputControl.h
 *
 *  Created on: 31/03/2015
 *      Author: Diego Serra
 *
 * llamar al metodo refreshInputs para obtener los nuevos estados de las entradas,
 * hacer la llamada luego del ciclo de vacia la lista de eventos de SDL, while (SDL_PollEvent(&event))
 *
 *
 */

#include "../headers/InputControl.h"
#include "SDL.h"
#include "../headers/MKGame.h"
#include "../headers/SecuenceInputManager.h"
#include <stddef.h>

bool somePunchButtonPressed(const Uint8* keyBoard);
bool someKickButtonPressed(const Uint8* keyBoard);

bool somePunchButtonPressed1(const Uint8* keyBoard);
bool someKickButtonPressed1(const Uint8* keyBoard);

bool somePunchButtonPressed2(const Uint8* keyBoard);
bool someKickButtonPressed2(const Uint8* keyBoard);

void InputControl::refreshInputs() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	//this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else if (currentKeyStates[SDL_SCANCODE_UP]) {

		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !somePunchButtonPressed(currentKeyStates)
				&& !someKickButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(someKickButtonPressed(currentKeyStates))
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
		}

		//COMBINATION WITH DOWN
	} else if (currentKeyStates[SDL_SCANCODE_DOWN]
			&& !currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (currentKeyStates[SDL_SCANCODE_A]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_PUNCH;
		} else if (currentKeyStates[SDL_SCANCODE_S]) {
			this->secondPlayerMove = FIRST_PLAYER_UPPERCUT;
		} else if (currentKeyStates[SDL_SCANCODE_Z]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_LOW_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_X]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN;

		}
		//COMBINATION WITH LEFT
	} else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (currentKeyStates[SDL_SCANCODE_X]) {
			this->secondPlayerMove = FIRST_PLAYER_SUPER_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_Z]) {
			this->secondPlayerMove = FIRST_PLAYER_UNDER_KICK;
		} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_LEFT;
		}
		//COMBINATION WITH RIGHT
	} else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !currentKeyStates[SDL_SCANCODE_LCTRL]
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
		} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		}
		//COMBINATION WITH S
	} else if (currentKeyStates[SDL_SCANCODE_S]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_HI_PUNCH;

		}
		//COMBINATION WITH A
	} else if (currentKeyStates[SDL_SCANCODE_A]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_LO_PUNCH;
		}

		//COMBINATION WITH LEFT CTRL
	} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])) {
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		} else if ((currentKeyStates[SDL_SCANCODE_DOWN])) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_BLOCK;
		}

	} else if (currentKeyStates[SDL_SCANCODE_X]) {
		this->secondPlayerMove = FIRST_PLAYER_HIGH_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_Z]) {
		this->secondPlayerMove = FIRST_PLAYER_LOW_KICK;
	} else if (currentKeyStates[SDL_SCANCODE_DELETE]) {
		this->secondPlayerMove = LAZY;
	}

}
void InputControl::refreshInputs1() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	this->firstPlayerMove = NO_INPUT;
	//this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else if (currentKeyStates[SDL_SCANCODE_W]) {

		if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& !somePunchButtonPressed1(currentKeyStates)
				&& !someKickButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& somePunchButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_PUNCH;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& (currentKeyStates[SDL_SCANCODE_A])
				&& somePunchButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_PUNCH_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& somePunchButtonPressed1(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_PUNCH_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& someKickButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& (currentKeyStates[SDL_SCANCODE_A])
				&& !(someKickButtonPressed1(currentKeyStates))
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& (currentKeyStates[SDL_SCANCODE_A])
				&& someKickButtonPressed1(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& someKickButtonPressed1(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& (currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
		}

		//COMBINATION WITH DOWN
	} else if (currentKeyStates[SDL_SCANCODE_S]
			&& !currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (currentKeyStates[SDL_SCANCODE_F]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_PUNCH;
		} else if (currentKeyStates[SDL_SCANCODE_G]) {
			this->firstPlayerMove = FIRST_PLAYER_UPPERCUT;
		} else if (currentKeyStates[SDL_SCANCODE_V]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_LOW_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_B]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_W])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& (currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
		} else if (!(currentKeyStates[SDL_SCANCODE_W])
				&& (currentKeyStates[SDL_SCANCODE_A])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_W])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN;

		}
		//COMBINATION WITH LEFT
	} else if (currentKeyStates[SDL_SCANCODE_A]) {
		if (currentKeyStates[SDL_SCANCODE_B]) {
			this->firstPlayerMove = FIRST_PLAYER_SUPER_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_V]) {
			this->firstPlayerMove = FIRST_PLAYER_UNDER_KICK;
		} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		} else if (!(currentKeyStates[SDL_SCANCODE_W])
				&& !(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_LEFT;
		}
		//COMBINATION WITH RIGHT
	} else if (currentKeyStates[SDL_SCANCODE_D]) {
		if (!(currentKeyStates[SDL_SCANCODE_W])
				&& !(currentKeyStates[SDL_SCANCODE_S])
				&& !currentKeyStates[SDL_SCANCODE_LCTRL]
				&& !(currentKeyStates[SDL_SCANCODE_A])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
		} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		}
		//COMBINATION WITH S
	} else if (currentKeyStates[SDL_SCANCODE_G]) {
		if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_HI_PUNCH;
			SoundManager::Instance()->playSound("punch2_1", 0);
		}
		//COMBINATION WITH A
	} else if (currentKeyStates[SDL_SCANCODE_F]) {
		if (!(currentKeyStates[SDL_SCANCODE_S])
				&& !(currentKeyStates[SDL_SCANCODE_A])
				&& !(currentKeyStates[SDL_SCANCODE_D])) {
			this->firstPlayerMove = FIRST_PLAYER_LO_PUNCH;
		}

		//COMBINATION WITH LEFT CTRL
	} else if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
		if (!(currentKeyStates[SDL_SCANCODE_S])) {
			this->firstPlayerMove = FIRST_PLAYER_BLOCK;
		} else if ((currentKeyStates[SDL_SCANCODE_S])) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_BLOCK;
		}

	} else if (currentKeyStates[SDL_SCANCODE_B]) {
		this->firstPlayerMove = FIRST_PLAYER_HIGH_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_V]) {
		this->firstPlayerMove = FIRST_PLAYER_LOW_KICK;
	}

	/**
	 * Special moves, replicar para refreshInput2
	 */
	else if (currentKeyStates[SDL_SCANCODE_Q]) {
		this->firstPlayerMove = SUBZERO_SWEEP;
	} else if (currentKeyStates[SDL_SCANCODE_E]) {
		this->firstPlayerMove = FIRST_PLAYER_FIRE;
	} else if (currentKeyStates[SDL_SCANCODE_T]) {
		this->firstPlayerMove = BABALITY;
	} else if (currentKeyStates[SDL_SCANCODE_U]) {
		this->firstPlayerMove = FATALITY;
	} else if (currentKeyStates[SDL_SCANCODE_O]) {
		this->firstPlayerMove = FRIENDSHIP;
	}

}

void InputControl::refreshInputs2() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	//this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else if (currentKeyStates[SDL_SCANCODE_UP]) {

		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !somePunchButtonPressed2(currentKeyStates)
				&& !someKickButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& somePunchButtonPressed2(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_PUNCH_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(someKickButtonPressed2(currentKeyStates))
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed2(currentKeyStates)
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_L;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& someKickButtonPressed2(currentKeyStates)
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_AIR_LOW_kICK_R;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
		}

		//COMBINATION WITH DOWN
	} else if (currentKeyStates[SDL_SCANCODE_DOWN]
			&& !currentKeyStates[SDL_SCANCODE_RCTRL]) {
		if (currentKeyStates[SDL_SCANCODE_J]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_PUNCH;
		} else if (currentKeyStates[SDL_SCANCODE_K]) {
			this->secondPlayerMove = FIRST_PLAYER_UPPERCUT;
		} else if (currentKeyStates[SDL_SCANCODE_N]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_LOW_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_M]) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_HIGH_kICK;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_DOWN;

		}
		//COMBINATION WITH LEFT
	} else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (currentKeyStates[SDL_SCANCODE_M]) {
			this->secondPlayerMove = FIRST_PLAYER_SUPER_kICK;
		} else if (currentKeyStates[SDL_SCANCODE_N]) {
			this->secondPlayerMove = FIRST_PLAYER_UNDER_KICK;
		} else if (currentKeyStates[SDL_SCANCODE_RCTRL]) {
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_LEFT;
		}
		//COMBINATION WITH RIGHT
	} else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !currentKeyStates[SDL_SCANCODE_RCTRL]
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])) {
			this->secondPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
		} else if (currentKeyStates[SDL_SCANCODE_RCTRL]) {
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		}
		//COMBINATION WITH S
	} else if (currentKeyStates[SDL_SCANCODE_K]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_HI_PUNCH;
		}
		//COMBINATION WITH A
	} else if (currentKeyStates[SDL_SCANCODE_J]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->secondPlayerMove = FIRST_PLAYER_LO_PUNCH;
		}

		//COMBINATION WITH LEFT CTRL
	} else if (currentKeyStates[SDL_SCANCODE_RCTRL]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])) {
			this->secondPlayerMove = FIRST_PLAYER_BLOCK;
		} else if ((currentKeyStates[SDL_SCANCODE_DOWN])) {
			this->secondPlayerMove = FIRST_PLAYER_DUCK_BLOCK;
		}

	} else if (currentKeyStates[SDL_SCANCODE_M]) {
		this->secondPlayerMove = FIRST_PLAYER_HIGH_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_N]) {
		this->secondPlayerMove = FIRST_PLAYER_LOW_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_DELETE]) {
		this->secondPlayerMove = LAZY;
	}

}

void InputControl::refreshJoystickInputs() {

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else {
		int joys;
		if (MKGame::Instance()->practiceMode) {
			joys = 1;
		} else {
			joys = SDL_NumJoysticks();
		}
		for (int joystick = 0; joystick < joys; joystick++) {


			loadSpecialSecuence(joystick);
			detectSpecialMove(joystick);

			if ( ( joystick == 0 && this->firstPlayerMove == NO_INPUT) ||
					( joystick == 1 && this->secondPlayerMove == NO_INPUT)) {

				if (isAxisUp(joystick)) {

					if (!(isAxisDown(joystick)) && !(isAxisLeft(joystick))
							&& !someJoyPunchButtonPressed(joystick)
							&& !someJoyKickButtonPressed(joystick)
							&& !(isAxisRight(joystick))
							&& !getActionButtonState(joystick, FIRE)) {
						setPlayerMove(joystick, FIRST_PLAYER_MOVE_UP);
					} else if (!(isAxisDown(joystick))
							&& !(isAxisLeft(joystick))
							&& !someJoyPunchButtonPressed(joystick)
							&& !someJoyKickButtonPressed(joystick)
							&& !(isAxisRight(joystick))
							&& getActionButtonState(joystick, FIRE)) {
						setPlayerMove(joystick, FIRST_PLAYER_FIRE);
					} else if (!(isAxisDown(joystick))
							&& !(isAxisLeft(joystick))
							&& someJoyPunchButtonPressed(joystick)
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_AIR_PUNCH);
					} else if (!(isAxisDown(joystick)) && (isAxisLeft(joystick))
							&& someJoyPunchButtonPressed(joystick)
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_AIR_PUNCH_L);
					} else if (!(isAxisDown(joystick))
							&& !(isAxisLeft(joystick))
							&& someJoyPunchButtonPressed(joystick)
							&& (isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_AIR_PUNCH_R);
					} else if (!(isAxisDown(joystick))
							&& !(isAxisLeft(joystick))
							&& someJoyKickButtonPressed(joystick)
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_AIR_HIGH_kICK);
					} else if (!(isAxisDown(joystick)) && (isAxisLeft(joystick))
							&& !(someJoyKickButtonPressed(joystick))
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_MOVE_UP_LEFT);
					} else if (!(isAxisDown(joystick)) && (isAxisLeft(joystick))
							&& someJoyKickButtonPressed(joystick)
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_AIR_LOW_kICK_L);
					} else if (!(isAxisDown(joystick))
							&& !(isAxisLeft(joystick))
							&& someJoyKickButtonPressed(joystick)
							&& (isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_AIR_LOW_kICK_R);
					} else if (!(isAxisDown(joystick))
							&& !(isAxisLeft(joystick))
							&& (isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_MOVE_UP_RIGHT);
					}

					//COMBINATION WITH DOWN
				} else if (isAxisDown(joystick)
						&& !getActionButtonState(joystick, BLOCK)) {

					if (getActionButtonState(joystick, LOW_PUNCH)) {
						setPlayerMove(joystick, FIRST_PLAYER_DUCK_PUNCH);
						setActionButtonStateFalse(joystick, LOW_PUNCH);
					} else if (getActionButtonState(joystick, FIRE)) {
						setPlayerMove(joystick, FIRST_PLAYER_DUCK_FIRE);
					} else if (getActionButtonState(joystick, HIGH_PUNCH)) {
						setPlayerMove(joystick, FIRST_PLAYER_UPPERCUT);
						setActionButtonStateFalse(joystick, HIGH_PUNCH);
					} else if (getActionButtonState(joystick, LOW_KICK)) {
						setPlayerMove(joystick, FIRST_PLAYER_DUCK_LOW_kICK);
						setActionButtonStateFalse(joystick, LOW_KICK);
					} else if (getActionButtonState(joystick, HIGH_KICK)) {
						setPlayerMove(joystick, FIRST_PLAYER_DUCK_HIGH_kICK);
						setActionButtonStateFalse(joystick, HIGH_KICK);
					} else if (!(isAxisUp(joystick)) && !(isAxisLeft(joystick))
							&& (isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_MOVE_DOWN_RIGHT);
					} else if (!(isAxisUp(joystick)) && (isAxisLeft(joystick))
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_MOVE_DOWN_LEFT);
					} else if (!(isAxisUp(joystick)) && !(isAxisLeft(joystick))
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_MOVE_DOWN);

					}
					//COMBINATION WITH LEFT
				} else if (isAxisLeft(joystick)) {
					if (getActionButtonState(joystick, HIGH_KICK)) {
						if (GameGUI::getInstance()->getCharacters()[joystick]->getIsRightOriented()) {
							this->setPlayerMove(joystick,
									FIRST_PLAYER_SUPER_kICK);
						} else {
							this->setPlayerMove(joystick,
									FIRST_PLAYER_HIGH_KICK);
						}
					} else if (getActionButtonState(joystick, BLOCK)) {
						setPlayerMove(joystick, FIRST_PLAYER_BLOCK);
					} else if (this->getActionButtonState(joystick, LOW_KICK)) {
						if (GameGUI::getInstance()->getCharacters()[joystick]->getIsRightOriented()) {
							this->setPlayerMove(joystick,
									FIRST_PLAYER_UNDER_KICK);
						} else {
							this->setPlayerMove(joystick,
									FIRST_PLAYER_LOW_KICK);
						}
					} else if (this->getActionButtonState(joystick,
							LOW_PUNCH)) {
						this->setPlayerMove(joystick, FIRST_PLAYER_LO_PUNCH);
						this->setActionButtonStateFalse(joystick, LOW_PUNCH);
					} else if (this->getActionButtonState(joystick,
							HIGH_PUNCH)) {
						this->setPlayerMove(joystick, FIRST_PLAYER_HI_PUNCH);
						this->setActionButtonStateFalse(joystick, HIGH_PUNCH);
					} else if (!(isAxisUp(joystick)) && !(isAxisDown(joystick))
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_MOVE_LEFT);
					}
					//COMBINATION WITH RIGHT
				} else if (isAxisRight(joystick)) {
					if (getActionButtonState(joystick, HIGH_KICK)) {
						if (!GameGUI::getInstance()->getCharacters()[joystick]->getIsRightOriented()) {
							this->setPlayerMove(joystick,
									FIRST_PLAYER_SUPER_kICK);
						} else {
							this->setPlayerMove(joystick,
									FIRST_PLAYER_HIGH_KICK);
						}
						this->setActionButtonStateFalse(joystick, HIGH_KICK);

					} else if (this->getActionButtonState(joystick, LOW_KICK)) {
						if (!GameGUI::getInstance()->getCharacters()[joystick]->getIsRightOriented()) {
							this->setPlayerMove(joystick,
									FIRST_PLAYER_UNDER_KICK);
						} else {
							this->setPlayerMove(joystick,
									FIRST_PLAYER_LOW_KICK);
						}
					} else if (this->getActionButtonState(joystick,
							LOW_PUNCH)) {
						this->setPlayerMove(joystick, FIRST_PLAYER_LO_PUNCH);
						this->setActionButtonStateFalse(joystick, LOW_PUNCH);
					} else if (this->getActionButtonState(joystick,
							HIGH_PUNCH)) {
						this->setPlayerMove(joystick, FIRST_PLAYER_HI_PUNCH);
						this->setActionButtonStateFalse(joystick, HIGH_PUNCH);
					} else if (!(isAxisUp(joystick)) && !(isAxisDown(joystick))
							&& !getActionButtonState(joystick, BLOCK)
							&& !(isAxisLeft(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_MOVE_RIGHT);
					} else if (getActionButtonState(joystick, BLOCK)) {
						setPlayerMove(joystick, FIRST_PLAYER_BLOCK);
					}
					//COMBINATION WITH S
				} else if (getActionButtonState(joystick, HIGH_PUNCH)) {
					if (!(isAxisDown(joystick)) && !(isAxisLeft(joystick))
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_HI_PUNCH);
					}
					//COMBINATION WITH A
				} else if (getActionButtonState(joystick, LOW_PUNCH)) {
					if (!(isAxisDown(joystick)) && !(isAxisLeft(joystick))
							&& !(isAxisRight(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_LO_PUNCH);
					}

					//COMBINATION WITH LEFT CTRL
				} else if (getActionButtonState(joystick, BLOCK)) {
					if (!(isAxisDown(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_BLOCK);
					} else if ((isAxisDown(joystick))) {
						setPlayerMove(joystick, FIRST_PLAYER_DUCK_BLOCK);
					}

				} else if (getActionButtonState(joystick, HIGH_KICK)) {
					setPlayerMove(joystick, FIRST_PLAYER_HIGH_KICK);
				}

				else if (getActionButtonState(joystick, LOW_KICK)) {
					setPlayerMove(joystick, FIRST_PLAYER_LOW_KICK);
				} else if (getActionButtonState(joystick, FIRE)) {
					setPlayerMove(joystick, FIRST_PLAYER_FIRE);
				}

				this->setActionButtonStateFalse(joystick, HIGH_KICK);
				this->setActionButtonStateFalse(joystick, LOW_KICK);
				this->setActionButtonStateFalse(joystick, HIGH_PUNCH);
				this->setActionButtonStateFalse(joystick, LOW_PUNCH);
				this->setActionButtonStateFalse(joystick, FIRE);
			}
		}
	}

}

bool InputControl::isAxisRight(int joystick) {
	if (SDL_NumJoysticks() > joystick)
		return this->joystickAxisStates[joystick].first > 0;
}

bool InputControl::isAxisLeft(int joystick) {
	if (SDL_NumJoysticks() > joystick)
		return this->joystickAxisStates[joystick].first < 0;
}

bool InputControl::isAxisUp(int joystick) {
	if (SDL_NumJoysticks() > joystick)
		return this->joystickAxisStates[joystick].second < 0;
}

bool InputControl::isAxisDown(int joystick) {
	if (SDL_NumJoysticks() > joystick)
		return this->joystickAxisStates[joystick].second > 0;
}

InputCommand InputControl::getFirstPlayerMove() {
	return this->firstPlayerMove;
}

InputCommand InputControl::getSecondPlayerMove() {
	return this->secondPlayerMove;
}

InputCommand InputControl::getControlOption() {
	return this->controlOption;
}

void InputControl::validateButtonsRange(int joyNum, int butCount) {

	int lk = joystickActionButton[joyNum][LOW_KICK];
	int hk = joystickActionButton[joyNum][HIGH_KICK];
	int lp = joystickActionButton[joyNum][LOW_PUNCH];
	int hp = joystickActionButton[joyNum][HIGH_PUNCH];
	int bl = joystickActionButton[joyNum][BLOCK];
	int fr = joystickActionButton[joyNum][FIRE];
	int qu = joystickActionButton[joyNum][QUIT];
	int rp = joystickActionButton[joyNum][RESET_PRACTICE];

	if (rp > butCount || qu > butCount || lk > butCount || hk > butCount || lp > butCount || hp > butCount
			|| bl > butCount || fr > butCount) {
		FILE_LOG(logERROR) << "Setted button in joystick " << joyNum
				<< " is higher than buttons in joystick (" << butCount << ")";
		FILE_LOG(logERROR) << "Bad buttons configuration in joystick " << joyNum
				<< ", default configuration loaded";
		this->loadDefaultButtons(joyNum);
	}
}

void InputControl::initJoysticks() {

	FILE_LOG(logDEBUG) << "Number of Joysticks connected: "
			<< SDL_NumJoysticks();

	//Check for joysticks
	if (SDL_NumJoysticks() < 1) {

		FILE_LOG(logERROR) << "Error: No joysticks connected!";

	} else {

		SDL_SetHint("SDL_JOYSTICK_ALLOW_BACKGROUND_EVENTS", "1"); //Linea magica que hace que funcione el input del joystick

		//Load joysticks
		for (int i = 0; i < SDL_NumJoysticks(); i++) {

			SDL_Joystick* joystick = SDL_JoystickOpen(i);

			if (joystick == NULL) {

				FILE_LOG(logERROR) << "Failed to open joystick " << i
						<< SDL_GetError();

			} else {

				int buttonCount = SDL_JoystickNumButtons(joystick);

				FILE_LOG(logDEBUG) << "Joystick " << i << " button count "
						<< buttonCount;

				validateButtonsRange(i, buttonCount);

				std::vector<bool> buttonStates;

				for (int j = 0; j < buttonCount; j++) {
					buttonStates.push_back(false);
				}

				this->joysticksButtonStates.push_back(buttonStates);
				this->joysticks.push_back(joystick);

				this->joystickAxisStates.push_back( { 0, 0 });
				FILE_LOG(logDEBUG) << "Joystick " << i << " initialized";
			}
		}
	}
}

void InputControl::update() {
}

void InputControl::clean() {

	for (unsigned int i = 0; i < this->joysticks.size(); i++) {
		SDL_JoystickClose(this->joysticks[i]);
	}
	this->joysticks.clear();

}

void InputControl::setActionButton(int joy, string action, int button) {

//	std::cout << SDL_JoystickNumButtons(this->joysticks[joy]) << std::endl;
	std::vector<std::map<std::string, int> > joysticks;
	std::map<std::string, int> actionButton;
	joysticks.push_back(actionButton);

	this->joystickActionButton.push_back(joysticks[0]);

	this->joystickActionButton.at(joy)[action] = button;

}

int InputControl::getActionButton(int joy, string action) {
	return this->joystickActionButton[joy][action];
}

bool InputControl::getActionButtonState(int joyNum, string action) {
	int buttonNumber = this->getActionButton(joyNum, action);
	return this->joysticksButtonStates[joyNum][buttonNumber];
}

void InputControl::setActionButtonStateFalse(int joy, string action) {
	int button = this->getActionButton(joy, action);
	this->joysticksButtonStates[joy][button] = false;
}

bool someKickButtonPressed(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_Z]) || (keyBoard[SDL_SCANCODE_X]);
}

bool somePunchButtonPressed(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_A]) || (keyBoard[SDL_SCANCODE_S]);
}

bool someKickButtonPressed1(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_V]) || (keyBoard[SDL_SCANCODE_B]);
}

bool somePunchButtonPressed1(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_F]) || (keyBoard[SDL_SCANCODE_G]);
}

bool someKickButtonPressed2(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_N]) || (keyBoard[SDL_SCANCODE_M]);
}

bool somePunchButtonPressed2(const Uint8* keyBoard) {
	return (keyBoard[SDL_SCANCODE_J]) || (keyBoard[SDL_SCANCODE_K]);
}

bool InputControl::someJoyKickButtonPressed(int joy) {
	if (SDL_NumJoysticks() > joy)
		return (getActionButtonState(joy, LOW_KICK))
				|| (getActionButtonState(joy, HIGH_KICK));
}

bool InputControl::someJoyPunchButtonPressed(int joy) {
	if (SDL_NumJoysticks() > joy)
		return (getActionButtonState(joy, LOW_PUNCH))
				|| (getActionButtonState(joy, HIGH_PUNCH));
}

void InputControl::setPlayerMove(int joy, InputCommand action) {
	//this->playerMove[joy] = action;
	if (joy == 0)
		this->firstPlayerMove = action;
	else if (joy == 1)
		this->secondPlayerMove = action;
}

InputCommand InputControl::getPlayerMove(int joy) {
	return this->playerMove[joy];
}

void InputControl::loadDefaultButtons(int joyNum) {
	setActionButton(joyNum, LOW_PUNCH, 1);
	setActionButton(joyNum, HIGH_PUNCH, 0);
	setActionButton(joyNum, LOW_KICK, 2);
	setActionButton(joyNum, HIGH_KICK, 3);
	setActionButton(joyNum, BLOCK, 4);
	setActionButton(joyNum, FIRE, 5);
	setActionButton(joyNum, QUIT, 6);
	setActionButton(joyNum, RESET_PRACTICE, 7);
}

void InputControl::loadSpecialSecuence(int joystick) {
	std::string up = "";
	std::string down = "";
	std::string left = "";
	std::string right = "";

	std::string block = "";
	std::string fire = "";
	std::string kickHigh = "";
	std::string kickLow = "";
	std::string puckHigh = "";
	std::string punchLow = "";

	std::string secuencia = "";

	bool isSetMove = SecuenceInputManager::Instance()->getIsSetMove(joystick);

	if (!isSetMove) {
		if ((isAxisLeft(joystick)) && (((joystick == 0) && (!SecuenceInputManager::Instance()->joy1LeftPressOnce)) || ((joystick == 1)	&& (!SecuenceInputManager::Instance()->joy2LeftPressOnce)))) {

			if ((joystick == 0) && (!SecuenceInputManager::Instance()->joy1LeftPressOnce) && (SecuenceInputManager::Instance()->firstPlayerRightOrientation)){
				left = CHARACTER_FOR_SPECIAL_MOVE_BACKWARD;
			}else if ((joystick == 0) && (!SecuenceInputManager::Instance()->joy1LeftPressOnce) && (!SecuenceInputManager::Instance()->firstPlayerRightOrientation)){
				left = CHARACTER_FOR_SPECIAL_MOVE_FORWARD;
			}
			if ((joystick == 1) && (!SecuenceInputManager::Instance()->joy2LeftPressOnce) && (SecuenceInputManager::Instance()->secondPlayerRightOrientation)){
				left = CHARACTER_FOR_SPECIAL_MOVE_BACKWARD;
			}else if ((joystick == 1) && (!SecuenceInputManager::Instance()->joy2LeftPressOnce) && (!SecuenceInputManager::Instance()->secondPlayerRightOrientation)){
				left = CHARACTER_FOR_SPECIAL_MOVE_FORWARD;
			}

			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1LeftPressOnce = true;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2LeftPressOnce = true;
			}
		} else if (!isAxisLeft(joystick)) {
			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1LeftPressOnce = false;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2LeftPressOnce = false;
			}
		}
		if ((isAxisRight(joystick))	&& (((joystick == 0) && (!SecuenceInputManager::Instance()->joy1RightPressOnce)) || ((joystick == 1) && (!SecuenceInputManager::Instance()->joy2RightPressOnce)))) {

			if ((joystick == 0) && (!SecuenceInputManager::Instance()->joy1RightPressOnce) && (SecuenceInputManager::Instance()->firstPlayerRightOrientation)){
				right = CHARACTER_FOR_SPECIAL_MOVE_FORWARD;
			}else if ((joystick == 0) && (!SecuenceInputManager::Instance()->joy1RightPressOnce) && (!SecuenceInputManager::Instance()->firstPlayerRightOrientation)){
				right = CHARACTER_FOR_SPECIAL_MOVE_BACKWARD;
			}
			if ((joystick == 1) && (!SecuenceInputManager::Instance()->joy2RightPressOnce) && (SecuenceInputManager::Instance()->secondPlayerRightOrientation)){
				right = CHARACTER_FOR_SPECIAL_MOVE_FORWARD;
			}else if ((joystick == 1) && (!SecuenceInputManager::Instance()->joy2RightPressOnce) && (!SecuenceInputManager::Instance()->secondPlayerRightOrientation)){
				right = CHARACTER_FOR_SPECIAL_MOVE_BACKWARD;
			}

			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1RightPressOnce = true;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2RightPressOnce = true;
			}
		} else if (!isAxisRight(joystick)) {
			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1RightPressOnce = false;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2RightPressOnce = false;
			}
		}
		if ((isAxisUp(joystick))
				&& (((joystick == 0)
						&& (!SecuenceInputManager::Instance()->joy1UpPressOnce))
						|| ((joystick == 1)
								&& (!SecuenceInputManager::Instance()->joy2UpPressOnce)))) {
			up = CHARACTER_FOR_SPECIAL_MOVE_UP;
			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1UpPressOnce = true;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2UpPressOnce = true;
			}
		} else if (!isAxisUp(joystick)) {
			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1UpPressOnce = false;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2UpPressOnce = false;
			}
		}
		if ((isAxisDown(joystick))
				&& (((joystick == 0)
						&& (!SecuenceInputManager::Instance()->joy1DownPressOnce))
						|| ((joystick == 1)
								&& (!SecuenceInputManager::Instance()->joy2DownPressOnce)))) {
			down = CHARACTER_FOR_SPECIAL_MOVE_DOWN;
			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1DownPressOnce = true;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2DownPressOnce = true;
			}
		} else if (!isAxisDown(joystick)) {
			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1DownPressOnce = false;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2DownPressOnce = false;
			}
		}
		if ((getActionButtonState(joystick, BLOCK))
				&& (((joystick == 0)
						&& (!SecuenceInputManager::Instance()->joy1BlockPressOnce))
						|| ((joystick == 1)
								&& (!SecuenceInputManager::Instance()->joy2BlockPressOnce)))) {
			block = CHARACTER_FOR_SPECIAL_MOVE_BLOCK;
			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1BlockPressOnce = true;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2BlockPressOnce = true;
			}
		} else if (!getActionButtonState(joystick, BLOCK)) {
			if (joystick == 0) {
				SecuenceInputManager::Instance()->joy1BlockPressOnce = false;
			} else if (joystick == 1) {
				SecuenceInputManager::Instance()->joy2BlockPressOnce = false;
			}
		}

		if (getActionButtonState(joystick, HIGH_PUNCH)) {
			puckHigh = CHARACTER_FOR_SPECIAL_MOVE_PUNCHHIGH;
		} else if (getActionButtonState(joystick, LOW_PUNCH)) {
			punchLow = CHARACTER_FOR_SPECIAL_MOVE_PUNCHLOW;
		} else if (getActionButtonState(joystick, HIGH_KICK)) {
			kickHigh = CHARACTER_FOR_SPECIAL_MOVE_KICKHIGH;
		} else if (getActionButtonState(joystick, LOW_KICK)) {
			kickLow = CHARACTER_FOR_SPECIAL_MOVE_KICKLOW;
		} else if (getActionButtonState(joystick, FIRE)) {
			fire = CHARACTER_FOR_SPECIAL_MOVE_FIRE;
		}

		secuencia += up + down + left + right + block + fire + kickHigh
				+ kickLow + puckHigh + punchLow;

		if (secuencia.length() > 0) {
			if (joystick == 0) {
				if (!SecuenceInputManager::Instance()->specialSecuenceOneActive) {
					SecuenceInputManager::Instance()->specialSecuenceOneActive =
							true;
				}
				SecuenceInputManager::Instance()->specialSecuenceOne +=
						secuencia;
			} else if (joystick == 1) {
				if (!SecuenceInputManager::Instance()->specialSecuenceTwoActive) {
					SecuenceInputManager::Instance()->specialSecuenceTwoActive =
							true;
				}
				SecuenceInputManager::Instance()->specialSecuenceTwo +=
						secuencia;
			}
		}
	}

}

void InputControl::detectSpecialMove(int joyNum) {

	int specialMove = SecuenceInputManager::Instance()->detectSpecialSecuence(
			joyNum);

	if ((joyNum == 0) && !(specialMove == -1)) {
		if (SecuenceInputManager::Instance()->getIsSetMove(joyNum)) {
			cout << "first player - special move: " << specialMove << "\n";
			if (specialMove == 0) {
				this->firstPlayerMove = SUBZERO_SWEEP;
			} else if (specialMove == 1) {
				this->firstPlayerMove = SPECIAL;
			} else if (specialMove == 2) {
				this->firstPlayerMove = FRIENDSHIP;
			} else if (specialMove == 3) {
				this->firstPlayerMove = BABALITY;
			} else if (specialMove == 4) {
				this->firstPlayerMove = FATALITY;
			}
		}
	} else if ((joyNum == 1) && !(specialMove == -1)) {
		if (SecuenceInputManager::Instance()->getIsSetMove(joyNum)) {
			cout << "second player - special move: " << specialMove << "\n";
			if (specialMove == 0) {
				this->secondPlayerMove = SUBZERO_SWEEP;
			} else if (specialMove == 1) {
				this->secondPlayerMove = SPECIAL;
			} else if (specialMove == 2) {
				this->secondPlayerMove = FRIENDSHIP;
			} else if (specialMove == 3) {
				this->secondPlayerMove = BABALITY;
			} else if (specialMove == 4) {
				this->secondPlayerMove = FATALITY;
			}
		}
	}
}

void InputControl::setPlayerSpecialMove(int joy, int specialMove) {

}

void InputControl::setSecondPlayerMove(InputCommand action) {
	this->secondPlayerMove = action;
}
