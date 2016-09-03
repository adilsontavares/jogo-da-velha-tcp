#include <iostream>
#include "SocketController.h"

using namespace std;

int main(int argc, char *argv[])
{
	SocketController *socketController = SocketController::instance();
	socketController->init(kSocketTypeClient);

	char message1[] = "Hello, server!";
	char message2[] = "It's my second message...";
	char message3[] = "Goodbye!";
		
	Socket *socket = socketController->getMainSocket();
	socket->send(message1, sizeof(message1));
	socket->send(message2, sizeof(message2));
	socket->send(message3, sizeof(message3));

	Sleep(2000);

	delete socketController;

	return 0;
}