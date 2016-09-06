#pragma once

#include "MessageHandler.h"

class ServerMessageHandler : public MessageHandler
{
protected:
	
	ServerMessageHandler();
	~ServerMessageHandler();

public:

	static ServerMessageHandler * instance();
	virtual void init();

	static void replyPlayerName(Socket * socket, SocketMessage * message);

	static void clientDidConnect(Socket * socket);
	static void clientDidDisconnect(Socket * socket);
};

