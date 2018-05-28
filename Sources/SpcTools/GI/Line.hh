#ifndef LINE_HH
#define LINE_HH

//=======================================================
//
// = LIBRARY
//     GI
//
// = FILENAME
//     Line.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:50:09 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Point.hh"
#include "Bool.hh"

#include <math.h>

template<class PointType>
class Line
//=======================================================
//
// = DESCRIPTION
//
//   The class <{Line}> describes a line segment by two point and some
//   operations which can be applied on it.
//
// = SEE ALSO
//   <{Point}>.
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTORS
  //=======================================================

  Line();
  // Default constructor.

  Line(const Point<PointType>& startPoint,  const Point<PointType>& endPoint);
  // Constructs a line with its two point.

  Line(const Line<PointType>& aLine);
  // Copy constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~Line();
  // Default destructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  Point<PointType> getStartPoint() const;
  // Gets the start point of the line.

  Point<PointType> getEndPoint() const;
  // Gets the end point of the line.

  PointType getXmin() const;
  // Gets the minimum x coordinate of the segment bounding box.

  PointType getYmin() const;
  // Gets the minimum y coordinate of the segment bounding box.

  PointType getXmax() const;
  // Gets the maximum x coordinate of the segment bounding box.

  PointType getYmax() const;
  // Gets the maximum y coordinate of the segment bounding box.

  //=======================================================
  // = OPERATORS
  //=======================================================

  Line<PointType>& operator=(const Line<PointType>& aLine);
  // Assignment operator.

  bool intersectWith(const Line<PointType> &aLine) const;
  // Is there an intersection between the current line and the line
  // <{aLine}>?

  //=======================================================
  // = PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

private:

  Point<PointType> startPoint_;
  // Store the start point.

  Point<PointType> endPoint_;
  // Store the end point.

  PointType xmin_;
  // Store the minimum x coordinate of the segment bounding box.

  PointType ymin_;
  // Store the minimum y coordinate of the segment bounding box.

  PointType xmax_;
  // Store the maximum x coordinate of the segment bounding box.

  PointType ymax_;
  // Store the maximum y coordinate of the segment bounding box.

};

// ============================================================
// = INLINE METHODS
// ============================================================

//=======================================================
// = ACCESSORS
//=======================================================

template<class PointType>
inline Point<PointType> Line<PointType>::getStartPoint() const
{
  return startPoint_;
}

//=======================================================
template<class PointType>
inline Point<PointType> Line<PointType>::getEndPoint() const
{
  return endPoint_;
}

//=======================================================
template<class PointType>
inline PointType Line<PointType>::getXmin() const
{
  return xmin_;
}

//=======================================================
template<class PointType>
inline PointType Line<PointType>::getYmin() const
{
  return ymin_;
}

//=======================================================
template<class PointType>
inline PointType Line<PointType>::getXmax() const
{
  return xmax_;
}

//=======================================================
template<class PointType>
inline PointType Line<PointType>::getYmax() const
{
  return ymax_;
}

//=======================================================
// = OPERATORS
//=======================================================

template<class PointType>
inline Line<PointType>& Line<PointType>::operator=(const Line<PointType>& aLine)
{
  Line(aLine.getStartPoint(),aLine.getEndPoint());

  return *this;
}


#if defined(SP)

#define POINT_INLINE inline
#include "Line.cc"

#else

#define POINT_INLINE
#include "Line.cc"

#endif 


#endif
