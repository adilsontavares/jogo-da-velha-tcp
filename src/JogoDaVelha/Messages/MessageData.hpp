#pragma once

#include <iostream>
#include "Player.h"

struct StartGameData
{
	int boardSize;

	StartGameData(int boardSize)
	{
		this->boardSize = boardSize;
	}
};

struct PlayerData
{
	int code;
	std::string name;
	char drawing;

	PlayerData(Player * player)
	{
		this->code = player->getCode();
		this->name = player->getName();
		this->drawing = player->getDrawing();
	}
};