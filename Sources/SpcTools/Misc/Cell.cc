//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     Cell.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:03:30 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Cell.hh"

//=======================================================
// = CONSTRUCTORS
//=======================================================

template<class CellType>
CELL_INLINE Cell<CellType>::Cell()
{
  //value_=(int) 0;
  nextCell_=0;
}

//=======================================================
template<class CellType>
CELL_INLINE Cell<CellType>::Cell(Cell<CellType> &aCell)
{
  *this=aCell;
}

//=======================================================
// = DESTRUCTOR
//=======================================================
  
template<class CellType>
CELL_INLINE Cell<CellType>::~Cell()
{
  if (nextCell_ != 0) delete nextCell_;
}

//=======================================================
// = OPERATOR
//=======================================================

template<class CellType>
CELL_INLINE Cell<CellType>& 
Cell<CellType>::operator=(const Cell<CellType> &aCell)
{
  value_=aCell.value_;
  nextCell_=aCell.nextCell_;

  return *this;
}


