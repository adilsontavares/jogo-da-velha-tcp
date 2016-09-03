#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <cstdlib>
#include <locale>

#include "Error.h"
#include "Console.h"
#include "Board.h"

using namespace std;

int main(int argc, char *argv[])
{
	Board *board = new Board(5);
	board->print();

	system("pause");

	return 0;
}
