#include <cstdlib>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include "Scout.h"

using namespace std;




//static const int ORE_VALUE_MAX = 80;

static char Scout_image[Scout::ROWS][Scout::COLUMNS];

Scout::Scout()
	: Enemy(0, 0, ROWS, COLUMNS)
{
	//randomizeOreValue();
	//assert(invariant());
	life = false;
}

Scout::Scout(const Scout& original)
	: Enemy(original)
{
	//ore_value = original.ore_value;
	//assert(invariant());
	life = original.life;
}

Scout& Scout::operator=(const Scout& original)
{
	if (&original != this)
	{
		Enemy::operator=(original);
		//rectangle = original.rectangle;
		//ore_value = original.ore_value;
		life = original.life;
	}
	//assert(invariant());
	return *this;
}

Scout::~Scout()
{
}

/*
int Asteroid::getRow() const
{
return rectangle.getRow();
}

int Asteroid::getColumn() const
{
return rectangle.getColumn();
}

int Asteroid::getRowSize() const
{
return rectangle.getRowSize();
}

int Asteroid::getColumnSize() const
{
return rectangle.getColumnSize();
}


const Rectangle& Asteroid::getRectangle() const
{
return rectangle;
}
*/
bool Scout::isDead() const
{
	return (life);
}

void Scout::markDead()
{
	life = true;
	//assert(invariant());
}

unsigned int Scout::getOreValue() const
{
	return ORE_VALUE;
}
/*
void Asteroid::randomizeOreValue()
{
//double fraction = double(rand()) / (double)RAND_MAX;
//int range = ORE_VALUE_MAX - ORE_VALUE_MIN;
//int displacement = (int)(fraction * range);
//ore_value = ORE_VALUE_MIN + displacement;
//assert(invariant());
}
*/
void Scout::draw(Buffer& buffer) const
{
	int r = getRow();      // current row of asteroid 
	int c = getColumn();   // current column of asteroid
	for (int i = 0; i < getRowSize(); i++)
	{
		for (int j = 0; j < getColumnSize(); j++)
		{
			buffer.setCell(Scout_image[i][j], r + i, c + j);
		}
	}
	//buffer.setCell(('0') + '0', r + 1, c + 1);
	//buffer.setCell(('0') + '0', r + 1, c + 2);
}

/*
void Asteroid::setPosition(int row1, int column1)
{
rectangle.setPosition(row1, column1);
assert(invariant());
}

void Asteroid::move(int row_change, int column_change)
{
rectangle.move(row_change, column_change);
assert(invariant());
}
*/
void Scout::loadImage()
{
	string myline;
	ifstream Scout_image_data("Scout.txt");
	if (!Scout_image_data)
	{
		cerr << "Scout image file is not available" << endl;
		return;
	}

	for (unsigned int i = 0; i < ROWS; i++)
	{
		getline(Scout_image_data, myline, '\n');
		if (!Scout_image_data || myline.length() < COLUMNS)
		{
			cerr << "Scout image file is missing some data" << endl;
			break; // break out of loop to close file
		}
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			Scout_image[i][j] = myline[j];
		}
	}
	Scout_image_data.close();
}

unsigned int Scout::getShieldCost() const
{
	return SHIELD_COST;
}

Enemy* Scout::getClone()const
{
	Scout scout;
	Scout *clone = new Scout(scout);
	return clone;
}
/*
bool Asteroid::invariant() const
{
return true;
(
(ore_value == ORE_VALUE_DEAD) ||
(ore_value >= ORE_VALUE_MIN && ore_value < ORE_VALUE_MAX)
);
}
*/

void Scout::update()
{
	rectangle.move(0, -3);
}