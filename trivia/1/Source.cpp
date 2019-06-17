#include <iostream>
#include <vector>
#include "SqliteDatabase.h"
#include "Server.h"
#include "JsonResponsePacketSerializer.h"


int main()
{
	SqliteDatabase * myDatabase = new SqliteDatabase{};
	Server server(myDatabase);
	server.run();

	system("pause");
	return 0;
}