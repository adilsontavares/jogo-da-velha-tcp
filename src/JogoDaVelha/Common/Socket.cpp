#include "Socket.h"
#include <iostream>

Socket::Socket(SOCKET socket, sockaddr_in address, socklen_t addressLength)
{
	_socket = socket;
	_address = address;
	_addressLength = addressLength;
}

int Socket::getId()
{
	return _socket;
}

void Socket::sendTo(Socket * socket, char * buffer, size_t size)
{
	sendto(socket->getId(), buffer, size, 0, (sockaddr*)&socket->_address, socket->_addressLength);
}

void Socket::send(char * buffer, size_t size)
{
	sendTo(this, buffer, size);
}

void Socket::sendTo(Socket * socket, SocketMessage * message)
{
	char *buffer = 0;
	size_t size;

	message->createBuffer(buffer, &size);
	sendTo(socket, buffer, size);
}

void Socket::send(SocketMessage * message)
{
	sendTo(this, message);
}
