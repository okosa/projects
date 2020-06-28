//
//  Your name here
//  CS 115, Section 00x
//  Assignment 4

//
//  main.cpp
//

#include "Player.h"
#include "Asteroid.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;



int main()
{
	srand((unsigned int)time(NULL));

	Game game;
	Game saved_game(game);

	Game::loadAllImages();

	bool continue_game = true;

	string commandline;
	do
	{
		game.draw();
		cout << "Next? ";
		getline(cin, commandline, '\n');
		if (commandline.length() > 0)
		{
			switch (commandline[0])
			{
			case 'q':
			case 'Q':
				continue_game = false;
				break;
			case 'w':
			case 'W':
				game.moveUp();
				break;
			case 's':
			case 'S':
				game.moveStraight();
				break;
			case 'x':
			case 'X':
				game.moveDown();
				break;
			case 'r':
			case 'R':
				game = saved_game;
				break;
			}
			if (game.isOver())
			{
				game = saved_game;
				//cout << "Game Over" << endl;
				//continue_game = false;
			}
		}
	} while (continue_game);

	char dummy;
	cout << "Press any key to continue" << endl;
	dummy = getc(stdin);
	return 0;
}

