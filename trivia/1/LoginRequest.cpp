#include "LoginRequest.h"

LoginRequest::LoginRequest(std::string username, std::string password)
{
	_username = username;
	_password = password;
}

LoginRequest::~LoginRequest()
{
}

