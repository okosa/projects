#include <cstdlib>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include "Asteroid.h"

using namespace std;



static const int ORE_VALUE_DEAD = 0;
static const int ORE_VALUE_MIN = 1;
static const int ORE_VALUE_MAX = 80;

static char asteroid_image[Asteroid::ROWS][Asteroid::COLUMNS];

Asteroid::Asteroid()
	: Enemy(0,0,ROWS,COLUMNS)
{
	randomizeOreValue();
	assert(invariant());
}

Asteroid::Asteroid(const Asteroid& original)
	: Enemy(original)
{
	ore_value = original.ore_value;
	assert(invariant());
}

Asteroid& Asteroid::operator=(const Asteroid& original) 
{
	if (&original != this)
	{
		Enemy::operator=(original);
		ore_value = original.ore_value;
	}
	assert(invariant());
	return *this;
}

Asteroid::~Asteroid()
{
}


bool Asteroid::isDead() const
{
	return (ore_value == ORE_VALUE_DEAD);
}

void Asteroid::markDead()
{
	ore_value = ORE_VALUE_DEAD;
	assert(invariant());
}

unsigned int Asteroid::getOreValue() const
{
	return ore_value;
}

void Asteroid::randomizeOreValue()
{
	double fraction = double(rand()) / (double)RAND_MAX;
	int range = ORE_VALUE_MAX - ORE_VALUE_MIN;
	int displacement = (int)(fraction * range);
	ore_value = ORE_VALUE_MIN + displacement;
	assert(invariant());
}

void Asteroid::draw(Buffer& buffer) const
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
	buffer.setCell((ore_value / 10) + '0', r + 1, c + 1);
	buffer.setCell((ore_value % 10) + '0', r + 1, c + 2);
}

void Asteroid::loadImage()
{
	string myline;
	ifstream asteroid_image_data("asteroid.txt");
	if (!asteroid_image_data)
	{
		cerr << "Asteroid image file is not available" << endl;
		return;
	}

	for (unsigned int i = 0; i < ROWS; i++)
	{
		getline(asteroid_image_data, myline, '\n');
		if (!asteroid_image_data || myline.length() < COLUMNS)
		{
			cerr << "Asteroid image file is missing some data" << endl;
			break; // break out of loop to close file
		}
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			asteroid_image[i][j] = myline[j];
		}
	}
	asteroid_image_data.close();
}

unsigned int Asteroid::getShieldCost() const
{
	return ore_value;
}

Enemy* Asteroid::getClone()const
{
	Asteroid asteroid;
	Asteroid *clone = new Asteroid(asteroid);
	return clone;
}

bool Asteroid::invariant() const
{
	return
		(
		(ore_value == ORE_VALUE_DEAD) ||
		(ore_value >= ORE_VALUE_MIN && ore_value < ORE_VALUE_MAX)
		);
}
