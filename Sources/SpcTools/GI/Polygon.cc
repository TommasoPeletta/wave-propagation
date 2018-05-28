//=======================================================
//
// = LIBRARY
//     GI
//
// = FILENAME
//     Polygon.cc
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.1 $
//
// = DATE RELEASED
//     $Date: 2000/05/30 15:50:22 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland
//
//=======================================================

#include "Polygon.hh"

#include <math.h>

//=======================================================
// = CONSTRUCTOR
//=======================================================

Polygon::Polygon()
{
  init();
}

//=======================================================
Polygon::Polygon(const Polygon& aPolygon)
{
  *this=aPolygon;
}

//=======================================================
// = DESTRUCTOR
//=======================================================

Polygon::~Polygon()
{

}

//=======================================================
// = OPERATORS
//=======================================================

Polygon& Polygon::operator=(const Polygon &aPolygon)
{
  list_=aPolygon.list_;
 
  return *this;
}

//=======================================================
bool Polygon::surround(const Point<int> &p)
{
  Point<float> floatPoint;
  
  floatPoint.setX((float) p.getX());
  floatPoint.setY((float) p.getY());

  return surround(floatPoint);
}

//=======================================================
bool Polygon::surround(const Point<float> &p)
{
  const float epsilon=0.001;

  bool result=true;
  float sum=0.0;

  // Allocates a vector of point
  Point<int> *polyPoint;
  int nbPoint=getSize();
  polyPoint=new Point<int>[nbPoint];

  // Sets the vector of point with the polygons point
  initTraversal();
  int i=0;
  do {
    polyPoint[i]=currentValue();
    i++;
  }
  while (isTraversalLastValue() == false);

  float ax,bx,ay,by,crossProduct,sign,a2,b2,dist,dot,prod;
  float difx,dify,ang,temp,a1,b1;

  int i1,i2;
  for (i=0;i<nbPoint;i++) {
    i1=i;
    i2=i+1;
    if (i == nbPoint-1) i2=0;

    ax=polyPoint[i1].getX()-p.getX();
    bx=polyPoint[i2].getX()-p.getX();
    ay=polyPoint[i1].getY()-p.getY();
    by=polyPoint[i2].getY()-p.getY();

    // Computes cross product of the vectors to determine sign of
    // angular segment
    crossProduct=ax*by-ay*bx;
    if (crossProduct < 0.0) sign=-1.0;
    else sign=1.0;
    a2=ax*ax+ay*ay;
    b2=bx*bx+by*by;

    a1=sqrt(a2);
    b1=sqrt(b2);
    difx=polyPoint[i1].getX()-polyPoint[i2].getX();
    dify=polyPoint[i1].getY()-polyPoint[i2].getY();
    dist=sqrt(difx*difx+dify*dify);
    if ((fabs(crossProduct)/2.0/dist) > epsilon) {
      dot=ax*bx+ay*by;
      prod=a2*b2;
      ang=0.0;
      if (fabs(prod) > epsilon) {
        temp=dot/sqrt(prod);
	if (fabs(temp) < 1.0) {
          ang=acos(temp);
          sum+=ang*sign;
        }
        else if ((a1 <= dist) && (b1 <= dist)) return result;
      }
    }
    else if ((a1 <= dist) && (b1 <= dist)) return result;
  }

  float factor=sum*0.159154943;
  if (fabs(1.0-factor) < epsilon) result=true;
  if (fabs(factor) <= epsilon) result=false;

  delete [] polyPoint;

  return result;
}
  
