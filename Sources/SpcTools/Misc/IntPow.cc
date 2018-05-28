//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     IntPow.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:03:39 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "IntPow.hh"

//=======================================================
// = CONSTRUCTORS
//=======================================================

IntPow::IntPow(const int base, const int nbMaxValue)
{
  base_=base;
  nbMaxValue_=nbMaxValue;

  pow_=new int[nbMaxValue_];

  int i;
  pow_[0]=1;
  for (i=1;i<nbMaxValue_;i++) pow_[i]=base_*pow_[i-1];
}

//=======================================================
IntPow::IntPow(const IntPow& aIntPow)
{
 *this=aIntPow;
}
 
//=======================================================
// = DESTRUCTOR
//=======================================================

IntPow::~IntPow()
{
  delete [] pow_;
}

//=======================================================
// = OPERATORS
//=======================================================
  
IntPow& IntPow::operator=(const IntPow& aIntPow)
{
  base_=aIntPow.getBase();
  nbMaxValue_=aIntPow.getNbMaxValue();

  if (pow_ != 0) delete [] pow_;

  pow_=new int[nbMaxValue_];

  int i;
  pow_[0]=1;
  for (i=1;i<nbMaxValue_;i++) pow_[i]=base_*pow_[i-1];  

  return *this;
}
