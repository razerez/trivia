#include "GameManager.h"

std::mutex mutexLockGameManager;

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
	std::unique_lock<std::mutex> myLock(mutexLockGameManager);
	vector<Question> myQuestions;// = this->_m_database->getQuestions(room.getRoomData()._questionCount);
	myLock.unlock();
	std::map<LoggedUser*, GameData*> vec;

	std::vector<LoggedUser> myPlayers= room.getAllUsers();

	for(std::vector<LoggedUser>::iterator it = myPlayers.begin(); it != myPlayers.end(); ++it)
	{
		GameData newGameData(Question("", std::vector<string>()), 0, 0, 0);
		std::pair<LoggedUser*, GameData*> myPair(&(*it), &newGameData);
		vec.insert(myPair);
	}

	myLock.lock();
	int id = 1;// this->_m_database->addNewGame();
	this->_m_game.push_back(Game(myQuestions, vec, this->_m_database, id));
	myLock.unlock();
	return &this->_m_game.back();
}

void GameManager::deleteGame(Game game)
{
	std::unique_lock<std::mutex> myLock(mutexLockGameManager);
	this->_m_game.pop_back();
	myLock.unlock();
}
