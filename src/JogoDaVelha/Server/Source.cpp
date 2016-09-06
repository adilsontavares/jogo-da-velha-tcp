#include "ServerController.h"

int main(int argc, char *argv[])
{
	ServerController * controller = new ServerController();
	controller->start();

	delete controller;

	return 0;
}