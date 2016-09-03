#include "Socket.h"

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
