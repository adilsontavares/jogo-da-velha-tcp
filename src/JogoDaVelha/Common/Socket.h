#pragma once

#include <WS2tcpip.h>

class Socket
{
private:

	int _socket;
	sockaddr_in _address;
	socklen_t _addressLength;

public:

	Socket(SOCKET socket, sockaddr_in address, socklen_t addressLength);

	int getId();

	void sendTo(Socket * socket, char *buffer, size_t size);
	void send(char * buffer, size_t size);
};

