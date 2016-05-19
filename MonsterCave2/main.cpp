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
	int* historia= new int[7];
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
	p->setHistoria(historia);
}

void logicaUpdate( Player* p, Sala* s, Monstruo* m)
{
	// elige una sala aleatoria
	int numSala;
	if(p->getNumeroSalas()<6){
		numSala = p->getHistoria(p->getNumeroSalas())-1 ;
	}

	if (p->getNumeroSalas()<= 6)
	{
		//A donde quieres ir
		cout << "¿Por donde deseas ir? N/S/E/W " << endl;
		char r = '0';
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

	int j=0;
	do{
		sa.getline(line,280);
		puntS[j].setCodSala(atoi(line));
//		cout << puntS[j].getCodSala() << endl;

		sa.getline(line,280);
		puntS[j].setTipo(atoi(line));
//		cout << puntS[j].getTipo() << endl;

		sa.getline(line,280);
		puntS[j].setRespuestaCorr(atoi(line));

		string* textosDeSala = new string[10];
		int n=0;
		do{
		sa.getline(line,280);
		string str(line);
		textosDeSala[n] = str;
		n++;
		}while(line[0]!='#');
		puntS[j].setTextosDeSala(textosDeSala);

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

	ifstream mons ("monstruo/Monstruos.txt");
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
		cout << "\nLa historia de %s , sera contada por los juglares, pase por la salida para recoger su escrito :)\n" << pl->getName() << endl;
		hist << "Life of " << pl->getName() << "\n" << endl;
		hist << "Era una oscura mañana de otoño, " << pl->getName() << " se disponía a empezar su primer dia en su nuevo trabajo.\nEra su oportunidad de servir a la sociedad y por primera vez cumplir su sueño  de ser un héroe,\nalguien que combatiera el mal y salvara al mundo varias veces. Pero sin embargo no era tal\ny como se esperaba, barrer el suelo en la taberna más sucia del barrio no era tan emocionante como pensaba que sería\ncuando le dijeron que su misión principal sería combatir la suciedad con esa escoba. Pero un día unos mercenarios entraron\nmientras él trabajaba, llegaron con el objetivo de cumplir la mision mas dificil que podría\nhaber llegado a los oídos de nuestro protagonista: 'Rescatar la gallina de los huevos dorados'\n"
				<< endl;

		for(int i=0;i<pl->getNumeroSalas();i++)
		{
			hist << historia[(pl->getHistoria(i)-1)].getFrase(0);
			if(i==5){
				hist << historia[(pl->getHistoria(i)-1)].getFrase(1);
				hist << "Encuentra la salida y vuelve a casa habiendo cumplido su sueño" << endl;
			}
			else if(i<pl->getNumeroSalas()-1){
				hist << historia[(pl->getHistoria(i)-1)].getFrase(1);
			}else{
				hist << historia[(pl->getHistoria(i)-1)].getFrase(2);
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
		logicaUpdate(pl ,s ,monstruos);

	}
	if(pl->getVida()<=0){
		cout << "----------------- Has perecido, en la cueva de los monstruos ----------------" << endl;
	}
	else{
		cout << "----------------- ENHORABUENA, HAS SALIDO DE LA CUEVA, AHORA SIGUE CON TU MORTAL VIDA -------------------" << endl;
	}

	printHistoria(pl,h1);


	return 0;
}
