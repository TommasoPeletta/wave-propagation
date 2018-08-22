#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <GL/glut.h>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
using std::vector;
using namespace std;

//Pour lancer le code : g++ 2d_wave_tools.cpp -o lookAtThis -lglut -lGL
//                      ./lookAtThis

typedef double ***type_F;
type_F f_in;

int main(int argc, char **argv) {
  char *buffer = 0;
  char* aux;
  f_in = (double***)malloc(10 * sizeof(double **));
  for (int index = 0;index < 10; index++){
    f_in[index] = (double **)malloc(10*sizeof(double*));
    for (int i = 0; i < 10;i++){
      f_in[index][i] = (double *)malloc((14)*sizeof(double));
    }
  }

  FILE *f = fopen("logfile.txt","r");
  if (f)
  {
    fseek (f, 0, SEEK_END);
    long length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer =(char*) malloc (length);
    if (buffer)
    {
      fread (buffer, 1, length, f);
    }
    fclose (f);
  }

  if (buffer)
  {
    aux = strtok(buffer, " ");
  //  f_in[0][0][0] =(double) atof(aux);
    //aux = strtok(NULL, " ");
    //f_in[0][0][1] = atof(aux);
   for (int i = 0; i < 14; i++){
      for (int j = 0; j < 10; j++){
        for (int k = 0; k < 10; k++){
          //if( aux != NULL ) {
          f_in[k][j][i] =(double) atof(aux);
          aux = strtok(NULL, " ");
      //  }
        }
      }
    }
    printf("%f\n",f_in[8][9][13]);
  }
  return 0;
}
