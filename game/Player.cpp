#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "Player.h"

static const unsigned int MAX_SHIELD_STRENGTH = 50;
static char player_ship_image[Player::ROWS][Player::COLUMNS];

Player::Player()
	: rectangle(0, 0, ROWS, COLUMNS)
{
	shield_strength = MAX_SHIELD_STRENGTH;
	ore_collected = 0;
	assert(invariant());
}

Player::Player(const Player& original)
	: rectangle(original.rectangle)
{
	ore_collected = original.ore_collected;
	shield_strength = original.shield_strength;
	assert(invariant());
}

Player& Player::operator= (const Player& original)
{
	if (this != &original)
	{
		rectangle = original.rectangle;
		ore_collected = original.ore_collected;
		shield_strength = original.shield_strength;
	}
	assert(invariant());
	return *this;
}


Player::~Player()
{
}

int Player::getRow() const
{
	return rectangle.getRow();
}

int Player::getColumn() const
{
	return rectangle.getColumn();
}

int Player::getRowSize() const
{
	return rectangle.getRowSize();
}

int Player::getColumnSize() const
{
	return rectangle.getColumnSize();
}

const Rectangle& Player::getRectangle() const
{
	return rectangle;
}

bool Player::isDead() const
{
	return (shield_strength == 0);
}

double Player::getShieldStrengthFraction() const
{
	return double(shield_strength) / double(MAX_SHIELD_STRENGTH);
}

unsigned int Player::getOreCollected() const
{
	return ore_collected;
}

void Player::draw(Buffer& buffer) const
{
	for (int i = 0; i < getRowSize(); i++)
	{
		for (int j = 0; j < getColumnSize(); j++)
		{
			buffer.setCell(player_ship_image[i][j],
				getRow() + i, getColumn() + j);
		}
	}
}

void Player::setPosition(int row1, int column1)
{
	rectangle.setPosition(row1, column1);
	assert(invariant());
}

void Player::move(int row_change, int column_change)
{
	rectangle.move(row_change, column_change);
	assert(invariant());
}

void Player::reduceShieldStrength(unsigned int shieldReduction)
{
	if (shield_strength > shieldReduction)
		shield_strength -= shieldReduction;
	else
		shield_strength = 0;
	assert(invariant());
}

void Player::increaseOreCollected(unsigned int oreAmount)
{
	ore_collected += oreAmount;
	assert(invariant());
}

void Player::update()
{
	if (shield_strength < MAX_SHIELD_STRENGTH)
	{
		shield_strength++;
	}
	assert(invariant());
}

void Player::loadImage()
{
	string myline;
	ifstream player_image_data("player.txt");
	if (!player_image_data)
	{
		cerr << "Player image file is not available" << endl;
		return;
	}

	for (unsigned int i = 0; i < ROWS; i++)
	{
		getline(player_image_data, myline, '\n');
		if (!player_image_data || myline.length() < COLUMNS)
		{
			cerr << "Player image file is missing some data" << endl;
			break;  // break out of loop to close file
		}

		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			player_ship_image[i][j] = myline[j];
		}
	}
	player_image_data.close();
}

void Player::printStatusBar(unsigned int length, double fraction) const
{
	assert(length >= 2);
	assert(fraction >= 0.0);
	assert(fraction <= 1.0);

	unsigned int full;
	unsigned int i;

	length -= 2;

	cout << '|';
	full = (unsigned int)(length * fraction);
	for (i = 0; i < full; i++)
		cout << '*';
	for (; i < length; i++)
		cout << '-';
	cout << '|';
}

void Player::printStatusRow() const
{
	cout << " Shields ";
	printStatusBar(22, getShieldStrengthFraction());
	cout << "   Power ";
	printStatusBar(7, 1.0);
	cout << "   Ore: ";
	for (unsigned int d = 100000; d > 0; d /= 10)
		cout << (ore_collected / d) % 10;
	cout << endl;
}

bool Player::invariant() const
{
	return shield_strength <= MAX_SHIELD_STRENGTH;
}

