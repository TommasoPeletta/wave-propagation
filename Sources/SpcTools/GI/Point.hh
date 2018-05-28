#ifndef POINT_HH
#define POINT_HH

//=======================================================
//
// = LIBRARY
//     GI
//
// = FILENAME
//     Point.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:50:18 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

template<class PointType>
class Point
//=======================================================
//
// = DESCRIPTION
//
//   The class <{Point}> describes a point in a two dimensional
//   space. This class is generic (template) in order to be in a
//   discrete, fully or any other kind of space.
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTOR
  //=======================================================

  Point();
  // Default constructor.

  Point(const PointType x, const PointType y, const PointType z=0);
  // Constructs a point with its two or three coordinates.

  Point(const Point<PointType> &aPoint);
  // Copy constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~Point();
  // Default destructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  void setX(const PointType x);
  // Sets the value of the x coordinate.

  PointType getX() const;
  // Gets the value of the x coordinate.

  void setY(const PointType y);
  // Sets the value of the y coordinate.

  PointType getY() const;
  // Gets the value of the y coordinate.  

  void setZ(const PointType z);
  // Sets the value of the z coordinate.

  PointType getZ() const;
  // Gets the value of the z coordinate.  

  Point<PointType>& getPoint();
  // Returns the reference onto the point.  

  //=======================================================
  // = OPERATORS
  //=======================================================

  Point<PointType>& operator=(const Point<PointType>& newPoint);
  // Assignment operator with an other point.

  Point<PointType>& operator=(const PointType value);
  // Assignment operator with a <{PointType}> value.

  Point<PointType> operator*(const PointType value);
  // Applies a scaling operation onto a point.

  Point<PointType> operator+(const PointType value);
  // Applies a translation operation onto a point.

  Point<PointType> operator-(const PointType value);
  // Applies a translation operation onto a point.

  float dist(const Point<PointType> &aPoint) const;
  // Computes the distance between the current point and the point
  // <{aPoint}>.

  //=======================================================
  // = PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

private:

  PointType x_; 
  // Store the x coordinate.

  PointType y_;
  // Store the y coordinate.

  PointType z_;
  // Store the z coordinate.

};

// ============================================================
// = INLINE METHODS
// ============================================================

//=======================================================
// = ACCESSORS
//=======================================================

template<class PointType>
inline void Point<PointType>::setX(const PointType x)
{
  x_=x;
}

// ============================================================
template<class PointType>
inline PointType Point<PointType>::getX() const
{
  return x_;
}

// ============================================================
template<class PointType>
inline void Point<PointType>::setY(const PointType y)
{
  y_=y;
}
  
// ============================================================
template<class PointType>
inline PointType Point<PointType>::getY() const
{
  return y_;
}

// ============================================================
template<class PointType>
inline void Point<PointType>::setZ(const PointType z)
{
  z_=z;
}
  
// ============================================================
template<class PointType>
inline PointType Point<PointType>::getZ() const
{
  return z_;
}

// ============================================================
template<class PointType>
inline Point<PointType>& Point<PointType>::getPoint()
{
  return *this;
}

//=======================================================
// = OPERATORS
//=======================================================

template<class PointType>
inline Point<PointType>& 
Point<PointType>::operator=(const Point<PointType>& newPoint)
{
  x_=newPoint.getX();
  y_=newPoint.getY();
  z_=newPoint.getZ();

  return *this;
}

// ============================================================
template<class PointType>
inline Point<PointType>&  
Point<PointType>::operator=(const PointType value)
{
  x_=value;
  y_=value;
  z_=value;

  return *this;
}

// ============================================================
template<class PointType>
inline float Point<PointType>::dist(const Point<PointType> &aPoint) const
{
  return sqrt((x_-aPoint.getX())*(x_-aPoint.getX())+
	      (y_-aPoint.getY())*(y_-aPoint.getY())+
	      (z_-aPoint.getZ())*(z_-aPoint.getZ()));
}


//#ifdef __GNUC__


#if defined(SP)

#define POINT_INLINE inline
#include "Point.cc"

#else

#define POINT_INLINE
#include "Point.cc"

#endif 


#endif
