/*
 * monstruo.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */

#include "monstruo.h"
#include <string>
#include <iostream>
using namespace std;

namespace monstruos{

	Monstruo::Monstruo(string nombre, int codsala, int vida, int ataque, int resistencia, string* interacciones){
		this->nombre=nombre;
		this->codsala=codsala;
		this->vida=vida;
		this->ataque=ataque;
		this->resistencia=resistencia;
		this->interacciones=interacciones;
	}

	void Monstruo::inicializarArrayMonstruos(Monstruo* monstruos){

	}
}
