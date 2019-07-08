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
	if(_m_handlerFactory!=nullptr)delete(_m_handlerFactory);
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
	std::cout << "Listening on Port " << PORT << std::endl;

	while (true)
		startThreadForNewClient();
}

std::vector<char> bufferOfLoggedUser(string myUser, std::vector<char> buffer)
{
	int size = myUser.size();
	buffer[4] = char(size);
	buffer[3] = char(14 + size);
	std::vector<char> newVec = stringToVectorChar(myUser);
	newVec.push_back('"'); //""\n}
	newVec.push_back('\n');
	newVec.push_back('}');

	buffer.insert(buffer.end(), newVec.begin(), newVec.end());

	return buffer;
}

Request Communicator::getMessageFromClient(SOCKET sc)
{
	std::vector<char> buffer;
	int bytes = FIRST_LENGTH;
	char* data;
	int res;
	for (int i = 0; i < 2 && bytes; i++)//smart read, we read id and size and read more by using the size the know how much more to read
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
			handler->setUsername(LoggedUser(username,socket));
			_m_clients[socket] = handler;
			l.unlock();
			if (req._id == 'X')
				throw("EXIT NOW");
			else if ((req._id == 'O') && username != "")//if we need to log out
				req._buffer = bufferOfLoggedUser(username,req._buffer);
			if (handler->isRequestRelevant(req))
			{
				response = new RequestResult(handler->handleRequest(req, socket));//take care of request
				l.lock();
				_m_clients[socket] = response->getNewHandler();
				l.unlock();

				if ((req._id == 'I' || req._id == 'U') && response->getResponse()[4] == 1)//if the user signed up or logged in
					username=response->getNewHandler()->getUsername().getUsername();
				if (req._id == 'O')//if the user logged out
				{
					username = "";
					l.lock();
					_m_clients[socket] = _m_handlerFactory->createLoginRequestHandler(LoggedUser("",socket));
					l.unlock();

				}
			}
			else
			{
				response = new RequestResult(stringToVectorChar("e"), handler);//if request is irrelevant
				for (int i = 0; i < 3; i++)
					response->_response.push_back(0);
			}
			if(response->_m_whoToSendTo.size()==0)
				sendMsg(vectorCharToString(response->getResponse()), socket);
			else
			{
				if (req._id == 'L')
					sendMsg(vectorCharToString(JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse(1))), socket);

				for (vector<SOCKET>::iterator it = response->_m_whoToSendTo.begin(); it != response->_m_whoToSendTo.end(); it++)
				{
					try 
					{
						sendMsg(vectorCharToString(response->getResponse()), *it);
						if (req._id == 'D')
							_m_clients[*it] = _m_handlerFactory->createMenuRequestHandler(LoggedUser("", *it));
					}
					catch (...) {}
				}
			}
			response->_newHandler = nullptr;//in order to not delete the new handler
			if (response != nullptr)delete(response);
			response = nullptr;
		}
	}
	catch (...)
	{
		vector<char> v;
		for (int i = 0; i < 4; i++)
			v.push_back(0);
		
		IRequestHandler* handler = _m_clients[socket];
		if (handler != nullptr)
		{
			RequestResult* res = nullptr;
			v[0] = 'L';
			Request leaveRoom('L', time(0), v);
			v[0] = 'D';
			Request closeRoom('D', time(0), v);
			if (handler->isRequestRelevant(leaveRoom))//makes sure that if the user joined a room we will leave it before he exits
				res = new RequestResult(handler->handleRequest(leaveRoom, socket));
			else if (handler->isRequestRelevant(closeRoom))//makes sure that if the user created a room it will by closed before he leaves 
				res = new RequestResult(handler->handleRequest(closeRoom, socket));
			if (res != nullptr) 
			{
				for (vector<SOCKET>::iterator it = res->_m_whoToSendTo.begin(); it != res->_m_whoToSendTo.end(); it++)
				{
					try 
					{
						if (*it != socket)
							sendMsg(vectorCharToString(res->getResponse()), *it);
						if (res != nullptr && res->_response[0] == 'd')
							_m_clients[*it] = _m_handlerFactory->createMenuRequestHandler(LoggedUser("", *it));
					}
					catch (...) {}
				}
			}
			if (res != nullptr)
				delete(res);
		}
		if (username != "")//send an exit request to handler that will also log the user out
		{
			vector<char> v1= stringToVectorChar(" {\nusername:\"");
			v[0] = 'X';
			v.push_back(username.size()+14);
			v.push_back(username.size());
			v.insert(v.end(),v1.begin(),v1.end());
			v = bufferOfLoggedUser(username, v); 
			LoginRequestHandler *r = _m_handlerFactory->createLoginRequestHandler(LoggedUser("",socket));
			r->handleRequest(Request('X', time(0), v), socket);
			if(r!=nullptr)delete(r);
			r = nullptr;
			std::unique_lock<std::mutex> l(lock);
			_m_clients.erase(socket);
			l.unlock();
		}
		if (response != nullptr)
			delete(response);
		response = nullptr;
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
	IRequestHandler * handler = (_m_handlerFactory->createLoginRequestHandler(LoggedUser("",client_socket)));// assign first handler

	std::unique_lock<std::mutex> l(lock);
	_m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, handler));
	l.unlock();

	std::cout << "New Client With Socket " << client_socket << std::endl;
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
