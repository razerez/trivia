#include "SubmitAnswerResponse.h"

SubmitAnswerResponse::SubmitAnswerResponse(int status, int correctAnswerId)
{
	this->_correctAnswerId = correctAnswerId;
	this->_status = status;
}

SubmitAnswerResponse::~SubmitAnswerResponse()
{
}
