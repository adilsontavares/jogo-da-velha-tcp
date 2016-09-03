#include "Board.h"
#include "Error.h"
#include <iostream>

Board::Board(int size)
{
	Error::assert(size > 2, "Board size must be 2 or bigger");

	_size = size;
	_matrix = 0;

	allocMatrix();
	fillMatrix('X');
}

void Board::allocMatrix()
{
	_matrix = new char*[_size];
	for (int i = 0; i < _size; ++i)
		_matrix[i] = new char[_size];
}

void Board::fillMatrix(char c)
{
	for (int i = 0; i < _size; ++i)
		for (int j = 0; j < _size; ++j)
			_matrix[i][j] = c;
}

void Board::print()
{
	for (int i = 0; i < _size; ++i)
	{
		// Draw horizontal lines

		if (i != 0)
		{
			printf("---");
			for (int k = 1; k < _size; ++k)
				printf("+---");
			printf("\n");
		}

		// Draw vertical lines and content

		printf(" %c ", _matrix[i][0]);

		for (int j = 1; j < _size; ++j)
			printf("| %c ", _matrix[i][j]);

		// Jump to next line

		printf("\n");
	}
}
