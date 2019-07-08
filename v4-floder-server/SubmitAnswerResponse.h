#pragma once


struct SubmitAnswerResponse
{
	int _status;
	int _correctAnswerId;
//---------------------------
	SubmitAnswerResponse(int status, int correctAnswerId);
	~SubmitAnswerResponse();
};