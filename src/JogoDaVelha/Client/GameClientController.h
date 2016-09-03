#pragma once

#include "GameController.h"

class GameClientController : public GameController
{
private:

	GameClientController();

protected:

	virtual void init();

public:

	static GameClientController *instance();
};

