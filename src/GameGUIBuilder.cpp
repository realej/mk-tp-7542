/*
 * StageBuilder.cpp
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#include "../headers/GameGUIBuilder.h"
#include <cstdlib>

using namespace std;

GameGUIBuilder::GameGUIBuilder() {
	// TODO Auto-generated constructor stub

}

GameGUIBuilder::~GameGUIBuilder() {
	// TODO Auto-generated destructor stub
}

bool fileExists(const char *s)
{
	ifstream archivo(s, std::ifstream::binary);

	if (archivo.good()) {
		return true;
	}else{
		FILE_LOG(logERROR) << "File not found: " << s;
		return false;
	}
}

float getRatio(int dimPx, int dimLg, std::string type) {
	float ratio = dimPx / dimLg;
	if (type == "X"){
		FILE_LOG(logDEBUG) << "RatioX (window_width_px / window_width_lg): " << ratio;
	}else if (type == "Y"){
		FILE_LOG(logDEBUG) << "RatioY (window_height_px / stage_height_lg): " << ratio;
	}
	return ratio;
}

Window jsonGetWindow(Json::Value root) {

	FILE_LOG(logDEBUG) << "WINDOW CONFIGURATION";
	Json::Value windowValue = root[JSON_KEY_VENTANA];
	int win_width_px;
	int win_height_px;
	int win_width;
	try {
		 string strValue = windowValue.get(JSON_KEY_ANCHOPX, "").asString();
	     win_width_px = atoi(strValue.c_str());
	     FILE_LOG(logDEBUG) << "JSON - Window width: " << strValue << " px";
	}catch(std::exception const & e){
		win_width_px=0;
	}
	try {
		 string strValue = windowValue.get(JSON_KEY_ALTOPX, "").asString();
		 win_height_px = atoi(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Window height: " << strValue << " px";
	}catch(std::exception const & e){
		win_height_px=0;
	}
	try {
		 string strValue = windowValue.get(JSON_KEY_ANCHO, 0).asString();
		 win_width = atoi(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Window width: " << strValue;
	}catch(std::exception const & e){
		win_width=0;
	}

	//validaciones de parametros para ventana
	bool widthPxOk = ((win_width_px>0) && (win_width_px <=MAX_WINDOW_WIDTH_PX));
	bool heightPxOk = ((win_height_px>0) && (win_height_px <=MAX_WINDOW_HEIGHT_PX));
	bool widthOk =(win_width_px>0);
	if (!widthOk || !widthPxOk || !heightPxOk){
			if (!(win_width>0)){
				FILE_LOG(logWARNING) << "Window logical width out of range or inexistent. Set by default: " <<DEFAULT_WINDOW_WIDTH;
				win_width = DEFAULT_WINDOW_WIDTH;
			}
			if (!widthPxOk) {
				win_width_px=DEFAULT_WINDOW_WIDTH_PX;
				FILE_LOG(logWARNING) << "Window width px out of range or inexistent (" <<"0 - "<< MAX_WINDOW_WIDTH_PX<<"). Set to default:"<<DEFAULT_WINDOW_WIDTH_PX<<" px";
			}
			if (!heightPxOk){
				win_height_px=DEFAULT_WINDOW_HEIGHT_PX;
				FILE_LOG(logWARNING) << "Window height px out of range or inexistent (" <<"0 - "<< MAX_WINDOW_HEIGHT_PX<<"). Set to default:"<<DEFAULT_WINDOW_HEIGHT_PX<<" px";
			}
			FILE_LOG(logWARNING) << "Window size set to: (" << win_width_px<<"-"<<win_height_px<<")";
	}
	//set de posiciones para centrado de ventana en pantalla
	int windowXpos = ((MAX_WINDOW_WIDTH_PX-win_width_px)/2);
	int windowYpos = ((MAX_WINDOW_HEIGHT_PX-win_height_px)/2);

	Window window(GAME_TITLE, windowXpos, windowYpos, win_width_px, win_height_px, win_width);
	return window;
}

Stage jsonGetStage(Json::Value root, int win_width_lg) {
	FILE_LOG(logDEBUG) << "STAGE CONFIGURATION";
	Json::Value stageValue = root[JSON_KEY_ESCENARIO];
	int stage_width;
	int stage_height;
	int stage_ypiso;

	try {
		 string strValue  = stageValue.get(JSON_KEY_ANCHO, 0).asString();
		 stage_width = atoi(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Stage width: " << strValue;
	}catch(std::exception const & e){
		stage_width=0;
	}
	try {
		 string strValue  = stageValue.get(JSON_KEY_ALTO, 0).asString();
		 stage_height = atoi(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Stage height: " << stage_height;
	}catch(std::exception const & e){
		stage_height=0;
	}
	try {
		 string strValue = stageValue.get(JSON_KEY_YPISO, 0).asString();
		 stage_ypiso = atoi(strValue.c_str());
		 FILE_LOG(logDEBUG) << "JSON - Stage ypiso: " << strValue;
	}catch(std::exception const & e){
		stage_ypiso=0;
	}

	//validaciones de parametros para escenario
	bool heightOk = (stage_height>0);
	if (!heightOk){
		stage_height = DEFAULT_STAGE_HEIGHT;
		FILE_LOG(logWARNING) << "Stage logical height out of range or inexistent (must be positive). Set to default:"<<DEFAULT_STAGE_HEIGHT;
	}

	bool yPisoOk = (stage_ypiso>0) && (stage_ypiso<=stage_height);
	if (!yPisoOk){
		//por defecto altura piso es 10% de la altura logica del escenario
		stage_ypiso = (stage_height/10);
		FILE_LOG(logWARNING) << "Stage floor 'y' position out of range or inexistent (0 - "<<stage_height<< "). Set to default:"<<stage_ypiso;
	}

	bool widthOk = (stage_width >=win_width_lg);
	if (!widthOk){
		stage_width = DEFAULT_STAGE_WIDTH;
		FILE_LOG(logWARNING) << "Stage logical width out of range or inexistent (must be higher than window logical width: "<<win_width_lg<< "). Set to default:"<<DEFAULT_STAGE_WIDTH;
	}

	Stage stage(stage_width, stage_height, stage_ypiso);
	return stage;
}


void resizeImage(int* width, int win_width_px, int* height, int win_height_px, int stage_width) {
	if (*width < win_width_px) *width = win_width_px;
}

vector<Layer*> jsonGetLayers(Json::Value root, float ratioX, float ratioY, Window* window, Stage* stage) {
	FILE_LOG(logDEBUG) << "LAYERS CONFIGURATION";
	const Json::Value array = root.get(JSON_KEY_CAPAS,0);
	FILE_LOG(logDEBUG) << "JSON - Number of Layers to process: " << array.size();
	vector<Layer*> layers;
	string path;
	int width;
	int height;
	for (unsigned int index = 0; index < array.size(); ++index) {
		path = array[index].get(JSON_KEY_IMAGEN_FONDO, "").asString();

		//validar existencia de imagen
		if (fileExists(path.c_str())) {
			try {
				 string strValue = array[index].get(JSON_KEY_ANCHO, "").asString();
				 width = atoi(strValue.c_str());
				 FILE_LOG(logDEBUG) << "JSON - Layer width: " << strValue;
			}catch(std::exception const & e){
				width=0;
			}
			//validaciones de parametros para layer
			bool widthOk = (width>0);
			if (!widthOk){
				width = stage->getWidth();
				FILE_LOG(logWARNING) << "Layer logical width out of range or inexistent (must be positive). Set by default:"<<stage->getWidth();
			}

			height = stage->getHeight();
			resizeImage(&width, window->widthPx, &height, window->heightPx, stage->getWidth());
			stringstream sLayerName;
			sLayerName.clear();
			sLayerName << "layer";
			sLayerName << index;

			//TODO calcular ratio
			Layer* layer = new Layer(new LoaderParams(0, 0, width, window->heightPx, index, ratioX,	ratioY, sLayerName.str()));
			layer->setImagePath(path);
			//Add layers to the game loop
			MKGame::Instance()->getObjectList().push_back(layer);

			FILE_LOG(logDEBUG) << "JSON - Layer ID: " << sLayerName.str();
			FILE_LOG(logDEBUG) << "JSON - Layer" << index << " background image: "	<< path;
			FILE_LOG(logDEBUG) << "JSON - Layer" << index << " width: "	<< width;
			layers.push_back(layer);
		}
	}
	FILE_LOG(logDEBUG) << "JSON - Number of Layers successfully process: " << layers.size();
	return layers;
}

vector<Character*> jsonGetCharacters(Json::Value root, float ratioX, float ratioY) {
	FILE_LOG(logDEBUG) << "CHARACTERS CONFIGURATION";
	Json::Value stageValue = root[JSON_KEY_ESCENARIO];
	int stage_win_ypiso = stageValue.get(JSON_KEY_YPISO, 700).asInt();

	Json::Value characterValue = root[JSON_KEY_PERSONAJE];
	string character_name =
			characterValue.get(JSON_KEY_NOMBRE, "nombre").asString();
	int character_width = characterValue.get(JSON_KEY_ANCHO, 700).asInt();
	int character_height = characterValue.get(JSON_KEY_ALTO, 700).asInt();
	int character_zindex = characterValue.get(JSON_KEY_ZINDEX, 700).asInt();
	string character_orientation = characterValue.get(JSON_KEY_ORIENTACION,
			"right").asString();

	FILE_LOG(logDEBUG) << "JSON - Character name: " << character_name;
	FILE_LOG(logDEBUG) << "JSON - Character width: " << character_width;
	FILE_LOG(logDEBUG) << "JSON - Character height: " << character_height;
	FILE_LOG(logDEBUG) << "JSON - Character z-index: " << character_zindex;
	FILE_LOG(logDEBUG) << "JSON - Character orientation: " << character_orientation;

	vector<Character*> characters;

	//TODO put in constant
	int posX = 100;
	bool isRightOrientation = (character_orientation == "right") ? true : false;
	LoaderParams* characterParams = new LoaderParams(posX, stage_win_ypiso, character_width, character_height, character_zindex, ratioX, ratioY, character_name);

	Character* playerOne = new Character(characterParams, GameGUI::getInstance()->getWindow().heightPx, isRightOrientation);

//	Character* playerOne = new Character(character_name, character_width, character_height,
//					character_zindex, true, ratio, GameGUI::getInstance()->window.heightPx);

	//Add player to the game loop
	playerOne->setImagePath("images/spritesheets_subzero/");
	MKGame::Instance()->getObjectList().push_back(playerOne);

	characters.push_back(playerOne);
	return characters;
}

//TODO Fixme
GameGUI* GameGUIBuilder::create() {
	FILE_LOG(logDEBUG) << "CONFIGURATION INITIALIZED";
	GameGUI *gameGUI = GameGUI::getInstance();

	Json::Value root;
	Json::Reader reader;

	//TODO refactor harcoded file path
	ifstream gameConfig("src/stageConfig.json", std::ifstream::binary);

	if (!gameConfig.good()) {
		MessageError fileNotFound(ERROR_FILE_NOT_FOUND, FILE_CONFIG_NOT_FOUND, LOG_LEVEL_ERROR);
		Log<Output2FILE>::logMsgError(fileNotFound);
		return createDefault();
	}

	bool parsingSuccessful = reader.parse(gameConfig, root, false);
	if (!parsingSuccessful) {
		MessageError parseException(ERROR_PARSER_JSON, reader.getFormattedErrorMessages(), LOG_LEVEL_ERROR);
		Log<Output2FILE>::logMsgError(parseException);
		return createDefault();
	}

	Window window = jsonGetWindow(root);
	Stage stage = jsonGetStage(root,window.width);

	float ratioX = getRatio(window.widthPx, window.width,"X");
	float ratioY = getRatio(window.heightPx, stage.getHeight(),"Y");

	TextureManager::Instance()->ratioHeight = ratioY;
	TextureManager::Instance()->ratioWidth = ratioX;

	vector<Layer*> layers = jsonGetLayers(root, ratioX, ratioY, &window, &stage);
	vector<Character*> characters = jsonGetCharacters(root, ratioX, ratioY);

	gameGUI->setWindow(window);
	gameGUI->setStage(stage);
	gameGUI->setCharacters(characters);
	gameGUI->setLayers(layers);

	LayerManager::Instance()->init();

	return gameGUI;
}

GameGUI* GameGUIBuilder::createDefault() {

	FILE_LOG(logDEBUG) << "Entire configuration set by default";
	GameGUI *gameGUI = GameGUI::getInstance();

	//window by default
	int windowXpos = ((MAX_WINDOW_WIDTH_PX-DEFAULT_WINDOW_WIDTH_PX)/2);
	int windowYpos = ((MAX_WINDOW_HEIGHT_PX-DEFAULT_WINDOW_HEIGHT_PX)/2);
	Window window(GAME_TITLE, windowXpos, windowYpos, DEFAULT_WINDOW_WIDTH_PX, DEFAULT_WINDOW_HEIGHT_PX, DEFAULT_WINDOW_WIDTH);
    FILE_LOG(logDEBUG) << "JSON - Window width: " << DEFAULT_WINDOW_WIDTH_PX << " px";
	FILE_LOG(logDEBUG) << "JSON - Window height: " << DEFAULT_WINDOW_HEIGHT_PX << " px";
	FILE_LOG(logDEBUG) << "JSON - Window width: " << DEFAULT_WINDOW_WIDTH;

	//stage by default
	Stage stage(DEFAULT_STAGE_WIDTH, DEFAULT_STAGE_HEIGHT, DEFAULT_STAGE_YFLOOR);
	 FILE_LOG(logDEBUG) << "JSON - Stage width: " << DEFAULT_STAGE_WIDTH;
	 FILE_LOG(logDEBUG) << "JSON - Stage height: " << DEFAULT_STAGE_HEIGHT;
	 FILE_LOG(logDEBUG) << "JSON - Stage ypiso: " << DEFAULT_STAGE_YFLOOR;

	float ratioX = getRatio(DEFAULT_WINDOW_WIDTH_PX, DEFAULT_WINDOW_WIDTH,"X");
	float ratioY = getRatio(DEFAULT_WINDOW_HEIGHT_PX, DEFAULT_STAGE_HEIGHT,"Y");

	//characters by default
	vector<Character*> characters;

	//TODO put in constant
	int posX = 400;
	bool isRightOrientation = true;
	LoaderParams* characterParams = new LoaderParams(posX, 0, 128, 82, 1,
			ratioX, ratioY, "defaultName");

	Character* playerOne = new Character(characterParams,
			GameGUI::getInstance()->getWindow().heightPx, isRightOrientation);

//	Character* character = new Character(new LoaderParams(0, 0, 128, 82, 2, ratioX, "scorpion"));
//	characters.push_back(character);

	//layers by default
	vector<Layer*> layers;
	Layer* layer = new Layer(new LoaderParams(0, 0, 128, 82, 1, ratioX, ratioY, "layer1"));
	layers.push_back(layer);
	Layer* layer2 = new Layer(new LoaderParams(0, 0, 128, 82, 2, ratioX, ratioY, "layer2"));
	layers.push_back(layer2);

	//Add layers to the game loop
	MKGame::Instance()->getObjectList().push_back(playerOne);

	//Add layers to the game loop
	MKGame::Instance()->getObjectList().push_back(layer);
	MKGame::Instance()->getObjectList().push_back(layer2);

	gameGUI->setWindow(window);
	gameGUI->setStage(stage);
	gameGUI->setCharacters(characters);
	gameGUI->setLayers(layers);

	FILE_LOG(logDEBUG) << "Configuration process finished";
	return gameGUI;

}

void GameGUIBuilder::handleError(string msgError) {

	//TODO log msg in level ERROR
	cout << msgError << endl;

}

