//
//  Asteroid.h
//
//  A module to encapsulate an asteroid.
//

#ifndef __SCOUT_H__
#define __SCOUT_H__
#include "Rectangle.h"
#include "Enemy.h"
#include "Buffer.h"

//
//  Asteroid
//
//  A class to represent an asteroid.  An asteroid has a
//    position, dimensions, and an ore value.  An Asteroid is
//    considered to be dead if it has an ore value of 0.
//
//  Class Invariant:
//	<1> row_size >= 1
//	<2> column_size >= 1
//	<3> ore_value == ORE_VALUE_DEAD  (hidden constant) ||
//	    (ore_value >= ORE_VALUE_MIN  (hidden constant) &&
//	     ore_value <  ORE_VALUE_MAX) (hidden constant)
//

class Scout : public Enemy
{
public:
	//
	//  ROWS
	//  COLUMNS
	//
	//  The dimensions of the asteroid image.
	//

	static const int ROWS = 1;
	static const int COLUMNS = 5;

public:
	//
	//  Default Constructor
	//
	//  Purpose: To create a new Asteroid with default values.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Asteroid is created at position (0, 0)
	//		 with the correct dimensions.  The new Asteroid
	//		 is set to have an ore value of 1.
	//

	Scout();

	//
	//  Copy Constructor
	//
	//  Purpose: To create a new Asteroid the same as an existing Asteroid.
	//  Argument(s): 
	//	<1> original: A constant reference to a Asteroid
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Asteroid is created with the same positions,
	//               dimensions and ore collected as the existing Asteroid
	//

	Scout(const Scout& original);


	//
	//  Assignment Operator 
	//
	//  Purpose: To assign the values from one Asteroid to another
	//  Argument(s): 
	//	<1> original: A constant reference to a Asteroid
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Asteroid is created with the same positions,
	//               dimensions, and ore collected as the existing Asteroid
	//

	Scout& operator= (const Scout& original);


	//
	//  Destructor 
	//
	//  Purpose: To delete an instance of the Asteroid class
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The Asteroid is deleted
	//

	virtual ~Scout();

	//
	//  getRow
	//  getColumn
	//
	//  Purpose: To determine the row/column of this Asteroid.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The row/column of this Asteroid.
	//  Side Effect: N/A
	//

	//int getRow() const;
	//int getColumn() const;

	//
	//
	//  getRowSize
	//  getColumnSize
	//
	//  Purpose: To determine the number of rows/columns that this
	//	     Asteroid covers.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The number of rows/columns covered by this
	//	     Asteroid.
	//  Side Effect: N/A
	//

	//int getRowSize() const;
	//int getColumnSize() const;

	//  getRectangle
	//
	//  Purpose: To return the Rectangle portion of an Asteroid.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The Rectangle that describes the position and size
	//           of the Asteroid.
	//  Side Effect: N/A
	//

	//const Rectangle& getRectangle() const;

	//
	//  isDead
	//
	//  Purpose: To determine if this Asteroid is dead.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: Whether this Asteroid is dead.
	//  Side Effect: N/A
	//

	virtual bool isDead() const;

	//
	//  markDead
	//
	//  Purpose: To mark this Asteroid as dead.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Asteroid is marked as dead.
	//

	virtual void markDead();

	//
	//  getOreValue
	//
	//  Purpose: To determine the ore value of this Asteroid.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The ore value of this Asteroid.
	//  Side Effect: N/A
	//

	virtual unsigned int getOreValue() const;

	//
	//  randomizeOreValue
	//
	//  Purpose: To change the ore value for this Asteroid to a
	//	     random value.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Asteroid is set have a random ore value.
	//

	//void randomizeOreValue();

	//
	//  draw
	//
	//  Purpose: To draw this Asteroid onto the specified Buffer.
	//  Argument(s):
	//	<1> buffer: A reference to the Buffer
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Asteroid is drawn, with its ore value,
	//		 onto Buffer buffer.
	//

	virtual void draw(Buffer& buffer) const;

	//
	//  setPosition
	//
	//  Purpose: To move this Asteroid to the specified position.
	//  Argument(s):
	//	<1> row1: The row coordinate of the new position
	//	<2> col1: The column coordinate of the new position
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Asteroid is set to be at 
	//               position (row1, col1).
	//

	//void setPosition(int row1, int col1);

	//
	//  move
	//
	//  Purpose: To move this Asteroid by the specified amount.
	//  Argument(s):
	//	<1> row_change: The change to the row coordinate of the position
	//	<2> col_change: The change to the column coordinate of the 
	//                      position
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Asteroid moved by (row_change, col_change).
	//

	//void move(int row_change, int column_change);

	//
	//  Class Function: loadImage
	//
	//  Purpose: To load the asteroid image from the appropriate
	//	     file.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The asteroid image is loaded into memory.
	//

	static void loadImage();


	virtual unsigned int getShieldCost()const;

	virtual Enemy* getClone()const;

	virtual void update();



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

	//bool invariant() const;
	static const int ORE_VALUE = 45;
	static const int SHIELD_COST = 15;
private:
	Rectangle rectangle;
	bool life;
	//unsigned int ore_value;
};

#endif

