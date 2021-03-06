/*
 * MKGame.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/MKGame.h"
#include "../headers/SecuenceInputManager.h"

using namespace std;


MKGame* MKGame::mk_pInstance = NULL;

MKGame* MKGame::Instance() {
	if (!mk_pInstance) {
		mk_pInstance = new MKGame();
		return mk_pInstance;
	} else {
		return mk_pInstance;
	}
}

bool MKGame::init(GameGUI* gameGui) {
	this->setOffReset();
	this->gameGui = gameGui;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		FILE_LOG(logDEBUG) << "SDL init success";


		InputControl::Instance()->initJoysticks();


		Window* gameWindow = this->gameGui->getWindow();
		m_pWindow = SDL_CreateWindow(gameWindow->title, gameWindow->xpos,
				gameWindow->ypos, gameWindow->widthPx, gameWindow->heightPx, 0);
		if (m_pWindow != 0) {
			FILE_LOG(logDEBUG) << "window creation success";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if (m_pRenderer != 0) {
				FILE_LOG(logDEBUG) << "renderer creation success";

				/*vector<SDLObjectGUI*> objects = getObjectList();
				for (unsigned int i = 0; i < objects.size(); i++) {
					SDLObjectGUI* object = objects[i];
					objects[i]->load(m_pRenderer);
				}*/
				//SecuenceInputManager::Instance()->load();
			} else {
				FILE_LOG(logERROR) << "renderer init fail";
				return false;
			}
		} else {
			FILE_LOG(logERROR) << "window init fail";
			return false;
		}
	} else {
		FILE_LOG(logERROR) << "SDL init fail";
		return false;
	}

    if( TTF_Init() == -1 ) {
    	FILE_LOG(logERROR) << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
    }else{
    	SecuenceInputManager::Instance()->load();
    }

	/*if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		FILE_LOG(logERROR) << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError();
	}
*/
	//agregar menus dentro de este metodo
	this->menuInit();

	FILE_LOG(logDEBUG) << "init success";
	m_bRunning = true;
	showFatality = false;
	showBabality = false;
	showFriendship = false;
	isFinishimMoment = false;
	lazyAnimationAlreadyTriggered = false;
	SecuenceInputManager::Instance()->fatalityTime = false;
	return true;
}

void MKGame::menuInit() {
	// Inicializacion de Menus
	//string menuItemsMK[] = { "New Game", "Credits", "Exit" };
	string menuItemsMK[] = { "New Game", "Exit" };
	string menuItemsNewGame[] = { "P1 vs P2", "P1 vs CPU", "Practice Mode", "Go Back" };
	string menuItemsCharacters[] = {
		"subzero", "liukang", "cyrax", "scorpion",
		"jax", "kabal", "kano", "kunglao",
		"scorpion", "motaro", "sektor", "subzero" };

	//nro de items, string con items, posX, posY, width, height, render
	//Menu principal
	menuMk = new Menu(2, menuItemsMK, 50, 150, 150, 50, m_pRenderer, true);
	menuMk->setMusicPath("sounds/menu-music.ogg");

	//Menu seleccion de modo de pelea
	menuNewGame = new Menu(4, menuItemsNewGame, 50, 150, 150, 50, m_pRenderer, true);

	//Menu seleccion de personaje
	int widthSelectBox = GameGUI::getInstance()->getWindow()->getWidthPx() / 8;
	float heightSelectBox = widthSelectBox * 59 / 48;
	int posX = GameGUI::getInstance()->getWindow()->getWidthPx()/2 - widthSelectBox*4/2;
	int posY = GameGUI::getInstance()->getWindow()->getHeightPx() * 0.15;
	menuCharacterSelect = new Menu(12, menuItemsCharacters, posX, posY, widthSelectBox, (int)heightSelectBox, m_pRenderer, false);

	//Arranco con el menu principal
	menuPpal = true;
	menuGame = false;
	menuCharacter = false;
	menuIA = false;
	practiceMode = false;

}

bool compareSDLObjectGUI(SDLObjectGUI* a, SDLObjectGUI* b) {
	return (a->getZIndex() < b->getZIndex());
}

