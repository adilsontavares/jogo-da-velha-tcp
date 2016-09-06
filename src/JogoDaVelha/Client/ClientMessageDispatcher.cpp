#include "ClientMessageDispatcher.h"	
#include "GameMessageCodes.h"

ClientMessageDispatcher::ClientMessageDispatcher()
{
}

ClientMessageDispatcher::~ClientMessageDispatcher()
{
}

Socket * ClientMessageDispatcher::getMainSocket()
{
	return SocketController::instance()->getMainSocket();
}

void ClientMessageDispatcher::replyPlayerName(std::string name)
{
	SocketMessage * message = new SocketMessage(kGameMessageCodeReplyPlayerName, name);
	getMainSocket()->send(message);
}
