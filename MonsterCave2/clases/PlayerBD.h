/*
 * PlayerBD.h
 *
 *  Created on: May 21, 2016
 *      Author: jomod
 */

#include <string>
#include <iostream>
#include "player.h"
#include "sqlite3.h"
using namespace players;

#ifndef BD_PLAYERBD_H_
#define BD_PLAYERBD_H_

class PlayerBD{
private:
	sqlite3 *db;
public:
	PlayerBD();
	void savePlayer(Player pl);
	bool hayPlayer();
	Player* cargarPlayer();
	~PlayerBD();

};



#endif /* BD_PLAYERBD_H_ */
