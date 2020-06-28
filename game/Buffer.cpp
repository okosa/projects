//
//  Buffer.cpp
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>

using namespace std;

#include "Buffer.h"

const char BUFFER_EMPTY = ' ';
const char BUFFER_BORDER = '#';

Buffer::Buffer()
{
	row_offset = 0;
	column_offset = 0;
}

void Buffer::clear()
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			buffer[i][j] = BUFFER_EMPTY;
		}
	}
}

void Buffer::print() const
{
	for (unsigned int j = 0; j < COLUMNS + 2; j++)
	{
		cout << BUFFER_BORDER;
	}
	cout << endl;
	for (unsigned int i = 0; i < ROWS; i++)
	{
		cout << BUFFER_BORDER;
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			cout << buffer[i][j];
		}
		cout << BUFFER_BORDER;
		cout << endl;
	}
	for (unsigned int j = 0; j < COLUMNS + 2; j++)
	{
		cout << BUFFER_BORDER;
	}
	cout << endl;
}

void Buffer::setCell(char c, int row1, int column1)
{
	int row = row1 - row_offset;
	int column = column1 - column_offset;
	if ((row >= 0 && row < ROWS) &&
		(column >= 0 && column < COLUMNS))
	{
		buffer[row][column] = c;
	}
}

void Buffer::setOffset(int row, int column)
{
	row_offset = row;
	column_offset = column;
}


