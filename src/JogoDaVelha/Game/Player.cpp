#include "Player.h"

Player::Player(PlayerCode code, Socket * socket)
{
	_code = code;
	_socket = socket;
}

Player::~Player()
{
}

bool Player::ready()
{
	return !_name.empty();
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

char Player::getDrawing()
{
	switch (_code)
	{
	case kPlayerCodeCross:
		return 'X';

	case kPlayerCodeNought:
		return '0';

	default:
		return '?';
	}
}

PlayerCode Player::getCode()
{
	return _code;
}
