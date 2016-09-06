#pragma once

enum GameMessageCode
{
	kGameMessageCodeUnknown = 0,

	kGameMessageCodeRequestPlayerName,
	kGameMessageCodeReplyPlayerName,

	kGameMessageCodeDisconnectBecauseSessionIsFull,


};