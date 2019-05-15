#pragma once

#include "PlayerResults.h"
#include <vector>

struct GetGameResultsResponse 
{
	int _status;
	std::vector<PlayerResults> _result;
//----------------------------------------------
	GetGameResultsResponse(int status, std::vector<PlayerResults> result);
	~GetGameResultsResponse();

};