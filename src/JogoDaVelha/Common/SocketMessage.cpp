#include "SocketMessage.h"
#include <stdio.h>

SocketMessage::SocketMessage(char * buffer, size_t size)
{
	_code = *((SocketMessageCode*)buffer);
	_content = (char*)((SocketMessageCode*)buffer + 1);
	_size = size - sizeof(SocketMessageCode);
}

SocketMessage::SocketMessage(SocketMessageCode code, char * content, size_t size)
{
	_code = code;
	_content = content;
	_size = size;
}

SocketMessageCode SocketMessage::getCode()
{
	return _code;
}

char * SocketMessage::getContent()
{
	return _content;
}

size_t SocketMessage::getSize()
{
	return _size;
}

void SocketMessage::createBuffer(char * &buffer, size_t * size)
{
	*size = sizeof(_code) + _size;
	buffer = (char*)malloc(*size);

	SocketMessageCode *codePointer = (SocketMessageCode*)buffer;
	*codePointer = _code;

	int offset = (char*)(codePointer + 1) - (char*)codePointer;

	for (int i = 0; i < _size; ++i)
		buffer[i + offset] = _content[i];
}