void MKGame::render() {
	SDL_RenderClear(m_pRenderer);
	vector<SDLObjectGUI*> objects = this->getObjectList();
	std::stable_sort (objects.begin(), objects.end(), compareSDLObjectGUI);

	for (std::vector<SDLObjectGUI*>::iterator it=objects.begin(); it!=objects.end(); ++it) {
		(*it)->draw();
		(*it)->setPositionY((*it)->getPositionY() - this->offSetPosY);
	}

	SecuenceInputManager::Instance()->draw();
	SDL_RenderPresent(m_pRenderer);
}


void MKGame::clean() {
	FILE_LOG(logDEBUG) << "cleaning game\n";


	std::for_each(objectList.begin(),objectList.end(),delete_pointer_to<SDLObjectGUI>);
	objectList.clear();

	LayerManager::Instance()->clean();
	InputControl::Instance()->clean();
	GameGUI::getInstance()->clean();
	AIMovement::Instance()->clean();
	SoundManager::Instance()->clean();

	TextureManager::Instance()->resetInstance();
	SDL_DestroyRenderer(this->m_pRenderer);
	SDL_DestroyWindow(this->m_pWindow);

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	this->m_bReset = false;
	this->shouldBeShaking = true;
	this->offSetPosY = 0;
	
	delete(menuMk);
	delete(menuNewGame);
	delete(menuCharacterSelect);
}

void MKGame::draw() {
	for (std::vector<SDLObjectGUI*>::size_type i = 0; i != objectList.size();
			i++) {
		objectList[i]->draw();
	}
}

void MKGame::drawMenu(Menu* menu, int opacity) {
	SDL_RenderClear(m_pRenderer);
	menu->show(opacity);
	SDL_RenderPresent(m_pRenderer);
}

void createGameInfo(Window* window, vector<Character*> characters, std::string nameOne, std::string nameTwo, float ratioX, float ratioY) {
	float windowWidth = window->getWidth();
	float windowHeight = window->getHeightPx();
	/*
	vector<string> playerName;
	for(unsigned int i = 0; i < characters.size(); ++i ) {
		playerName.push_back(characters[i]->getName());
	}*/
	LoaderParams* params = new LoaderParams(WINDOW_MARGIN, 0, windowWidth, windowHeight * 0.10 , 100, ratioX, ratioY, "gameInfo");
	GameInfo* info = new GameInfo(params, characters, nameOne, nameTwo);
	MKGame::Instance()->getObjectList().push_back(info);
}

void createThrowableObject(vector<Character*> characters, Window* window, float ratioX, float ratioY) {
	float windowWidth = window->getWidth();
	float throwableHeight1 = characters[0]->getHeight();
	float throwableHeight2 = characters[1]->getHeight();

	LoaderParams* params1 = new LoaderParams(100, 100, throwableHeight1 * 0.1,  throwableHeight1 * 0.1 , characters[0]->getZIndex(), ratioX, ratioY, "throwable1");
	LoaderParams* params2 = new LoaderParams(100, 100, throwableHeight2 * 0.1,  throwableHeight2 * 0.1 , characters[1]->getZIndex(), ratioX, ratioY, "throwable2");
	ThrowableObject* tObject1 = new ThrowableObject(params1, windowWidth);
	ThrowableObject* tObject2 = new ThrowableObject(params2, windowWidth);

	tObject1->setReleaser(characters[0]);
	tObject1->setReceiver(characters[1]);
	tObject1->setImagePath("images/subzero/throwable.gif");
	MKGame::Instance()->getObjectList().push_back(tObject1);


	tObject2->setReleaser(characters[1]);
	tObject2->setReceiver(characters[0]);
	tObject2->setImagePath("images/subzero/throwable.gif");
	MKGame::Instance()->getObjectList().push_back(tObject2);


	GameGUI::getInstance()->vCollitionable.push_back(characters[0]);
	GameGUI::getInstance()->vCollitionable.push_back(characters[1]);
	GameGUI::getInstance()->vCollitionable.push_back(tObject1);
	GameGUI::getInstance()->vCollitionable.push_back(tObject2);
}

