#include "../headers/Menu.h"


void Menu::initFlag() {
	//musica desactivada por defecto
	this->music = false;
	this->musicStarted = false;
}

void Menu::createMenuItemList(int no_of_items, std::string * strings, int x, int y, int width, int height) {

	start = new MenuItem(x, y, width, height, strings[0]);
	y = y + height;
	start->previous = NULL;
	MenuItem * temp1 = start;
	MenuItem * temp2 = start;

	int i = 1;
	while (i < no_of_items) {
		temp2 = new MenuItem(x, y, width, height, strings[i]);
		temp1->next = temp2;
		temp2->previous = temp1;
		temp1 = temp2;
		y = y + height;
		i++;
	}

	temp2->next = NULL;
	selected = start;
	selected->setColor(255, 255, 255, 255);
}

void Menu::createGridCharacters(int no_of_items, std::string * strings, int x, int y, int width, int height) {

	start = new MenuItem(x, y, width, height, strings[0]);
	start->setColor(0, 0, 0, 0);
	start->previous = NULL;
	MenuItem * temp1 = start;
	MenuItem * temp2 = start;

	int i = 1;
	int j = 2;
	int auxX = x + width;
	while (i < no_of_items) {
		while (j < 5 && i < no_of_items) {
			temp2 = new MenuItem(auxX, y, width, height, strings[i]);
			temp2->setColor(150, 150, 150, 150);
			temp1->next = temp2;
			temp2->previous = temp1;
			temp1 = temp2;
			auxX = auxX + width;
			i++;
			j++;
		}
		y = y + height;
		auxX = x;
		j = 1;
	}

	temp2->next = NULL;
	selected = start;
	selectedTwo = start->next;
	selectedTwo = selectedTwo->next;
	selectedTwo = selectedTwo->next;
	selected->setColor(0, 255, 0, 255);
	selectedTwo->setColor(255, 0, 0, 255);
}

void Menu::loadBackgroundImage(std::string path) {
	SDL_Surface* pTempSurface = IMG_Load(path.c_str());
	background = SDL_CreateTextureFromSurface(this->render, pTempSurface);
	SDL_FreeSurface(pTempSurface);
}

void Menu::loadSoundEffect(std::string path) {
	sound = Mix_LoadWAV(path.c_str());
}

void Menu::setMusicPath(std::string path) {
	this->musicMenu = Mix_LoadMUS(path.c_str());
	this->music = true;
}

Menu::Menu(int no_of_items, std::string * strings, int start_x, int start_y, int width, int height, SDL_Renderer* rd, bool tm) {
	state = "";
	this->playerOneName = "";
	this->playerTwoName = "";
	this->renderTextOne = false;
	this->renderTextTwo = false;
	this->playerOneSelected = false;
	this->playerTwoSelected = false;
	this->nameOneSet = false;
	this->nameTwoSet = false;
	this->textMenu = tm;
	this->render = rd;

	this->initFlag();

	this->loadSoundEffect("sounds/menu/menumov.ogg");
	selectSoundOne = Mix_LoadWAV("sounds/menu/selectPlayerOne.ogg");
	selectSoundTwo = Mix_LoadWAV("sounds/menu/selectPlayerTwo.ogg");

	if (textMenu)
		this->createMenuItemList(no_of_items, strings, start_x, start_y, width, height);
	else
		this->createGridCharacters(no_of_items, strings, start_x, start_y, width, height);

	this->loadBackgroundImage("images/mk-bg-menu.jpg");
	this->twoCharacters = true;
}

void Menu::draw(SDL_Texture* tx) {
	SDL_Rect destRect;

	destRect.w = GameGUI::getInstance()->getWindow()->getWidthPx();
	destRect.h = GameGUI::getInstance()->getWindow()->getHeightPx();
	destRect.x = 0;
	destRect.y = 0;

	SDL_RenderCopyEx(render, tx, NULL, &destRect, 0, 0,
		SDL_FLIP_NONE);
}

void Menu::loadImgCharacterOne(SDL_Renderer* render) {
	std::string path = "images/" + selected->text + "/stance.png";
	SDL_Surface* pTempSurface = IMG_Load(path.c_str());
	characterOneImg = SDL_CreateTextureFromSurface(this->render, pTempSurface);
	SDL_FreeSurface(pTempSurface);
}

