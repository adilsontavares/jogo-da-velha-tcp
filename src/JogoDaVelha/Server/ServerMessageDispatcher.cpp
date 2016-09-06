#include "ServerMessageDispatcher.h"
#include "GameMessageCodes.h"
#include "SocketController.h"

using namespace std;

ServerMessageDispatcher::ServerMessageDispatcher()
{
}

ServerMessageDispatcher::~ServerMessageDispatcher()
{
}

void ServerMessageDispatcher::sendTo(Socket * socket, SocketMessage * message)
{
	Socket * mainSocket = SocketController::instance()->getMainSocket();
	socket->sendTo(socket, message);
}

void ServerMessageDispatcher::sendToAll(SocketMessage * message)
{
	vector<Socket*> sockets = SocketController::instance()->getSockets();
	for (auto it = sockets.begin(); it != sockets.end(); ++it)
		sendTo(*it, message);
}

void ServerMessageDispatcher::sendToAllExcept(Socket * socket, SocketMessage * message)
{
	vector<Socket*> sockets = SocketController::instance()->getSockets();

	for (auto it = sockets.begin(); it != sockets.end(); ++it)
		if (*it != socket)
			sendTo(socket, message);
}

void ServerMessageDispatcher::askPlayerName(Player * player)
{
	SocketMessage * message = new SocketMessage(kGameMessageCodeRequestPlayerName);
	sendTo(player->getSocket(), message);
}

void ServerMessageDispatcher::disconnectBecauseSessionIsFull(Socket * socket)
{
	SocketMessage * message = new SocketMessage(kGameMessageCodeDisconnectBecauseSessionIsFull);
	sendTo(socket, message);
}