void MKGame::configureFight(std::string fighterOneName, std::string fighterTwoName, std::string nameOne, std::string nameTwo) {
	Character* fighterOne;
	Character* fighterTwo;
	vector<Character*> characters = GameGUI::getInstance()->getCharacters();
	Fight* fight = new Fight();

	for (unsigned int index=0; index<characters.size(); index++) {
		Character* character = characters[index];
		if (character->getName() == fighterOneName) {
			fighterOne = character->getCopyInstance();
		}
		if (character->getName() == fighterTwoName) {
			fighterTwo = character->getCopyInstance();
		}
	}

	fighterOne->setPlayerNumber("1");
	fighterOne->setPositionX(GameGUI::getInstance()->getWindow()->widthPx / 4 - fighterOne->getWidth() * fighterOne->getRatioX()/2);
	fight->setFighterOne(fighterOne);
	fighterTwo->setPlayerNumber("2");
	fighterTwo->setPositionX((GameGUI::getInstance()->getWindow()->widthPx / 4)*3 -  fighterTwo->getWidth() * fighterTwo->getRatioX()/2);
	fight->setFighterTwo(fighterTwo);

	GameGUI::getInstance()->setFight(fight);
	if (fight->getFighterOne()->getName() == fight->getFighterTwo()->getName()) {
		fight->getFighterTwo()->setIsAlternativePlayer(true);
	}
	fight->getFighterOne()->setIsRightOriented(true);
	MKGame::Instance()->getObjectList().push_back(fight->getFighterOne());
	MKGame::Instance()->getObjectList().push_back(fight->getFighterTwo());


	vector<Character*> fightingCharacters;
	fightingCharacters.push_back(fight->getFighterOne());
	fightingCharacters.push_back(fight->getFighterTwo());
	GameGUI::getInstance()->setCharacters(fightingCharacters);
	createGameInfo(GameGUI::getInstance()->getWindow(), fightingCharacters, nameOne, nameTwo,
			TextureManager::Instance()->ratioWidth, TextureManager::Instance()->ratioHeight);
	createThrowableObject(fightingCharacters, GameGUI::getInstance()->getWindow(),
			TextureManager::Instance()->ratioWidth, TextureManager::Instance()->ratioHeight);

	vector<SDLObjectGUI*> objects = getObjectList();
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i]->load(m_pRenderer);
	}
	//MKGame::Instance()->init(GameGUI::getInstance());
}

//obtengo un player aleatorio
std::string MKGame::randomCharacter(vector<string> characters) {
	std::cout << characters.size();
	srand(time(NULL));
	int index = (rand() % characters.size());
	return characters[index];
}


