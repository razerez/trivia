#pragma once
#include <string>
class ErrorResponse
{
public:
	ErrorResponse(std::string message);
	~ErrorResponse();

private:
	std::string message;
};