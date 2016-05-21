/*
 * PlayerBD.cpp
 *
 *  Created on: May 21, 2016
 *      Author: jomod
 */

#include "PlayerBD.h"
#include <string>

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

	int* historia= new int[7];

	char *zErrMsg = 0;

	char* a="Select * from Player";

	sqlite3_stmt *stmt;

	sqlite3_prepare_v2(db, a, -1, &stmt, 0);

	int rc = sqlite3_step(stmt);

	new Player(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));

	pl->setFuerza(reinterpret_cast<int>(sqlite3_column_int(stmt, 1)));

	pl->setInteligencia(reinterpret_cast<int>(sqlite3_column_int(stmt, 2)));

	pl->setVida(reinterpret_cast<int>(sqlite3_column_int(stmt, 3)));

	pl->setNumeroSalas(reinterpret_cast<int>(sqlite3_column_int(stmt, 4)));

	int i=5;
	while (i < 12){

		historia[i-5]=reinterpret_cast<int>(sqlite3_column_int(stmt, i));
	}

	pl->setHistoria(historia);

	a="delete from Player"

	sqlite3_exec(db,a,callback,0,&zErrMsg);

	return pl;
}
bool PlayerBD::hayPlayer(){

}
void PlayerBD::savePlayer(Player pl){

}
PlayerBD::~PlayerBD(){

}
