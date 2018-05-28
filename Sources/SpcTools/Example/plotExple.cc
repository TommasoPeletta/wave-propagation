#include "GraphicsInterface.hh"
#include <iostream>
#include "Point.hh"
#include "PlotGI.hh"


using namespace std;

float xValue(int i){return ( (float)i/ 100.);}
float yValue(int i){float y=(float)i/100.; return y*y;}

int main()
{
  PlotGI plot1(256,256,0.,1.,0.,1.);
  Color mycolor1=GI_green, mycolor2=GI_blue, mycolor3=GI_red;

//--first  example--------
  plot1.moveto(xValue(0),yValue(0));
  for(int i=1;i<=100;i++){plot1.lineto(xValue(i),yValue(i),mycolor1);}

//--second example: plot array y versus array x--------
  int size=64;
  float* x=new float[size];
  float* y=new float[size];

  for(int i=0;i<size;i++){x[i]=i; y[i]=cos(.2*(float) i); }
  plot1.setXY(0.,64.,-1.,1.);
  plot1.plotArray(x,y,size,mycolor2);

  cout << "type return to continue"<<endl;
  cin.get();
//--third  example: plot array y versus array x, and update in time--------
  plot1.startPlotArray(x,y,size,mycolor3);
  cout << "type return to continue"<<endl;
  cin.get();

  float scale=1.;
  for(int iter=0;iter<200;iter++){
    scale*=.995;
    for(int i=0;i<size;i++){x[i]=i; y[i]=scale*cos(.2*(float) i);}
    plot1.updatePlotArray(x,y);
  }
  cout << "type return to clear screen"<<endl;
  cin.get();
  plot1.clear();
  cout << "type return to quit"<<endl;
  cin.get();

  return 0;
}
