//
//  Game.h
//
//  A module to encapsulate a game.
//

#ifndef __GAME_H__
#define __GAME_H__

#include "Buffer.h"

//
//  Game
//
//  A class to represent a Game. A game has a Player, an
//  array of ASTEROID_COUNT asteroids, and a current column
//  for the display.
//


class Game
{
public:
	static const int ENEMY_COUNT = 10;

public:
	//
	//  Default Constructor
	//
	//  Purpose: To create a new Game with default values.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Game is created with a player at (0, 0)
	//		 and ASTEROID_COUNT asteroids at random places.
	//               The current column of the display is initialized
	//               to 0.
	//

	Game();

	//
	//  Copy Constructor
	//
	//  Purpose: To create a new Game the same as an existing Game.
	//  Argument(s): 
	//	<1> original: A constant reference to a Game
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Game is created in the same state as an
	//               existing Game.
	//

	Game(const Game& original);


	//
	//  Assignment Operator 
	//
	//  Purpose: To assign the values from one Game to another.
	//  Argument(s): 
	//	<1> original: A constant reference to a Game
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The current instance of a Game is assigned
	//               the same values as an existing Game that
	//               is referenced by original.
	//

	Game& operator= (const Game& original);


	//
	//  Destructor 
	//
	//  Purpose: To delete an instance of the Game class.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The Game is deleted.
	//

	~Game();



	//
	//  isOver
	//
	//  Purpose: To determine if this Game is over.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: Whether this Game is over.
	//  Side Effect: N/A
	//

	bool isOver() const;

	//
	//  draw
	//
	//  Purpose: To draw a rectangular space including the player and 
	//           and possibly up to ASTEROID_COUNT asteroids.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The current state of the game is shown on the console.
	//

	void draw() const;

	//
	//  moveStraight
	//
	//  Purpose: To move the Player one position to the right
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Player is moved by (0, 1).
	//

	void moveStraight();

	//
	//  moveUp
	//
	//  Purpose: To move the Player one position to the right.  If possible
	//           to move the Player up in the display while keeping it fully 
	//           visible, it is also moved one position up.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: If the Player's row is greater than 0, the Player 
	//               is moved by (-1, 1) and otherwise, the Player is
	//               moved by (0, 1).
	//

	void moveUp();

	//
	//  moveUp
	//
	//  Purpose: To move the Player one position to the right.  If possible
	//           to move the Player down in the display while keeping it fully 
	//           visible, it is also moved one position down.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: If the Player's row is greater than 0, the Player 
	//               is moved by (1, 1) and otherwise, the Player is
	//               moved by (0, 1).
	//

	void moveDown();

	//
	//  loadAllImages
	//
	//  Purpose: To load all game images from appropriate files.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The images are loaded into memory.
	//

	static void loadAllImages();

	//
	//  update
	//
	//  Purpose: To update the state of the Game after the player has
	//           been moved to a new location.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The game is updated for one time unit.  
	//

	void update();

	//
	//  updateOneAsteroid
	//
	//  Purpose: To update the state of the Game (excluding the player's
	//           position) with respect to one asteroid with which the 
	//           player be in collision with.
	//  Argument(s): 
	//	<1> i: index of the asteroid to be considered during updating
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The game is updated for one time unit with respect to
	//               a possible collision with the asteroid with index i.  
	//

	void updateOneAsteroid(int i);

	//
	//  isCollision
	//
	//  Purpose: To check whether the Player is overlapping with 
	//           an Asteroid.
	//  Argument(s):
	//	<1> player1:    The Player
	//	<2> asteroid1:  The Asteroid
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Game is set to be at 
	//               position (row1, col1).
	//

	bool isCollision(const Player& player1, const Enemy *enemy1);

	private:
		//
		//  invariant
		//
		//  Purpose: To determine if the class invariant is true.
		//  Argument(s): N/A
		//  Precondition(s): N/A
		//  Returns: Whether the class invariant is true.
		//  Side Effect: N/A
		//

		Enemy* createRandomEnemy();

		void Delete();

		bool invariant();


private:
	Player player;
	Enemy *enemy_array[ENEMY_COUNT];

	int current_column;
};

#endif

