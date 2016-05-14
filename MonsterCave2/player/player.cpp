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
	string Player::getName(){
		return this->name;
	}
	int Player::getVida(){
		return this->vida;
	}
	int Player::getNumeroSalas(){
		return this->numeroDeSalas;
	}
	int Player::getHistoria(int i){
		return this->historia[i];
	}
	void Player::modificarVida(int i){
		this->vida+=i;
	}
	void Player::modificarNumeroSalas(int i){
		this->numeroDeSalas+=i;
	}
	Historia::Historia(string* frases){
		this->frases=frases;
	}

}
