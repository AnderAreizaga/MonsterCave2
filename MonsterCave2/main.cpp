/*
 * main.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */
#include "clases/sala.h"
#include "clases/player.h"
#include "clases/monstruo.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;
using namespace players;
using namespace salas;
using namespace monstruos;

/*
 * Este metodo crea la historia sin repeticiones
 */
void creaHistoria(Player* p)
{
	int x ;
	int i=0;
	srand(time(NULL));
	int* historia= new int[7];
	while (i < 6)
	{
		int r = (rand() % 14 )+ 1 ;

		for (x = 0; x < i; x++)
		{
			if (historia[x] == r)
			{
				break;
			}
		}
		if (x == i)
		{
			historia[i++] = r;
		}
	}
	p->setHistoria(historia);
}


void cargarSalas(Sala *puntS)
{
	int endF=0;
	Sala sala;
	ifstream sa ("salas.txt");
	char line[280];

	int j=0;
	do{
		sa.getline(line,280);
		int codSala = atoi(line);
//		cout << puntS[j].getCodSala() << endl;

		sa.getline(line,280);
		int tipo = atoi(line);
//		cout << puntS[j].getTipo() << endl;

		sa.getline(line,280);
		int respuestaCorr = atoi(line);

		string* textosDeSala = new string[10];
		int n=0;
		do{
		sa.getline(line,280);
		string str(line);
		textosDeSala[n] = str;
		n++;
		}while(line[0]!='#');
		if(tipo == 0){
			sala = SalaAdivinanza(codSala,tipo,respuestaCorr,textosDeSala);
		}
		else if(tipo == 1){
			sala = SalaPeleas(codSala,tipo,respuestaCorr,textosDeSala);
		}
		else if(tipo == 2){
			sala = SalaObjetos(codSala,tipo,respuestaCorr,textosDeSala);
		}
		puntS[j] = sala;
		j++;
		sa.getline(line,280);
		if(line[0]=='@'){
			endF=1;
		}

	}while(endF!=1);
	sa.close();
}

void inicializarArrayMonstruos(Monstruo* monstruos){
	Monstruo m;
	char str[200];

	ifstream mons ("Monstruos.txt");
	int i=0;
	int x=0;
	int z=0;
	do{
		mons.getline(str, 200);
		if(str[0]!='&'&&str[0]!='%'){
			string nombre(str);
			m.setNombre(nombre);
			mons.getline(str, 200);
			m.setCodSala(atoi(str));
			mons.getline(str, 200);
			m.setVida(atoi(str));
			mons.getline(str, 200);
			m.setAtaque(atoi(str));
			mons.getline(str, 200);
			m.setResistencia(atoi(str));
			int y=0;
			string* interacciones = new string[10];
			do{
				mons.getline(str, 200);
				if(str[0]!='%'&&str[0]!='&'){
					string interaccion(str);
					interacciones[z]=interaccion;
				}
				else if(str[0]=='&'){
					y=1;
					i=1;
				}
				else if(str[0]=='%'){
					y=1;
				}
				else{
					z++;
				}
			}while(y==0);
			m.setInteracciones(interacciones);
			monstruos[x] = m;
			x++;
		}
	}while(i==0);
	mons.close();
}

void cargarHistoria(Historia* historia)
{
	char str[280];
	ifstream his ("historia.txt");

	int i=0;
	int x=0;
	do{
		int z=0;
		his.getline(str,280);
		if(str[0]!='&'&&str[0]!='%'){
			int y=0;
			string* frases = new string[50];
			do{
				his.getline(str,280);
				if(str[0]!='%'&&str[0]!='&'){
					string hist(str);
					frases[z]=hist;
					z++;
				}
				else if(str[0]=='&'){
					y=1;
					i=1;
				}
				else{
					y=1;
				}
			}while(y==0);
			historia[x].setFrases(frases);
			x++;
		}
	}while(i==0);
	his.close();
}

void printHistoria(Player* pl, Historia* historia)
{

	ofstream hist ("tuHistoria.txt");

	if(hist!=NULL)
	{
		cout << "La historia de " << pl->getName()  <<", sera contada por los juglares, pase por la salida para recoger su escrito :)" << endl;
		hist << "Life of " << pl->getName() << "\n" << endl;
		hist << "Era una oscura mañana de otoño, " << pl->getName() << " se disponía a empezar su primer dia en su nuevo trabajo.\nEra su oportunidad de servir a la sociedad y por primera vez cumplir su sueño  de ser un héroe,\nalguien que combatiera el mal y salvara al mundo varias veces. Pero sin embargo no era tal\ny como se esperaba, barrer el suelo en la taberna más sucia del barrio no era tan emocionante como pensaba que sería\ncuando le dijeron que su misión principal sería combatir la suciedad con esa escoba. Pero un día unos mercenarios entraron\nmientras él trabajaba, llegaron con el objetivo de cumplir la mision mas dificil que podría\nhaber llegado a los oídos de nuestro protagonista: 'Rescatar la gallina de los huevos dorados'\n"
				<< endl;

		for(int i=0;i<pl->getNumeroSalas();i++)
		{
			hist << historia[(pl->getHistoria(i)-1)].getFrase(0);
			if(i==5){
				hist << historia[(pl->getHistoria(i)-1)].getFrase(1) << endl;
				hist << "Encuentra la salida y vuelve a casa habiendo cumplido su sueño" << endl;
			}
			else if(i<pl->getNumeroSalas()-1){
				hist << historia[(pl->getHistoria(i)-1)].getFrase(1) << endl;
			}else{
				hist << historia[(pl->getHistoria(i)-1)].getFrase(2) << endl;
			}

		}
	}

	hist.close();
}

