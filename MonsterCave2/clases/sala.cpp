/*
 * sala.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */
#include "player.h"
#include "sala.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

namespace salas{
	Sala::Sala(){
		this->codSala=0;
		this->tipo=0;
		this->textosDeSala=0;
	}
	Sala::Sala(int codSala, int tipo,  string* textosDeSala ){
		this->codSala=codSala;
		this->tipo=tipo;
		this->textosDeSala=textosDeSala;
	}
	SalaAdivinanza::SalaAdivinanza(int codSala, int tipo, int repuestaCorr, string* textosDeSala):Sala(codSala, tipo, textosDeSala){
		this->respuestaCorr=respuestaCorr;
	}
	SalaPeleas::SalaPeleas(int codSala, int tipo, string* textosDeSala):Sala(codSala, tipo, textosDeSala){}
	SalaObjetos::SalaObjetos(int codSala, int tipo, string* textosDeSala):Sala(codSala, tipo, textosDeSala){}
	void SalaAdivinanza::logicaUpdate(Player* p){
		//pasa algo
		int numSala;
		if(p->getNumeroSalas()<6){
			numSala = p->getHistoria(p->getNumeroSalas())-1 ;
		}
		cout << "Inicio sala adivinanza" << endl;
		sleep(1);

		//supongamos que recibes un array de salas y abres la sala x entonces te aparece un acertijo
		cout << "Sala " << numSala+1 << "\n"<< this->getTextoSala(0) << endl;
		sleep(1);
		cout << "Opcion 1 " << this->getTextoSala(3) << endl;
		cout << "Opcion 2 " << this->getTextoSala(4) << endl;
		cout << "Opcion 3 " << this->getTextoSala(5) << endl;
		int elec = 0;
		int corr = this->getRespuestaCorr();
		do{
			cout << "ELIGE TU RESPUESTA CON SABIDURIA (1/2/3): ";
			cin >> elec;
			if(corr!=elec)
			{
				cout <<  this->getTextoSala(1) << endl;
				cout << "Pierdes 20 de vida" << endl;
				p->modificarVida(-20);
			}

		}while(elec!=corr);
		//texto de salida de la
	}


	int Sala::getCodSala(){
		return this->codSala;
	}
	int Sala::getTipo(){
		return this->tipo;
	}
	int SalaAdivinanza::getRespuestaCorr(){
		return this->respuestaCorr;
	}
	string Sala::getTextoSala(int i){
		return this->textosDeSala[i];
	}
	void Sala::setCodSala(int codSala){
		this->codSala=codSala;
	}
	void Sala::setTipo(int tipo){
		this->tipo=tipo;
	}
	void SalaAdivinanza::setRespuestaCorr(int respuestaCorr){
		this->respuestaCorr=respuestaCorr;
	}
	void Sala::setTextosDeSala(string* textosDeSala){
		this->textosDeSala=textosDeSala;
	}
}

