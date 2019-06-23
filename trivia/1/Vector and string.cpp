#include "Vector and string.h"

string vectorCharToString(vector<char> v)
{
	std::string str(v.begin(), v.end());
	return str;
}

vector<char> stringToVectorChar(string str)
{
	std::vector<char> v(str.begin(), str.end());

	return v;
}
