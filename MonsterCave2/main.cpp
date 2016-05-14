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

void creaHistoria(Player* p)
{
	int x ;
	int j;
	int i=0;
	int historia[7];
	for(unsigned int i=0;i<sizeof(historia);i++){
		historia[i]=p->getHistoria(i);
	}
	srand(time(NULL));
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

int main()
{
}

