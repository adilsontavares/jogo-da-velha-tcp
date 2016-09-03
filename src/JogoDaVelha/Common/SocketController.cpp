#include "SocketController.h"
#include "Error.h"
#include "Console.h"
#include <thread>

using namespace std;

SocketController::SocketController()
{
	_winSocketStarted = false;
	_initialized = false;
}

SocketController * SocketController::instance()
{
	static SocketController *instance = 0;
	if (!instance)
		instance = new SocketController();
	return instance;
}

bool SocketController::init(SocketType socketType)
{
	Error::assert(!_initialized, "SocketController is already initialized.");
	Error::assert(init(), "Could not initialize for using sockets.");

	switch (socketType)
	{
	case kSocketTypeServer:
		_initialized = initAsServer();
		break;
	case kSocketTypeClient:
		_initialized = initAsClient();
		break;
	default:
		Error::fatal("Socket type is not allowed: %d", socketType);
		break;
	}

	return _initialized;
}

bool SocketController::init()
{
	if (!_winSocketStarted)
	{
		WSAData data;
		WSAStartup(MAKEWORD(2, 2), &data);
		_winSocketStarted = true;
	}

	return true;
}

bool SocketController::initAsServer()
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	Error::assert(sock != SOCKET_ERROR, "Could not open socket.");

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr.s_addr);

	Error::assert(::bind(sock, (sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR, "Could not bind socket.");
	Error::assert(listen(sock, SOMAXCONN) != SOCKET_ERROR, "Could not listen for clients.");

	_acceptClientsThread = new thread(&SocketController::acceptLoop);

	return true;
}

void SocketController::acceptLoop()
{
	while (true)
	{
		sockaddr_in caddress;
		socklen_t caddressLength = sizeof(caddress);

		int sock = accept(_mainSocket->getId(), (sockaddr*)&caddress, &caddressLength);
		if (sock == SOCKET_ERROR)
		{
			Console::warning("Could not accept client socket: %d", sock);
			continue;
		}

		Socket *socket = new Socket(sock, caddress, caddressLength);
		_sockets.push_back(socket);
	}
}

bool SocketController::initAsClient()
{


	return true;
}

void SocketController::handleClient(Socket *socket)
{
	size_t size;
	char buffer[1024];

	while (true)
	{
		size = recv(socket->getId(), buffer, sizeof(buffer) - 1, 0);

		if (size == 0)
		{
			socketWasDisconnected(socket);
			return;
		}

		if (size == SOCKET_ERROR)
			socketFailedToReceiveData(socket);
		else
		{
			buffer[size] = 0;
			socketDidReceiveData(socket, buffer, size);
		}
	}
}

void SocketController::socketWasDisconnected(Socket * socket)
{
}

void SocketController::socketFailedToReceiveData(Socket * socket)
{
}

void SocketController::socketDidReceiveData(Socket * socket, char * data, size_t size)
{
}
