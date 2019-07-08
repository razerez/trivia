#include "JsonResponsePacketSerializer.h"



std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorRes)
{
	
	std::vector<char> vec;
	vec.push_back('e');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b0);

	return vec;
	
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes)
{
	std::vector<char> vec;
	vec.push_back('i');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(loginRes._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signupRes)
{
	std::vector<char> vec;
	vec.push_back('u');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(signupRes._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutRes)
{
	std::vector<char> vec;
	vec.push_back('o');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(logoutRes._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse roomRes)
{
	std::cout << "Sending Rooms: ";
	std::string data = " {\nlength:" + std::to_string(roomRes._rooms.size()) + "\nRooms[";



	for (std::vector<RoomData>::iterator it = roomRes._rooms.begin(); it != roomRes._rooms.end(); ++it)
	{
		data += "\n\"" + (*it)._name + "\":" + std::to_string((*it)._id);
		std::cout << "-" << (*it)._name << ":" << std::to_string((*it)._id);
	}

	std::cout << "-\n";

	data += "\n]\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('g');


	int size = data.size();

	optionAndLenghVec.push_back(0b0);

	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;

	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);

	std::vector<char> dataVector = stringToVectorChar(data);
	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	return optionAndLenghVec;	
}





std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse playerInRoomRes)
{
	std::string data = " {\nlength:" + std::to_string(playerInRoomRes._players.size()) + "\nNames[";

	std::cout << "Sending Names: ";

	for (std::vector<std::string>::iterator it = playerInRoomRes._players.begin(); it != playerInRoomRes._players.end(); ++it)
	{
		data += "\n\"" + (*it) + "\"";
		std::cout << "-" << (*it);
	}

	std::cout << "-\n";

	data += "\n]\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('p');

	int size = data.size();
	
	optionAndLenghVec.push_back(0b0);

	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;

	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);
	

	std::vector<char> dataVector = stringToVectorChar(data);

	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	
	return optionAndLenghVec;
	
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse roomRes)
{
	
	std::vector<char> vec;
	vec.push_back('j');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(roomRes._status);
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomRes)
{
	std::vector<char> vec;
	vec.push_back('c');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(createRoomRes._status);
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(HighscoreResponse highscoreRes)
{
	
	std::string data = " {\nlength:" + std::to_string(highscoreRes._highscores.getHighscores().size()) + "\nHighscores[";
	
	map<LoggedUser*, int> mymap = highscoreRes._highscores.getHighscores();
	
	std::cout << "Sending Highscores: ";

	for (std::map<LoggedUser*, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		data += "\n\"" + it->first->getUsername() + "\":" + std::to_string(it->second);
		std::cout << "-" << it->first->getUsername() << ":" << std::to_string(it->second);
	}

	std::cout << "-\n";

	data += "\n]\n}";

	//copy this
	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('h');
	int size = data.size(); //change this number of items you push
	optionAndLenghVec.push_back(0b0);
	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;
	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);
	//push items(as char(item))
	std::vector<char> dataVector = stringToVectorChar(data);
	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	return optionAndLenghVec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoomRes)
{
	std::vector<char> vec;
	vec.push_back('d');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(closeRoomRes._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGameRes)
{
	std::vector<char> vec;
	vec.push_back('s');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(startGameRes._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomStatRes)
{

	bool mybool = getRoomStatRes._hasGameBegun;
	int boolInt = mybool ? 1 : 0;

	std::string str = " {\nStatus:\"" + std::to_string(getRoomStatRes._status) 
		+ "\"\nHasStarted:\"" + std::to_string(boolInt)
		+ "\"\nQuestionCount:\"" + std::to_string(getRoomStatRes._questionCount) 
		+ "\"\nAnswerTimeout:\"" + std::to_string(getRoomStatRes._answerTimeount) 
		+ "\"\nlength:\"" + std::to_string(getRoomStatRes._players.size()) + "\""
		+ "\nNames[";
	

	for (std::vector<std::string>::iterator it = getRoomStatRes._players.begin(); it != getRoomStatRes._players.end(); ++it)
	{
		str += "\n\"" + (*it) + "\"";
	}

	str += "\n]\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('r');

	int size = str.size()+5;
	
	optionAndLenghVec.push_back(0b0);

	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;

	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);
	optionAndLenghVec.push_back(1);
	optionAndLenghVec.push_back(1);
	optionAndLenghVec.push_back(char(std::to_string(getRoomStatRes._questionCount).length()));
	optionAndLenghVec.push_back(char(std::to_string(getRoomStatRes._answerTimeount).length()));
	optionAndLenghVec.push_back(char(std::to_string(getRoomStatRes._players.size()).length()));
	

	std::vector<char> dataVector = stringToVectorChar(str);

	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	
	return optionAndLenghVec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomRes)
{
	std::vector<char> vec;
	vec.push_back('l');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(leaveRoomRes._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(MyStatusResponse myStatus)
{
	float avr = myStatus._m_avgTimePerQuestion;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << avr;
	std::string avrString = stream.str();

	int numOfGames = std::to_string(myStatus._m_numGames).size();
	int numRight = std::to_string(myStatus._m_numRight).size();
	int numWrong = std::to_string(myStatus._m_numWrong).size();
	int avgTimePerAns = avrString.size();





	std::string data = " {\nNumberOfGames:\"" + std::to_string(myStatus._m_numGames)
		+ "\"\nNumRight:\"" + std::to_string(myStatus._m_numRight)
		+ "\"\nNumWrong:\"" + std::to_string(myStatus._m_numWrong)
		+ "\"\nAvgTimePerAns:\"" + avrString + "\"\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('m');


	int size = data.size() + 4;

	optionAndLenghVec.push_back(0b0);

	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;

	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);

	optionAndLenghVec.push_back(char(numOfGames));
	optionAndLenghVec.push_back(char(numRight));
	optionAndLenghVec.push_back(char(numWrong));
	optionAndLenghVec.push_back(char(avgTimePerAns));

	std::vector<char> dataVector = stringToVectorChar(data);
	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	return optionAndLenghVec;
}


std::vector<char> JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse submitAnswerRes)
{
	std::string data = "{\nStatus:\"" + std::to_string(submitAnswerRes._status) + "\",\nCurrectAnswerId:\"" + std::to_string(submitAnswerRes._correctAnswerId) + "\",\n}";
	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('a');
	int size = data.size() + 2;
	optionAndLenghVec.push_back(0b0);
	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;
	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);
	optionAndLenghVec.push_back(char(std::to_string(submitAnswerRes._status).size()));
	optionAndLenghVec.push_back(char(std::to_string(submitAnswerRes._correctAnswerId).size()));
	std::vector<char> dataVector = stringToVectorChar(data);
	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	return optionAndLenghVec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse questionRes)
{
	std::string data = "{\nStatus:\"" + std::to_string(questionRes._status) + "\",\nQuestion:\"" + questionRes._question + "\"\nAnswers:\n{";
	for (std::map<int, std::string>::iterator it = questionRes._answers.begin(); it != questionRes._answers.end(); ++it)
	{
		data += "\n\"" + std::to_string(it->first) + "\":\"" + it->second + "\"";
		std::cout << "-" << std::to_string(it->first) << ":" << it->second;
	}
	std::cout << "-\n";
	data += "\n}\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('q');
	int size = data.size() + 2;
	optionAndLenghVec.push_back(0b0);
	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;
	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);
	optionAndLenghVec.push_back(char(std::to_string(questionRes._status).size()));
	optionAndLenghVec.push_back(char(questionRes._question.size()));
	std::vector<char> dataVector = stringToVectorChar(data);
	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	return optionAndLenghVec;

}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse gameResultRes)
{
	std::string data = "{\nStatus:\"" + std::to_string(gameResultRes._status) + "\",\nResults:\n[\n";
	for (std::vector<PlayerResults>::iterator it = gameResultRes._result.begin(); it != gameResultRes._result.end(); ++it)
	{
		data += "{\nusername:\"" + it->_username + "\",\ncorrectAnswerCount:\"" + std::to_string(it->_correctAnswerCount) + "\",\n}\n";
	}
	data += "]\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('z');
	int size = data.size() + 1;
	optionAndLenghVec.push_back(0b0);
	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;
	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);
	optionAndLenghVec.push_back(char(std::to_string(gameResultRes._status).size()));
	std::vector<char> dataVector = stringToVectorChar(data);
	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	return optionAndLenghVec;
}

