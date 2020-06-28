//
//  Asteroid.h
//
//  A module to encapsulate an asteroid.
//

#ifndef __ASTEROID_H__
#define __ASTEROID_H__
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

class Asteroid : public Enemy
{
public:
	//
	//  ROWS
	//  COLUMNS
	//
	//  The dimensions of the asteroid image.
	//

	static const int ROWS = 3;
	static const int COLUMNS = 4;

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

	Asteroid();

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

	Asteroid(const Asteroid& original);


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

	Asteroid& operator= (const Asteroid& original);


	//
	//  Destructor 
	//
	//  Purpose: To delete an instance of the Asteroid class
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The Asteroid is deleted
	//

	virtual ~Asteroid();


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

	void randomizeOreValue();

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



	//
	//  getShieldCost
	// 
	//
	//  Purpose: To determine the shield cost of this asteroid.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The shield cost of this asteroid.
	//  Side Effect:only implemented in derived class
	//

	virtual unsigned int getShieldCost()const;


	//
	//  getClone
	// 
	//
	//  Purpose: To replicate a copy or clone of this asteroid.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The clone or copy of this asteroid.
	//  Side Effect:only implemented in derived class
	//

	virtual Enemy* getClone()const;



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

	bool invariant() const;

private:
	Rectangle rectangle;
	unsigned int ore_value;
};

#endif




