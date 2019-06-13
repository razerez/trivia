#include "GetGameResultsResponse.h"

GetGameResultsResponse::GetGameResultsResponse(int status, std::vector<PlayerResults> result)
{
	this->_result = result;
	this->_status = status;
}

GetGameResultsResponse::~GetGameResultsResponse()
{
}
