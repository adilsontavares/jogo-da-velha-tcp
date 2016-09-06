#pragma once

enum GameMessageCode
{
	kGameMessageCodeUnknown = 0,

	kGameMessageCodeRequestPlayerName,
	kGameMessageCodeReplyPlayerName,
	kGameMessageCodePlayerDidChangeName,

	kGameMessageCodePlayerDidConnect,
	kGameMessageCodePlayerDidDisconnect,

	kGameMessageCodeDisconnectBecauseSessionIsFull,

	kGameMessageCodeStartGame
};