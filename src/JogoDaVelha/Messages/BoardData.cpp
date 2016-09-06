#include "BoardData.h"
#include <iostream>

BoardData::BoardData(char ** board, int size)
{
	this->size = size;

	board = (char**)malloc(sizeof(char*) * size);
	for (int i = 0; i < size; ++i)
		board[i] = (char*)malloc(sizeof(char) * size);
}
