#include "SocketController.h"
#include "Error.h"
#include "Console.h"
#include <thread>

using namespace std;

SocketController::SocketController()
{
	_winSocketStarted = false;
	_initialized = false;

	_socketDidConnectCallback = 0;
	_socketDidDisconnectCallback  = 0;
	_socketDidReceiveDataCallback = 0;
	_socketDidFailToReceiveDataCallback = 0;
}

SocketController::~SocketController()
{
	while (!_sockets.empty())
	{
		Socket *socket = _sockets.back();
		disconnect(socket);

		delete socket;
	}

	disconnect(_mainSocket);
}

bool SocketController::disconnect(Socket *socket)
{
	closesocket(socket->getId());
	socketDidDisconnect(socket);

	auto it = find(_sockets.begin(), _sockets.end(), socket);
	if (it == _sockets.end())
		return false;

	_sockets.erase(it);

	return true;
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

Socket * SocketController::getMainSocket()
{
	return _mainSocket;
}

std::vector<Socket*> SocketController::getSockets()
{
	return _sockets;
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

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9999);
	inet_pton(AF_INET, "0.0.0.0", &address.sin_addr.s_addr);

	Error::assert(::bind(sock, (sockaddr*)&address, sizeof(address)) != SOCKET_ERROR, "Could not bind socket.");
	Error::assert(listen(sock, SOMAXCONN) != SOCKET_ERROR, "Could not listen for clients.");

	_mainSocket = new Socket(sock, address, sizeof(address));
	_acceptClientsThread = new thread(&SocketController::acceptLoop, this);

	return true;
}

bool SocketController::initAsClient()
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	Error::assert(sock != SOCKET_ERROR, "Could not open socket.");

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9999);
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);

	int result = connect(sock, (sockaddr*)&address, sizeof(address));
	Error::assert(result != SOCKET_ERROR, "Could not connect to server.");

	_mainSocket = new Socket(sock, address, sizeof(address));

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
		socketDidConnect(socket);
	}
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
			disconnect(socket);
			return;
		}

		if (size == SOCKET_ERROR)
		{
			socketDidFailToReceiveData(socket);
			disconnect(socket);
			return;
		}
		else
		{
			buffer[size] = 0;
			socketDidReceiveData(socket, buffer, size);
		}
	}
}

void SocketController::socketDidConnect(Socket * socket)
{
	Console::log("Socket did connect: %d.", socket->getId());

	_sockets.push_back(socket);
	new thread(&SocketController::handleClient, this, socket);

	if (_socketDidConnectCallback)
		_socketDidConnectCallback(socket);
}

void SocketController::socketDidDisconnect(Socket * socket)
{
	Console::log("Socket did disconnect: %d.", socket->getId());

	if (_socketDidDisconnectCallback)
		_socketDidDisconnectCallback(socket);
}

void SocketController::socketDidFailToReceiveData(Socket * socket)
{
	Console::log("Socket failed to receive data from %d.", socket->getId());

	if (_socketDidFailToReceiveDataCallback)
		_socketDidFailToReceiveDataCallback(socket);
}

void SocketController::socketDidReceiveData(Socket * socket, char * data, size_t size)
{
	Console::log("Socket did receive data from %d.", socket->getId());

	if (_socketDidReceiveDataCallback)
		_socketDidReceiveDataCallback(socket, data, size);
}

void SocketController::setSocketDidConnectCallback(FuncSocketDidConnect callback)
{
	_socketDidConnectCallback = callback;
}

void SocketController::setSocketDidDisconnectCallback(FuncSocketDidDisconnect callback)
{
	_socketDidDisconnectCallback = callback;
}

void SocketController::setSocketDidReceiveDataCallback(FuncSocketDidReceiveData callback)
{
	_socketDidReceiveDataCallback = callback;
}

void SocketController::setSocketDidFailToReceiveDataCallback(FuncSocketDidFailToReceiveData callback)
{
	_socketDidFailToReceiveDataCallback = callback;
}