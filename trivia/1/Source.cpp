#include <iostream>
#include <vector>
#include "SqliteDatabase.h"
#include "Server.h"

int main()
{
	std::cout << "Debbuged!!! :D" << std::endl;
	SqliteDatabase * myDatabase = new SqliteDatabase{};
	Server server(myDatabase);
	server.run();

	system("pause");
	return 0;
}