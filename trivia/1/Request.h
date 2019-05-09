#pragma once
#include <ctime>
#include <vector>
struct Request
{
public:
	Request(int id, std::time_t receivalTime, std::vector<char> buffer);
	~Request();
	int getId();
	std::time_t getReceivalTime();
	std::vector<char> getBuffer();
private:
	int _id;
	std::time_t _receivalTime;
	std::vector<char> _buffer;
};
