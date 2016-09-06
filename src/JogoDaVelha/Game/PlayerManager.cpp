#include "PlayerManager.h"
#include "Error.h"
#include "Console.h"

using namespace std;

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

PlayerManager * PlayerManager::instance()
{
	static PlayerManager *instance = 0;
	if (!instance)
		instance = new PlayerManager();
	return instance;
}

void PlayerManager::addPlayer(Player * player)
{
	Console::log("Adding player for drawing: %c", player->getDrawing());

	Error::assert(_players.find(player->getCode()) == _players.end(), "Player with this code is already added.");
	_players[player->getCode()] = player;
}

void PlayerManager::removePlayer(Player * player)
{
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		if (it->second == player)
		{
			_players.erase(it);
			return;
		}
	}
}

std::vector<Player*> PlayerManager::getPlayers()
{
	vector<Player*> players;
	for (auto it = _players.begin(); it != _players.end(); ++it)
		players.push_back(it->second);
	return players;
}

Player * PlayerManager::getPlayer(Socket * socket)
{
	for (auto it = _players.begin(); it != _players.end(); ++it)
		if (it->second->getSocket() == socket)
			return it->second;
	return 0;
}

Player * PlayerManager::getPlayer(PlayerCode code)
{
	auto it = _players.find(code);
	if (it == _players.end())
		return 0;
	return _players[code];
}

PlayerCode PlayerManager::getAvailablePlayerCode()
{
	for (PlayerCode i = kPlayerCodeCross; i <= kPlayerCodeNought; i = (PlayerCode)(i + 1))
		if (_players.find(i) == _players.end())
			return i;
	return kPlayerCodeUnknown;
}

size_t PlayerManager::getPlayerCount()
{
	return _players.size();
}