#pragma once

#include <iostream>
#include "SocketController.h"

class ClientMessageDispatcher
{
private:

	ClientMessageDispatcher();
	~ClientMessageDispatcher();

	static Socket * getMainSocket();

public:

	static void replyPlayerName(std::string name);
};

