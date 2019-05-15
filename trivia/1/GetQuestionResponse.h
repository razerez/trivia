#pragma once

#include <iostream>
#include <map>

struct GetQuestionResponse
{
	int _status;
	std::string _question;
	std::map<int, std::string> _answers;
//---------------------------------------
	GetQuestionResponse(int status, std::string question, std::map<int, std::string> answers);
	~GetQuestionResponse();
};