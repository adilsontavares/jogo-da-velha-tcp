#include "ClientMessageHandler.h"
#include "SocketMessageListener.h"
#include "ClientMessageDispatcher.h"
#include "GameMessageCodes.h"
#include "Console.h"
#include "MessageData.hpp"
#include "PlayerManager.h"

using namespace std;
using namespace std::placeholders;

ClientMessageHandler::ClientMessageHandler()
{
}

ClientMessageHandler::~ClientMessageHandler()
{
}

void ClientMessageHandler::socketDidDisconnect(Socket * socket)
{
	Console::log("You are not connected to server anymore.");
	GameController::instance()->exit();
}

void ClientMessageHandler::wantsPlayerName(Socket * socket, SocketMessage * message)
{
	string name = GameController::instance()->askPlayerName();
	ClientMessageDispatcher::replyPlayerName(name);
}

void ClientMessageHandler::playerDidChangeName(Socket * socket, SocketMessage * message)
{
	PlayerManager * playerManager = PlayerManager::instance();
	Player * player = playerManager->getPlayer(socket);

	if (player)
		player->setName(message->getContent());
}

void ClientMessageHandler::disconnectBecauseSessionIsFull(Socket * socket, SocketMessage * message)
{
	Console::log("Session is full. You cannot connect this time.");
	GameController::instance()->exit();
}

void ClientMessageHandler::playerDidConnect(Socket * socket, SocketMessage * message)
{
	PlayerData * data = (PlayerData*)message->getContent();
	Console --- ::log("Player %c is now connected.", data->drawing);
}

void ClientMessageHandler::playerDidDisconnect(Socket * socket, SocketMessage * message)
{
	PlayerData * data = (PlayerData*)message->getContent();
	Console --- ::log("Player %c did disconnect from server.", data->drawing);
}

void ClientMessageHandler::startGame(Socket * socket, SocketMessage * message)
{
	GameController * gameController = GameController::instance();
	StartGameData *data = (StartGameData*)message->getContent();

	gameController->resetBoard(data->boardSize);
	gameController->startGame();
}

ClientMessageHandler * ClientMessageHandler::instance()
{
	static ClientMessageHandler * instance = 0;
	if (!instance)
		instance = new ClientMessageHandler();
	return instance;
}

void ClientMessageHandler::init()
{
	SocketController * socketController = SocketController::instance();
	socketController->setSocketDidDisconnectCallback(bind(&ClientMessageHandler::socketDidDisconnect, _1));

	SocketMessageListener * listener = SocketMessageListener::instance();
	listener->init();
	listener->registerMessage(kGameMessageCodeRequestPlayerName, bind(&ClientMessageHandler::wantsPlayerName, _1, _2));
	listener->registerMessage(kGameMessageCodeDisconnectBecauseSessionIsFull, bind(&ClientMessageHandler::disconnectBecauseSessionIsFull, _1, _2));
	listener->registerMessage(kGameMessageCodePlayerDidConnect, bind(&ClientMessageHandler::playerDidConnect, _1, _2));
	listener->registerMessage(kGameMessageCodePlayerDidDisconnect, bind(&ClientMessageHandler::playerDidDisconnect, _1, _2));
	listener->registerMessage(kGameMessageCodeStartGame, bind(&ClientMessageHandler::startGame, _1, _2));
	listener->registerMessage(kGameMessageCodePlayerDidChangeName, bind(&ClientMessageHandler::playerDidChangeName, _1, _2));
}
