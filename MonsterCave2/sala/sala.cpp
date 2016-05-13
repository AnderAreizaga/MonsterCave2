/*
 * sala.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */
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
}

