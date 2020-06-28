#include <cstdlib>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include "Spacemine.h"

using namespace std;




//static const int ORE_VALUE_MAX = 80;

static char asteroid_image[Spacemine::ROWS][Spacemine::COLUMNS];

Spacemine::Spacemine()
	: Enemy(0, 0, ROWS, COLUMNS)
{
	//randomizeOreValue();
	//assert(invariant());
	life = false;
}

Spacemine::Spacemine(const Spacemine& original)
	: Enemy(original)
{
	//ore_value = original.ore_value;
	//assert(invariant());
	life = original.life;
}

Spacemine& Spacemine::operator=(const Spacemine& original)
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

Spacemine::~Spacemine()
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
bool Spacemine::isDead() const
{
	return (life);
}

void Spacemine::markDead()
{
	life = true;
	//assert(invariant());
}

unsigned int Spacemine::getOreValue() const
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
void Spacemine::draw(Buffer& buffer) const
{
	int r = getRow();      // current row of asteroid 
	int c = getColumn();   // current column of asteroid
	for (int i = 0; i < getRowSize(); i++)
	{
		for (int j = 0; j < getColumnSize(); j++)
		{
			buffer.setCell(asteroid_image[i][j], r + i, c + j);
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
void Spacemine::loadImage()
{
	string myline;
	ifstream asteroid_image_data("Spacemine.txt");
	if (!asteroid_image_data)
	{
		cerr << "Space mine image file is not available" << endl;
		return;
	}

	for (unsigned int i = 0; i < ROWS; i++)
	{
		getline(asteroid_image_data, myline, '\n');
		if (!asteroid_image_data || myline.length() < COLUMNS)
		{
			cerr << "Space mine image file is missing some data" << endl;
			break; // break out of loop to close file
		}
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			asteroid_image[i][j] = myline[j];
		}
	}
	asteroid_image_data.close();
}

unsigned int Spacemine::getShieldCost() const
{
	return SHIELD_COST;
}

Enemy* Spacemine::getClone()const
{
	Spacemine asteroid;
	Spacemine *clone = new Spacemine(asteroid);
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