#include "Player.h"

Player::Player(PlayerCode code, Socket * socket)
{
	_code = code;
	_socket = socket;
}

Player::~Player()
{
}

void Player::setName(std::string name)
{
	_name = name;
}

std::string Player::getName()
{
	return _name;
}

Socket * Player::getSocket()
{
	return _socket;
}

PlayerCode Player::getCode()
{
	return _code;
}
