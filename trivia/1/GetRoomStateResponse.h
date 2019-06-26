#pragma once

#include <iostream>
#include <vector>

struct GetRoomStateResponse
{
	int _status;
	bool _hasGameBegun;
	std::vector<std::string> _players;
	int _questionCount;
	int _answerTimeount;
//----------------------------
	GetRoomStateResponse(int status, bool hasGameBegun, std::vector<std::string> players,
		int questionCount, int answerTimeount);
	~GetRoomStateResponse();
};
