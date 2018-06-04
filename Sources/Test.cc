#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//enum ArrayDimensions {sizeX = 2, sizeY = 2};
using namespace std;

//Pour lancer le code : g++ Test.cc -o Test
//                      ./Test
const int sizeX = 10000;
const int sizeY = 3000;
const int q = 4;
//int ***mat;
typedef int ***typemat;
typedef double **typemat2;
typemat mat;
typemat2 mat2;

void change(typemat x){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int k = 0; k < q+1; k++){
        x[i][j][k] = 0;
      }
    }
  }
}

void change(typemat2 x){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
        x[i][j] = 0;
    }
  }
}



int main(void)  {



  mat = (int ***) malloc (sizeof(int ***)*sizeX);
  for (int h = 0; h < sizeX; h++) {
  	mat[h] = (int **) malloc(sizeof(int*)*sizeY);
    for (int r = 0; r < sizeY; r++) {
      mat[h][r] = (int *) malloc(sizeof(int)*q+1);
    }
  }

  mat2 = (double **) malloc (sizeof(double **)*sizeX);
  for (int i = 0; i < sizeX; i++) {
    mat2[i] = (double *) malloc(sizeof(double)*sizeY);
  }
    mat[9000][2000][4] = 1000;
    change(mat);
    //mat[9009][1009][4] = 1000;
    cout << mat[99][9][1] << endl;
  //  cout << mat[9009][1009][4] << endl;
    return 0;
}
