#include "ErrorResponse.h"

ErrorResponse::ErrorResponse(std::string message)
{
	this->message = message;
}

ErrorResponse::~ErrorResponse()
{
}
