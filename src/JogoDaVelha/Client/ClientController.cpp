#include "ClientController.h"
#include "SocketController.h"
#include "ClientMessageHandler.h"

ClientController::ClientController()
{
}

ClientController::~ClientController()
{
}

void ClientController::start()
{
	SocketController::instance()->init(kSocketTypeClient);
	
	ClientMessageHandler * messageHandler = ClientMessageHandler::instance();
	messageHandler->init();

	while (true);
}


