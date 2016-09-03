#include "GameClientController.h"

int main(int argc, char *argv[])
{
	GameClientController *controller = GameClientController::instance();
	controller->run();

	delete controller;

	return 0;
}