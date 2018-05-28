//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     List.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.3 $
//
// = DATE RELEASED
//     $Date: 2001/09/15 19:12:50 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================
 
#include "List.hh"

#include <iostream>

//=======================================================
// = CONSTRUCTORS
//=======================================================

template<class CellType>
LIST_INLINE List<CellType>::List()
{
  first_=0;
  last_=0;
  cursor_=0;
  size_=0;
}

//=======================================================
template<class CellType>
LIST_INLINE List<CellType>::List(const List<CellType> &aList)
{
  *this=aList;
}

//=======================================================
// = DESTRUCTOR
//=======================================================

template<class CellType>
LIST_INLINE List<CellType>::~List()
{
  if (first_ != 0) delete first_;
}

//=======================================================
// = ACCESSORS
//=======================================================

template<class CellType>
LIST_INLINE void List<CellType>::addValue(CellType value)
{
  if (first_ == 0) {
    // If the list is empty, creates a new one and sets the value.
    first_=new Cell<CellType>;
    first_->setValue(value);
    last_=first_;
  }
  else {
    // If not, the last cell creates its successor and sets the value.
    Cell<CellType> *cursor;
    cursor=last_;
    last_=new Cell<CellType>;
    last_->setValue(value);
    cursor->setNextCell(last_);
  }
  size_++;
}

//=======================================================
// = OPERATORS
//=======================================================

template<class CellType>
LIST_INLINE List<CellType>&
List<CellType>::operator=(const List<CellType> &aList)
{
  if (aList.size_ > 0) {

    Cell<CellType> *aListCursor=aList.cursor_;
  
    aListCursor=aList.first_;
    
    init();

    while(1) {
    
      addValue(aListCursor->getValue());
  
      if (aListCursor == aList.last_) break;
    
      aListCursor=aListCursor->getNextCell();
    }
  }

  return *this;
}

//=======================================================
template<class CellType>
LIST_INLINE void List<CellType>::init()
{
  if (first_ != 0) delete first_;

  first_=0;
  last_=0;  
  size_=0;
  cursor_=0;
}

//=======================================================
template<class CellType>
LIST_INLINE bool List<CellType>::isTraversalLastValue()
{
  if (cursor_ == last_) return true;
  else {
    cursor_=cursor_->getNextCell();
    return false;
  }
}

//=======================================================
template<class CellType>
inline void List<CellType>::moveCursorTo(const int position)
{
  int i;
  cursor_=first_;
  for(i=0;i<position;i++)
    cursor_=cursor_->getNextCell();
}

//=======================================================
template<class CellType>
LIST_INLINE void List<CellType>::delCurrentValue()
{
  if (size_ != 0) {

    // The current value is the first one
    if (first_ == cursor_) {
      
      // And also the last one -> the list is now empty
      if (first_ == last_) init();

      // Deletes the first one and sets the first pointer to the right
      // value.
      else { 
	first_=cursor_->getNextCell();
	cursor_->setNextCell(0);
	delete cursor_;
	size_--;
      }
    }
    else {

      // Finds the predecessor
      Cell<CellType> *pred=first_;  
      while (pred->getNextCell() != cursor_) {
	pred=pred->getNextCell();
	if (pred == 0) {
	  cerr << "The end of the list is reached and "
	       << "the predecessor is not found." << endl;
	  return;
	}
      }

      // Sets the last pointer to pred if the item to delete is the
      // last one
      if (cursor_ == last_) last_=pred;

      // Deletes the cursor and sets the first pointer to the right
      // value.
      pred->setNextCell(cursor_->getNextCell());
      //cursor_->setNextCell(0);
      cout << "Avant delete" << endl;
      delete cursor_;
      size_--;

    }
  }
    
}
