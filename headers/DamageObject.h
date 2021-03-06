/*
 * DamageObject.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef DAMAGEOBJECT_H_
#define DAMAGEOBJECT_H_
#include "Constants.h"
#include <string>
#include <SDL.h>
#include <stdio.h>
#include <map>
#include <iostream>

using namespace std;


class DamageObject {
private:
	bool isDestroy;
	float energy;
	string doMovement;

public:
	DamageObject();
	bool isWeapon;
	virtual ~DamageObject();
	float getEnergy();
	bool getDestroy();
	void setEnergy(float newEnergyValue);
	void setDamage(float damage);
	void setDOMovement(string movement);
	string getDOMovement();
	void setIsWeapon(bool isWeapon);
	bool isCharacter();
	void setLive();
	void setKill();
};

#endif /* CHARACTER_H_ */
