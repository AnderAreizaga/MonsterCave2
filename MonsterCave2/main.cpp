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
using namespace players;
using namespace salas;
using namespace monstruos;

void creaHistoria(Player* p)
{
	int x ;
	int j;
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
	for (j = 0; j < 6; j++)
	{
		cout <<  historia[j] << endl;
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
//			system("cls");
			//texto de salida de la
			cout << s[numSala].getTextoSala(2) << endl;
			//Limpia la consola
//			system("cls");

		}
		else if (s[numSala].getTipo() == 1)//sala de peleas
		{
			cout << "Sala " << numSala +1 << "\n" << s[numSala].getTextoSala(0) << endl;//Te has encontrado con un mega monstruo feo
			//Busca el monstruo con el codigo de sala
			int i = 0;
			for(;i<1;i++ )//OJOOOO EL  con el numero de monstruos en el array esta en 1 para probar
			{
				if(s[numSala].getCodSala() == m[i].getCodSala())
				{
					break;
				}
			}

			int vida = m[i].getVida();

			cout << m[i].getInteraccion(0) << endl;
			while(vida>0)
			{

				if(p->getVida()<=0)//Game over
				{
					cout << s[numSala-1].getTextoSala(2) << "/nVaya, parece que tu vida esta a 0" << endl;// Texto de game over
					char m;
					cin >> m;
					break;

				}
				//Print de la vida
				cout << m[i].getNombre() << endl;
				cout << "Vida del monstruo :";
				int j=0;
				for(;j<vida;j++)
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
					cout << ",genial ahora tienes un resfriado!" << endl;
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


			//texto de salida de la
			cout << "\n" << s->getTextoSala(2) << endl;
		}
		else if (s[numSala].getTipo() == 2)// sala en la que consigues algo

		{
			cout << "Sala " << numSala << "\n" << s->getTextoSala(0);
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

int main()
{

//	Player pl;
//	Historia * h1= malloc(sizeof(Historia)*30);
//	crearPlayer(&pl);
//
//	Sala* s = malloc(sizeof(Sala)*30);
//
//
//	cargarSalas(s);
//
//
//	//system("cls");
//
//
//
//	Monstruo* monstruos=malloc(sizeof(Monstruo)*10);
//	inicializarArrayMonstruos(monstruos);
//
//	cargarHistoria(h1);
//
//	fflush(stdout);
//
//	creaHistoria(&pl);
//
//	fflush(stdout);
//
//
////	Bucle constante
//	while (pl.vida>=1 && pl.numerodesalas<=6)
//	{
//		logicaUpdate(&pl ,s , monstruos);
//
//	}
//	if(pl.vida<=0)
//	{
//	printf("----------------- Has perecido, en la cueva de los monstruos ----------------");
//	fflush(stdout);
//	}
//	else
//	{
//	printf("----------------- ENHORABUENA, HAS SALIDO DE LA CUEVA, AHORA SIGUE CON TU MORTAL VIDA -------------------");
//	fflush(stdout);
//	}
//
//	printHistoria(&pl,h1);


	return 0;
}
