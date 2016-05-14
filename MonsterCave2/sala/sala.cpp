/*
 * sala.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */

#include "sala.h"
#include <string>
#include <iostream>
using namespace std;

namespace salas{
	Sala::Sala(int codSala, int tipo, int repuestaCorr, string* textosDeSala ){
		this->codSala=codSala;
		this->tipo=tipo;
		this->respuestaCorr=respuestaCorr;
		this->textosDeSala=textosDeSala;
	}
	void Sala::cargarSalas(Sala *puntS){

	}
	int Sala::getCodSala(){
		return this->codSala;
	}
	int Sala::getTipo(){
		return this->tipo;
	}
	int Sala::getRespuestaCorr(){
		return this->respuestaCorr;
	}
	string Sala::getTextoSala(int i){
		return this->textosDeSala[i];
	}
}

