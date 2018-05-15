#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using std::vector;
using namespace std;

//Pour lancer le code : g++ 2d_wave_propagation.cc -o Wave
//                      ./Wave

const int sizeX = 10;
const int sizeY = 10;
const int q = 4;

typedef double type_F[sizeX][sizeY][q+1];


// !!!! A FAIRE !!!!!
// jComputation


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
          switch (k) {
            case 0 : f_in[i][j][k] = f_out[i][j][k];
                      break;
            case 1 : if (j != (sizeY-1)) {
                      f_in[i][j+1][k] = f_out[i][j][k];}
                      break;
            case 2 : if (i != 0) {
                        f_in[i-1][j][k] = f_out[i][j][k];}
                      break;
            case 3 : if (j != 0) {
                      f_in[i][j-1][k] = f_out[i][j][k];}
                    break;
            case 4 : if (i != (sizeX-1)) {
                      f_in[i+1][j][k] = f_out[i][j][k];}
                    break;
          }
        }
      }
    }
}

int rhoComputation(double matrice[sizeX][sizeY][q+1], int i, int j) { //Calcule du rho
  int sum = 0;
  for (int k = 0; k < q+1; k++){
    sum = sum + matrice[i][j][k];
  }
  int rho = sum;
  return rho;
}


void afficher(type_F matrice) { //Fonction pour afficher une matrice
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      cout << rhoComputation(matrice, x, y) << "    ";
    }
    cout << endl;
  }
  cout << endl;
}

void foutComputation(double n[sizeX][sizeY], double v, double vi[q+1][2], double f_in[sizeX][sizeY][q+1] ){
  type_F f_out;
  //calcul de vj = vi * j
  //calcul du rho
  double rho;
  double vj = 2; //!!!!!
  double nn = 0.4; //!!!!!!
//  double new_q = (double)q;
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      rho = rhoComputation(f_in,i,j);
      for (int k = 0; k < q+1; k++){
        if (k != 0){
          //f_out[i][j][k] = 2/(pow(n[i][j],2)* q) * rho + (1/v) * vj - f_in[i][j][k];
          f_out[i][j][k] = 2/(pow(nn,2)* q) * rho - f_in[i][j][k];
        } else {
          //f_out[i][j][k] = 2*(pow(n[i][j],2) - 1)/(pow(n[i][j],2)) * rho - f_in[i][j][k];
          f_out[i][j][k] = 2*(pow(nn,2) - 1)/(pow(nn,2)) * rho - f_in[i][j][k];
        }
      }
    }
  }
  vector_cpy(f_out, f_in);
}

int main() {
    type_F f_in;
    //vecdouble tabl_n;
    //vector<qsize> f_in(sizeX*sizeY);
    //vector<qsize > f_out(sizeX*sizeY);
    double tabl_n[sizeX][sizeY];
    double deltaX = 2;
    double deltaT = 3;
    double v = deltaX/deltaT;
    double vi[q+1][2] = {{0,0},{v,0},{0,v},{-v,0},{0,-v}};
  //  double x[2] = {2,3};
  //  double y[2] = {4,1};
  //  double  z = vectors_dot_prod(x,y);

    tabl_n[2][3] = 1;
    f_in[2][3][4] = 1000;

    afficher(f_in);
    foutComputation(tabl_n,v,vi,f_in);
    afficher(f_in);
    cout << tabl_n[2][2] << "\n";
    cout << rhoComputation(f_in,2,3)  << "\n";
    cout << f_in[5][5][4] << "\n";
    //cout << vi[4][1]  << "\n";
    //cout << sizeof(y)  << "\n";
    //cout << z  << "\n";
    //cout << typeof(y)  << "\n";
    return 0;
}
