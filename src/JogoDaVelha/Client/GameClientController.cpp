#include "GameClientController.h"

GameClientController::GameClientController()
{
}

GameClientController * GameClientController::instance()
{
	static GameClientController *instance = 0;
	if (!instance)
		instance = new GameClientController();
	return instance;
}

GameClientController::~GameClientController()
{
}

void GameClientController::run()
{

}