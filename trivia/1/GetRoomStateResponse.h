#pragma once

#include <iostream>
#include <vector>

struct GetRoomStateResponse
{
	int _status;
	bool _hasGameBegun;
	std::vector<std::string> _players;
	int _questionCount;
	int _answerTimeCount;
//----------------------------
	GetRoomStateResponse(int status, bool haGameBegun, std::vector<std::string> players,
		int questionCount, int answerTimeCount);
	~GetRoomStateResponse();
};
