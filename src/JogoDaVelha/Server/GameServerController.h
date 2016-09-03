#pragma once

#include "SocketController.h"
#include "GameController.h"

class GameServerController : public GameController
{
private:

	GameServerController();

	void receivedMessageShowText(Socket * socket, SocketMessage * message);

protected:

	virtual void init();

public:

	static GameServerController *instance();
};