void Menu::loadImgCharacterTwo(SDL_Renderer* render) {
	std::string path = "images/" + selectedTwo->text + "/stance.png";
	SDL_Surface* pTempSurface = IMG_Load(path.c_str());
	characterTwoImg= SDL_CreateTextureFromSurface(this->render, pTempSurface);
	SDL_FreeSurface(pTempSurface);
}

void Menu::drawCharacterStance(SDL_Renderer* render) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = SPRITE_WIDTH / 3;
	srcRect.y = 0;
	srcRect.w = SPRITE_WIDTH / 3;
	srcRect.h = SPRITE_HEIGHT;

	destRect.w = GameGUI::getInstance()->getWindow()->getWidthPx() / 6 * 0.90;
	destRect.h = GameGUI::getInstance()->getWindow()->getHeightPx() * 0.60;
	destRect.x = 0;
	destRect.y = GameGUI::getInstance()->getWindow()->getHeightPx() * 0.30;

	resetCharacterRender(render);

	loadImgCharacterOne(render);
	SDL_RenderCopyEx(render, characterOneImg , &srcRect, &destRect, 0, 0,
		SDL_FLIP_NONE);
	SDL_DestroyTexture(characterOneImg);

	if (twoCharacters) {
		destRect.x = GameGUI::getInstance()->getWindow()->getWidthPx() - destRect.w;
		loadImgCharacterTwo(render);
		SDL_RenderCopyEx(render, characterTwoImg, &srcRect, &destRect, 0, 0,
			SDL_FLIP_HORIZONTAL);
		SDL_DestroyTexture(characterTwoImg);
	}


}

void Menu::show(int alpha) {
	SDL_SetTextureAlphaMod(background, alpha);

	if (alpha != 250)
		this->draw(background);

	MenuItem * temp = start;
	while (temp != 0) {
		if (textMenu) {
			temp->show(render);
			temp = temp->next;
		}
		else {
			this->drawCharacterStance(render);
			temp->drawBox(render);
			temp = temp->next;
		}
	}
}

std::string Menu::clicked(int mouse_x, int mouse_y) {
	MenuItem * next = start;
	while (next != 0) {
		if (next->checkBounds(mouse_x, mouse_y))
			return next->text;
		next = next->next;
	}
	return "None";
}

void Menu::resetCharacterRender(SDL_Renderer* render) {
	int windowsWidthPx = GameGUI::getInstance()->getWindow()->getWidthPx();
	int windowsHeightPx = GameGUI::getInstance()->getWindow()->getHeightPx();
	SDL_Texture* target_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowsWidthPx, windowsHeightPx);
	SDL_SetRenderTarget(render, target_texture);

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = windowsWidthPx;
	dst.h = windowsHeightPx;

	SDL_RenderCopy(render, background, NULL, &dst);
	SDL_RenderPresent(render);
	SDL_SetRenderTarget(render, NULL);
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = windowsWidthPx / 6;
	src.h = windowsHeightPx;
	this->columCharacterOne.x = 0;
	this->columCharacterOne.y = 0;
	this->columCharacterOne.w = windowsWidthPx / 6;
	this->columCharacterOne.h = windowsHeightPx;

	this->columCharacterTwo.x = windowsWidthPx * 5 / 6;
	this->columCharacterTwo.y = 0;
	this->columCharacterTwo.w = windowsWidthPx / 6;
	this->columCharacterTwo.h = windowsHeightPx;

	SDL_RenderCopyEx(render, target_texture, &src, &columCharacterOne, 0, 0,
		SDL_FLIP_NONE);
	src.x = windowsWidthPx * 5 / 6;
	src.y = 0;
	src.w = windowsWidthPx / 6;
	src.h = windowsHeightPx;
	SDL_RenderCopyEx(render, target_texture, &src, &columCharacterTwo, 0, 0,
		SDL_FLIP_NONE);
	SDL_DestroyTexture(target_texture);
}

void Menu::resetNameInputRender(SDL_Renderer* render, int x, int y, int w, int h) {
	SDL_Rect fillRect = { x, y, w, h };
	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(render, &fillRect);
}

void Menu::moveSelectedToNext(MenuItem** item, int cant) {
	for (unsigned int i = 0; i < cant; i++) {
		*item = (*item)->next;
	}
}