int main()
{
	cout << "Escribe el nombre de tu personaje: ";
	string nombre;
	cin >> nombre ;
	Player *pl;
	pl= new Player(nombre);
	Historia* h1 = new Historia[30];

	//Se crea el jugador
	Sala* s= new Sala[30];

	//Se cargan las salas de fichero
	cargarSalas(s);

	//system("cls");

	Monstruo* monstruos= new Monstruo[10];//Se crean los monstruos
	inicializarArrayMonstruos(monstruos);
	//Se carga la historia
	cargarHistoria(h1);

	creaHistoria(pl);


	cout << "Life of " << pl->getName() <<"\n" << endl;
	sleep(1);
	cout << "Era una oscura mañana de otoño, " << pl->getName() << " se disponía a empezar su primer dia en su nuevo trabajo." << endl;
	sleep(1);
	cout << "Era su oportunidad de servir a la sociedad y por primera vez cumplir su sueño  de ser un héroe," << endl;
	sleep(1);
	cout << "alguien que combatiera el mal y salvara al mundo varias veces. Pero sin embargo no era tal" << endl;
	sleep(1);
	cout << "y como se esperaba, barrer el suelo en la taberna más sucia del barrio no era tan emocionante como pensaba que sería" << endl;
	sleep(1);
	cout << "cuando le dijeron que su misión principal sería combatir la suciedad con esa escoba. Pero un día unos mercenarios entraron" << endl;
	sleep(1);
	cout << "mientras él trabajaba, llegaron con el objetivo de cumplir la mision mas dificil que podría" << endl;
	sleep(1);
	cout << "haber llegado a los oídos de nuestro protagonista: 'Rescatar la gallina de los huevos dorados'" << endl;
	sleep(1);

	//	Bucle constante
	while (pl->getVida()>=1 && pl->getNumeroSalas()<6){
		int numSala;
			if(pl->getNumeroSalas()<6){
				numSala = pl->getHistoria(pl->getNumeroSalas())-1 ;
			}

			if (pl->getNumeroSalas()<= 6)
			{
				//A donde quieres ir
				cout << "¿Por donde deseas ir? N/S/E/W " << endl;
				char r = '0';
				while (r != 'N' && r != 'S' && r != 'E' && r != 'W' && r != 'n'
						&& r != 's' && r != 'e' && r != 'w')
				{
					cin >> r;
				}
				if(s[numSala].getTipo()==0){
					SalaAdivinanza sala = SalaAdivinanza(s[numSala].getCodSala(),s[numSala].getTipo(),s[numSala].getRespuestaCorr(),s[numSala].getTextosSala());
					sala.logicaUpdate(pl,numSala,monstruos);
				}
				else if(s[numSala].getTipo()==1){
					SalaPeleas sala = SalaPeleas(s[numSala].getCodSala(),s[numSala].getTipo(),s[numSala].getRespuestaCorr(),s[numSala].getTextosSala());
					sala.logicaUpdate(pl,numSala,monstruos);
				}
				else if(s[numSala].getTipo()==2){
					SalaObjetos sala = SalaObjetos(s[numSala].getCodSala(),s[numSala].getTipo(),s[numSala].getRespuestaCorr(),s[numSala].getTextosSala());
					sala.logicaUpdate(pl,numSala,monstruos);
				}
			}
			if(pl->getVida()>1)//Victoria
			{
				cout << s[numSala].getTextoSala(2) << endl;
			}

			pl->modificarNumeroSalas(1);
			cout << "Numero de salas pasadas : " << pl->getNumeroSalas() << endl;

	}
	if(pl->getVida()<=0){
		cout << "----------------- Has perecido, en la cueva de los monstruos ----------------" << endl;
	}
	else{
		cout << "----------------- ENHORABUENA, HAS SALIDO DE LA CUEVA, AHORA SIGUE CON TU MORTAL VIDA -------------------" << endl;
	}

	printHistoria(pl,h1);
	s[0].~Sala();

	return 0;
}
