// g++ -I/user/connex/parallel/Pelabs/Include parity.cc -L/user/connex/parallel/Pelabs/Lib -L/usr/X11R6/lib -lMisc -lGI -lX11
#include <fstream>
#include <cstdlib>

#include "GraphicsInterface.hh"
#include "Random.hh"

// for simplicity, we use global variables. No need to
// pass the parameters to the functions

Random rng;
int nx, nz, nbIter;
int** ac;
int** nac;

GraphicsInterface window;
Matrix<unsigned char> image;

void drawImage(int** a)
{
  int i,j;
  unsigned char pix;   

  for (i=0;i<nx;i++) {
    for (j=0;j<nz;j++){
      image.set(j,i,(unsigned char) (a[i][j]+1)); // +1 is for the choice of color
    }    
  }
  window.drawMatrix(image);
}

int main(int argc, char ** argv)
{
  if (argc != 4) {
    cout << "Usage: parity <sizex> <sizey>  <nbIter>" << endl;
    return 1;
  }

  nx=atoi(argv[1]);
  nz=atoi(argv[2]);
  nbIter=atoi(argv[3]);

  rng.init();
  window.open(nz,nx);
  image.setDimension(nz,nx);

  // allocation memory for the ac
  ac=new int*[nx];
  for(int i=0;i<nx;i++)ac[i]=new int[nz];
  nac=new int*[nx];
  for(int i=0;i<nx;i++)nac[i]=new int[nz];

  // initial condition: zero everywhere except in the center----------
  for(int i=0;i<nx;i++)
    for(int j=0;j<nz;j++)ac[i][j]=0;

  for(int i=nx/2-3;i<nx/2+3;i++)
    for(int j=nz/2-3;j<nz/2+3;j++)ac[i][j]=(int) (rng.get()+.5);
  //---------------------------------------------

  cout << "size = " << nx <<"  " << nz << endl;
  cout << "nbIter = " << nbIter << endl;

  //-------Iterations of the Cellular Automata --------------
  for (int iter=0;iter<nbIter;iter++) {

    // implement the evolution rule (Parity rule, here)
    for(int i=0;i<nx;i++){
      for (int j=0;j<nz;j++){
		nac[i][j]=(ac[(i+nx-1)%nx][j] + ac[(i+nx+1)%nx][j] +
	        ac[i][(j+nz-1)%nz] + ac[i][(j+nz+1)%nz]
	                  )%2;
      }
    }

    // copy new values in old ones
    for(int i=0;i<nx;i++)
      for(int j=0;j<nz;j++)ac[i][j]=nac[i][j];

    // display the new configuration
    drawImage(ac);
  }


  window.close();

  return 0;
}
