/*
 * player.h
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */

#include <string>
#include <iostream>
using namespace std;

#ifndef PLAYER_PLAYER_H_
#define PLAYER_PLAYER_H_

namespace players{
	class Player{
	private:
		string name;
		int fuerza;
		int inteligencia;
		int carisma;
		int vida;
		int numeroDeSalas;
		int historia[7];
	public:
		Player(string name, int fuerza, int inteligencia, int carisma, int vida, int numeroDeSalas, int historia[7]);
		string getName();
		int getVida();
		int getNumeroSalas();
		int getHistoria(int i);
		void modificarVida(int i);
		void modificarNumeroSalas(int i);
	};

	class Historia{
	private:
		string* frases;
	public:
		Historia(string* frases);
	};
}

#endif /* PLAYER_PLAYER_H_ */
