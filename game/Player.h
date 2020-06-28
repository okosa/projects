//
//  Player.h
//
//  A module to encapsulate the Player.
//

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Rectangle.h"
#include "Buffer.h"


//
//  Player
//
//  A class to represent the player.  A player has a position,
//    dimensions, and counters for shield strength and ore
//    collected.  A player is considered to be dead if it has a
//    shield strength of 0.
//
//  Class Invariant:
//	<1> m_row_size >= 1
//	<2> m_column_size >= 1
//	<3> m_shield_strength <= SHIELD_STRENGTH_MAX
//					       (hidden constant)
//

class Player
{
public:
	//
	//  ROWS
	//  COLUMNS
	//
	//  The dimensions of the asteroid image.
	//

	static const unsigned int ROWS = 5;
	static const unsigned int COLUMNS = 7;

public:
	//
	//  Default Constructor
	//
	//  Purpose: To create a new Player with default values.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Player is created at position (0, 0) with
	//		 the correct dimensions.  The new Player is set
	//		 to have a maximum shield strength and to have
	//		 collected 0 ore.
	//

	Player();

	Player(const Player& original);

	Player& operator=(const Player& original);

	~Player();


	//
	//  getRow
	//  getColumn
	//
	//  Purpose: To determine the row/column of this Player.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The row/column of this Player.
	//  Side Effect: N/A
	//

	int getRow() const;
	int getColumn() const;

	//
	//  getRowSize
	//  getColumnSize
	//
	//  Purpose: To determine the number of rows/columns this
	//	     Player covers.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The number of rows/columns covered by this Player.
	//  Side Effect: N/A
	//

	int getRowSize() const;
	int getColumnSize() const;

	//  getRectangle
	//
	//  Purpose: To return the Rectangle portion of a Player.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The Rectangle that describes the position and size
	//           of the Player.
	//  Side Effect: N/A
	//

	const Rectangle& getRectangle() const;

	//
	//  isDead
	//
	//  Purpose: To determine if this Player is dead.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: Whether this Player is dead.
	//  Side Effect: N/A
	//

	bool isDead() const;

	//
	//  getShieldStrengthFraction
	//
	//  Purpose: To determine the current shield strength of this
	//	     Player as a fraction in the range [0.0, 1.0].
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The fraction of its maximum shield strength this
	//	     Player currently has.
	//  Side Effect: N/A
	//

	double getShieldStrengthFraction() const;

	//
	//  getOreCollected
	//
	//  Purpose: To determine the amount of ore collected by this
	//	     Player.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The amount of ore collected by this Player.
	//  Side Effect: N/A
	//

	unsigned int getOreCollected() const;

	//
	//  draw
	//
	//  Purpose: To draw this Player onto the specified Buffer.
	//  Argument(s):
	//	<1> buffer: A reference to the Buffer
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Player is drawn onto Buffer buffer.
	//

	void draw(Buffer& buffer) const;

	//
	//  setPosition
	//
	//  Purpose: To move this Player to the specified position.
	//  Argument(s):
	//	<1> r
	//	<2> c: The new position
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Player is set to be at position (r, c).
	//

	void setPosition(int r, int c);

	//
	//  move
	//
	//  Purpose: To move this Player by the specified amount.
	//  Argument(s):
	//	<1> r
	//	<2> c: The amount to move
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Player is moved by (r, c).
	//

	void move(int r, int c);

	//
	//  reduceShieldStrength
	//
	//  Purpose: To reduce the shield strength of this Player by the
	//	     specified amount.
	//  Argument(s):
	//	<1> amount: The amount
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: If amount is greater than the current shield
	//		 strength of this Player, this Player is marked
	//		 as dead.  Otherwise, the shield stength of this
	//		 Player is reduced by amount.
	//

	void reduceShieldStrength(unsigned int amount);

	//
	//  increaseOreCollected
	//
	//  Purpose: To increase the ore collected by this Player by the
	//	     specified amount.
	//  Argument(s):
	//	<1> amount: The amount of ore
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Player's ore collected amount is increased
	//		 by amount.
	//

	void increaseOreCollected(unsigned int amount);

	//
	//  update
	//
	//  Purpose: To update this Player for one time unit.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Player is updated for one time unit.  If
	//		 this Player is not dead, its shield strength is
	//		 increased by 1.
	//

	void update();

	//
	//  printStatusRow
	//
	//  Purpose: To display the status of this Player.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The status of this player is printed to
	//		 standard output.
	//

	void printStatusRow() const;

	//
	//  loadImage
	//
	//  Purpose: To load the player image from the appropriate file.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The player image is loaded into memory.
	//

	static void loadImage();

private:
	//
	//  printStatusBar
	//
	//  Purpose: To print a status bar of the specified
	//	     length that has two pipe symbols at the two
	//           ends and asterisks and hyphens between.
	//           The number of asterisks corresponds to the 
	//           specified fraction of length - 2. The
	//           asterisks appear on the left of the status
	//           bar and the remaining space is filled with
	//           hyphens.
	//  Argument(s):
	//	<1> length: The length of the desired status bar, 
	//                  including the pipe ('|') symbols on 
	//                  the two ends, in characters
	//	<2> fraction: The fraction of the bar that is full 
	//                   asterisks
	//  Precondition(s):
	//	<1> length >= 2
	//	<2> fraction >= 0.0
	//	<3> fraction <= 1.0
	//  Returns: N/A
	//  Side Effect: A status bar of the given length (including pipe
	//		 symbols on both ends) is printed to standard output.
	//		 The leftmost fraction of the status bar contains
	//               asterisks and the remainder contains hyphens.
	//

	void printStatusBar(unsigned int, double) const;

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
	unsigned int shield_strength;
	unsigned int ore_collected;
};



#endif
