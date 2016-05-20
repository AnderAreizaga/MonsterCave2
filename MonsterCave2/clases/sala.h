/*
 * sala.h
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */

#include "player.h"
#include <string>
#include <iostream>
using namespace std;
using namespace players;

#ifndef SALA_SALA_H_
#define SALA_SALA_H_

namespace salas{
	class Sala{
	private:
		int codSala; //de 0 a 29
		int tipo; // 0: Adivinanza 1: Pelea 2: No recuerdo, igual era sala de movimiento simple
		string* textosDeSala;  // Son normalmente 1º estado de presentacion, 2º estado de fallido(respuesta incorrecta) 3º puedes seguir
		//en el caso de sala de monstruos el estado 2 se repite hasta que la vida del monstruo tenga 0 vida
		//el cambio de sala siempre es aleatorio
	public:
		Sala();
		Sala(int codSala, int tipo, string* textosDeSala);
		virtual ~Sala();
		virtual void logicaUpdate();

		int getCodSala();
		int getTipo();
		string getTextoSala(int i);

		void setCodSala(int codSala);
		void setTipo(int tipo);
		void setTextosDeSala(string* textosDeSala);
	};
	class SalaAdivinanza : public Sala{
	private:
		int respuestaCorr;// char* resCorrecta;
	public:
		SalaAdivinanza(int codSala, int tipo, int repuestaCorr, string* textosDeSala);
		void logicaUpdate(Player* p);
		int getRespuestaCorr();
		void setRespuestaCorr(int respuestaCorr);
	};
	class SalaPeleas : public Sala{
	public:
		SalaPeleas(int codSala, int tipo, string* textosDeSala);
		void logicaUpdate();
	};
	class SalaObjetos : public Sala{
	public:
		SalaObjetos(int codSala, int tipo, string* textosDeSala);
		void logicaUpdate();
	};
}
#endif /* SALA_SALA_H_ */
