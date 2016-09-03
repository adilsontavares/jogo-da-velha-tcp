#include "GameServerController.h"
#include "SocketMessage.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	GameServerController *controller = GameServerController::instance();
	controller->run();

	delete controller;

	return 0;
}