void Menu::moveSelectedToPrevious(MenuItem** item, int cant) {
	for (unsigned int i = 0; i < cant; i++) {
		*item = (*item)->previous;
	}
}

void Menu::buttonUp() {
	if (textMenu) {
		if (selected->previous != NULL) {
			Mix_PlayChannel(-1, sound, 0);
			selected->setColor(150, 150, 150, 255);
			selected->show(render);
			moveSelectedToPrevious(&selected, 1);
			selected->setColor(255, 255, 255, 255);
			selected->show(render);
		}
	}
	else {
		if (selected->positionY - selected->height >= start->positionY) {
			Mix_PlayChannel(-1, sound, 0);
			selected->setColor(150, 150, 150, 150);
			selected->drawBox(render);
			moveSelectedToPrevious(&selected, COLUMNS);
			selected->setColor(0, 255, 0, 255);
			this->drawCharacterStance(render);
			selected->drawBox(render);
		}
	}
}

void Menu::buttonDown() {
	if (textMenu) {
		if (selected->next != NULL) {
			Mix_PlayChannel(-1, sound, 0);
			selected->setColor(150, 150, 150, 255);
			selected->show(render);
			moveSelectedToNext(&selected, 1);
			selected->setColor(255, 255, 255, 255);
			selected->show(render);
		}
	}
	else {
		if (selected->positionY + selected->height < start->positionY + start->height * 3) {
			Mix_PlayChannel(-1, sound, 0);
			selected->setColor(150, 150, 150, 150);
			selected->drawBox(render);
			moveSelectedToNext(&selected, COLUMNS);
			selected->setColor(0, 255, 0, 255);
			this->drawCharacterStance(render);
			selected->drawBox(render);
		}
	}
}

void Menu::buttonLeft() {
	if (!textMenu) {
		if (selected->positionX - selected->width >= start->positionX) {
			Mix_PlayChannel(-1, sound, 0);
			selected->setColor(150, 150, 150, 150);
			selected->drawBox(render);
			moveSelectedToPrevious(&selected, 1);
			selected->setColor(0, 255, 0, 255);
			this->drawCharacterStance(render);
			selected->drawBox(render);
		}
	}
}

void Menu::buttonRight() {
	if (!textMenu) {
		if (selected->positionX + selected->width < start->positionX + start->width * 4) {
			Mix_PlayChannel(-1, sound, 0);
			selected->setColor(150, 150, 150, 150);
			selected->drawBox(render);
			moveSelectedToNext(&selected, 1);
			selected->setColor(0, 255, 0, 255);
			this->drawCharacterStance(render);
			selected->drawBox(render);
		}
	}
}
void Menu::buttonW(){
	if (!textMenu) {
		if (selectedTwo->positionY - selectedTwo->height >= start->positionY) {
			Mix_PlayChannel(-1, sound, 0);
			selectedTwo->setColor(150, 150, 150, 150);
			selectedTwo->drawBox(render);
			moveSelectedToPrevious(&selectedTwo, COLUMNS);
			selectedTwo->setColor(255, 0, 0, 255);
			this->drawCharacterStance(render);
			selectedTwo->drawBox(render);
		}
	}
}
void Menu::buttonS(){
	if (!textMenu) {
		if (selectedTwo->positionY + selectedTwo->height < start->positionY + start->height * 3) {
			Mix_PlayChannel(-1, sound, 0);
			selectedTwo->setColor(150, 150, 150, 150);
			selectedTwo->drawBox(render);
			moveSelectedToNext(&selectedTwo, COLUMNS);
			selectedTwo->setColor(255, 0, 0, 255);
			this->drawCharacterStance(render);
			selectedTwo->drawBox(render);
		}
	}
}
void Menu::buttonA(){
	if (!textMenu) {
		if (selectedTwo->positionX - selectedTwo->width >= start->positionX) {
			Mix_PlayChannel(-1, sound, 0);
			selectedTwo->setColor(150, 150, 150, 150);
			selectedTwo->drawBox(render);
			moveSelectedToPrevious(&selectedTwo, 1);
			selectedTwo->setColor(255, 0, 0, 255);
			this->drawCharacterStance(render);
			selectedTwo->drawBox(render);
		}
	}
}
void Menu::buttonD(){
	if (!textMenu) {
		if (selectedTwo->positionX + selectedTwo->width < start->positionX + start->width * 4) {
			Mix_PlayChannel(-1, sound, 0);
			selectedTwo->setColor(150, 150, 150, 150);
			selectedTwo->drawBox(render);
			moveSelectedToNext(&selectedTwo, 1);
			selectedTwo->setColor(255, 0, 0, 255);
			this->drawCharacterStance(render);
			selectedTwo->drawBox(render);
		}
	}
}

