#include "GameClientController.h"
#include "SocketController.h"
#include "GameMessageCodes.h"

GameClientController::GameClientController()
{
	SocketController::instance()->init(kSocketTypeClient);
}

void GameClientController::init()
{
	Socket *socket = SocketController::instance()->getMainSocket();
	socket->send(new SocketMessage(kGameMessageCodeShowText, "Hello, server!!!!"));
}

GameClientController * GameClientController::instance()
{
	static GameClientController *instance = 0;
	if (!instance)
		instance = new GameClientController();
	return instance;
}