#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//enum ArrayDimensions {sizeX = 2, sizeY = 2};
using namespace std;

//Pour lancer le code : g++ Test.cc -o Test
//                      ./Test
const int sizeX = 10000;
const int sizeY = 10000;
const int q = 4;

int main(void)  {

    int ***mat = (int***)malloc(sizeY * sizeof(int **));
    for (int index = 0;index < sizeY; index++){
      mat[index] = (int **)malloc(sizeX*sizeof(int*));
      for (int i = 0; i < sizeX;i++){
        mat[index][i] = (int *)malloc((q+1)*sizeof(int));
      }
    }
    mat[99][9][1] = 1000;
    mat[9009][1009][4] = 1000;
    cout << mat[99][9][1] << endl;
    cout << mat[9009][1009][4] << endl;
    return 0;
}
