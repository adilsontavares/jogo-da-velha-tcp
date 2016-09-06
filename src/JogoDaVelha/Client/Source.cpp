#include "ClientController.h"

int main(int argc, char *argv[])
{
	ClientController * controller = new ClientController();
	controller->start();

	delete controller;

	return 0;
}