#include "ServerMessageHandler.h"
#include "SocketMessageListener.h"
#include "GameMessageCodes.h"
#include "PlayerManager.h"
#include "ServerMessageDispatcher.h"

using namespace std;
using namespace std::placeholders;

ServerMessageHandler::ServerMessageHandler()
{
}

ServerMessageHandler::~ServerMessageHandler()
{
}

ServerMessageHandler * ServerMessageHandler::instance()
{
	static ServerMessageHandler * instance = 0;
	if (!instance)
		instance = new ServerMessageHandler();
	return instance;
}

void ServerMessageHandler::init()
{
	SocketController * socketController = SocketController::instance();
	socketController->setSocketDidConnectCallback(bind(&ServerMessageHandler::clientDidConnect, _1));
	socketController->setSocketDidDisconnectCallback(bind(&ServerMessageHandler::clientDidDisconnect, _1));

	SocketMessageListener * listener = SocketMessageListener::instance();
	listener->init();
	listener->registerMessage(kGameMessageCodeReplyPlayerName, bind(&ServerMessageHandler::replyPlayerName, this, _1, _2));
}

void ServerMessageHandler::replyPlayerName(Socket * socket, SocketMessage * message)
{
	PlayerManager * manager = PlayerManager::instance();
	Player * player = manager->getPlayer(socket);

	if (player)
		player->setName(message->getContent());
}

void ServerMessageHandler::clientDidConnect(Socket * socket)
{
	PlayerManager * manager = PlayerManager::instance();
	PlayerCode code = manager->getAvailablePlayerCode();

	if (code == kPlayerCodeUnknown)
	{
		ServerMessageDispatcher::disconnectBecauseSessionIsFull(socket);
		return;
	}

	Player * player = new Player(code, socket);
	manager->addPlayer(player);
}

void ServerMessageHandler::clientDidDisconnect(Socket * socket)
{

}
