//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     RandomS.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:04:16 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "RandomS.hh"

Random RandomS::rand_;

//=======================================================
// = CONSTRUCTORS
//=======================================================

RandomS::RandomS()
{
  init();
}

//=======================================================
RandomS::RandomS(const RandomS &rand)
{
  *this=rand;
}

//=======================================================
// = DESTRUCTOR
//=======================================================

RandomS::~RandomS()
{

}

//=======================================================
// = OPERATORS
//=======================================================

RandomS& RandomS::operator=(const RandomS &rand)
{
  rand_.init(rand.getSeed());

  return *this;
}

//=======================================================
void RandomS::init(const long seed)
{
  rand_.init(seed);
}
