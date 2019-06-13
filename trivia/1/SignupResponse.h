#pragma once
struct SignupResponse
{
public:
	SignupResponse(int status);
	~SignupResponse();
	int _status;
};