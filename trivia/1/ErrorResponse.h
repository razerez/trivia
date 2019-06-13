#pragma once
#include <string>
struct ErrorResponse
{
	ErrorResponse(std::string message);
	~ErrorResponse();

	std::string message;
};