#include "SocketMessage.h"
#include <stdio.h>
#include <string>

using namespace std;

SocketMessage::SocketMessage(SocketMessageCode code)
{
	_code = code;
	_content = 0;
	_size = 0;
}

SocketMessage::SocketMessage(SocketMessageCode code, string text)
{
	_code = code;
	_size = text.length() + 1;
	_content = (char*)malloc(_size);
	strcpy_s(_content, _size, text.c_str());
}

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