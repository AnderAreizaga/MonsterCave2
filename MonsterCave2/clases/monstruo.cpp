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
	Monstruo::Monstruo(){
		this->nombre="h";
		this->codsala=0;
		this->vida=0;
		this->ataque=0;
		this->resistencia=0;
		this->interacciones=0;
	}
	Monstruo::Monstruo(string nombre, int codsala, int vida, int ataque, int resistencia, string* interacciones){
		this->nombre=nombre;
		this->codsala=codsala;
		this->vida=vida;
		this->ataque=ataque;
		this->resistencia=resistencia;
		this->interacciones=interacciones;
	}

	string Monstruo::getNombre(){
		return this->nombre;
	}
	int Monstruo::getCodSala(){
		return this->codsala;
	}
	int Monstruo::getVida(){
		return this->vida;
	}
	int Monstruo::getAtaque(){
		return this->ataque;
	}
	int Monstruo::getResistencia(){
		return this->resistencia;
	}
	string Monstruo::getInteraccion(unsigned int i){
		return this->interacciones[i];
	}
	void Monstruo::setNombre(string nombre){
		this->nombre=nombre;
	}
	void Monstruo::setCodSala(int codSala){
		this->codsala=codSala;
	}
	void Monstruo::setVida(int vida){
		this->vida=vida;
	}
	void Monstruo::setAtaque(int ataque){
		this->ataque=ataque;
	}
	void Monstruo::setResistencia(int resistencia){
		this->resistencia=resistencia;
	}
	void Monstruo::setInteracciones(string* interacciones){
		this->interacciones=interacciones;
	}
}
