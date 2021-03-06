/*
 * Layer.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef LAYER_H_
#define LAYER_H_
#include <string>
#include "SDL.h"
#include "SDLObjectGUI.h"
#include "TextureManager.h"
#include "Log.h"

using namespace std;

class Layer: public SDLObjectGUI {
private:
	float offScene;
	float scrollingOffset;
	float bkgSpeed;
	int orientation; /* 1=right -1=left */
	bool needRefresh;



public:
	Layer(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual ~Layer();
	void setLayerSpeed(float speedFirstLayer, float offSceneFirstLayer);
	void setLayerOffScene(float windowsWidth);
	float getLayerOffScene();
	float getLayerSpeed();
	void setImagePath(std::string path);
	void setNeedRefresh(bool needRefresh);
	void setPositionX(int position);
	int getPositionX();
	float getScrollingOffset();
	int getWidth();

	int getOrientation() const;

	void setOrientation(int orientation);
};

#endif /* LAYER_H_ */
