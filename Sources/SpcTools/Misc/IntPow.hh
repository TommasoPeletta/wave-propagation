#ifndef INTPOW_HH
#define INTPOW_HH

//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     IntPow.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:03:37 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "conditions.hh"

class IntPow
//=======================================================
//
// = DESCRIPTION
//
//   The class <{IntPow}> features a tool which computes integer power
//   of any number.
//
//=======================================================
{
public:
  
  //=======================================================
  // = CONSTRUCTORS
  //=======================================================

  IntPow(const int base=2, const int nbMaxValue=30);
  // Constructs an object with a base <{base}> and for a maximum
  // number of value <{nbMaxValue}>.

  IntPow(const IntPow& aIntPow);
  // Copy constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~IntPow();
  // Default destructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  int get(const int index) const;
  // Returns the specified base powered by <{index}>.

  int getBase() const;
  // Gets the base.

  int getNbMaxValue() const;
  // Gets the maximum returnable number of value.

  //=======================================================
  // = OPERATORS
  //=======================================================

  IntPow& operator=(const IntPow& aIntPow);
  // Assignment operator.

private:

  int *pow_;
  // Vector of powered values.

  int base_;
  // Stores the base.

  int nbMaxValue_;
  // Stores the maximum number of value (the length of the vector).

};

// ============================================================
// = INLINE METHODS
// ============================================================

//=======================================================
// = ACCESSORS
//=======================================================

inline int IntPow::get(const int index) const
{
  require ("0 <= index < nbValue_",((index >= 0) && (index < nbMaxValue_))); 

  return pow_[index];
}

//=======================================================
inline int IntPow::getBase() const
{
  return base_;
}

//=======================================================
inline int IntPow::getNbMaxValue() const
{
  return nbMaxValue_;
}

#endif
