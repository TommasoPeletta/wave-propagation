//=======================================================
//
// = LIBRARY
//     GI
//
// = FILENAME
//     Line.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:50:07 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Line.hh"

//=======================================================
// = CONSTRUCTORS
//=======================================================

template<class PointType>
POINT_INLINE Line<PointType>::Line()
{

}

// ============================================================
template<class PointType>
POINT_INLINE Line<PointType>::Line(const Point<PointType>& startPoint, const Point<PointType>& endPoint)
{
  // Stores the two points
  startPoint_=startPoint;
  endPoint_=endPoint;

  // Finds segments bounding boxes
  if (startPoint_.getX() < endPoint_.getX()) {
    xmin_=startPoint_.getX();
    xmax_=endPoint_.getX();
  }
  else {
    xmin_=endPoint_.getX();
    xmax_=startPoint_.getX();
  }
  if (startPoint_.getY() < endPoint_.getY()) {
    ymin_=startPoint_.getY();
    ymax_=endPoint_.getY();
  }
  else {
    ymin_=endPoint_.getY();
    ymax_=startPoint_.getY();
  }
}

// ============================================================
template<class PointType>
POINT_INLINE Line<PointType>::Line(const Line<PointType>& aLine)
{
  Line(aLine.getStartPoint(),aLine.getEndPoint());
}

//=======================================================
// = DESTRUCTOR
//=======================================================

template<class PointType>
POINT_INLINE Line<PointType>::~Line()
{

}

//=======================================================
// = OPERATORS
//=======================================================

template<class PointType>
POINT_INLINE bool Line<PointType>::intersectWith(const Line &aLine) const
{
  //
  // segment 1: x(t1)=x1+t1*(x2-x1); y(t1)=y1+t1*(y2-y1) t1 in [0,1]
  // segment 2: x(t2)=x3+t2*(x4-x3); y(t2)=y3+t2*(y4-y3) t2 in [0,1]
  //
  // if d=(x2-x1)*(y4-y3)-(y2-y1)*(x4-x3)
  // then t1=((x3-x1)*(y4-y3)-(y3-y1)*(x4-x3))/d
  // and  t2=((x3-x1)*(y2-y1)+(y1-y3)*(x2-x1))/d
  //
  const float eps=0.0000001;

  // Checks the bounding boxes overlaping
  if ((aLine.getXmin() > xmax_) || (xmin_ > aLine.getXmax())) 
    return false;
  if ((aLine.getYmin() > ymax_) || (ymin_ > aLine.getYmax())) 
    return false;

  // Stores points in float format
  float x1=startPoint_.getX();
  float y1=startPoint_.getY();
  float x2=endPoint_.getX();
  float y2=endPoint_.getY();

  float x3=aLine.getStartPoint().getX();
  float y3=aLine.getStartPoint().getY();
  float x4=aLine.getEndPoint().getX();
  float y4=aLine.getEndPoint().getY();
  

  // Checks if segments are parallel
  float d=(x2-x1)*(y4-y3)-(y2-y1)*(x4-x3);
  if (fabs(d) < eps) {

    float d1=sqrt((aLine.getXmin()-xmin_)*(aLine.getXmin()-xmin_)+
		  (aLine.getYmin()-ymin_)*(aLine.getYmin()-ymin_));
    float d2=aLine.getStartPoint().dist(aLine.getEndPoint());
    float d3=sqrt((aLine.getXmax()-xmax_)*(aLine.getXmax()-xmax_)+
		  (aLine.getYmax()-ymax_)*(aLine.getYmax()-ymax_));
    float d4=startPoint_.dist(endPoint_);

    if (fabs(d4-d1-d2-d3) < eps) return true;
    
    return false;
  }

  float t1=((x3-x1)*(y4-y3)-(y3-y1)*(x4-x3))/d;
  
  // Intersection outside segment 1
  if ((t1 < 0.0) || (t1 > 1.0)) return false;
			   
  float t2=((x3-x1)*(y2-y1)+(y1-y3)*(x2-x1))/d;
  
  // Intersection outside segment 2
  if ((t2 < 0.0) || (t2 > 1.0)) return false;

  // Compute intersection
  // x0=x1+t1*(x2-x1);
  // y0=y1+t1*(y2-y1);

  return true;
}

