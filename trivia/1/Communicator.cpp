#include "Communicator.h"

Communicator::Communicator(IDataBase * db)
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//new socket
	if (serverSocket == INVALID_SOCKET)//if it didn't work
		throw std::exception(__FUNCTION__ " - socket");
	_m_handlerFacroty = new RequestHandlerFactory(db);
}

Communicator::~Communicator()
{
	_m_clients.clear();
	delete(_m_handlerFacroty);
	_m_handlerFacroty = nullptr;
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

void Communicator::handleRequests()
{
}

Request Communicator::getMessageFromClient() 
{
	vector<char> v;
	time_t t=0;
	Request r(1, t, v);
	return r;
}

void Communicator::clientHandler(SOCKET socket)
{
	while(true)
	{
		try
		{
			RequestResult * response;
			
			Request req(getMessageFromClient());
			IRequestHandler* handler = (*_m_clients.find(socket)).second;
			if (handler==nullptr)
			{
				return;
			}
			if (handler->isRequestRelevant(req))
			{
				response = new RequestResult(handler->handleRequest(req));
			}
			else
			{
				string errorString="";
				vector<char> vectorOfResponse;
				response=new RequestResult(vectorOfResponse,handler);
			}
			sendMsg(vectorCharToString(response->getResponse()), socket);
		}
		catch (...) {

		}
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
	// notice that we step out to the global namespace
	// for the resolution of the function accept
	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	IRequestHandler * handler;
	handler=&(_m_handlerFacroty->createLoginRequestHandler());
	_m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket,handler));
	std::cout << "Client accepted. Server and client can speak" << std::endl;

	std::thread  t1(&Communicator::clientHandler, this, client_socket);//new thread for the client
	t1.detach();
}
