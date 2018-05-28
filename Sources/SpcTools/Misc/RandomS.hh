#ifndef RANDOMS_HH
#define RANDOMS_HH

//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     RandomS.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:04:13 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Random.hh"

class RandomS
//=======================================================
//
// = DESCRIPTION
//
//   The class <{RandomS}> features a static generator number. So that
//   every instace of the class refers to the same generator. The
//   generator can be initialized with a seed or with a default value.
//
// = SEE ALSO
//   <{Random}>
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTORS
  //=======================================================

  RandomS();
  // Default constructor.

  RandomS(const RandomS &rand);
  // Copy constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~RandomS();
  // Default destructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  float get() const;
  // Gets a random value.

  long getSeed() const;
  // Gets the seed of the generator.

  //=======================================================
  // = OPERATORS
  //=======================================================

  RandomS& operator=(const RandomS &rand);
  // Assignement operator.

  void init(const long seed=-9999);
  // Initializes the generator with the seed <{seed}>.

  //=======================================================
  // = PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

private:

  static Random rand_;
  // This the unique generator of the session.

};

//=======================================================
// INLINE METHODS
//=======================================================

//=======================================================
// = ACCESSORS
//=======================================================

inline float RandomS::get() const
{
  return rand_.get();
}

//=======================================================
inline long RandomS::getSeed() const
{
  return rand_.getSeed();
}

#endif
