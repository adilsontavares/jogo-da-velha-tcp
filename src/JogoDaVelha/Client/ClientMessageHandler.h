#pragma once

#include "MessageHandler.h"

class ClientMessageHandler : public MessageHandler
{
private:

	ClientMessageHandler();
	~ClientMessageHandler();

protected:

	void requestPlayerName(Socket * socket, SocketMessage * message);
	void disconnectBecauseSessionIsFull(Socket * socket, SocketMessage * message);

public:

	static ClientMessageHandler * instance();

	virtual void init();
};

