#pragma once

#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include <vector>



class GameManager
{
	IDataBase * _m_database;
	std::vector<Game> _m_game;
public:
	GameManager(IDataBase * database, std::vector<Game> game);
	~GameManager();

	Game CreateGame(Room room);
	void deleteGame();


};