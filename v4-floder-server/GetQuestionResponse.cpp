#include "GetQuestionResponse.h"

GetQuestionResponse::GetQuestionResponse(int status, std::string question, std::map<int, std::string> answers)
{
	this->_answers = answers;
	this->_question = question;
	this->_status = status;
}

GetQuestionResponse::~GetQuestionResponse()
{
}
