#include "LoginRequest.h"

LoginRequest::LoginRequest(std::string username, std::string password)
{
	_username = username;
	_password = password;
}

LoginRequest::~LoginRequest()
{
}

std::string LoginRequest::getUsername()
{
	return this->getUsername;
}

std::string LoginRequest::getPassword()
{
	return this->_password;
}

