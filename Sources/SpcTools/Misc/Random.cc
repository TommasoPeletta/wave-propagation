//=======================================================
//
// = LIBRARY
//     Misc
//
// = FILENAME
//     Random.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.3 $
//
// = DATE RELEASED
//     $Date: 2001/01/11 10:17:59 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Random.hh"

const long IM1 = 2147483563;
const long IM2 = 2147483399;
const float AM = 1./IM1;
const long IMM1 = IM1 - 1;
const int IA1 = 40014;
const int IA2 = 40692;
const int IQ1 = 53668;
const int IQ2 = 52774;
const int IR1 = 12211;
const int IR2 = 3791;
const int NDIV = 1+IMM1/NTAB;
const float EPS = 1.2e-7;
const float RNMX = 1. - EPS;

//=======================================================
// = CONSTRUCTORS
//=======================================================

Random::Random()
{
  // Inits the seed
  init();
}

//=======================================================
Random::Random(const Random &rand)
{
  *this=rand;
}

//=======================================================
// = DESTRUCTOR
//=======================================================

Random::~Random()
{

}

//=======================================================
// = OPERATORS
//=======================================================

Random& Random::operator=(const Random &rand)
{
  seed_=rand.getSeed();

  init(seed_);
  //srand48(seed_);

  return *this;
}

//=======================================================
void Random::init(const long seed)
{
  seed_=seed;

  // Chooses a seed if it was not specified in the call
  if (seed == -9999) {

    struct timeval time;
    gettimeofday(&time,NULL);

    seed_=time.tv_sec;
  }

  int j;
  long k;

  idum_ = seed_;
  idum2_ = idum_;
  for (j=NTAB+7; j>=0; j--)
    {
      k = idum_/IQ1;
      idum_ = IA1 * (idum_ - k*IQ1) - k*IR1;
      if (idum_ < 0) idum_ += IM1;
      if (j < NTAB) iv_[j] = idum_;
    }
  iy_ = iv_[0];


//   // Chooses a seed if it was not specified in the call
//   if (seed == -9999) {
// 
//     struct timeval time;
//     gettimeofday(&time,NULL);
// 
//     seed_=time.tv_sec;
//   }
// 
//   srand48(seed_);
}

//=======================================================
float Random::getNormal()
{
  //Random rnd1;
  return ((float) cos(2*3.1415926535*get())*sqrt(-2*log(get())));
}

//=======================================================
float Random::get()
{
//   return (float) drand48();

  int j;
  long k;
  float temp;

  k = idum_/IQ1;
  idum_ = IA1 * (idum_ - k*IQ1) - k*IR1;
  if (idum_ < 0) idum_ += IM1;
  k = idum2_/IQ2;
  idum2_ = IA2 * (idum2_ - k*IQ2) - k*IR2;
  if (idum2_ < 0) idum2_ += IM2;
  j = iy_/NDIV;
  iy_ = iv_[j] - idum2_;
  iv_[j] = idum_;
  if (iy_ < 1) iy_ += IMM1;
  if ((temp = AM*iy_) > RNMX) return RNMX;
  else return temp;
}
