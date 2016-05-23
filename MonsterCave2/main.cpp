/*
 * main.cpp
 *
 *  Created on: 13/5/2016
 *      Author: ander.areizagab
 */
#include "clases/sala.h"
#include "clases/player.h"
#include "clases/monstruo.h"
#include "clases/PlayerBD.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace players;
using namespace salas;
using namespace monstruos;

char res;// para el modo demo
/*
 * Este metodo crea la historia sin repeticiones
 */
void creaHistoria(Player* p)
{
	//Modo demo
	cout<<"¿Modo demo? (S/N)"<< endl;
	cin>>res;

	int x ;
	int i=0;
	srand(time(NULL));
	int* historia= new int[7];


	if (res=='S'||res=='s')
	{
			historia[0]=1;
			historia[1]=4;
			historia[2]=5;
			historia[3]=4;
			historia[4]=9;
			historia[5]=6;
			historia[6]=12;
	}
	else
	{
	while (i < 7)
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
		int numSalas = pl->getNumeroSalas();
		if(numSalas==10){
			numSalas-=3;
		}
		for(int i=0;i<numSalas;i++)
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

//AQUI METO TODO LO DEL BUSCAMINAS PERDON POR LA SUCIEDAD
//{


int bomb_count, checkx, checky;//Campos importantes
const int sizex = 4, sizey = 4;//Campos importantes
bool lose;

class Grid {
public:
	bool has_bomb, marked,showed, checked;
	int closebombs;
	Grid(void) {
		has_bomb = false;
		marked = false;
		showed = false;
		checked= false;
		closebombs=0;

	}
};
void closeBombs(Grid board[sizex][sizey], int posx, int posy)
{
//	|_|b|b| Comprueba si en los alrededores hay bomba y le da un numero
//	|_|3|_|
//	|_|b|_|

	if( posy<sizex && board[posx][posy+1].has_bomb) //abajo                  //	|_|_|_|
	{                                                                        //	|_|1|_|
		board[posx][posy].closebombs=board[posx][posy].closebombs+1;         //	|_|+|_|
	}
	if( posx<sizex && posy<sizey && board[posx+1][posy+1].has_bomb)//abajo dcha //	|_|_|_|
	{                                                                           //	|_|1|_|
		board[posx][posy].closebombs=board[posx][posy].closebombs+1;            //	|_|_|+|
	}
	if(posx<sizex && board[posx+1][posy].has_bomb) //dcha                  //	|_|_|_|
	{                                                                      //	|_|3|+|
		board[posx][posy].closebombs=board[posx][posy].closebombs+1;       //	|_|_|_|
	}
	if(posx<sizex && posy>0 && board[posx+1][posy-1].has_bomb) // arriba dch//	|_|_|+|
	{                                                                      //	|_|3|_|
		board[posx][posy].closebombs=board[posx][posy].closebombs+1;       //	|_|_|_|
	}
	if( posy>0 && board[posx][posy-1].has_bomb)// arriba                  //	|_|+|_|
	{                                                                     //	|_|3|_|
		board[posx][posy].closebombs=board[posx][posy].closebombs+1;      //	|_|_|_|
	}
	if(posx>0 && posy<sizey &&board[posx-1][posy+1].has_bomb)//abajo izda   //	|_|_|_|
	{                                                                       //	|_|3|_|
		board[posx][posy].closebombs=board[posx][posy].closebombs+1;        //	|+|_|_|
	}
	if(posx>0 && board[posx-1][posy].has_bomb)//izda                        //	|_|_|_|
	{                                                                       //	|+|3|_|
		board[posx][posy].closebombs=board[posx][posy].closebombs+1;        //	|_|_|_|
	}
	if(posx>0 && posy>0 && board[posx-1][posy-1].has_bomb)//arriba izda     //	|+|_|_|
	{                                                                      //	|_|3|_|
		board[posx][posy].closebombs=board[posx][posy].closebombs+1;       //	|_|_|_|
	}
	board[posx][posy].checked=true;

}
void drawBoad(Grid board[sizex][sizey])
{
	//  _0_1_2_3_4_5_6_7_8_9_
	// 0|_|_|_|_|_|_|_|_|_|_|
	// 1|_|_|_|_|_|_|_|_|_|_|
	// 2|_|_|_|_|_|_|_|_|_|_|
	// 3|_|_|_|_|_|_|_|_|_|_|
	// 4|_|_|_|_|_|_|_|_|_|_|
	// 5|_|_|_|_|_|_|_|_|_|_|
	// 6|_|_|_|_|_|_|_|_|_|_|
	// 7|_|_|_|_|_|_|_|_|_|_|
	// 8|_|_|_|_|_|_|_|_|_|_|
	// 9|_|_|_|_|_|_|_|_|_|_|


	cout << " _";
	for (int i = 0; i < sizex; i++)
	{
		cout << i+1 << "_";
	}
	cout << endl;


	for (int y = 0; y < sizey; y++)
	{
		cout << y+1 << "|";
		for (int x = 0; x < sizex; x++)
		{
			if (board[x][y].has_bomb && board[x][y].showed)
			{
				cout << "*|";
			}
			else if (board[x][y].marked)
			{
				cout << "!|";

			}
			else if (board[x][y].showed && !board[x][y].has_bomb)
			{
				if(board[x][y].checked==false)
				{
				closeBombs( board,  x, y);
				}
				cout << board[x][y].closebombs<< "|";
			}
			else
			{
				cout << "_|";
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << " _";
//	ESTA PARTE ES PARA DEMOSTRAR QUE HAY BOMBAS
	if(res=='S'||res=='s')
	{
	for (int i = 0; i < sizex; i++)
	{
		cout << i+1 << "_";
	}
	cout << endl;

	for (int y = 0; y < sizey; y++)
		{
			cout << y+1 << "|";
			for (int x = 0; x < sizex; x++)
			{

				if (board[x][y].has_bomb)
				{
					cout << "b|";
				}

				else
				{
					cout << "_|";
				}
			}
			cout << endl;
		}
	}

}
void logicaBuscaMinas(Player *p)
{
	bool win = false;
	srand(time(NULL));
	lose = false;
	bomb_count = 3;
	int bombasRes = bomb_count;
	checkx = 0;
	checky = 0;
	Grid gameboard[sizex][sizey];
	for (int i = 0; i < bomb_count; i++)
	{
		int xpos = rand() % sizex;
		int ypos = rand() % sizey;
		if (gameboard[xpos][ypos].has_bomb == false) {
			gameboard[xpos][ypos].has_bomb = true;
		}
		else
		{
			i--;
		}
	}
	drawBoad(gameboard);
	cout << endl;
	while (lose != true && win != true)
	{
		char select;
		cout << "Elige enseñar (S/s) o Marcar (M/m)" << endl;
		cin >> select;
		if(select=='S' || select=='s')
		{
			cout << "Elige una casilla para enseñar del 1 al"<< sizex <<" en el eje x" << endl;
			cin >> checkx;
			cout << endl << "Elige una casilla para enseñar del 1 al"<< sizey <<"en el eje y" << endl;
			cin >> checky;
			gameboard[checkx - 1][checky - 1].showed = true;

			if (gameboard[checkx - 1][checky - 1].has_bomb == true)
			{
			cout << "Boom!Cuidado con tu vida" << endl;
			bombasRes=bombasRes-1;
			p->modificarVida(-20);
			if (p->getVida()<=0)
			{
				cout<<"No te quedan fuerzas para recibir otra explosion" << endl;
				break;
			}
			}
			cout << endl;
			drawBoad(gameboard);
			cout << endl;
		}
		else if(select=='M' || select=='m')
		{
			cout << "Elige una casilla para marcar del 1 al "<< sizex <<" en el eje x" << endl;
			cin >> checkx;
			cout << endl << "Elige una casilla para enseñar del 1 al "<< sizey <<" en el eje y" << endl;
			cin >> checky;
			gameboard[checkx - 1][checky - 1].marked = true;
			if(gameboard[checkx - 1][checky - 1].has_bomb)
			{
				bombasRes=bombasRes-1;
			}
			cout << endl;
			drawBoad(gameboard);
			cout << endl;
		}
		else
		{
			cout << "Aun quedan bombas..." << endl;

		}


		if(bombasRes==0)
		{
			win=true;
			cout<< "ya no quedan bombas!" <<endl;
		}


	}
	if(win && !lose)
	{
		cout<<"click" << endl <<"Bien! la puerta esta abierta"<< endl;
	}
	if(lose)
	{
		cout<<"Has muerto"<<endl;
	}

}
//}


int main()
{

	PlayerBD bd;

	cout << "MONSTER CAVE: \n\n";

	cout << "1. Nueva Partida\n";

	if(bd.hayPlayer()){
		cout << "2. Cargar Partida\n";
	}

	int menu;

	while(menu != 1){
		cin >> menu ;
		if(menu==2 && bd.hayPlayer()){
			break;
		}
	}

	Player *pl;
	if(menu==1){
		cout << "Escribe el nombre de tu personaje: ";
		string nombre;
		cin >> nombre ;
		pl= new Player(nombre);


	}
	else if(menu==2){

		pl=bd.cargarPlayer();

		cout<<pl->getName() <<" "<<pl->getFuerza()<<" "<<pl->getInteligencia()<<" "<<pl->getHistoria(2);

	}

	creaHistoria(pl);

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

	if(menu==1){
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
	}

	int numSala;
	//	Bucle constante
	while (pl->getVida()>=1 && pl->getNumeroSalas()<7){

			if(pl->getNumeroSalas()<7){
				numSala = pl->getHistoria(pl->getNumeroSalas())-1 ;
			}

			if (pl->getNumeroSalas()<= 7)
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
				else if(s[numSala].getTipo()==2)
				{
					if(res=='S'|| res=='s')
					{
					cout<<"Una especie de mecanismo bloquea la puerta, parece que es un panel con celdas para voltear o marcar" <<endl;
					logicaBuscaMinas(pl);
					}
					SalaObjetos sala = SalaObjetos(s[numSala].getCodSala(),s[numSala].getTipo(),s[numSala].getRespuestaCorr(),s[numSala].getTextosSala());
					if(pl->getVida()>0)
					{
					sala.logicaUpdate(pl,numSala,monstruos);
					}
				}


			}
			if(pl->getVida()>1)//Victoria
			{
				cout << s[numSala].getTextoSala(2) << endl;
			}

			pl->modificarNumeroSalas(1);
			cout << "Numero de salas pasadas : " << pl->getNumeroSalas() << endl;

			cout << "Quieres guardar la partida??: (s/n)";
			char r='0';

			if(pl->getVida()>0){

				while (r != 'N' && r != 'S' && r  && r != 'n' && r != 's')
				{
					cin >> r;

				}
				if(r=='s'){
					bd.savePlayer((*pl));
				}
			}


	}
	if(pl->getVida()>=1 &&pl->getNumeroSalas()==7){
//		cout<<"Una especie de mecanismo bloquea la puerta, parece que es un panel con celdas para voltear o marcar" <<endl;
//		logicaBuscaMinas(pl);
		pl->modificarNumeroSalas(1);
		cout << "Numero de salas pasadas : " << pl->getNumeroSalas() << endl;
	}
	if(pl->getVida()>=1 &&pl->getNumeroSalas()==8){
		cout << "Despues de muchas salas pasadas, llegas a una sala bastante curiosa.\nEs como si fuese una armeria muy bestia donde pudieses coger lo que quisieses sin ningun tipo de trampa.\n 'Woooooooooow'- Exclama "
				<< pl->getName() << "\nCorriendo se propone pillar lo mejor para su esbelto cuerpo:\nDe entre todas las armaduras su inteligencia le dice que en vez de coger la de adamantium coja una bolsa de patatas y se la ponga por encima."
				<< "\n De entre todas las armas en vez del sable laser se propone cambiar sus grandes artes culinarias por un muslo de pollo podrido.\nY por ultimo cambia su baston de aprendiz de mago pooooor.... El SUPER BASTON LEGENDARIO DE ANTONIDAS"
				<< endl;
		pl->setFuerza(20);
		pl->setInteligencia(30);
		pl->setVida(700);
		pl->modificarNumeroSalas(1);
		cout << "Numero de salas pasadas : " << pl->getNumeroSalas() << endl;
	}
	if(pl->getVida()>=1 &&pl->getNumeroSalas()==9){
		numSala = 15;
		SalaPeleas sala = SalaPeleas(s[numSala].getCodSala(),s[numSala].getTipo(),s[numSala].getRespuestaCorr(),s[numSala].getTextosSala());
		sala.logicaUpdate(pl,numSala,monstruos);
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
