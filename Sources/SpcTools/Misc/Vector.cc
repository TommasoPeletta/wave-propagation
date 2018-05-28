//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     Vector.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.2 $
//
// = DATE RELEASED
//     $Date: 2001/04/05 09:29:38 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Vector.hh"

//=======================================================
// = CONSTRUCTORS
//=======================================================

template<class Type> 
VECTOR_INLINE Vector<Type>::Vector()
{
  size_=0;
  vector_=0;
}

// ============================================================
template<class Type> 
VECTOR_INLINE Vector<Type>::Vector(const int size)
{
  require ("The vector size must to be positive", (size > 0));

  size_=size;
  vector_=new Type[size_];
}

// ============================================================
template<class Type> 
VECTOR_INLINE Vector<Type>::Vector(const Vector<Type> &aVector)
{
  size_=0;
  vector_=0;

  *this=aVector;
}

//=======================================================
// = DESTRUCTOR
//=======================================================

template<class Type> 
VECTOR_INLINE Vector<Type>::~Vector()
{
  if (vector_ != 0) delete [] vector_;
}

//=======================================================
// = MUTATOR
//=======================================================

template<class Type> 
VECTOR_INLINE void Vector<Type>::setSize(const int size)
{
  require ("The vector size must to be positive", (size > 0));

  size_=size;

  if (vector_ != 0) delete [] vector_;
  vector_=new Type[size_];
}

//=======================================================
// = ACCESSORS
//=======================================================

template<class Type> 
VECTOR_INLINE void Vector<Type>::print() const
{
  int i;

  for (i=0;i<size_;i++)
    cout << vector_[i] << " ";

  cout << endl;
}

//=======================================================
// = OPERATORS
//=======================================================

template<class Type> 
VECTOR_INLINE Vector<Type> Vector<Type>::operator*(const Type value) const
{
  require ("The vector has been allocated", (vector_ != 0));

  Vector<Type> result(size_);

  int i;
  for (i=0;i<size_;i++) result.set(i,vector_[i]*value);

  return result;
}

// ============================================================
template<class Type> 
VECTOR_INLINE Vector<Type> 
Vector<Type>::operator+(const Vector<Type>& vector) const
{
  require ("The vector has been allocated", (vector_ != 0));

  Vector<Type> result(size_);

  int i;
  for (i=0;i<size_;i++) result.set(i,vector_[i]+vector.get(i));
  
  return result;
}

// ============================================================
template<class Type>
VECTOR_INLINE Vector<Type>&
Vector<Type>::operator+=(const Vector<Type>& vector)
{
  require ("The vector has been allocated", (vector_ != 0));

  int i;
  for (i=0;i<size_;i++) add(i,vector.get(i));
  
  return *this;
}

// ============================================================
template<class Type> 
VECTOR_INLINE Vector<Type> 
Vector<Type>::operator-(const Vector<Type>& vector) const
{
  require ("The vector has been allocated", (vector_ != 0));

  Vector<Type> result(size_);

  int i;
  for (i=0;i<size_;i++) result.set(i,vector_[i]-vector.get(i));
  
  return result;
}

// ============================================================
template<class Type> 
VECTOR_INLINE Type Vector<Type>::operator*(const Vector<Type>& vector) const
{
  require ("The vector has been allocated", (vector_ != 0));

  Type result=0;

  int i;
  for (i=0;i<size_;i++) 
    result+=vector_[i]*vector.get(i);

  return result;
}

// ============================================================
template<class Type> 
VECTOR_INLINE Vector<Type>& Vector<Type>::operator=(const Type value)
{
  require ("The vector has been allocated", (vector_ != 0));

  int i;
  for (i=0;i<size_;i++) vector_[i]=value;

  return *this;
}

// ============================================================
template<class Type> 
VECTOR_INLINE Vector<Type>& Vector<Type>::operator=(const Vector<Type>& vector)
{
  setSize(vector.getSize());

  int i;
  for (i=0;i<size_;i++) vector_[i]=vector.get(i);

  return *this;
}

// ============================================================
template<class Type> 
VECTOR_INLINE Vector<Type> Vector<Type>::operator/=(const Type value)
{
  require ("The vector has been allocated", (vector_ != 0));

  int i;
  for (i=0;i<size_;i++) vector_[i]/=value;
  
  return *this;
}
