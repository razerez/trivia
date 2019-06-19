#include "Communicator.h"
#define FIRST_LENGTH 4
std::mutex lock;
Communicator::Communicator(IDataBase * db)
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//new socket
	if (serverSocket == INVALID_SOCKET)//if it didn't work
		throw std::exception(__FUNCTION__ " - socket");
	_m_handlerFactory = new RequestHandlerFactory(db);
}


Communicator::~Communicator()
{
	std::unique_lock<std::mutex> l(lock);
	_m_clients.clear();
	l.unlock();
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
										// Connects between the socket and the configuration (port and etc..)
	if (bind(serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
		startThreadForNewClient();
}


Request Communicator::getMessageFromClient(SOCKET sc)
{
	std::vector<char> buffer;
	int bytes = FIRST_LENGTH;
	char* data;
	int res;
	for (int i = 0; i < 2 && bytes; i++)
	{
		data = new char[bytes + 1];
		res = recv(sc, data, bytes, 0);
		if (res == INVALID_SOCKET)
		{
			std::string s = "Error while recieving from socket: " + std::to_string(sc);
			throw std::exception(s.c_str());
		}
		data[bytes] = 0;
		for (size_t i = 0; i < bytes; i++)
			buffer.push_back(data[i]);
		if (!i)
			bytes = int((unsigned char)(data[1]) << 16 |//get length of data
			(unsigned char)(data[2]) << 8 |
				(unsigned char)(data[3]));
		delete(data);
		data = nullptr;
	}
	Request r(buffer[0], time(0), buffer);
	return r;
}


void Communicator::clientHandler(SOCKET socket)
{
	string username = "";
	RequestResult * response = nullptr;
	try
	{
		while (true)
		{
			Request req(getMessageFromClient(socket));// get request from client
			std::unique_lock<std::mutex> l(lock);
			IRequestHandler* handler = _m_clients[socket];
			l.unlock();
			if ((req._buffer[0] == 'X' || req._buffer[0] == 'O') && username != "")//if we need to quit
			{
				for (int i = 0; i < username.size(); i++)
					req._buffer.push_back(username[i]);
				req._buffer[3] = username.size();
			}
			if (handler->isRequestRelevant(req))
			{
				response = new RequestResult(handler->handleRequest(req));//take care of request
				l.lock();
				_m_clients[socket] = response->getNewHandler();
				l.unlock();
				if ((req._buffer[0] == 'I' || req._buffer[0] == 'U') && response->getResponse()[4] == 1)
				{
					void* menuHandler = response->getNewHandler();
					username = static_cast<MenuRequestHandler*>(menuHandler)->getUser();
				}
				if (req._buffer[0] == 'O')
					username = "";
			}
			else
			{
				response = new RequestResult(stringToVectorChar("e"), handler);//if request is irrelevant
				for (int i = 0; i < 3; i++)
					response->_response.push_back('0');
			}
			if (req._buffer[0] != 'X')
				sendMsg(vectorCharToString(response->getResponse()), socket);
			else//EXIT
			{
				if (response != nullptr)
					delete(response);
				exit(socket);
				return;
			}
			response->_newHandler = nullptr;//in order to not delete the new handler
			if (response != nullptr)delete(response);
		}
	}
	catch (...)
	{
		if (username != "")
		{
			vector<char> v;
			v.push_back('X');
			v.push_back(0);
			v.push_back(0);
			v.push_back(username.size());
			for (int i = 0; i < username.size(); i++)
				v.push_back(username[i]);
			LoginRequestHandler *r = _m_handlerFactory->createLoginRequestHandler();
			r->handleRequest(Request('X', time(0), v));
			delete(r);
			r = nullptr;
		}
		if (response != nullptr)
			delete(response);
		exit(socket);
		return;
	}

}




void Communicator::sendMsg(string message, SOCKET sc)
{
	const char* data = message.c_str();
	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}


void Communicator::startThreadForNewClient()
{
	SOCKET client_socket = ::accept(serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	IRequestHandler * handler = (_m_handlerFactory->createLoginRequestHandler());// assign first handler

	std::unique_lock<std::mutex> l(lock);
	_m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, handler));
	l.unlock();

	std::cout << "New Client. Socket: " << client_socket << std::endl;
	std::thread  t1(&Communicator::clientHandler, this, client_socket);//new thread for the client
	t1.detach();//thread can work separately
}


void Communicator::exit(SOCKET s)
{
	cout << "Client With Socket " << s << " Exited" << endl;
	std::unique_lock<std::mutex> l(lock);
	_m_clients.erase(s);
	l.unlock();
}







