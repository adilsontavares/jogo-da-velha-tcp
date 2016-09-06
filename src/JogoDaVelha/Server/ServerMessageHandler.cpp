#include "ServerMessageHandler.h"
#include "SocketMessageListener.h"
#include "GameMessageCodes.h"
#include "PlayerManager.h"
#include "ServerMessageDispatcher.h"
#include "Console.h"

using namespace std;
using namespace std::placeholders;

ServerMessageHandler::ServerMessageHandler()
{
}

ServerMessageHandler::~ServerMessageHandler()
{
}

void ServerMessageHandler::initGameIfPossible()
{
	PlayerManager * playerManager = PlayerManager::instance();

	if (playerManager->getPlayerCount() != 2)
		return;

	vector<Player*> players = playerManager->getPlayers();

	for (auto it = players.begin(); it != players.end(); ++it)
		if (!(*it)->ready())
			return;

	ServerMessageDispatcher::startGame();
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
	listener->registerMessage(kGameMessageCodeReplyPlayerName, bind(&ServerMessageHandler::replyPlayerName, _1, _2));
}

void ServerMessageHandler::replyPlayerName(Socket * socket, SocketMessage * message)
{
	PlayerManager * manager = PlayerManager::instance();
	Player * player = manager->getPlayer(socket);

	if (player)
	{
		player->setName(message->getContent());
		ServerMessageDispatcher::playerDidChangeName(player);

		initGameIfPossible();
	}
}

void ServerMessageHandler::clientDidConnect(Socket * socket)
{
	PlayerManager * manager = PlayerManager::instance();
	PlayerCode code = manager->getAvailablePlayerCode();

	Console::log("New client connected: %d", socket->getId());

	if (code == kPlayerCodeUnknown)
	{
		Console::log("Disconnecting client %d because session is full.", socket->getId());
		ServerMessageDispatcher::disconnectBecauseSessionIsFull(socket);

		return;
	}

	Player * player = new Player(code, socket);
	manager->addPlayer(player);

	Console::log("CALLING PLAYER DID CONNECT!");

	ServerMessageDispatcher::playerDidConnect(player);

	Console::log("CALLING ASK PLAYER NAME!");

	ServerMessageDispatcher::askPlayerName(player);
}

void ServerMessageHandler::clientDidDisconnect(Socket * socket)
{
	PlayerManager * playerManager = PlayerManager::instance();
	Player * player = playerManager->getPlayer(socket);

	if (!player)
		return;

	ServerMessageDispatcher::playerDidDisconnect(player);

	playerManager->removePlayer(player);
}
