//
//  Game.cpp
//
#include <cstdlib>
#include "Buffer.h"
#include "Player.h"
#include "Asteroid.h"
#include "Game.h"
#include "Enemy.h"
#include "Spacemine.h"
#include "Scout.h"


using namespace std;

static const int STARTING_COLUMN = 30;

Game::Game()
	: player()//, asteroids()
{
	player.setPosition(10, 1);
	for (unsigned i = 0; i < ENEMY_COUNT; i++)
	{
		//asteroids[i].setPosition(10, 39);
		// rand_row, rand_column;
		createRandomEnemy();
		int rand_row = rand() % (Buffer::ROWS - enemy_array[i]->getRowSize());
		int rand_column = STARTING_COLUMN +
				 rand() % (Buffer::COLUMNS - enemy_array[i]->getColumnSize());
			 enemy_array[i]->setPosition(rand_row, rand_column);
	}

	current_column = 0;
}

Game::Game(const Game& original)
	: player(original.player) 
{
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		enemy_array[i] = enemy_array[i]->getClone();
	}
	current_column = original.current_column;
}

Game& Game::operator= (const Game& original)
{
	if (&original != this)
	{
		player = original.player;
		Delete();
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			enemy_array[i] = enemy_array[i]->getClone();
		}
		current_column = original.current_column;
	}
	return *this;
}

void Game::Delete()
{
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		if (enemy_array[i]->isDead())
		{ 
		delete enemy_array[i];
		enemy_array[i] = NULL;
		}
	}	
}

bool Game::invariant()
{
	
	for (int i = 0; i < ENEMY_COUNT; i++)
		return enemy_array[i] != nullptr;
	
	return true;
}

Game::~Game()
{
	Delete();
}

bool Game::isOver() const
{
	return player.isDead();
}

void Game::draw() const
{
	Buffer buffer;
	buffer.clear();
	buffer.setOffset(0, current_column);
	player.draw(buffer);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		enemy_array[i]->draw(buffer);
	 }
	buffer.print();
	player.printStatusRow();

}

void Game::moveStraight()
{
	current_column++;
	player.move(0, 1);
	update();
}

void Game::moveUp()
{
	current_column++;
	if (player.getRow() > 0)
		player.move(-1, 1);
	else
		player.move(0, 1);
	update();
}

void Game::moveDown()
{
	current_column++;
	if (player.getRow() + player.getRowSize() < Buffer::ROWS)
		player.move(1, 1);
	else
		player.move(0, 1);
	update();
}

void Game::loadAllImages()
{
	Player::loadImage();
	Asteroid::loadImage();
	Spacemine::loadImage();
	Scout::loadImage();
}


void Game::update()
{
	player.update();
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		//updateOneAsteroid(i);
		enemy_array[i]->update();
	}
}

void Game::updateOneAsteroid(int i)
{
	// this game allows a player to collide simultaneously with multiple asteroids
	// and get the ore from all as well as dying
	for (unsigned i = 0; i < ENEMY_COUNT; i++)
	{
		if (isCollision(player, enemy_array[i]))
		{
			unsigned int oreValue = enemy_array[i]->getOreValue();
			player.increaseOreCollected(oreValue);
			player.reduceShieldStrength(enemy_array[i]->getShieldCost());
			//Delete();
			createRandomEnemy();
		}
		if (enemy_array[i]->getColumn() + enemy_array[i]->getColumnSize() - 1 < current_column)
		{
			enemy_array[i]->markDead();
		}

		if (enemy_array[i]->isDead())
		{
			//enemy_array[i]->randomizeOreValue();
			int number_rows = Buffer::ROWS - enemy_array[i]->getRowSize() + 1;
			int number_columns = Buffer::COLUMNS - enemy_array[i]->getColumnSize() + 1;
			int next_row = rand() % number_rows;
			int next_column = current_column + Buffer::COLUMNS + rand() % number_columns;

			enemy_array[i]->setPosition(next_row, next_column);
		}
	}
}

bool Game::isCollision(const Player& player1, const Enemy *asteroid1)
{
	Rectangle r1 = player1.getRectangle();
	Rectangle r2 = asteroid1->getRectangle();
	return r1.isOverlapping(r2);
}


Enemy* Game::createRandomEnemy()
{
	Asteroid asteroid;
	Spacemine spacemine;
	Scout scout;
	//Delete();
	Enemy *enemy = new Asteroid(asteroid);
	for (unsigned i = 0; i < ENEMY_COUNT; i++)
	{
		if (i >= 5)
		{
			Asteroid *enemy = new Asteroid(asteroid);
		}
		else if (i < 2)
		{
			Spacemine *enemy = new Spacemine(spacemine);
		}
		else if (i > 1 && i < 5)
		{
			Scout *enemy = new Scout(scout);
		}
		
	}
	return enemy;
}

