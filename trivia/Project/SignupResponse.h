#pragma once
struct SignupResponse
{
public:
	SignupResponse(int status);
	~SignupResponse();

private:
	int _status;
};