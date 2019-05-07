#pragma once
struct LoginResponse
{
public:
	LoginResponse(int status);
	~LoginResponse();

private:
	int _status;

};