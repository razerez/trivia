#include "SignupRequest.h"

SignupRequest::SignupRequest(std::string username, std::string password, std::string email)
{
	_username = username;
	_password = password;
	_email = email;
}

SignupRequest::~SignupRequest()
{
}
