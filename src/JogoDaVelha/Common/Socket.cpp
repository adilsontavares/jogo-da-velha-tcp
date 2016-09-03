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