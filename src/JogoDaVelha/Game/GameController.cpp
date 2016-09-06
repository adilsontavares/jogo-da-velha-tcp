#include "GameController.h"
#include "SocketMessageListener.h"
#include "Console.h"
#include "Console.h"

GameController::GameController()
{
	_board = 0;
}

GameController::~GameController()
{
}

void GameController::resetBoard(int size)
{
	_board = new Board(size);
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
	Console::pause();

	::exit(0);
}

GameController * GameController::instance()
{
	static GameController * instance = 0;
	if (!instance)
		instance = new GameController();
	return instance;
}

void GameController::startGame()
{
	Console::clear();
	Console::log("Game started!!");

	_board->print();
}