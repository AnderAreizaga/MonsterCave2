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
	Player::Player(string name){
		this->name=name;
		this->fuerza=5;
		this->inteligencia=5;
		this->vida=100;
		this->numeroDeSalas=0;
		this->historia=0;

	}
	string Player::getName(){
		return this->name;
	}
	int Player::getFuerza(){
		return this->fuerza;
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
	void Player::setFuerza(int a){
		fuerza=a;
	}
	void Player::setInteligencia(int a){
		inteligencia=a;
	}
	void Player::setVida(int a){
		vida=a;
	}
	void Player::setNumeroSalas(int a){
		numeroDeSalas=a;
	}
	void Player::modificarVida(int i){
		this->vida+=i;
	}
	void Player::modificarNumeroSalas(int i){
		this->numeroDeSalas+=i;
	}
	void Player::setHistoria(int* historia){
		this->historia=historia;
	}
	Historia::Historia(){
		this->frases=0;
	}
	Historia::Historia(string* frases){
		this->frases=frases;
	}
	string Historia::getFrase(unsigned int i){
		return this->frases[i];
	}
	void Historia::setFrases(string* frases){
		this->frases=frases;
	}

}
