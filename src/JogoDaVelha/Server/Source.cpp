#include <iostream>
#include "Semaphore.h"
#include "SocketController.h"
#include "Console.h"

using namespace std;

void socketConnected(Socket *socket);
void socketDisconnected(Socket *socket);
void socketDataFailed(Socket *socket);
void socketData(Socket *socket, char *data, size_t size);

int main(int argc, char *argv[])
{
	SocketController *socketController = SocketController::instance();
	socketController->init(kSocketTypeServer);
	socketController->setSocketDidConnectCallback(socketConnected);
	socketController->setSocketDidDisconnectCallback(socketDisconnected);
	socketController->setSocketDidFailToReceiveDataCallback(socketDataFailed);
	socketController->setSocketDidReceiveDataCallback(socketData);

	while (true);

	delete socketController;

	return 0;
}

void socketConnected(Socket * socket)
{
	Console::log("Socket connected: %d", socket->getId());
}

void socketDisconnected(Socket * socket)
{
	Console::log("Socket disconnected: %d", socket->getId());
}

void socketDataFailed(Socket * socket)
{
	Console::log("Failed to receive data from socket %d", socket->getId());
}

void socketData(Socket * socket, char * data, size_t size)
{
	Console::log("Received data from socket %d: %s", socket->getId(), data);
}
