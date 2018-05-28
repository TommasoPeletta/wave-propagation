#ifndef PLOTGI_HH
#define PLOTGI_HH


#include "GraphicsInterface.hh"
#include "Point.hh"

class PlotGI
{
private:
  int Lx, Ly;
  float xmin,xmax, ymin,ymax;
  float currentX, currentY;
  GraphicsInterface window;
  Color currentColor;
  float* xArray;  float* yArray;
  int arraySize;
public:
  PlotGI(int, int, float, float, float, float);

  ~PlotGI();

  void clear();
  void setXY(float, float, float, float);
  int xTransform(float);
  int yTransform(float);

  void moveto(float, float);
  void lineto(float, float, Color);
  void plotArray(float* , float* , int, Color);
  void startPlotArray(float* , float* , int, Color);
  void updatePlotArray(float* , float* );
};

#endif
