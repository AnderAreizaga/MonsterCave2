/*
 * sala.h
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */

#include <string>
#include <iostream>
using namespace std;

#ifndef SALA_SALA_H_
#define SALA_SALA_H_

namespace salas{
	class Sala{
	private:
		int codSala; //de 0 a 29
		int tipo; // 0: Adivinanza 1: Pelea 2: No recuerdo, igual era sala de movimiento simple
		int respuestaCorr;// char* resCorrecta;
		string* textosDeSala;  // Son normalmente 1º estado de presentacion, 2º estado de fallido(respuesta incorrecta) 3º puedes seguir
		//en el caso de sala de monstruos el estado 2 se repite hasta que la vida del monstruo tenga 0 vida
		//el cambio de sala siempre es aleatorio
	public:
		Sala(int codSala, int tipo, int repuestaCorr, string* textosDeSala);
		void cargarSalas(Sala *puntS);
		int getCodSala();
		int getTipo();
		int getRespuestaCorr();
		string getTextoSala(int i);

	};
}
#endif /* SALA_SALA_H_ */
