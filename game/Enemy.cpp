#include <cstdlib>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "Enemy.h"



Enemy::Enemy()
	: rectangle(/*0, 0, ROWS, COLUMNS*/)
{
	
}

Enemy::Enemy(int row1, int column1, int row_size1, int column_size1) : rectangle( row1,  column1,  row_size1,  column_size1)
{}

Enemy::Enemy(const Enemy& original)
	: rectangle(original.rectangle)
{
}

Enemy& Enemy::operator=(const Enemy& original)
{
	if (&original != this)
	{
		rectangle = original.rectangle;
		
	}
	
	return *this;
}

Enemy::~Enemy()
{
}


int Enemy::getRow() const
{
	return rectangle.getRow();
}

int Enemy::getColumn() const
{
	return rectangle.getColumn();
}

int Enemy::getRowSize() const
{
	return rectangle.getRowSize();
}

int Enemy::getColumnSize() const
{
	return rectangle.getColumnSize();
}

const Rectangle& Enemy::getRectangle() const
{
	return rectangle;
}


void Enemy::setPosition(int row1, int column1)
{
	rectangle.setPosition(row1, column1);
	
}

void Enemy::move(int row_change, int column_change)
{
	rectangle.move(row_change, column_change);
	
}

void Enemy::update()
{

}

