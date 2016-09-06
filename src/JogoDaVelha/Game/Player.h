#pragma once

#include "Socket.h"

enum PlayerCode
{
	kPlayerCodeUnknown,
	kPlayerCodeCross,
	kPlayerCodeNought,
};

class Player
{
private:

	PlayerCode _code;
	std::string _name;
	Socket *_socket;

public:

	Player(PlayerCode code, Socket * socket);
	~Player();

	void setName(std::string name);
	std::string getName();
	Socket * getSocket();

	PlayerCode getCode();
};

