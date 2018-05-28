#ifndef LIST_HH
#define LIST_HH

//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     List.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.2 $
//
// = DATE RELEASED
//     $Date: 2001/09/15 19:12:38 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================
 
#include "Bool.hh"
#include "Cell.hh"

template<class CellType>
class List
//=======================================================
//
// = DESCRIPTION
//
//   The generic class <{List}> implements a singly-linked list of
//   type <{CellType}>. A top to bottom traversal is also proposed.
//
// = SEE ALSO
//
//   <{Cell}>.
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTORS
  //=======================================================

  List();
  // Default constructor.

  List(const List<CellType> &aList);
  // Default constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~List();
  // Default destructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  int getSize() const;
  // Returns the number of elements.

  CellType currentValue() const;
  // Returns the current value of the list.

  void setCurrentValue(const CellType value);

  void delCurrentValue();
  // Deletes the current value of the list.

  void addValue(CellType value);
  // Adds a value <{value}> of type <{CellType}> to the list.

  //=======================================================
  // = OPERATORS
  //=======================================================

  List<CellType>& operator=(const List<CellType> &aList);
  // Assignement operator.

  void init();
  // Initializes the list.

  void initTraversal();
  // Initializes the traversal of the list. Then, the function
  // <{nextValue}> return the first value of the list.

  void moveCursorTo(const int position);
  // move cursor to position <{position}> in list.

  bool isTraversalLastValue();
  // Is the last value of the traversal? If not, it jumps to the next
  // value.

  //=======================================================
  // = PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

private:

  Cell<CellType> *first_;
  // Pointer onto the first cell of the list.

  Cell<CellType> *last_;
  // Pointer onto the last cell of the list.

  int size_;
  // Number of cells.

  Cell<CellType> *cursor_;
  // Pointer onto the current traversal cell.

};

//=======================================================
// INLINE METHODS
//=======================================================

//=======================================================
// = ACCESSORS
//=======================================================

template<class CellType>
inline int List<CellType>::getSize() const
{
  return size_;
}

//=======================================================
template<class CellType>
inline CellType List<CellType>::currentValue() const 
{
  return cursor_->getValue();
}

//=======================================================
template<class CellType>
inline void List<CellType>::setCurrentValue(const CellType value) 
{
  cursor_->setValue(value);
}

//=======================================================
// = OPERATORS
//=======================================================

//=======================================================
template<class CellType>
inline void List<CellType>::initTraversal()
{
  cursor_=first_;
}


//#ifdef __GNUC__

#if defined(SP)

#define LIST_INLINE inline
#include "List.cc"

#else

#define LIST_INLINE 
#include "List.cc"


#endif

#endif
