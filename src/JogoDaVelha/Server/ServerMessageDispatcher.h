#pragma once

#include "Socket.h"
#include "Player.h"

class ServerMessageDispatcher
{
private:

	ServerMessageDispatcher();
	~ServerMessageDispatcher();

	static void sendTo(Socket * socket, SocketMessage * message);
	static void sendToAll(SocketMessage * message);
	static void sendToAllExcept(Socket * socket, SocketMessage * message);

public:

	static void askPlayerName(Player * player);
	static void playerDidChangeName(Player * player);

	static void disconnectBecauseSessionIsFull(Socket * socket);

	static void playerDidConnect(Player * player);
	static void playerDidDisconnect(Player * player);

	static void startGame();
};

