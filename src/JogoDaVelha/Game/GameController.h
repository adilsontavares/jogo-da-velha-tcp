#pragma once

#include "Board.h"

class GameController
{
private:

	Board *_board;

	void initDependencies();

protected:

	virtual void init();

public:

	GameController();
	~GameController();

	void run();
};

