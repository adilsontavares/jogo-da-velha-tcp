#include "ClientMessageHandler.h"
#include "SocketMessageListener.h"
#include "ClientMessageDispatcher.h"
#include "GameMessageCodes.h"
#include "Console.h"

using namespace std;
using namespace std::placeholders;

ClientMessageHandler::ClientMessageHandler()
{
}

ClientMessageHandler::~ClientMessageHandler()
{
}

void ClientMessageHandler::requestPlayerName(Socket * socket, SocketMessage * message)
{
	string name = _gameController->askPlayerName();
	ClientMessageDispatcher::replyPlayerName(name);
}

void ClientMessageHandler::disconnectBecauseSessionIsFull(Socket * socket, SocketMessage * message)
{
	Console::log("Session is full. You cannot connect this time.");
	_gameController->exit();
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
	SocketMessageListener * listener = SocketMessageListener::instance();
	listener->init();
	listener->registerMessage(kGameMessageCodeRequestPlayerName, bind(&ClientMessageHandler::requestPlayerName, this, _1, _2));
	listener->registerMessage(kGameMessageCodeDisconnectBecauseSessionIsFull, bind(&ClientMessageHandler::disconnectBecauseSessionIsFull, this, _1, _2));
}
