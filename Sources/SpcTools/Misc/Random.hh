#ifndef RANDOM_HH
#define RANDOM_HH

//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     Random.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//     Stefan Marconi
//
// = VERSION
//     $Revision: 1.3 $
//
// = DATE RELEASED
//     $Date: 2001/01/11 10:18:08 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

const int NTAB = 32;

class Random
//=======================================================
//
// = DESCRIPTION
//
//   The class <{Random}> features the generation of random numbers. 
//   They can be initialized with a specified seed or not. The 
//   random numbers available are: non-negative double-precision
//   floating-point values uniformly distributed over the 
//   interval [0.0, 1.0] and double-precision floating-point normally
//   distributed values. The uniform set is obtained with linear 
//   congruential algorithm and 48-bit integer arithmetic while the second 
//   is obtained from the first with Polar coordinate method by Knuth.
//   
// = NOTE
//   
//   This class has been modified in order to generate random number as 
//   proposed by L'Ecuyer. The functions drand48 and srand48 are consequently 
//   not called anymore. References: Numerical Recipes in C, second edition, 
//   p. 281-282. Thanks to R. Chatagny for his class.
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTORS
  //=======================================================

  Random();
  // Default constructor.

  Random(const Random &rand);
  // Copy constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~Random();
  // Default destructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  float get();
  // Gets a random value uniformly distributed in [0.0,1.0].

  float getNormal();
  // Gets a random value normally distributed

  long getSeed() const;
  // Gets the seed of the generator.

  //=======================================================
  // = OPERATORS
  //=======================================================

  Random& operator=(const Random &rand);
  // Assignement operator.

  void init(const long seed=-9999);
  // Initializes the generator with the seed <{seed}>.

  //=======================================================
  // = PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

private:

  long seed_;
  long idum_;
  long idum2_;
  long iy_;
  long iv_[NTAB];
};

//=======================================================
// INLINE METHODS
//=======================================================

inline long Random::getSeed() const
{
  return seed_;
}

#endif
