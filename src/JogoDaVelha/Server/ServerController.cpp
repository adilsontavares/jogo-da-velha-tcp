#include "ServerController.h"
#include "SocketController.h"
#include "ServerMessageHandler.h"

ServerController::ServerController()
{
}

ServerController::~ServerController()
{
}

void ServerController::start()
{
	SocketController::instance()->init(kSocketTypeServer);

	ServerMessageHandler * messageHandler = ServerMessageHandler::instance();
	messageHandler->init();

	while (true);
}