#pragma once

enum GameMessageCode
{
	kGameMessageCodeUnknown = 0,

	kGameMessageCodeShowText,
	kGameMessageCodeSetPosition,
	kGameMessageCodeSetName,
	kGameMessageCodeStartTurn,
	kGameMessageCodeEndTurn
};