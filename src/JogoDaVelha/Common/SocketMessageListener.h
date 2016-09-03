#pragma once

#include "Socket.h"
#include "SocketMessage.h"
#include <functional>
#include <map>

typedef std::function<void(Socket*, SocketMessage*)> FuncRegisterSocketMessage;

class SocketMessageListener
{
private:

	std::map<SocketMessageCode, FuncRegisterSocketMessage> _messages;
	bool _initialized;

	SocketMessageListener();

	void onReceiveSocketData(Socket * socket, char * buffer, size_t size);

public:

	static SocketMessageListener *instance();
	~SocketMessageListener();

	void init();

	void registerMessage(SocketMessageCode code, FuncRegisterSocketMessage callback);
};

