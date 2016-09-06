#pragma once

#include "GameController.h"

class MessageHandler
{
protected:

	GameController * _gameController;

	MessageHandler();
	~MessageHandler();

public:

	virtual void init();
};

