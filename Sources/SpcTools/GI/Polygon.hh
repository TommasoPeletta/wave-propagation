#ifndef POLYGON_HH
#define POLYGON_HH

//=======================================================
//
// = LIBRARY
//     GI
//
// = FILENAME
//     Polygon.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:50:24 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Point.hh"
#include "List.hh"
#include "Bool.hh"

class Polygon
//=======================================================
//
// = DESCRIPTION
//
//   The class <{Polygon}> describes a polygon composed of a list of
//   points.
//
// = SEE ALSO
//   <{Point}>, <{List}>.
//
// = INHERITS
//   <{List}>.
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTOR
  //=======================================================

  Polygon();
  // Default constructor.

  Polygon(const Polygon& aPolygon);
  // Copy constructor.
  
  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~Polygon();
  //Default destructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

//   List< Point<int> > getList() const;

  //=======================================================
  // = OPERATORS
  //=======================================================

  Polygon& operator=(const Polygon &aPolygon);
  // Assignment operator.

  bool surround(const Point<float> &p);
  // Indicates wether a point <{p}> is interior or on the contour to a
  // polygonal domain.
  // 
  // <{Warning :}> The contour is supposed to be described
  // counter-clockwise.

  bool surround(const Point<int> &p);
  // Indicates wether a point <{p}> is interior or on the contour to a
  // polygonal domain.
  // 
  // <{Warning :}> The contour is supposed to be described
  // counter-clockwise.

  bool operator==(const int size) const;
  // Returns true if the polygon has the size <{size}>, false
  // otherwise.

  //=======================================================
  // = POINT LIST METHODS
  //=======================================================

  int getSize() const;
  // get the size of the point list.

  Point<int> currentValue() const;
  // Gets the current value of the point list traversal.

  void addValue(const Point<int> &value);
  // Adds a Point.

  void init();
  // Initializes the list.

  void initTraversal();
  // Initializes the list traversal.

  bool isTraversalLastValue();
  // is the last value of list traversal?

  //=======================================================
  // PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

private:
 
  List< Point<int> > list_;

};

// ============================================================
// INLINE METHODS
// ============================================================

//=======================================================
// POINT LIST METHODS
//=======================================================

inline int Polygon::getSize() const
{
  return list_.getSize();
}

//=======================================================
inline Point<int> Polygon::currentValue() const
{
  return list_.currentValue();
}

//=======================================================
inline void Polygon::addValue(const Point<int> &value)
{
  list_.addValue(value);
}

//=======================================================
inline void Polygon::init()
{
  list_.init();
}

//=======================================================
inline void Polygon::initTraversal()
{
  list_.initTraversal();
}

//=======================================================
inline bool Polygon::isTraversalLastValue()
{
  return list_.isTraversalLastValue();
}

//=======================================================
// OPERATORS
//=======================================================

inline bool Polygon::operator==(const int size) const
{
  if (getSize() == size) return true;
  else return false;
}

// //=======================================================
// // ACCESSORS
// //=======================================================
// 
// inline List< Point<int> > Polygon::getList() const
// {
//   return list_;
// }

#endif
