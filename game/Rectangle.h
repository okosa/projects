//
//  Rectangle.h
//
//  A module to encapsulate a rectangle.
//

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Buffer.h"

//
//  Rectangle
//
//  A class to represent a Rectangle.  A Rectangle has a
//    position and two dimensions.  
//
//  Class Invariant:
//	<1> row_size >= 1
//	<2> column_size >= 1
//

class Rectangle
{
public:
	//
	//  Default Constructor
	//
	//  Purpose: To create a new Rectangle with default values.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Rectangle is created at position (0, 0)
	//		 with the dimensions of (1, 1).  
	//

	Rectangle();

	//
	//  Initializing Constructor
	//
	//  Purpose: To create a new Rectangle with initial values.
	//  Argument(s): 
	//	<1> row1: The initial row coordinate 
	//	<2> column1: The initial column coordinate 
	//	<3> row_size1: The row size
	//	<4> column_size1: The column size 
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Rectangle is created at the specified
	//		 with the specified dimensions.  
	//

	Rectangle(int row1, int column1, int row_size1, int column_size1);

	//
	//  Copy Constructor
	//
	//  Purpose: To create a new Rectangle the same as an existing Rectangle.
	//  Argument(s): 
	//	<1> original: A constant reference to a Rectangle
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Rectangle is created with the same positions
	//               and dimensions as the existing Rectangle
	//

	Rectangle(const Rectangle& original);


	//
	//  Assignment Operator 
	//
	//  Purpose: To assign the values from one Rectangle to another
	//  Argument(s): 
	//	<1> original: A constant reference to a Rectangle
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: A new Rectangle is created with the same positions
	//               and dimensions as the existing Rectangle
	//

	Rectangle& operator= (const Rectangle& original);


	//
	//  Destructor 
	//
	//  Purpose: To delete an instance of the Rectangle class
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The Rectangle is deleted
	//

	~Rectangle();

	//
	//  getRow
	//  getColumn
	//
	//  Purpose: To determine the row/column of this Rectangle.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The row/column of this Rectangle.
	//  Side Effect: N/A
	//

	int getRow() const;
	int getColumn() const;

	//
	//  getRowSize
	//  getColumnSize
	//
	//  Purpose: To determine the number of rows/columns that this
	//	     Rectangle covers.
	//  Argument(s): N/A
	//  Precondition(s): N/A
	//  Returns: The number of rows/columns covered by this
	//	     Rectangle.
	//  Side Effect: N/A
	//

	int getRowSize() const;
	int getColumnSize() const;

	//
	//  isOverlapping
	//
	//  Purpose: To check whether another Rectangle is overlapping with 
	//           this Rectangle.
	//  Argument(s):
	//	<1> other: The other Rectangle
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Rectangle is set to be at 
	//               position (row1, col1).
	//

	bool isOverlapping(const Rectangle& other);

	//
	//  setPosition
	//
	//  Purpose: To move this Rectangle to the specified position.
	//  Argument(s):
	//	<1> row1: The row coordinate of the new position
	//	<2> col1: The column coordinate of the new position
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Rectangle is set to be at 
	//               position (row1, col1).
	//

	void setPosition(int row1, int col1);

	//
	//  move
	//
	//  Purpose: To move this Rectangle by the specified amount.
	//  Argument(s):
	//	<1> row_change: The change to the row coordinate of the position
	//	<2> col_change: The change to the column coordinate of the 
	//                      position
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Rectangle moved by (row_change, col_change).
	//

	void move(int row_change, int column_change);

	//
	//  setSize
	//
	//  Purpose: To set the dimensions for this Rectangle.
	//  Argument(s):
	//	<1> row1: The new row size 
	//	<2> col1: The new column size
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: This Rectangle is changed to have the specified
	//               row size and column size
	//

	void setSize(int row_size1, int col_size1);

	//
	//  copy
	//
	//  Purpose: A helper function to copy the fields of another Rectangle
	//           to this Rectangle.
	//  Argument(s): 
	//	<1> original: A constant reference to a Rectangle
	//  Precondition(s): N/A
	//  Returns: N/A
	//  Side Effect: The values for the fields of another Rectangle are
	//               copied into this Rectangle
	//

private:
	void copy(const Rectangle& original);

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
	int row;
	int column;
	int row_size;
	int column_size;
};

#endif


