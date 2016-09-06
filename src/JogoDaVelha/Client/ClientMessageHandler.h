#pragma once

#include "MessageHandler.h"

class ClientMessageHandler : public MessageHandler
{
private:

	ClientMessageHandler();
	~ClientMessageHandler();

protected:

	static void socketDidDisconnect(Socket * socket);

	static void wantsPlayerName(Socket * socket, SocketMessage * message);
	static void playerDidChangeName(Socket * socket, SocketMessage * message);

	static void disconnectBecauseSessionIsFull(Socket * socket, SocketMessage * message);

	static void playerDidConnect(Socket * socket, SocketMessage * message);
	static void playerDidDisconnect(Socket * socket, SocketMessage * message);

	static void startGame(Socket * socket, SocketMessage * message);

public:

	static ClientMessageHandler * instance();

	virtual void init();
};

