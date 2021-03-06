#ifndef MENU_H
#define MENU_H

#define RATIOBOX 81
#define WIDTHBOX 48
#define HEIGHTBOX 59
#define ROWS 3
#define COLUMNS 4
#define MAXLENGHTNAME 10

#include "MenuItem.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "GameGUI.h"
#include "Constants.h"
#include "InputControl.h"
//#include <vld.h> 


class Menu
{
public:
	Menu(int no_of_items, std::string * strings, int start_x, int start_y, int width, int height, SDL_Renderer*, bool textMenu);
	void show(int alpha);
	//true 2 personajes false 1 personaje
	std::string identify_event();
	virtual ~Menu();
	std::string clicked(int mouse_x, int mouse_y);
	SDL_Renderer* render;
	bool music;
	void setMusicPath(std::string);
	void buttonUp();
	void buttonDown();
	void buttonRight();
	void buttonLeft();
	void buttonW();
	void buttonS();
	void buttonA();
	void buttonD();
	void buttonRETURN();
	void buttonG();
	void buttonJoystickZero();
	void buttonJoystickOne();
	void stopMusic();
	bool twoCharacters;

private:
	//Estado del Menu, se retorna al detectarse un evento
	std::string state;

	//Items Menu para ciclar
	MenuItem * start;
	MenuItem * selected;
	MenuItem * selectedTwo;

	//Estructuras auxiliares
	SDL_Texture * background;
	Mix_Chunk * sound;
	Mix_Chunk * selectSoundOne;
	Mix_Chunk * selectSoundTwo;
	Mix_Music * musicMenu;
	SDL_Rect columCharacterOne;
	SDL_Rect columCharacterTwo;
	SDL_Texture* characterOneImg;
	SDL_Texture* characterTwoImg;

	bool musicStarted;
	void draw(SDL_Texture*);
	void initFlag();
	bool textMenu;
	void createMenuItemList(int nItems, std::string * strings, int x, int y, int width, int height);
	void createGridCharacters(int nItems, std::string * strings, int x, int y, int width, int height);
	void loadBackgroundImage(std::string path);
	void loadSoundEffect(std::string path);
	void drawCharacterStance(SDL_Renderer*);
	void resetCharacterRender(SDL_Renderer*);
	void loadImgCharacterOne(SDL_Renderer*);
	void loadImgCharacterTwo(SDL_Renderer*);
	bool playerOneSelected;
	bool playerTwoSelected;
	void getJoystickInput(SDL_Event event);
	void showTextBox();
	string playerOneName;
	string playerTwoName;
	bool renderTextOne;
	bool renderTextTwo;
	bool nameOneSet;
	bool nameTwoSet;
	void resetNameInputRender(SDL_Renderer*, int, int, int, int);
	bool isKey(SDL_Event e, int key);
	bool isType(SDL_Event e, int key);
	bool readKey(SDL_Event);
	bool readJoystickZero();
	bool readJoystickOne();
	bool readMouseMotion();
	bool readMouseButton(SDL_Event);
	void moveSelectedToNext(MenuItem** item, int cant);
	void moveSelectedToPrevious(MenuItem** item, int cant);


};

#endif // MENU_H
