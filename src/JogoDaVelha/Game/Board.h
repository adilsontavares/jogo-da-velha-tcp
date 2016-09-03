#pragma once

class Board
{
private:

	int _size;
	char **_matrix;

	void allocMatrix();
	void fillMatrix(char c);

public:
	
	Board(int size);
	
	void print();
};

