#include <iostream>
#include <vector>
using std::vector;
using namespace std;

//Pour lancer le code : g++ 2d_wave_propagation.cc -o Test
//                      ./Test

const int sizeX = 10;
const int sizeY = 10;
const int q = 4;
double tabl_n[sizeX][sizeY];
double f_in[sizeX][sizeY][q+1];
double f_out[sizeX][sizeY][q+1];
//typedef vector<double> vecdouble(sizeX*sizeY);
//typedef vector<double> qsize(5)

int rhoComputation(int i, int j) { //Calcule du rho
  int sum = 0;
  for (int k = 0; k < q+1; k++){
    sum = sum + f_in[i][j][k];
  }
  int rho = sum;
  return rho;
}
int main() {
    //vecdouble tabl_n;
    //vector<qsize> f_in(sizeX*sizeY);
    //vector<qsize > f_out(sizeX*sizeY);
    double deltaX = 2;
    double deltaT = 3;
    double v = deltaX/deltaT;
    double vi[q+1][2] = {{0,0},{v,0},{0,v},{-v,0},{0,-v}};
    tabl_n[2][3] = 1;
    f_in[2][3][4] = 1000;
    f_in[2][3][0] = 50;
    cout << tabl_n[2][3] << "\n";
    cout << rhoComputation(2,3)  << "\n";
    cout << vi[4][1]  << "\n";
    return 0;
}
