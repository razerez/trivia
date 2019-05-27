#include <iostream>
#include <vector>
#include "JsonRequestPacketDeserializer.h"
#include "LoginRequest.h"
int main()
{
	std::vector<char> buf;
	buf.push_back('U');
	buf.push_back(3); 
	buf.push_back(4);
	buf.push_back(5);
	buf.push_back(0);
	buf.push_back('{');
	buf.push_back('\n');
	buf.push_back('u');
	buf.push_back('s');
	buf.push_back('e');
	buf.push_back('r');
	buf.push_back('n');
	buf.push_back('a');
	buf.push_back('m');
	buf.push_back('e');
	buf.push_back(':');
	buf.push_back(' ');
	buf.push_back('"');
	buf.push_back('r');
	buf.push_back('a');
	buf.push_back('z');
	buf.push_back('"');
	buf.push_back('\n');
	buf.push_back('p');
	buf.push_back('a');
	buf.push_back('s');
	buf.push_back('s');
	buf.push_back('w');
	buf.push_back('o');
	buf.push_back('r');
	buf.push_back('d');
	buf.push_back(':');
	buf.push_back(' ');
	buf.push_back('"');
	buf.push_back('1');
	buf.push_back('2');
	buf.push_back('3');
	buf.push_back('4');
	buf.push_back('"');
	buf.push_back('\n');
	buf.push_back('e');
	buf.push_back('m');
	buf.push_back('a');
	buf.push_back('i');
	buf.push_back('l');
	buf.push_back(':');
	buf.push_back(' ');
	buf.push_back('"');
	buf.push_back('r');
	buf.push_back('a');
	buf.push_back('z');
	buf.push_back('@');
	buf.push_back('c');
	buf.push_back('"');
	buf.push_back('\n');
	buf.push_back('}');
	for (int i = 0; i < buf.size(); i++) {
		std::cout << buf.at(i);
	}
	JsonRequestPacketDeserializer js;
	SignupRequest log = js.deserializeSignupRequest(buf);
	std::cout << std::endl << log._username << ' ' << log._password << ' ' << log._email << std::endl;
	std::cout << "Debbuged!!! :D" << std::endl;
	system("pause");
	return 0;
}