void Menu::buttonRETURN() {
	if (textMenu) {
		state = selected->text;
	}
	//Sino finalizo el input del nick
	else {
		if (playerOneSelected && !nameOneSet && playerOneName != "") {
			nameOneSet = true;
		}
		else if (playerTwoSelected && !nameTwoSet && nameOneSet && playerTwoName != "") {
			nameTwoSet = true;
		}
	}
}

void Menu::buttonG() {
	if (textMenu) {
		state = selectedTwo->text;
	}
	else {
		this->playerTwoSelected = true;
		this->playerTwoName = selectedTwo->text;
	}
}

void Menu::buttonJoystickOne() {
	if (textMenu) {
	}
	//Leo nick del jugador 2
	else {
		Mix_PlayChannel(-1, selectSoundOne, 0);
		playerTwoSelected = true;
		renderTextTwo = true;
		playerTwoName = selectedTwo->text;
	}
}

void Menu::buttonJoystickZero() {
	//Seteo estado con el nombre del menu
	if (textMenu) {
		state = selected->text;
	}
	//Leo nick del jugador 1
	else {
		Mix_PlayChannel(-1, selectSoundTwo, 0);
		playerOneSelected = true;
		renderTextOne = true;
		playerOneName = selected->text;
	}
}


void Menu::showTextBox() {
	SDL_Color fColor = { 255, 255, 255, 255 };
	TTF_Font* font = TTF_OpenFont("fonts/MK3.ttf", 30);
	//TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
	float ratioX = TextureManager::Instance()->ratioWidth;
	float ratioY = TextureManager::Instance()->ratioHeight;
	int windowsWidth = GameGUI::getInstance()->getWindow()->getWidthPx() / ratioX;
	int windowsHeight = GameGUI::getInstance()->getWindow()->getHeightPx() / ratioY;
	SDL_Rect rs = { 0, 0, 0, 0 };
	std::string nameMax = "";

	if (renderTextOne)
	{
		//Text is not empty
		if (playerOneName != "")
		{
			//Render new text
			if (playerOneName.length() > MAXLENGHTNAME) {
				nameMax = playerOneName.substr(playerOneName.length() - MAXLENGHTNAME, playerOneName.length());
			}
			else {
				nameMax = playerOneName;
			}
			TextureManager::Instance()->loadFromRenderedText("namePlayerOne", nameMax, fColor, font, render);
			rs = TextureManager::Instance()->queryTexture("namePlayerOne" + nameMax);
		}
		int x = windowsWidth / 6 * 0.10;
		int y = windowsHeight*0.91;
		int width = rs.w / ratioX;
		int height = 40 / ratioY;
		resetNameInputRender(render, x*ratioX, y*ratioY, windowsWidth * ratioX * 0.40,height * ratioY);
		SDL_Rect recuadroColorTexto = { x*ratioX, y*ratioY, windowsWidth * ratioX * 0.40, height * ratioY };
		SDL_SetRenderDrawColor(render, 0, 255, 0, 0xFF);
		SDL_RenderDrawRect(render, &recuadroColorTexto);
		TextureManager::Instance()->draw("namePlayerOne" + nameMax, x, y, width, height, render);
	}

	if (renderTextTwo)
	{
		//Text is not empty
		if (playerTwoName != "")
		{
			//Render new text
			if (playerTwoName.length() > MAXLENGHTNAME) {
				nameMax = playerTwoName.substr(playerTwoName.length() - MAXLENGHTNAME, playerTwoName.length());
			}
			else {
				nameMax = playerTwoName;
			}
			TextureManager::Instance()->loadFromRenderedText("namePlayerTwo", nameMax, fColor, font, render);
			rs = TextureManager::Instance()->queryTexture("namePlayerTwo" + nameMax);
		}
		int x = (windowsWidth - rs.w/ratioX);
		int y = windowsHeight*0.91;
		int width = rs.w / ratioX;
		int height = 40 / ratioY;
		resetNameInputRender(render, (windowsWidth - windowsWidth * 0.4)*ratioX, y*ratioY, windowsWidth * ratioX * 0.40, height * ratioY);
		SDL_Rect recuadroColorTexto = { (windowsWidth - windowsWidth * 0.40)*ratioX, y*ratioY, windowsWidth * ratioX * 0.40, height * ratioY };
		SDL_SetRenderDrawColor(render, 255, 0, 0, 0xFF);
		SDL_RenderDrawRect(render, &recuadroColorTexto);
		TextureManager::Instance()->draw("namePlayerTwo" + nameMax, x, y, width, height, render);

	}

	SDL_RenderPresent(render);
	TTF_CloseFont(font);
}

