#include "GameManager.h"

std::mutex mutexLock;

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
	std::unique_lock<std::mutex> myLock(mutexLock);
	vector<Question> myQuestions = this->_m_database->getQuestions(room.getRoomData()._questionCount);
	myLock.unlock();
	std::map<LoggedUser*, GameData*> vec;

	for(std::vector<LoggedUser>::iterator it = room.getAllUsers().begin(); it != room.getAllUsers().end(); ++it)
	{
		GameData newGameData(myQuestions.front(), 0, 0, 0);
		std::pair<LoggedUser*, GameData*> myPair(&(*it), &newGameData);
		vec.insert(myPair);
		
	}

	std::unique_lock<std::mutex> myLock(mutexLock);
	int id = this->_m_database->addNewGame();
	Game myGame(myQuestions, vec, this->_m_database, id);
	this->_m_game.push_back(myGame);
	myLock.unlock();
	return &myGame;
}

void GameManager::deleteGame(Game game)
{
	std::unique_lock<std::mutex> myLock(mutexLock);
	this->_m_game.pop_back();
	myLock.unlock();
}
