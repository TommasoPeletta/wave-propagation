#ifndef VECTOR_HH
#define VECTOR_HH

//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     Vector.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.2 $
//
// = DATE RELEASED
//     $Date: 2001/04/05 09:29:31 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "conditions.hh"

template<class Type> 
class Vector
//=======================================================
//
// = DESCRIPTION
//
//   The template class <{Vector}> describes a vector composed of any
//   uniform type of variable. Basic operations are defined on it.
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTORS
  //=======================================================

  Vector();
  // Default constructor.

  Vector(const int size);
  // Constructs a vector of <{size}> elements.

  Vector(const Vector<Type> &aVector);
  // Copy constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~Vector();
  // Default destructor.

  //=======================================================
  // = MUTATOR
  //=======================================================

  void setSize(const int size);
  // Sets the size of the vector to <{size}> elements.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  void set(const int pos, const Type value);
  // Sets the position <{pos}> to the value <{value}>.

  Type get(const int pos) const;
  // Gets the position <{pos}>.

  int getSize() const;
  // Gets the size of the vector.

  void print() const;
  // Prints the components of the vector.

  //=======================================================
  // = OPERATORS
  //=======================================================

  Vector<Type>& operator=(const Vector<Type>& vector);
  // Assignement operator.

  Vector<Type> operator*(const Type value) const;
  // V*w

  Vector<Type> operator+(const Vector<Type>& vector) const;
  // V*W

  Vector<Type>& operator+=(const Vector<Type>& vector);
  // V+=W

  Vector<Type> operator-(const Vector<Type>& vector) const;
  // V-W

  Type operator*(const Vector<Type>& vector) const;
  // V*W

  Vector<Type>& operator=(const Type value);
  // V=w

  void add(const int pos, const Type value);
  // V[pos]=w

  Vector<Type> operator/=(const Type value);
  // V=V/w

  //=======================================================
  // = PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

protected:

  Type *vector_;
  // The vector.

  int size_;
  // Size of the vector.

};

// ============================================================
// = INLINE METHODS
// ============================================================

//=======================================================
// = ACCESSORS
//=======================================================
template<class Type> 
inline void Vector<Type>::set(const int pos, const Type value)
{
  require ("0 <= pos < size", ((pos >= 0) && (pos < size_)));

  vector_[pos]=value;
}

// ============================================================
template<class Type> 
inline Type Vector<Type>::get(const int pos) const
{
  require ("0 <= pos < size", ((pos >= 0) && (pos < size_)));

  return vector_[pos];
}

// ============================================================
template<class Type> 
inline int Vector<Type>::getSize() const
{
  return size_;
}

//=======================================================
// = OPERATORS
//=======================================================

template<class Type> 
inline void Vector<Type>::add(const int pos, const Type value)
{
  require ("0 <= pos < size", ((pos >= 0) && (pos < size_)));

  vector_[pos]+=value;
}


//#ifdef __GNUC__

#if defined(SP)

#define VECTOR_INLINE inline
#include "Vector.cc"

#else

#define VECTOR_INLINE
#include "Vector.cc"

#endif

#endif
