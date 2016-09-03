#pragma once

#include "SocketController.h"

class GameServerController
{
private:

	GameServerController();

public:

	static GameServerController *instance();
	~GameServerController();

	void run();
};

