#include <cstdlib>
#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;

#include "Rectangle.h"

void copy(const Rectangle& original);

Rectangle::Rectangle()
{
	row = 0;
	column = 0;
	row_size = 1;
	column_size = 1;
	assert(invariant());
}

Rectangle::Rectangle(int row1, int column1, int row_size1, int column_size1)
{
	row = row1;
	column = column1;
	row_size = row_size1;
	column_size = column_size1;
	assert(invariant());
}

Rectangle::Rectangle(const Rectangle& original)
{
	copy(original);
	assert(invariant());
}

Rectangle& Rectangle::operator= (const Rectangle& original)
{
	if (this != &original)
	{
		copy(original);
	}
	assert(invariant());
	return *this;
}

Rectangle::~Rectangle()
{
}

int Rectangle::getRow() const
{
	return row;
}

int Rectangle::getColumn() const
{
	return column;
}

int Rectangle::getRowSize() const
{
	return row_size;
}

int Rectangle::getColumnSize() const
{
	return column_size;
}

bool Rectangle::isOverlapping(const Rectangle& other)
{
	int rmin1 = row;
	int rmax1 = rmin1 + row_size - 1;
	int cmin1 = column;
	int cmax1 = cmin1 + column_size - 1;

	int rmin2 = other.getRow();
	int rmax2 = rmin2 + other.getRowSize() - 1;
	int cmin2 = other.getColumn();
	int cmax2 = cmin2 + other.getColumnSize() - 1;

	if (rmax1 < rmin2) return false;
	if (rmax2 < rmin1) return false;
	if (cmax1 < cmin2) return false;
	if (cmax2 < cmin1) return false;
	return true;
}

void Rectangle::setPosition(int row1, int column1)
{
	row = row1;
	column = column1;
	assert(invariant());
}

void Rectangle::move(int row_change, int column_change)
{
	row += row_change;
	column += column_change;
	assert(invariant());
}

void Rectangle::setSize(int row_size1, int column_size1)
{
	row_size = row_size1;
	column_size = column_size1;
	assert(invariant());
}

void Rectangle::copy(const Rectangle& original)
{
	row = original.row;
	column = original.column;
	row_size = original.row_size;
	column_size = original.column_size;
}

bool Rectangle::invariant() const
{
	return
		row_size >= 1 &&
		column_size >= 1;
}
