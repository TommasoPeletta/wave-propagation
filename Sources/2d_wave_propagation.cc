#include <iostream>
#include <vector>
#include <cmath>
using std::vector;
using namespace std;

//Pour lancer le code : g++ 2d_wave_propagation.cc -o Wave
//                      ./Wave

const int sizeX = 10;
const int sizeY = 10;
const int q = 4;



//typedef vector<double> vecdouble(sizeX*sizeY);
//typedef vector<double> qsize(5)

double vectors_dot_prod(double x[2],double y[2])
{
    double res = 0.0;
    int i;
    for (i = 0; i < 2; i++)
    {
        res += x[i] * y[i];
    }
    return res;
}

  void vector_cpy(double f_out[sizeX][sizeY][q+1],  double f_in[sizeX][sizeY][q+1]){
    for (int i = 0; i < sizeX; i++){
      for (int j = 0; j < sizeY; j++){
        for (int k = 0; k < q+1; k++){
          f_in[i][j][k] = f_out[i][j][k];
        }
      }
    }
}

double foutComputation(double n[sizeX][sizeY], double v, double vi[q+1][2], double f_out[sizeX][sizeY][q+1] ){
  double f_in[sizeX][sizeY][q+1];
  vector_cpy(f_out, f_in);
  //calcul de vj = vi * j
  //calcul du rho
  double rho = 1; //!!!!
  double vj = 2; //!!!!!
  int i;
  double new_q = (double)q;
  for (i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int k = 0; k < q+1; k++){
        if (k != 0){
          f_out[i][j][k] = 2/(pow(n[i][j],2)* new_q) * rho + (1/v) * vj - f_in[i][j][k];
        } else {
          f_out[i][j][k] = 2*(pow(n[i][j],2) - 1)/(pow(n[i][j],2)) * rho - f_in[i][j][k];
        }
      }
    }
  }
  return 2;
}

int rhoComputation(double f_in[sizeX][sizeY][q+1], int i, int j) { //Calcule du rho
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
    double tabl_n[sizeX][sizeY];
    double f_in[sizeX][sizeY][q+1];
    double f_out[sizeX][sizeY][q+1];
    double deltaX = 2;
    double deltaT = 3;
    double v = deltaX/deltaT;
    double vi[q+1][2] = {{0,0},{v,0},{0,v},{-v,0},{0,-v}};
  //  double x[2] = {2,3};
  //  double y[2] = {4,1};
  //  decltype(x) vect2;
  //  double  z = vectors_dot_prod(x,y);

    tabl_n[2][3] = 1;
    f_in[2][3][4] = 1000;
    f_out[2][3][4] = 500;


    cout << tabl_n[0][0] << "\n";
    cout << rhoComputation(f_in,2,3)  << "\n";
    cout << f_in[2][3][4] << "\n";
    cout << f_out[2][3][4] << "\n";
    //cout << vi[4][1]  << "\n";
    //cout << sizeof(y)  << "\n";
    //cout << z  << "\n";
    //cout << typeof(y)  << "\n";
    return 0;
}
