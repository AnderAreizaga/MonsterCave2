/*
 * main.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */
#include "sala/sala.h"
#include "player/player.h"
#include "monstruo/monstruo.h"
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
	int historia[7];
	for(unsigned int i=0;i<sizeof(historia);i++){
		historia[i]=p->getHistoria(i);
	}
	while (i < 6)
	{
		int r = rand() % 14 + 1 ;

		for (x = 0; x < i; x++)
		{
			if (historia[x] == r)
			{
				break;
			}
		}
		if (x == i)
		{
			historia[i++] = r+1;
		}
	}
}

void logicaUpdate( Player* p, Sala* s, Monstruo* m)
{
	int historia[7];
	for(unsigned int i=0;i<sizeof(historia);i++){
		historia[i]=p->getHistoria(i);
	}
	// elige una sala aleatoria
	int numSala = historia[p->getNumeroSalas()];


	if (p->getNumeroSalas()<= 6)
	{
		//A donde quieres ir
		cout << "¿Por donde deseas ir? N/S/E/W " << endl;
		char r;
		while (r != 'N' && r != 'S' && r != 'E' && r != 'W' && r != 'n'
				&& r != 's' && r != 'e' && r != 'w')
		{

			cin >> r;
		}

		if (s[numSala].getTipo() == 0)// Sala de adivinanza
		{
			//pasa algo
			cout << "Inicio sala adivinanza" << endl;
			sleep(1);

			//supongamos que recibes un array de salas y abres la sala x entonces te aparece un acertijo
			cout << "Sala" << numSala << "\n" << s[numSala].getTextoSala(0) << endl;
			sleep(1);
			cout << "Opcion 1 " << s[numSala].getTextoSala(3) << endl;
			cout << "Opcion 2 " << s[numSala].getTextoSala(4) << endl;
			cout << "Opcion 3 " << s[numSala].getTextoSala(5) << endl;
			int elec = 0;
			int corr = s[numSala].getRespuestaCorr();
			do{


				cout << "ELIGE TU RESPUESTA CON SABIDURIA (1/2/3): ";
				int elec;
				cin >> elec;
				cout << endl;
				if(corr!=elec)
				{
					cout <<  s[numSala].getTextoSala(1) << endl;
					cout << "Pierdes 20 de vida" << endl;
					p->modificarVida(-20);
				}

			}while(corr!=elec);
			//texto de salida de la
			cout << s[numSala].getTextoSala(2) << endl;

		}
		else if (s[numSala].getTipo() == 1)//sala de peleas
		{
			cout << "Sala " << numSala+2 << "\n" << s[numSala].getTextoSala(0) << endl;//Te has encontrado con un mega monstruo feo
			//Busca el monstruo con el codigo de sala
			int i = 0;
			for(;i<5;i++ )//OJOOOO EL  con el numero de monstruos en el array esta en 1 para probar
			{
				if(s[numSala].getCodSala() == m[i].getCodSala())
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
					cout << s[numSala].getTextoSala(2) << "/nVaya, parece que tu vida esta a 0" << endl;// Texto de game over
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
				for(;k<p->getVida();k++)
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
					vida=vida-20;
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
			if(p->getVida()>1)//Game over
			{
				cout << "\n" << s->getTextoSala(2) << endl;
			}

			//texto de salida de la

		}
		else if (s[numSala].getTipo() == 2)// sala en la que consigues algo

		{
			cout << "Sala " << numSala + 2 << "\n" << s->getTextoSala(0);
			p->modificarVida(100);
			if(p->getVida()>100)
			{
				p->modificarVida(-(p->getVida()-100));
			}
			int k=0;
			for(;k<p->getVida();k++)
			{
				cout << "|";
				sleep(0.005);
			}


		}



	}

	p->modificarNumeroSalas(1);
	cout << "Numero de salas pasadas : " << p->getNumeroSalas() << endl;

}

void cargarSalas(Sala *puntS)
{
	int endF=0;

	ifstream sa ("salas.txt");
	char line[280];

	int endS=0;

	int j=0;
	do{

		endS=0;
		sa.getline(line,2);
		puntS[j].setCodSala(atoi(line));
//		printf("%i\n",puntS[j].codSala);

		sa.getline(line,2);
		puntS[j].setTipo(atoi(line));
//		printf("%i\n",puntS[j].tipo);

		sa.getline(line,2);
		puntS[j].respuestaCorr=atoi(line);

		sa.getline(line,280);
		puntS[j].textosDeSala= line;
		j++;
		sa.getline(line,280);
		if(line[0]=='@'){
			endF=1;
		}

	}while(endF!=1);

	fclose(salas);
}

int main()
{
//	cout << "Escribe el nombre de tu personaje: ";
//	string nombre;
//	cin >> nombre ;
//	Player *pl;
//	pl= new Player(nombre);
//	Historia * h1= malloc(sizeof(Historia)*30);


	//Se crea el jugador
	Sala* s= new Sala[30];

	//Se cargan las salas de fichero
//		cargarSalas(s);

	//system("cls");

//	Monstruo* monstruos=malloc(sizeof(Monstruo)*10);//Se crean los monstruos
//		inicializarArrayMonstruos(monstruos);
//		//Se carga la historia
//		cargarHistoria(h1);
//
//		fflush(stdout);
//
//		creaHistoria(&pl);
//
//		fflush(stdout);
//
//		printf("Life of %s \n\n", pl.name);
//		fflush(stdout);
//		sleep(1);
//		printf("Era una oscura mañana de otoño, %s se disponía a empezar su primer dia en su nuevo trabajo.\n",pl.name);
//		fflush(stdout);
//		sleep(1);
//		printf("Era su oportunidad de servir a la sociedad y por primera vez cumplir su sueño  de ser un héroe,\n");
//		fflush(stdout);
//		sleep(1);
//		printf("alguien que combatiera el mal y salvara al mundo varias veces. Pero sin embargo no era tal\n");
//		fflush(stdout);
//		sleep(1);
//		printf("y como se esperaba, barrer el suelo en la taberna más sucia del barrio no era tan emocionante como pensaba que sería\n");
//		fflush(stdout);
//		sleep(1);
//		printf("cuando le dijeron que su misión principal sería combatir la suciedad con esa escoba. Pero un día unos mercenarios entraron\n");
//		fflush(stdout);
//		sleep(1);
//		printf("mientras él trabajaba, llegaron con el objetivo de cumplir la mision mas dificil que podría\n");
//		fflush(stdout);
//		sleep(1);
//		printf("haber llegado a los oídos de nuestro protagonista: ''Rescatar la gallina de los huevos dorados''\n");
//		fflush(stdout);
//		sleep(1);
//
//	//	Bucle constante
//		while (pl.vida>=1 && pl.numerodesalas<6)
//		{
//			logicaUpdate(&pl ,s , monstruos);
//
//		}
//		if(pl.vida<=0)
//		{
//		printf("----------------- Has perecido, en la cueva de los monstruos ----------------");
//		fflush(stdout);
//		}
//		else
//		{
//		printf("----------------- ENHORABUENA, HAS SALIDO DE LA CUEVA, AHORA SIGUE CON TU MORTAL VIDA -------------------");
//		fflush(stdout);
//		}
//
//		printHistoria(&pl,h1);
//
//
//		return 0;
	}
