#include "Communicator.h"

Communicator::Communicator(IDataBase * db)
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//new socket
	if (serverSocket == INVALID_SOCKET)//if it didn't work
		throw std::exception(__FUNCTION__ " - socket");
	_m_handlerFactory = new RequestHandlerFactory(db,LoggedUsers);
}

Communicator::~Communicator()
{
	_m_clients.clear();
	delete(_m_handlerFactory);
	_m_handlerFactory = nullptr;
	try
	{
		closesocket(serverSocket);//if you exit
	}
	catch (...) {}
}

void Communicator::bindAndListen()
{
	
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		startThreadForNewClient();
	}
}


Request Communicator::getMessageFromClient(SOCKET sc)
{
	string dataString = "";
	int bytes = 4;
	char* data;
	int res;
	/*
	this is the problem
	dont get all the buffer
	*/
	for (int i = 0; i < 2; i++)
	{
		data= new char[bytes + 1];
		res = recv(sc, data, bytes, 0);

		if (res == INVALID_SOCKET)
		{
			std::string s = "Error while recieving from socket: ";
			s += std::to_string(sc);
			throw std::exception(s.c_str());
		}
		data[bytes] = 0;
		dataString += data;
		if (!i)bytes = int((unsigned char)(dataString[1]) << 16 |
			(unsigned char)(dataString[2]) << 8 |
			(unsigned char)(dataString[3]));
		delete(data);
		data = nullptr;
	}
	vector<char> v=stringToVectorChar(dataString);
	time_t t=time(0);
	int id = dataString[0];
	Request r(id, t, v);

	std::cout << "this is my request:\n" << r._id << "\n" << r._receivalTime << std::endl;
	std::cout << "the buffer is:\n";
	for (std::vector<char>::const_iterator i = r._buffer.begin(); i != r._buffer.end(); ++i)
		std::cout << *i << ' ';
	std::cout << "\n" << std::endl;


	return r;
}

void Communicator::clientHandler(SOCKET socket)
{
	try
	{
		while (true)
		{
			std::cout << "enter to here" << std::endl;
			RequestResult * response;
			Request req(getMessageFromClient(socket));
			IRequestHandler* handler = _m_clients[socket];
			if (handler == nullptr)
				response = new RequestResult(stringToVectorChar("x"), handler);
			else if (handler->isRequestRelevant(req))
			{
				response = new RequestResult(handler->handleRequest(req));
				_m_clients[socket] = response->getNewHandler();
			}
			else
				response = new RequestResult(stringToVectorChar("e"), handler);

			sendMsg(vectorCharToString(response->getResponse()), socket);
			if (response->getNewHandler() == nullptr)//EXIT
			{
				if (response != nullptr)delete(response);
				_m_clients.erase(socket);
				return;
			}
			if (response != nullptr)delete(response);
		}
	}
	catch (...) 
	{
		std::cout << "error" << std::endl;
	}
	
}
string Communicator::vectorCharToString(vector<char> v)
{
	std::string str(v.begin(), v.end());
	return str;
}
vector<char> Communicator::stringToVectorChar(string str)
{
	std::vector<char> v(str.begin(), str.end());
	v.push_back('\0');
	return v;
}
void Communicator::sendMsg(string message, SOCKET sc)
{
	const char* data = message.c_str();
	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}


void Communicator::startThreadForNewClient()
{
	SOCKET client_socket = ::accept(serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	IRequestHandler * handler;
	handler=(_m_handlerFactory->createLoginRequestHandler());
	_m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket,handler));
	std::cout << "Client accepted. Server and client can speak" << std::endl;

	std::thread  t1(&Communicator::clientHandler, this, client_socket);//new thread for the client
	t1.detach();//thread can work separately
}
