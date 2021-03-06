#pragma once

#include <WS2tcpip.h>
#include <iostream>

typedef UINT32 SocketMessageCode;

class SocketMessage
{
private:

	SocketMessageCode _code;
	char *_content;
	size_t _size;

public:

	SocketMessage(char * buffer, size_t size);
	SocketMessage(SocketMessageCode code);
	SocketMessage(SocketMessageCode code, std::string text);
	SocketMessage(SocketMessageCode code, char * content, size_t size);

	SocketMessageCode getCode();
	char * getContent();
	size_t getSize();

	void createBuffer(char * &buffer, size_t * size);
};

