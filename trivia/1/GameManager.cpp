#include "GameManager.h"

GameManager::GameManager(IDataBase * database, std::vector<Game> game)
{
	this->_m_database = database;
	this->_m_game = game;
}

GameManager::~GameManager()
{
}

Game * GameManager::CreateGame(Room room)
{
	vector<Question> myQuestions = this->_m_database->getQuestions(room.getRoomData()._questionCount);
	std::map<LoggedUser*, GameData*> vec;

	for(std::vector<LoggedUser>::iterator it = room.getAllUsers().begin(); it != room.getAllUsers().end(); ++it)
	{
		GameData newGameData(myQuestions.front(), 0, 0, 0);
		std::pair<LoggedUser*, GameData*> myPair(&(*it), &newGameData);
		vec.insert(myPair);
		
	}


	Game myGame(myQuestions, vec);

	this->_m_game.push_back(myGame);

	return &myGame;
}

void GameManager::deleteGame(Game game)
{
	//this->_m_game.pop_back();
}
