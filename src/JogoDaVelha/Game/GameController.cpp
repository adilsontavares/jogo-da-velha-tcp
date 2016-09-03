#include "GameController.h"
#include "SocketController.h"
#include "SocketMessageListener.h"

GameController::GameController()
{
	_board = new Board(3);
}

void GameController::init()
{
}

void GameController::initDependencies()
{
	SocketMessageListener::instance()->init();
}

void GameController::run()
{
	initDependencies();
	init();

	while (true);
}

GameController::~GameController()
{
	delete SocketMessageListener::instance();
	delete SocketController::instance();
}