//Agregar eventos de los menus en este metodo
void MKGame::menuActions(std::string action) {
	if (action == "Exit") {
		this->quit();
	}
	if (action == "New Game") {
		this->menuPpal = false;
		this->menuCharacter = false;
		this->menuGame = true;
	}
	if (action == "Go Back") {
		this->menuPpal = true;
		this->menuCharacter = false;
		this->menuGame = false;
	}
	if (action == "P1 vs P2") {
		this->menuPpal = false;
		this->menuGame = false;
		this->menuCharacter = true;
		this->menuCharacterSelect->twoCharacters = true;
		SecuenceInputManager::Instance()->drawSecuenceOne = false;
		SecuenceInputManager::Instance()->drawSecuenceTwo = false;
	}

	std::size_t found = action.find("selected:");
	if (found != std::string::npos) {


		vector<string> characters;
		std::istringstream iss(action);
		std::string token;
		while (std::getline(iss, token, ' '))
		{
			characters.push_back(token);
		}
		if (this->menuCharacterSelect->twoCharacters == true) {
			if ((characters[1] == "scorpion" || characters[1] == "subzero") && (characters[2] == "scorpion" || characters[2] == "subzero")) {
				this->menuPpal = false;
				this->menuGame = false;
				this->menuCharacter = false;
				this->configureFight(characters[1], characters[2], characters[3], characters[4]);
				this->menuMk->stopMusic();
			}
		}
		else {
			vector<string> chDisponibles;
			chDisponibles.push_back("scorpion");
			chDisponibles.push_back("subzero");
			string randCh = randomCharacter(chDisponibles);
			if (characters[1] == "scorpion" || characters[1] == "subzero") {
				this->menuPpal = false;
				this->menuGame = false;
				this->menuCharacter = false;
				this->configureFight(characters[1], randCh, characters[3], randCh);
				this->menuMk->stopMusic();
			}

		}
	}

	if (action == "P1 vs CPU") {
		this->menuIA = true;
		this->menuPpal = false;
		this->menuGame = false;
		this->menuCharacter = true;
		this->menuCharacterSelect->twoCharacters = false;
		SecuenceInputManager::Instance()->drawSecuenceOne = false;
		SecuenceInputManager::Instance()->drawSecuenceTwo = false;
	}

	if (action == "Jugar IA") {
		this->menuPpal = false;
		this->menuGame = false;
		this->menuCharacter = false;
		this->menuIA = true;
		this->configureFight("subzero", "scorpion", "menem", "de la rua");
		this->menuMk->stopMusic();
		this->menuCharacterSelect->twoCharacters = false;
		SecuenceInputManager::Instance()->drawSecuenceOne = false;
		SecuenceInputManager::Instance()->drawSecuenceTwo = false;
	}

	if (action == "Jugar") {
		this->menuPpal = false;
		this->menuGame = false;
		this->menuCharacter = false;
		this->menuIA = false;
		this->configureFight("subzero", "scorpion", "menem", "de la rua");
		this->menuMk->stopMusic();
		this->menuCharacterSelect->twoCharacters = false;
		SecuenceInputManager::Instance()->drawSecuenceOne = false;
		SecuenceInputManager::Instance()->drawSecuenceTwo = false;
	}

	if (action == "Practice Mode") {
		SecuenceInputManager::Instance()->drawSecuenceOne = true;
		SecuenceInputManager::Instance()->drawSecuenceTwo = true;
		this->menuPpal = false;
		this->menuGame = false;
		this->menuCharacter = true;
		this->menuIA = false;
		this->menuCharacterSelect->twoCharacters = false;
		this->practiceMode = true;

	}
}

bool MKGame::menu() {
	std::string action = "";
	if (menuPpal || menuGame || menuCharacter) {
		if (menuPpal) {
			drawMenu(this->menuMk, 255);
			action = menuMk->identify_event();
		}
		if (menuGame) {
			drawMenu(this->menuNewGame, 255);
			action = menuNewGame->identify_event();
		}
		if (menuCharacter) {
			drawMenu(this->menuCharacterSelect, 255);
			action = menuCharacterSelect->identify_event();
		}
	}
	this->menuActions(action);
//	bool isMenuActive = (menuPpal || menuGame || menuCharacter);
//	if (!isMenuActive)
	return (menuPpal || menuGame || menuCharacter);
}

vector<Collitionable*> convertVector(vector<Character*> oldVec){
	vector<Collitionable*> newVec;
	for (std::vector<Character*>::size_type i = 0; i != oldVec.size(); i++) {
		newVec.push_back((Collitionable*) oldVec[i]);
	}
	return newVec;
}
void addVector(vector<ThrowableObject*> oldVec, vector<Collitionable*> *newVec){
	for (std::vector<ThrowableObject*>::size_type i = 0; i != oldVec.size(); i++) {
		newVec->push_back((Collitionable*) oldVec[i]);
	}
}

