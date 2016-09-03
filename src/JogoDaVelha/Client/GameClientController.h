#pragma once

class GameClientController
{
private:

	GameClientController();

public:

	static GameClientController *instance();
	~GameClientController();

	void run();
};

