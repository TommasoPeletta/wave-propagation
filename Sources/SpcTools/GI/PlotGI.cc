#include "PlotGI.hh"


PlotGI::PlotGI(int sizeX, int sizeY, float x0, float x1, float y0, float y1){
    Lx=sizeX; Ly=sizeY; xmin=x0; xmax=x1; ymin=y0; ymax=y1;
    currentX=xmin; currentY=ymin;
    window.open(Ly,Lx,Point<int>(1,0),
             discreteColor,String("my plot"));
    window.setLineStyle(continuous);
    xArray=0;  yArray=0;
  }
PlotGI::~PlotGI(){if(xArray!=0)delete [] xArray; if(yArray!=0)delete [] yArray;}

void PlotGI::clear(){window.clearScreen();}
void PlotGI::setXY(float x0, float x1, float y0, float y1){
    xmin=x0; xmax=x1; ymin=y0; ymax=y1;
  }
int PlotGI::xTransform(float x){ return (int) ((Lx-1)*(x-xmin)/(xmax-xmin)); }
int PlotGI::yTransform(float y){ return (int) ((Ly-1)*(1.-(y-ymin)/(ymax-ymin))); }

void PlotGI::moveto(float x, float y){ currentX=x;  currentY=y;  }
void PlotGI::lineto(float x, float y, Color mycolor){
    int p0x,p0y,p1x,p1y;
    p0x=xTransform(currentX);    p0y=yTransform(currentY);
    p1x=xTransform(x);    p1y=yTransform(y);
    window.setDrawingColor(mycolor);
    window.drawLine(Point<int>(p0x,p0y),Point<int>(p1x,p1y));
    currentX=x;  currentY=y;
  }
void PlotGI::plotArray(float* x, float* y, int noElement, Color mycolor){
    currentX=x[0]; currentY=y[0];
    for(int i=1;i<noElement;i++){lineto(x[i],y[i],mycolor);}
  }
void PlotGI::startPlotArray(float* x, float* y, int noElement, Color mycolor){
    arraySize=noElement;
    currentColor=mycolor;
    currentX=x[0]; currentY=y[0];
    xArray=new float[arraySize];
    yArray=new float[arraySize];
    xArray[0]=x[0]; yArray[0]=y[0];
    for(int i=1;i<noElement;i++){
      lineto(x[i],y[i],mycolor);
      xArray[i]=x[i]; yArray[i]=y[i];
    }
  }
void PlotGI::updatePlotArray(float* x, float* y){
    // first erase previous curve stored in xyArray
    currentX=xArray[0]; currentY=yArray[0];
    for(int i=1;i<arraySize;i++){lineto(xArray[i],yArray[i],GI_white);}
    // then draw the new version
    currentX=x[0]; currentY=y[0];
    xArray[0]=x[0];  yArray[0]=y[0];
    for(int i=1;i<arraySize;i++){
      lineto(x[i],y[i],currentColor);
      xArray[i]=x[i]; yArray[i]=y[i];
    }
  }