void Menu::stopMusic() {
	Mix_FadeOutMusic(2000);
	//music = t;
	musicStarted = false;

}

bool Menu::isKey(SDL_Event e, int key) {
	return (e.key.keysym.sym == key);
}

bool Menu::isType(SDL_Event e, int type) {
	return (e.type == type);
}

bool Menu::readKey(SDL_Event e) {
	std::string nameMax = "";
	if (textMenu) {
		if (isKey(e, SDLK_UP)) {
			buttonUp();
		}
		if (isKey(e, SDLK_w)) {
			buttonW();
		}
		if (isKey(e, SDLK_DOWN)) {
			buttonDown();
		}
		if (isKey(e, SDLK_s)) {
			buttonS();
		}
		if (isKey(e, SDLK_LEFT)) {
			buttonLeft();
		}
		if (isKey(e, SDLK_RIGHT)) {
			buttonRight();
		}
		if (isKey(e, SDLK_a)) {
			buttonA();
		}
		if (isKey(e, SDLK_d)) {
			buttonD();
		}
	}

	if (isKey(e, SDLK_RETURN)) {
		buttonRETURN();
		if (textMenu) return true;
	}
	if (isKey(e, SDLK_BACKSPACE)) {
		//Borro un caracter y destruyo la textura anterior
		if (!textMenu)
			if (playerOneSelected && playerTwoSelected && !nameOneSet && playerOneName.length() > 0) {
				if (playerOneName.length() > MAXLENGHTNAME) {
					nameMax = playerOneName.substr(playerOneName.length() - MAXLENGHTNAME, playerOneName.length());
				}
				else {
					nameMax = playerOneName;
				}
				TextureManager::Instance()->unload("namePlayerOne" + nameMax);
				playerOneName.pop_back();
				renderTextOne = true;
			}
			else if (playerTwoSelected && playerTwoSelected && nameOneSet && !nameTwoSet && playerTwoName.length() > 0) {
				if (playerTwoName.length() > MAXLENGHTNAME) {
					nameMax = playerTwoName.substr(playerTwoName.length() - MAXLENGHTNAME, playerTwoName.length());
				}
				else {
					nameMax = playerTwoName;
				}
				TextureManager::Instance()->unload("namePlayerTwo" + nameMax);
				playerTwoName.pop_back();
				renderTextTwo = true;
			}
	}

	return false;
}

bool Menu::readJoystickZero() {
	//Joystick 0
	if (InputControl::Instance()->isAxisUp(0)) {
		buttonUp();
	}
	if (InputControl::Instance()->isAxisDown(0)) {
		buttonDown();
	}
	if (InputControl::Instance()->isAxisLeft(0)) {
		buttonLeft();
	}
	if (InputControl::Instance()->isAxisRight(0)) {
		buttonRight();
	}
	if (InputControl::Instance()->someJoyKickButtonPressed(0)) {
		buttonJoystickZero();
		InputControl::Instance()->setActionButtonStateFalse(0, LOW_KICK);
		InputControl::Instance()->setActionButtonStateFalse(0, HIGH_KICK);
		return true;
	}
	return false;
}

bool Menu::readJoystickOne() {
	//Joystick 1
	if (InputControl::Instance()->isAxisUp(1)) {
		buttonW();
	}
	if (InputControl::Instance()->isAxisDown(1)) {
		buttonS();
	}
	if (InputControl::Instance()->isAxisLeft(1)) {
		buttonA();
	}
	if (InputControl::Instance()->isAxisRight(1)) {
		buttonD();
	}
	if (InputControl::Instance()->someJoyKickButtonPressed(1)) {
		buttonJoystickOne();
		InputControl::Instance()->setActionButtonStateFalse(1, LOW_KICK);
		InputControl::Instance()->setActionButtonStateFalse(1, HIGH_KICK);
		return true;
	}
	return false;
}

