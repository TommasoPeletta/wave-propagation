#ifndef CELL_HH
#define CELL_HH
 
//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     Cell.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis 
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:03:33 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

template<class CellType>
class Cell 
//=======================================================
//
// = DESCRIPTION
//
//   The template class <{Cell}> features a list element of type
//   <{CellType}>.
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTORS
  //=======================================================

  Cell();
  // Default constructor.

  Cell(Cell<CellType> &aCell);
  // Copy constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~Cell();
  // Default destructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  void setValue(const CellType &value);
  // Sets the value <{value}> of the cell.

  CellType getValue(); //const;
  // Gets the value of the cell.

  Cell<CellType> *getNextCell() const;
  // Gets a pointer onto its next cell.

  void setNextCell(Cell<CellType> *nextCell);
  // Sets the value of the pointer to the next cell.

  //=======================================================
  // = OPERATOR
  //=======================================================

  Cell<CellType>& operator=(const Cell<CellType> &aCell);
  // Assignement operator.

  //=======================================================
  // = PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

private:

  CellType value_;
  // Value of the cell.

  Cell<CellType> *nextCell_;
  // Pointer onto its next cell.

};

//=======================================================
// INLINE METHODS
//=======================================================

//=======================================================
// = ACCESSORS
//=======================================================

template<class CellType>
inline void Cell<CellType>::setValue(const CellType &value)
{
  value_=value;
}

//=======================================================
template<class CellType>
inline CellType Cell<CellType>::getValue() //const
{
  return value_;
}

//=======================================================
template<class CellType>
inline Cell<CellType> *Cell<CellType>::getNextCell() const
{
 return nextCell_;
}

//=======================================================
template<class CellType>
inline void Cell<CellType>::setNextCell(Cell<CellType> *nextCell)
{
  nextCell_=nextCell;
}


//#ifdef __GNUC__


#if defined(SP)

#define CELL_INLINE inline
#include "Cell.cc"

#else

#define CELL_INLINE 
#include "Cell.cc"

#endif

#endif
