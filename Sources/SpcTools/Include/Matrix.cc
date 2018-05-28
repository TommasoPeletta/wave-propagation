//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     Matrix.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:03:56 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Matrix.hh"
#include "conditions.hh"

#include <iostream>

//=======================================================
// = CONSTRUCTORS
//=======================================================

template<class Type> 
MATRIX_INLINE Matrix<Type>::Matrix()
{
  matrix_=0;
  nbLine_=0;
  nbRow_=0;
}

// ============================================================
template<class Type> 
MATRIX_INLINE Matrix<Type>::Matrix(const Matrix<Type> &matrix)
{
  setDimension(matrix.getNbLine(),matrix.getNbRow());

  *this=matrix;
}

// ============================================================
template<class Type> 
MATRIX_INLINE Matrix<Type>::Matrix(const int nbLine, const int nbRow)
{
  require ("nbLine > 0", (nbLine > 0));
  require ("nbRow > 0", (nbLine > 0));

  nbLine_=nbLine;
  nbRow_=nbRow;
  matrix_=new Type*[nbLine_];
  
  int i;
  for (i=0;i<nbLine_;i++) 
    matrix_[i]=new Type[nbRow_];
}

//=======================================================
// = DESTRUCTOR
//=======================================================

template<class Type> 
MATRIX_INLINE Matrix<Type>::~Matrix()
{
  if (matrix_ != 0) {

    int i;
    for (i=0;i<nbLine_;i++)
      delete [] matrix_[i];

    delete [] matrix_;

    matrix_=0;
    nbLine_=0;
    nbRow_=0;

  }
}

//=======================================================
// = MUTATOR
//=======================================================

template<class Type> 
MATRIX_INLINE void Matrix<Type>::setDimension(const int nbLine, 
					      const int nbRow)
{
  require ("nbLine > 0", (nbLine > 0));
  require ("nbRow > 0", (nbLine > 0));

  nbLine_=nbLine;
  nbRow_=nbRow;
  
  matrix_=new Type*[nbLine_];
  
  int i;
  for (i=0;i<nbLine_;i++) 
    matrix_[i]=new Type[nbRow_];
}

//=======================================================
// = ACCESSORS
//=======================================================

template<class Type> 
MATRIX_INLINE void Matrix<Type>::setLine(const int line, const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));
  require ("0 <= line < nbLine", ((line >= 0) && (line < nbLine_)));

  int i;
  for (i=0;i<nbRow_;i++)
    matrix_[line][i]=value;
}

// ============================================================
template<class Type> 
MATRIX_INLINE void Matrix<Type>::setRow(const int row, const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));
  require ("0 <= row < nbRow", ((row >= 0) && (row < nbRow_)));

  int i;
  for(i=0;i<nbLine_;i++) 
    matrix_[i][row]=value;
}

//=======================================================
// = OPERATORS
//=======================================================

template<class Type> 
MATRIX_INLINE Matrix<Type>& Matrix<Type>::operator=(const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  int i,j;
  for(i=0;i<nbLine_;i++) 
    for(j=0;j<nbRow_;j++) 
    matrix_[i][j]=value;

  return *this;
}

// ============================================================
template<class Type> 
MATRIX_INLINE Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& matrix)
{

  if (matrix_ != 0) {

    int i;
    for (i=0;i<nbLine_;i++)
      delete [] matrix_[i];

    delete [] matrix_;

    matrix_=0;
    nbLine_=0;
    nbRow_=0;

  }

  setDimension(matrix.getNbLine(),matrix.getNbRow());
    
  int i,j;
  for(i=0;i<nbLine_;i++)
    for(j=0;j<nbRow_;j++) matrix_[i][j]=matrix.get(i,j);
  
  return *this;
}

// ============================================================
template<class Type> 
MATRIX_INLINE Matrix<Type>& Matrix<Type>::operator*=(const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  int i,j;
  for(i=0;i<nbLine_;i++) 
    for (j=0;j<nbRow_;j++)
      matrix_[i][j]*=value;
  
  return *this;
}
   
// ============================================================
template<class Type> 
MATRIX_INLINE Matrix<Type> Matrix<Type>::operator*(const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  Matrix<Type> result(nbLine_,nbRow_);

  int i,j;
  for(i=0;i<nbLine_;i++) 
    for (j=0;j<nbRow_;j++)
      result.set(i,j,matrix_[i][j]*value);

  return result; 
}

// ============================================================
template<class Type> 
MATRIX_INLINE Matrix<Type> Matrix<Type>::operator*(const Matrix<Type> &matrix)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  Matrix<Type> result(nbLine_,nbRow_);
  
  Type prod;

  int i,j,k;
  for(i=0;i<nbLine_;i++)
    for(j=0;j<nbRow_;j++) {
      prod=0;
      for (k=0;k<nbLine_;k++) prod+=matrix_[i][k]*matrix.get(k,j);
      result.set(i,j,prod);
    }

  return result;
}

// ============================================================
template<class Type> 
MATRIX_INLINE     Matrix<Type>& Matrix<Type>::operator-=(const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  int i,j;
  for(i=0;i<nbLine_;i++) 
    for (j=0;j<nbRow_;j++)
      matrix_[i][j]-=value;
  
  return *this;
}

// ============================================================
template<class Type> 
MATRIX_INLINE   Matrix<Type> Matrix<Type>::operator-(const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  Matrix<Type> result(nbLine_,nbRow_);

  int i,j;
  for(i=0;i<nbLine_;i++) 
    for (j=0;j<nbRow_;j++)
      result.set(i,j,matrix_[i][j]-value);

  return result; 
}

// ============================================================
template<class Type> 
MATRIX_INLINE   Matrix<Type>& Matrix<Type>::operator+=(const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  int i,j;
  for(i=0;i<nbLine_;i++) 
    for (j=0;j<nbRow_;j++)
      matrix_[i][j]+=value;
  
  return *this;
}

// ============================================================
template<class Type> 
MATRIX_INLINE   Matrix<Type> Matrix<Type>::operator+(const Type value)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  Matrix<Type> result(nbLine_,nbRow_);

  int i,j;
  for(i=0;i<nbLine_;i++) 
    for (j=0;j<nbRow_;j++)
      result.set(i,j,matrix_[i][j]+value);

  return result; 
}

// ============================================================
template<class Type> 
MATRIX_INLINE void Matrix<Type>::print()
{
  require ("The matrix has been allocated", (matrix_ != 0));

  int i,j;
  
  cout << "nbLine_ = " << nbLine_ << " nbRow_ = " << nbRow_ << endl;

  for (i=0;i<nbLine_;i++) {
    for (j=0;j<nbRow_;j++) cout << matrix_[i][j] << "\t";
    cout << endl;
  }
}

// ============================================================
template<class Type> 
MATRIX_INLINE Matrix<Type> Matrix<Type>::operator+(const Matrix<Type> &matrix)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  Matrix<Type> result(nbLine_,nbRow_);

  int i,j;
  for(i=0;i<nbLine_;i++)
    for(j=0;j<nbRow_;j++) 
      result.set(i,j,matrix_[i][j]+matrix.get(i,j));

  return result;
}

// ============================================================
template<class Type> 
MATRIX_INLINE Matrix<Type> Matrix<Type>::operator-(const Matrix<Type> &matrix)
{
  require ("The matrix has been allocated", (matrix_ != 0));

  Matrix<Type> result(nbLine_,nbRow_);

  int i,j;
  for(i=0;i<nbLine_;i++) 
    for(j=0;j<nbRow_;j++)
      result.set(i,j,matrix_[i][j]-matrix.get(i,j));

  return result;
}
