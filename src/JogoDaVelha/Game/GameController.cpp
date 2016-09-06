#include "GameController.h"
#include "SocketMessageListener.h"
#include "Console.h"
#include "Console.h"

GameController::GameController()
{
	_board = new Board(3);
}

GameController::~GameController()
{
}

std::string GameController::askPlayerName()
{
	Console::clear();
	Console::writeLine("Whats is your name?");

	return Console::readLine();
}

void GameController::exit()
{
	Console::log("Game finished.");
	::exit(0);
}

GameController * GameController::instance()
{
	static GameController * instance = 0;
	if (!instance)
		instance = new GameController();
	return instance;
}
