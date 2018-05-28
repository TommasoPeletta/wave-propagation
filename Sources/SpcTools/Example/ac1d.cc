// g++ -I/home/chopard/Pelabs/Include d2q9.cc -L/home/chopard/Pelabs/Lib -L/usr/X11R6/lib -lMisc -lGI -lX11
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "GraphicsInterface.hh"
#include "Random.hh"

using namespace std;

Random rng;
int nx, nz, nbIter;
int* ac;
int* nac;

GraphicsInterface window;
Matrix<unsigned char> image;


void drawImage(int* a)
{
  int i,j;
  unsigned char pix;   

  // move up the image
    for (i=0;i<nx;i++) {
      for (j=0;j<nz-1;j++) {
          pix=image.get(j+1,i);
          image.set(j,i,pix);
        }
      }

    for (i=0;i<nx;i++) {
      image.set(nz-1,i,(unsigned char) a[i]);
    }    
    window.drawMatrix(image);
}

int main(int argc, char ** argv)
{
  if (argc != 4) {
    cout << "Usage: ac1d <sizex> <sizey>  <nbIter>" << endl;
    return 1;
  }

  nx=atoi(argv[1]);
  nz=atoi(argv[2]);
  nbIter=atoi(argv[3]);

  rng.init();
  window.open(nz,nx);
  image.setDimension(nz,nx);

  ac=new int[nx];
  nac=new int[nx];

  for(int i=0;i<nx;i++)ac[i]=(int) (rng.get()+.5);

  cout << "size = " << nx << endl;
  cout << "nbIter = " << nbIter << endl;

  for (int iter=0;iter<nbIter;iter++) {

    for(int i=0;i<nx;i++)nac[i]=(ac[(i+nx-1)%nx] + ac[(i+nx+1)%nx])%2;
    for(int i=0;i<nx;i++)ac[i]=nac[i];

    drawImage(ac);
  }


  window.close();

  return 0;
}
