#include "GameServerController.h"
#include "SocketController.h"
#include "SocketMessageListener.h"
#include "GameMessageCodes.h"

using namespace std;
using namespace std::placeholders;

GameServerController::GameServerController()
{
	SocketController::instance()->init(kSocketTypeServer);
}

void GameServerController::init()
{
	SocketMessageListener *listener = SocketMessageListener::instance();
	listener->registerMessage(kGameMessageCodeShowText, std::bind(&GameServerController::receivedMessageShowText, this, _1, _2));
}

GameServerController * GameServerController::instance()
{
	static GameServerController *instance = 0;
	if (!instance)
		instance = new GameServerController();
	return instance;
}

void GameServerController::receivedMessageShowText(Socket * socket, SocketMessage * message)
{
	printf("ALERTA: %s\n", message->getContent());
}