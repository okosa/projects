//
//  Buffer.h
//
//  A module to encapsulate a text screen buffer.
//

#ifndef __BUFFER_H__
#define __BUFFER_H__



//
//  Buffer
//
//  A class to represent a buffer for a text-based display.
//    Everything to be displayed should be drawn to the Buffer
//    and then, afterwards, the Buffer should be drawn to the
//    screen.  A Buffer is drawn with a border of '#' characters
//    around it.  Each position in the Buffer is called a cell,
//    and there exist functions to clear all cells and to change
//    the character in a specific cell.
//
//  A Buffer has an offset in row and column coordinates.  The
//    Buffer in considered to represent an area of space with
//    its top left corner at the offset position.  Characters
//    drawn to a Buffer take this offset into account.
//

class Buffer
{
public:
	//
	//  ROWS
	//  COLUMNS
	//
	//  The dimensions of a Buffer.
	//

	static const int ROWS = 20;
	static const int COLUMNS = 60;

public:
	//
	//  Default Constructor
	//
	//  Purpose: To create a new Buffer.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Buffer is created with an offset of
	//		 (0, 0) and all cells set to blank (' ').
	//

	Buffer();

	//
	//  clear
	//
	//  Purpose: To clear this Buffer.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: All cells in this Buffer are set to blank
	//		 (' ').
	//

	void clear();

	//
	//  print
	//
	//  Purpose: To print this Buffer to standard output.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Buffer, including its border, is printed
	//		 to standard output.
	//

	void print() const;

	//
	//  setOffset
	//
	//  Purpose: To change the offset for this Buffer.
	//  Argument(s):
	//	<1> r
	//	<2> c: The new row and column offset
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Buffer is set to have an offset of (r, c).
	//

	void setOffset(int row1, int col1);

	//
	//  setCell
	//
	//  Purpose: To change the value of the specified cell in this
	//	     Buffer.
	//  Argument(s):
	//	<1> value: The new value
	//	<2> row1: The row of the cell to change  
	//	<3> col1: The column of the cell to change
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: If cell (row1, col1) is within the bounds of this
	//		 Buffer, when the offset is taken into account,
	//		 it is set to have value value.
	//

	void setCell(char value, int row1, int col1);

private:
	int row_offset;
	int column_offset;
	char buffer[ROWS][COLUMNS];
};



#endif
