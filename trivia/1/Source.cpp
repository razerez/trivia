#include <iostream>
#include <vector>
#include "SqliteDatabase.h"
#include "Server.h"
#include "JsonResponsePacketSerializer.h"


int main()
{

	std::vector<std::string> names;
	names.push_back("nitay");
	names.push_back("elay");
	names.push_back("raz");

	GetRoomStateResponse l(1, 0, names, 5, 7);

	std::vector<char> path = JsonResponsePacketSerializer::serializeResponse(l);

	for (std::vector<char>::iterator i = path.begin(); i != path.end(); ++i)
		std::cout << *i;

	system("pause");

	SqliteDatabase * myDatabase = new SqliteDatabase{};
	Server server(myDatabase);
	server.run();
	if(myDatabase!=nullptr)delete(myDatabase);
	myDatabase = nullptr;
	system("pause");
	return 0;
}