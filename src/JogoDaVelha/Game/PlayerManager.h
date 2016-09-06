#pragma once

#include "Player.h"
#include <map>

class PlayerManager
{
private:

	std::map<PlayerCode, Player*> _players;

	PlayerManager();
	~PlayerManager();

public:

	static PlayerManager *instance();

	void addPlayer(Player * player);
	void removePlayer(Player * player);

	Player * getPlayer(PlayerCode code);
	Player * getPlayer(Socket * socket);

	PlayerCode getAvailablePlayerCode();

	size_t getPlayerCount();
};