void MKGame::update() {
	if (shouldBeShaking) {
		this->offSetPosY = (rand() % shakeIntensity) - 0.5f;
		shakeLength--;
		if (shakeLength <= 0) {
			shouldBeShaking = false;
			shakeLength = 10;
			shakeIntensity = 5;
			this->offSetPosY = 0;
		}
	}
	for (std::vector<SDLObjectGUI*>::size_type i = 0; i != objectList.size();
			i++) {
		LayerManager::Instance()->refresh();
		objectList[i]->update();
		objectList[i]->setPositionY(objectList[i]->getPositionY() + this->offSetPosY);
	}

	//GameGUI* pgamegui = this->getGameGUI();
	//metemos caracteres
	//vector<Collitionable*> collObjects = convertVector(this->getGameGUI()->getCharacters());
	//metemos arrojables
	//vector<ThrowableObject*> throObjects= this->getGameGUI()->tObjects;
	//addVector(throObjects, &collObjects);

	CollitionManager::Instance()->solveCollitions(this->getGameGUI()->vCollitionable);
	SecuenceInputManager::Instance()->update();

}
void MKGame::getJoystickInput(SDL_Event event) {
	if (event.type == SDL_JOYBUTTONDOWN ) {
		InputControl::Instance()->joysticksButtonStates[event.jaxis.which][event.jbutton.button] = true;
	}
	if (event.type == SDL_JOYBUTTONUP ) {
		InputControl::Instance()->joysticksButtonStates[event.jaxis.which][event.jbutton.button] = false;
	}
	if (event.type == SDL_JOYAXISMOTION ){

		int num_joy = event.jaxis.which;

		//derecha e izquierda
		if (event.jaxis.axis == 0) {

			if (event.jaxis.value > MAX_XAXIS || event.jaxis.value < MIN_XAXIS) {
				InputControl::Instance()->joystickAxisStates[num_joy].first = event.jaxis.value;
			} else {
				InputControl::Instance()->joystickAxisStates[num_joy].first = 0;
			}

		}

		//arriba y abajo
		if (event.jaxis.axis == 1) {

			if (event.jaxis.value > MAX_YAXIS || event.jaxis.value < MIN_YAXIS){
				InputControl::Instance()->joystickAxisStates[num_joy].second = event.jaxis.value;
			} else {
				InputControl::Instance()->joystickAxisStates[num_joy].second = 0;
			}

		}

	}


}


void MKGame::handleEvents() {
	SDL_Event event;
	bool reset = false;
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			MKGame::Instance()->quit();
		}
		//if (this->allowPlayerMovements) {
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r && event.key.repeat == 0) {
				reset = true;
			}

			MKGame::getJoystickInput(event);
			//InputControl::Instance()->update();

			//Para solo jugar con joysticks comentar todos

			// Para teclado y joystick descomentar el siguiente
			InputControl::Instance()->refreshInputs();

			//Para jugar 2 con teclado usar estos 2
			//InputControl::Instance()->refreshInputs1();
			//InputControl::Instance()->refreshInputs2();
		/*} else  {
			if (int a = SDL_NumJoysticks() > 1) {
				for (int i = 0 ; i < a; ++i ) {
					InputControl::Instance()->joystickAxisStates[i].first = 0;
					InputControl::Instance()->joystickAxisStates[i].second = 0;
					for (int j = 0 ; j < 10 ; j++) {
						InputControl::Instance()->joysticksButtonStates[i][j] = false;
					}

				}
				InputControl::Instance()->refreshJoystickInputs();

			}

		}*/

	}

	for ( unsigned int a = 0; a < InputControl::Instance()->joysticks.size() ; ++a) {
		if (InputControl::Instance()->getActionButtonState(a, QUIT) ) reset = true;
	}

	if (InputControl::Instance()->joysticks.size() > 0 && SDL_NumJoysticks() > 0)
		InputControl::Instance()->refreshJoystickInputs();

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r && event.key.repeat == 0) {
		reset = true;
	}


	if (reset == true){
		MKGame::Instance()->setOnReset();
	}


}


void MKGame::handleAI() {
	if ( !AIMovement::Instance()->isInitialized) AIMovement::Instance()->init();
	AIMovement::Instance()->solveAIMovement();
}

void MKGame::quit(){
	this->m_bRunning = false;
}

vector<SDLObjectGUI*>& MKGame::getObjectList() {
	return objectList;
}

GameGUI* MKGame::getGameGUI(){
	return gameGui;
}

void MKGame::setShaking(bool shaking) {
	this->shouldBeShaking = shaking;
}
