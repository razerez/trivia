#pragma once
#include <ctime>
#include <vector>
struct Request
{
public:
	Request(int id, std::time_t receivalTime, std::vector<char> buffer);
	~Request();
	int _id;
	std::time_t _receivalTime;
	std::vector<char> _buffer;
};
