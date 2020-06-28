//
//  Asteroid.h
//
//  A module to encapsulate an asteroid.
//

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Rectangle.h"
#include "Buffer.h"

//
//  Enemy
//
//  A class to represent an Enemy.  An Enemy has a
//    position and dimensions.  An Enemy is
//    considered to be dead if there is collision.
//


class Enemy
{

public:
	//
	//  Default Constructor
	//
	//  Purpose: To create a new Enemy with default values.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Enemy is created at position (0, 0)
	//		 with the correct dimensions.  .
	//

	Enemy();


	Enemy(int row1, int column1, int row_size1, int column_size1);


	//
	//  Copy Constructor
	//
	//  Purpose: To create a new Enemy the same as an existing Enemy.
	//  Argument(s): 
	//	<1> original: A constant reference to an Enemy
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Enemy is created with the same positions,
	//               dimensions as the existing Enemy
	//

	Enemy(const Enemy& original);


	//
	//  Assignment Operator 
	//
	//  Purpose: To assign the values from one Enemy to another
	//  Argument(s): 
	//	<1> original: A constant reference to an Enemy
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Enemy is created with the same positions,
	//               dimensions as the existing Enemy
	//

	Enemy& operator= (const Enemy& original);


	//
	//  Destructor 
	//
	//  Purpose: To delete an instance of the Enemy class
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The Enemy is deleted
	//

	virtual ~Enemy();

	//
	//  getRow
	//  getColumn
	//
	//  Purpose: To determine the row/column of this Enemy.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The row/column of this Enemy.
	//  Side Effect: N/A
	//

	int getRow() const;
	int getColumn() const;

	//
	//
	//  getRowSize
	//  getColumnSize
	//
	//  Purpose: To determine the number of rows/columns that this
	//	     Enemy covers.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The number of rows/columns covered by this
	//	     Enemy.
	//  Side Effect: N/A
	//

	int getRowSize() const;
	int getColumnSize() const;

	//  getRectangle
	//
	//  Purpose: To return the Rectangle portion of an Enemy.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The Rectangle that describes the position and size
	//           of the Enemy.
	//  Side Effect: N/A
	//

	const Rectangle& getRectangle() const;

	//
	//  isDead
	//
	//  Purpose: To determine if this Enemy is dead.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: Whether this Enemy is dead.
	//  Side Effect: Only implemented in derived class
	//

	virtual bool isDead() const = 0;

	//
	//  markDead
	//
	//  Purpose: To mark this Enemy as dead.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Enemy is marked as dead. Only implemented in derived class
	//

	virtual void markDead() = 0;

	//
	//  getOreValue
	//
	//  Purpose: To determine the ore value of this enemy.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The ore value of this enemy.
	//  Side Effect: Only implemented in derived class
	//

	virtual unsigned int getOreValue() const = 0;

	

	//
	//  draw
	//
	//  Purpose: To draw this enemy onto the specified Buffer.
	//  Argument(s):
	//	<1> buffer: A reference to the Buffer
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This enemy is drawn
	//		 onto Buffer buffer. Only implemented in derived class
	//

	virtual void draw(Buffer& buffer) const = 0;

	//
	//  setPosition
	//
	//  Purpose: To move this enemy to the specified position.
	//  Argument(s):
	//	<1> row1: The row coordinate of the new position
	//	<2> col1: The column coordinate of the new position
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This enemy is set to be at 
	//               position (row1, col1).
	//

	void setPosition(int row1, int col1);

	//
	//  move
	//
	//  Purpose: To move this enemy by the specified amount.
	//  Argument(s):
	//	<1> row_change: The change to the row coordinate of the position
	//	<2> col_change: The change to the column coordinate of the 
	//                      position
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This enemy moved by (row_change, col_change).
	//

	void move(int row_change, int column_change);

	//
	//  getShieldCost
	// 
	//
	//  Purpose: To determine the shield cost of this enemy.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The shield cost of this enemy.
	//  Side Effect:only implemented in derived class
	//

	virtual unsigned int getShieldCost()const = 0;


	//
	//  getClone
	// 
	//
	//  Purpose: To replicate a copy or clone of this enemy.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The clone or copy of this enemy.
	//  Side Effect:only implemented in derived class
	//

	virtual Enemy* getClone()const = 0;


	//
	//  update
	// 
	//
	//  Purpose: To update the state of the enemy after each move.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: could be implemented in derived or base class

	virtual void update();

private:
	Rectangle rectangle; // store ints for dimension and position
	//unsigned int ore_value;
};

#endif


