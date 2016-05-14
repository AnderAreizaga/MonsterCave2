/*
 * monstruo.h
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */


#include <string>
#include <iostream>
using namespace std;

#ifndef MONSTRUO_MONSTRUO_H_
#define MONSTRUO_MONSTRUO_H_

namespace monstruos{
	class Monstruo {
		private:
			string nombre;//El nombre del monstruo
			int codsala;//La sala en la que esta el monstruo
			int vida;//La vida del monstruo
			int ataque;//El daño que hace el monstruo
			int resistencia ;//0 fisico , 1 Fuego , 2 viento , 3 tierra , 4 agua, 5 nada
			string* interacciones; //Frases que dice el monstruo durante el combate
		public:
			Monstruo(string nombre, int codsala, int vida, int ataque, int resistencia, string* interacciones);
			void inicializarArrayMonstruos(Monstruo* monstruos);
			string getNombre();
			int getCodSala();
			int getVida();
			string getInteraccion(unsigned int i);
	};
}

#endif /* MONSTRUO_MONSTRUO_H_ */
