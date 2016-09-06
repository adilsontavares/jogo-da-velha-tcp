#pragma once

#include "Board.h"
#include "SocketController.h"

class GameController
{
private:

	Board *_board;

protected:

	GameController();
	~GameController();

public:

	static GameController * instance();

	std::string askPlayerName();

	void exit();
};

