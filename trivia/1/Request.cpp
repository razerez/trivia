#include "Request.h"

Request::Request(int id, std::time_t receivalTime, std::vector<char> buffer)
{
	this->_id = id;
	this->_receivalTime = receivalTime;
	this->_buffer = buffer;
}

Request::~Request()
{
}

int Request::getId()
{
	return this->_id;
}

std::time_t Request::getReceivalTime()
{
	return this->_receivalTime;
}

std::vector<char> Request::getBuffer()
{
	return this->_buffer;
}