bool Menu::readMouseMotion() {
	MenuItem* aux = start;
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (textMenu) {
		for (unsigned int i = 0; i < ROWS * COLUMNS; i++) {
			if (aux->checkBounds(x, y) && selected != aux) {
				Mix_PlayChannel(-1, sound, 0);
				selected->setColor(150, 150, 150, 255);
				selected->show(render);
				selected = aux;
				selected->setColor(255, 255, 255, 255);
				selected->show(render);
			}
			else if (aux->next){
				aux = aux->next;
			}
		}
	}
	else if (!textMenu && !playerOneSelected) {
		for (unsigned int i = 0; i < ROWS * COLUMNS; i++) {
			if (aux->checkBounds(x, y) && selected != aux) {
				Mix_PlayChannel(-1, sound, 0);
				selected->setColor(150, 150, 150, 150);
				selected->drawBox(render);
				selected = aux;
				selected->setColor(0, 255, 0, 255);
				this->drawCharacterStance(render);
				selected->drawBox(render);
				return true;
			}
			else
			if (aux->next){
				aux = aux->next;
			}
		}
		return false;
	}
	else if (!textMenu && playerOneSelected && !playerTwoSelected && twoCharacters) {
		for (unsigned int i = 0; i < ROWS * COLUMNS; i++) {
			if (aux->checkBounds(x, y) && selectedTwo != aux) {
				Mix_PlayChannel(-1, sound, 0);
				selectedTwo->setColor(150, 150, 150, 150);
				selectedTwo->drawBox(render);
				selectedTwo = aux;
				selectedTwo->setColor(255, 0, 0, 255);
				this->drawCharacterStance(render);
				selectedTwo->drawBox(render);
			}
			else
			if (aux->next){
				aux = aux->next;
			}
			
		}
	}
}

bool Menu::readMouseButton(SDL_Event event) {
	MenuItem* aux = start;
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (textMenu && (event.button.button == SDL_BUTTON_LEFT)) {
		for (unsigned int i = 0; i < ROWS * COLUMNS; i++) {
			if (aux->checkBounds(x, y)) {
				selected = aux;
				state = selected->text;
			}
			else
			if (aux->next){
				aux = aux->next;
			}
		}
	}
	else if (!textMenu && (event.button.button == SDL_BUTTON_LEFT) && !playerOneSelected) {
		for (unsigned int i = 0; i < ROWS * COLUMNS; i++) {
			if (aux->checkBounds(x, y)) {
				selected = aux;
				Mix_PlayChannel(-1, selectSoundOne, 0);
				playerOneSelected = true;
				renderTextOne = true;
				playerOneName = selected->text;
				return true;
			}
			else
			if (aux->next){
				aux = aux->next;
			}	
		}
		return false;
	}
	else if (!textMenu && (event.button.button == SDL_BUTTON_LEFT) && playerOneSelected && !playerTwoSelected && twoCharacters) {
		for (unsigned int i = 0; i < ROWS * COLUMNS; i++) {
			if (aux->checkBounds(x, y)) {
				selectedTwo = aux;
				Mix_PlayChannel(-1, selectSoundTwo, 0);
				playerTwoSelected = true;
				renderTextTwo = true;
				playerTwoName = selectedTwo->text;
			}
			else if (aux->next){
				aux = aux->next;
			}
			
		}
	}
}

