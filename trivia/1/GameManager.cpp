#include "GameManager.h"

GameManager::GameManager(IDataBase * database, std::vector<Game> game)
{
	this->_m_database = database;
	this->_m_game = game;
}

GameManager::~GameManager()
{
}

Game GameManager::CreateGame(Room room)
{

	std::vector<Question> vec1;
	std::map<LoggedUser, GameData> vec2;
	return Game(vec1, vec2);
}

void GameManager::deleteGame()
{
}
