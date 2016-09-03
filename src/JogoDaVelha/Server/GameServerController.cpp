#include "GameServerController.h"
#include "SocketController.h"

GameServerController::GameServerController()
{
	SocketController *socketController = SocketController::instance();
	socketController->init(kSocketTypeServer);
}

GameServerController * GameServerController::instance()
{
	static GameServerController *instance = 0;
	if (!instance)
		instance = new GameServerController();
	return instance;
}

GameServerController::~GameServerController()
{
	delete SocketController::instance();
}

void GameServerController::run()
{

}