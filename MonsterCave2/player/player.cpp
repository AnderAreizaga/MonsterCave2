/*
 * player.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */

#include "player.h"
#include <string>
#include <iostream>
using namespace std;

namespace players{
	Player::Player(string name, int fuerza, int inteligencia, int carisma, int vida, int numeroDeSalas, int historia[7]){
		this->name=name;
		this->fuerza=fuerza;
		this->inteligencia=inteligencia;
		this->carisma=carisma;
		this->vida=vida;
		this->numeroDeSalas=numeroDeSalas;

	}
	int Player::getHistoria(int i){
		return this->historia[i];
	}
	Historia::Historia(string* frases){
		this->frases=frases;
	}

}
