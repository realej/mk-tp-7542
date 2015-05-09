
#include "../headers/Collitionable.h"
#include "../headers/Box.h"
#include <iostream>
#include <stdlib.h>

void Collitionable::initShapes(int qty,float X, float Y, int W, int H){

	Box* mainShape = new Box(X,Y,W,H,true);
	this->Shapes.push_back(mainShape);

	for (int i=1; i<=qty-1; i++){
		Box* auxShape = new Box(X,Y,0,0,false); //X,Y sin validez para figura inactiva
		this->Shapes.push_back(auxShape);
	}
};

void Collitionable::getNextPosition(float* X, float* Y){

}
