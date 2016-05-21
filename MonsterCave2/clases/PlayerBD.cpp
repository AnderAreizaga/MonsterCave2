/*
 * PlayerBD.cpp
 *
 *  Created on: May 21, 2016
 *      Author: jomod
 */

#include "PlayerBD.h"
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   return 0;
}

PlayerBD::PlayerBD(){
	int a;
	char *zErrMsg = 0;

	a=sqlite3_open("playerDB.db", &db);

	char* b ="CREATE TABLE Player("  \
		         "nombre varchar(10) PRIMARY KEY     NOT NULL," \
		         "fuerza number(2)    NOT NULL," \
				 "inteligencia number(2)   NOT NULL," \
				 "vida number(3)   NOT NULL," \
				 "numSalas number(2)  NOT NULL," \
				 "hist0 number(2)  NOT NULL," \
				 "hist1 number(2)  NOT NULL," \
				 "hist2 number(2)  NOT NULL," \
				 "hist3 number(2)  NOT NULL," \
				 "hist4 number(2)  NOT NULL," \
				 "hist5 number(2)  NOT NULL," \
				 "hist6 number(2)  NOT NULL);";

	a=sqlite3_exec(db,b,callback,0,&zErrMsg);

}
Player* PlayerBD::cargarPlayer(){

	Player* pl;

	int historia[7];

	char *zErrMsg = 0;

	char* a="Select * from Player";

	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(db, a, -1, &stmt, 0);

	int rc = sqlite3_step(stmt);

	pl=new Player(string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))));

	pl->setFuerza(reinterpret_cast<int>(sqlite3_column_int(stmt, 1)));

	pl->setInteligencia(reinterpret_cast<int>(sqlite3_column_int(stmt, 2)));

	pl->setVida(reinterpret_cast<int>(sqlite3_column_int(stmt, 3)));

	pl->setNumeroSalas(reinterpret_cast<int>(sqlite3_column_int(stmt, 4)));

	historia[0]=reinterpret_cast<int>(sqlite3_column_int(stmt, 5));
	historia[1]=reinterpret_cast<int>(sqlite3_column_int(stmt, 6));
	historia[2]=reinterpret_cast<int>(sqlite3_column_int(stmt, 7));
	historia[3]=reinterpret_cast<int>(sqlite3_column_int(stmt, 8));
	historia[4]=reinterpret_cast<int>(sqlite3_column_int(stmt, 9));
	historia[5]=reinterpret_cast<int>(sqlite3_column_int(stmt, 10));
	historia[6]=reinterpret_cast<int>(sqlite3_column_int(stmt, 11));

	pl->setHistoria(historia);

	a="delete from Player";

	sqlite3_exec(db,a,callback,0,&zErrMsg);

	return pl;
}
bool PlayerBD::hayPlayer(){
	char* a="Select count(*) from Player";

	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(db, a, -1, &stmt, 0);
	sqlite3_step(stmt);

	if(0==sqlite3_column_int(stmt, 0)){
		return false;
	}else{
		return true;
	}
}
void PlayerBD::savePlayer(Player pl){

	char *zErrMsg = 0;
	int  rc;
	char sql[500]="";
	char fuerza[3];
	char inteligencia[3];
	char vida[4];
	char numSalas[3];
	char hist0[4];
	char hist1[4];
	char hist2[4];
	char hist3[4];
	char hist4[4];
	char hist5[4];
	char hist6[4];

	sprintf(fuerza, "%i", pl.getFuerza());
	sprintf(inteligencia, "%i", pl.getInteligencia());
	sprintf(vida, "%i", pl.getVida());
	sprintf(numSalas, "%i", pl.getNumeroSalas());
	sprintf(hist0, "%i", pl.getHistoria(0));
	sprintf(hist1, "%i", pl.getHistoria(1));
	sprintf(hist2, "%i", pl.getHistoria(2));
	sprintf(hist3, "%i", pl.getHistoria(3));
	sprintf(hist4, "%i", pl.getHistoria(4));
	sprintf(hist5, "%i", pl.getHistoria(5));
	sprintf(hist6, "%i", pl.getHistoria(6));


	strcat(sql,"INSERT INTO Player (nombre,fuerza,inteligencia,vida,numSalas,hist0,hist1,hist2,hist3,hist4,hist5,hist6) ");
	strcat(sql, "values('");
	strcat(sql,pl.getName().c_str());
	strcat(sql, "',");
	strcat(sql,fuerza);
	strcat(sql, ",");
	strcat(sql,inteligencia);
	strcat(sql, ",");
	strcat(sql,vida);
	strcat(sql, ",");
	strcat(sql,numSalas);
	strcat(sql, ",");
	strcat(sql,hist0);
	strcat(sql, ",");
	strcat(sql,hist1);
	strcat(sql, ",");
	strcat(sql,hist2);
	strcat(sql, ",");
	strcat(sql,hist3);
	strcat(sql, ",");
	strcat(sql,hist4);
	strcat(sql, ",");
	strcat(sql,hist5);
	strcat(sql, ",");
	strcat(sql,hist6);
	strcat(sql, ");");

	cout<< sql;

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

}
PlayerBD::~PlayerBD(){
	sqlite3_close(db);
}
