/*
 * sala.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */

#include "monstruo.h"
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
		this->respuestaCorr=0;
		this->textosDeSala=0;
	}
	Sala::Sala(int codSala, int tipo, int resp,  string* textosDeSala){
		this->codSala=codSala;
		this->tipo=tipo;
		this->respuestaCorr = resp;
		this->textosDeSala=textosDeSala;
	}
	Sala::~Sala(){

	}
	void Sala::logicaUpdate(Player* p, int numSala, Monstruo* m){
	}
	SalaAdivinanza::SalaAdivinanza(int codSala, int tipo, int repuestaCorre, string* textosDeSala):Sala(codSala, tipo, repuestaCorre, textosDeSala){}
	SalaAdivinanza::~SalaAdivinanza(){}
	SalaPeleas::SalaPeleas(int codSala, int tipo,int repuestaCorre, string* textosDeSala):Sala(codSala, tipo, repuestaCorre, textosDeSala){}
	SalaPeleas::~SalaPeleas(){}
	SalaObjetos::SalaObjetos(int codSala, int tipo,int repuestaCorre, string* textosDeSala):Sala(codSala, tipo, repuestaCorre, textosDeSala){}
	SalaObjetos::~SalaObjetos(){}
	void SalaAdivinanza::logicaUpdate(Player* p, int numSala, Monstruo* m){
		//pasa algo
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

	void SalaPeleas::logicaUpdate(Player* p, int numSala,  Monstruo* m){
		cout << "Sala " << numSala + 1 << "\n"<< this->getTextoSala(0) << endl;//Te has encontrado con un mega monstruo feo
		//Busca el monstruo con el codigo de sala
		int i = 0;
		for(;i<5;i++ )//OJOOOO EL  con el numero de monstruos en el array esta en 1 para probar
		{
			if(this->getCodSala() == m[i].getCodSala())
			{
				cout << m[i].getCodSala() << endl;
				break;
			}
		}

		int vida = m[i].getVida();

		cout << m[i].getInteraccion(0) << endl;
		while(vida>0)
		{

			if(p->getVida()<=0)//Game over
			{
				cout << this->getTextoSala(2) << "Vaya, parece que tu vida esta a 0" << endl;// Texto de game over
				char m;
				cin >> m;
				break;

			}
			//Print de la vida
			cout << m[i].getNombre() << endl;
			cout << "Vida del monstruo :";
			int j=0;
			for(;j<vida/10;j++)
			{
				cout << "|";
			}
			cout << "\n" << p->getName() << ":";

			int k=0;
			for(;k<p->getVida()/10;k++)
			{
				cout << "|";
			}

			cout << "\n 1 - Espada de palo      2 - Piro++      \n 3-Hielo++          4 - Cura++       " << endl;
			cout << " Escoge un arma (1/2/3/4) : ";
			int eleccion;
			cin >> eleccion;
			switch(eleccion)
			{
			case 1:
				vida=vida-5*p->getFuerza();
				cout << "Dañas al monstruo con tu legendaria espadad de madera, ";
				sleep(2);
				p->modificarVida(-10);
				cout << "sin embargo el monstruo te goplpea y obviamente recibes daño." << endl;
				sleep(1);
				break;

			case 2:
				vida=vida-15;
				cout << "Conjuras una gran llama, el fuego daña al monstruo, ";
				p->modificarVida(-7);
				sleep(2);
				cout << "te escupe y te da asco, genial, ahora tienes baba de llama." << endl;
				sleep(1);
				break;
			case 3:
				vida=vida-5;
				cout << "Enfrias la sala muchisimo, ";
				sleep(2);
				p->modificarVida(-3);
				cout << "genial ahora tienes un resfriado!" << endl;
				sleep(1);
				break;
			case 4:
				cout << "Aparece un obispo que te echa agua bendita, se curan tus heridas, un poco, mas bien casi nada, digamos que es placebo." << endl;
				sleep(1);
				p->modificarVida(20);
				if(p->getVida()>100)
				{
					p->modificarVida(-(p->getVida()-100));
				}
				break;
			default:

				cout << "La proxima vez ataque subnormal" << endl;
				sleep(2);
				p->modificarVida(-10);
				break;
			}
		}
	}

	void SalaObjetos::logicaUpdate(Player* p, int numSala,  Monstruo* m){
		cout << "Sala " << numSala + 1 << "\n" << this->getTextoSala(0) << endl;
		p->modificarVida(100);
		if(p->getVida()>100)
		{
			p->modificarVida(-(p->getVida()-100));
		}
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
	string* Sala::getTextosSala(){
		return this->textosDeSala;
	}
	void Sala::setCodSala(int codSala){
		this->codSala=codSala;
	}
	void Sala::setTipo(int tipo){
		this->tipo=tipo;
	}
	void Sala::setRespuestaCorr(int respuestaCorr){
		this->respuestaCorr=respuestaCorr;
	}
	void Sala::setTextosDeSala(string* textosDeSala){
		this->textosDeSala=textosDeSala;
	}
}