std::string Menu::identify_event() {
	if (music && !musicStarted) {
		Mix_PlayMusic(musicMenu, -1);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
		musicStarted = true;
	}

	playerOneSelected = false;
	playerTwoSelected = false;
	nameOneSet = false;
	nameTwoSet = false;
	if (!twoCharacters) {
		nameTwoSet = true;
		selectedTwo->setColor(150, 150, 150, 150);
		selectedTwo->drawBox(render);
		playerTwoSelected = true;
	}
	renderTextOne = false;
	renderTextTwo = false;

	SDL_Event event;
	SDL_StartTextInput();
	while (1) {
		while (SDL_PollEvent(&event)) {

			//Reseteo el input

			//Fin del juego devuelvo el estado EXIT
			if (isType(event, SDL_QUIT))
				return "Exit";

			//MENU PLAYERS: Si ambos jugadores completaron su nombre devuelvo string con estado: nombres y nikcs de ambos
			if (nameOneSet && nameTwoSet) {
				SDL_StopTextInput();
				if (playerOneName.length() > MAXLENGHTNAME) playerOneName = playerOneName.substr(0, MAXLENGHTNAME);
				if (playerTwoName.length() > MAXLENGHTNAME) playerTwoName = playerTwoName.substr(0, MAXLENGHTNAME);
				InputControl::Instance()->setActionButtonStateFalse(1, QUIT);
				InputControl::Instance()->setActionButtonStateFalse(0, QUIT);
				if (twoCharacters)
					return "selected: " + selected->text + " " + selectedTwo->text + " " + playerOneName + " " + playerTwoName;
				else 
					return "selected: " + selected->text + " " + "xxxx" + " " + playerOneName + " " + "xxxx";
			}

			//Leo input jugador 1
			if (isType(event, SDL_TEXTINPUT) && !nameOneSet && !isKey(event, SDLK_BACKSPACE) && !isKey(event, SDLK_RETURN)
				&& (playerOneSelected && playerTwoSelected)) {
				TextureManager::Instance()->unload("namePlayerOne" + playerOneName);
				playerOneName += event.text.text;
				renderTextOne = true;
			}

			//Leo input jugador 2, lee una ves que esta seteado el primero input
			else if (isType(event, SDL_TEXTINPUT) && !nameTwoSet && nameOneSet && !isKey(event, SDLK_BACKSPACE) &&
				!isKey(event, SDLK_RETURN) && (playerOneSelected && playerTwoSelected) && twoCharacters) {
				TextureManager::Instance()->unload("namePlayerTwo" + playerTwoName);
				playerTwoName += event.text.text;
				renderTextTwo = true;
			}


			//Leo teclado y devuelvo un string con el estado
			else if (isType(event, SDL_KEYDOWN)) {
				if (readKey(event))
					return state;
			}

			//Leo movimientos del joystick
			else if (isType(event, SDL_JOYAXISMOTION) || isType(event, SDL_JOYBUTTONDOWN)) {
				this->getJoystickInput(event);
				if (textMenu) {
					if (readJoystickZero()) return state;
				}
				//Si no, selecciono jugadores
				else {
					if (twoCharacters) {
					readJoystickZero();
					readJoystickOne();
					}
					else {
						readJoystickZero();
					}

				}

			}

			//Leo movimientos del mouse
			else if (isType(event, SDL_MOUSEMOTION)) {
				readMouseMotion();
			}

			//Leo boton del mouse
			else if (isType(event, SDL_MOUSEBUTTONDOWN)) {
				readMouseButton(event);
				if (textMenu) {
					return state;
				}
			}

			//Muestro cuadros de texto para el input
			showTextBox();
		}
	}
}


Menu::~Menu() {
	delete this->start;
}


void Menu::getJoystickInput(SDL_Event event) {
	if (event.type == SDL_JOYBUTTONDOWN) {
		InputControl::Instance()->joysticksButtonStates[event.jaxis.which][event.jbutton.button] = true;
	}
	if (event.type == SDL_JOYBUTTONUP) {
		InputControl::Instance()->joysticksButtonStates[event.jaxis.which][event.jbutton.button] = false;
	}
	if (event.type == SDL_JOYAXISMOTION){

		int num_joy = event.jaxis.which;

		//derecha e izquierda
		if (event.jaxis.axis == 0) {

			if (event.jaxis.value > MAX_XAXIS || event.jaxis.value < MIN_XAXIS) {
				InputControl::Instance()->joystickAxisStates[num_joy].first = event.jaxis.value;
			}
			else {
				InputControl::Instance()->joystickAxisStates[num_joy].first = 0;
			}

		}

		//arriba y abajo
		if (event.jaxis.axis == 1) {

			if (event.jaxis.value > MAX_YAXIS || event.jaxis.value < MIN_YAXIS){
				InputControl::Instance()->joystickAxisStates[num_joy].second = event.jaxis.value;
			}
			else {
				InputControl::Instance()->joystickAxisStates[num_joy].second = 0;
			}

		}

	}
}
