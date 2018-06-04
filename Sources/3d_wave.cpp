#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <GL/glut.h>
#include <cstdlib>

using std::vector;
using namespace std;

/*Pour lancer le code : g++ 3d_wave.cpp -o 3d_wave
                    ./3d_wave
                    */


const int sizeX = 100;
const int sizeY = 200;
const int sizeZ = 500;
const int q = 6;
const double deltaX = 75;
const double v = pow((q/2),1/2)*3*pow(10,8);
const double deltaT = deltaX/v;
const double pi = 3.14159265358979323846;
const double size_c = 40;
//double beta[sizeX][sizeY][sizeZ];
double rho_max;

typedef double ****type_F;
typedef double ***type_coeff_reffrac;
typedef double vecteur[3];
type_F f_in;
type_F f_out;
type_coeff_reffrac tabl_n;
type_coeff_reffrac beta;




void allocate(){


  f_in = (double ****) malloc (sizeof(double ****)*sizeX);
  for (int i = 0; i < sizeX; i++){
    f_in[i] = (double ***) malloc(sizeof(double **)*sizeY);
    for (int j = 0; j < sizeY; j++){
      f_in[i][j] = (double **) malloc(sizeof(double *)* sizeZ);
      for (int z = 0; z < sizeZ; z++){
        f_in[i][j][z] = (double *) malloc(sizeof(double)* q+1);
      }
    }
  }

  f_out = (double ****) malloc (sizeof(double ****)*sizeX);
  for (int i = 0; i < sizeX; i++){
    f_out[i] = (double ***) malloc(sizeof(double **)*sizeY);
    for (int j = 0; j < sizeY; j++){
      f_out[i][j] = (double **) malloc(sizeof(double *)* sizeZ);
      for (int z = 0; z < sizeZ; z++){
        f_out[i][j][z] = (double *) malloc(sizeof(double)* q+1);
      }
    }
  }

  tabl_n = (double***)malloc(sizeX * sizeof(double **));
  for (int index = 0;index < sizeX; index++){
    tabl_n[index] = (double **)malloc(sizeY*sizeof(double*));
    for (int i = 0; i < sizeY;i++){
      tabl_n[index][i] = (double *)malloc(sizeZ*sizeof(double));
    }
  }

  beta = (double***)malloc(sizeX * sizeof(double **));
  for (int index = 0;index < sizeX; index++){
    beta[index] = (double **)malloc(sizeY*sizeof(double*));
    for (int i = 0; i < sizeY;i++){
      beta[index][i] = (double *)malloc(sizeZ*sizeof(double));
    }
  }

}

void define_fin(type_F x){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int z = 0; z < sizeZ; z++){
        for (int k = 0; k < q+1; k++)
        x[i][j][z][k] = 0;
      }
    }
  }
}

double vectors_prod(vecteur x,vecteur y)
{
    double res = 0.0;
    int i;
    for (i = 0; i < 3; i++)
    {
        res += x[i] * y[i];
    }
    return res;
}




void scalar_prod(vecteur x, double y){
  for (int i = 0; i < 3; i++){
    x[i] = x[i] * y;
  }
}




void vector_sum(vecteur x, vecteur y){
  for (int i = 0; i < 3; i++){
    x[i] = x[i] + y[i];
  }
}




void jComputation(vecteur res,double vi[q+1][3], type_F f_in ,int x ,int y, int z){
  res[0] = 0;
  res[1] = 0;
  res[2] = 0;
  vecteur v_aux;
  for (int i = 1; i < q+1; i++){
    v_aux[0] = vi[i][0];
    v_aux[1] = vi[i][1];
    v_aux[2] = vi[i][2];
    scalar_prod(v_aux, f_in[x][y][z][i]);
    vector_sum(res,v_aux);
  }
}




void vector_cpy(type_F f_out, type_F f_in){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int z = 0; z < sizeZ; z++){
        for (int k = 0; k < q+1; k++){
          switch (k) {
            case 0 :  f_in[i][j][z][k] = beta[i][j][z] * f_out[i][j][z][k];
                      break;

            case 1 :  if (j != (sizeY-1)) {
                        f_in[i][j+1][z][k] = beta[i][j][z] * f_out[i][j][z][k];
                      }
                      break;

            case 2 :  if (i != 0) {
                        f_in[i-1][j][z][k] = beta[i][j][z] * f_out[i][j][z][k];
                      }
                      break;

            case 3 :  if (j != 0) {
                        f_in[i][j-1][z][k] =beta[i][j][z] * f_out[i][j][z][k];
                      }
                      break;

            case 4 :  if (i != (sizeX-1)) {
                        f_in[i+1][j][z][k] =beta[i][j][z] * f_out[i][j][z][k];
                      }
                      break;

            case 5 :  if (z != 0) {
                        f_in[i][j][z-1][k] =beta[i][j][z] * f_out[i][j][z][k];
                      }
                      break;

            case 6 :  if (z != (sizeZ-1)) {
                        f_in[i][j][z+1][k] =beta[i][j][z] * f_out[i][j][z][k];
                      }
                      break;
          }
        }
      }
    }
  }
}



double rhoComputation(type_F matrix, int i, int j, int z) { //Calcule du rho
  double sum = 0;
  for (int k = 0; k < q+1; k++){
    sum = sum + matrix[i][j][z][k];
  }
  double rho = sum;
  return rho;
}



void afficher(type_F matrix, int z) { //Fonction pour afficher une matrice
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      double r = rhoComputation(matrix,x,y,z);
      cout << r << "    ";
    }
    cout << endl;
  }
  cout << endl;
//}
}




void foutComputation(type_coeff_reffrac n, double v, double vi[q+1][3], type_F f_in, int iteration){
  double rho;
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int z = 0; z < sizeZ; z++){
        if (n[i][j][z]>=1) {
          rho = rhoComputation(f_in,i,j,z);
          if (abs(rho)>rho_max){
            rho_max = rho;
          }
          vecteur j_sum;
          jComputation(j_sum,vi,f_in,i,j,z);
          for (int k = 0; k < q+1; k++){
            vecteur vi_aux;
            vi_aux[0] = vi[k][0];
            vi_aux[1] = vi[k][1];
            vi_aux[2] = vi[k][2];
            double vj = vectors_prod(vi_aux,j_sum);
            if (k != 0){
              f_out[i][j][z][k] = 2/(pow(n[i][j][z],2)* q) * rho + (1/pow(v,2)) * vj - f_in[i][j][z][k];
            } else {
              f_out[i][j][z][k] = 2*(pow(n[i][j][z],2) - 1)/(pow(n[i][j][z],2)) * rho - f_in[i][j][z][k];
            }
          }
        } else if(n[i][j][z] > 0){       //in this programme, sources are represented by a refraction coefficient between 0 and 1
          double Amplitude = 100;
          double facteur = 0.04;
          double frequence = 2*pow(10,5);
          for (int k = 0; k < q+1 ; k++){
            f_out[i][j][z][k] = Amplitude*sin(2*pi*frequence*iteration*deltaT);
          }
        } else {    //reflecting surfaces represented by a negative refraction coefficient
          for (int k = 0; k < q+1; k++){
            f_out[i][j][z][k] = -f_in[i][j][z][k];
          }
        }
      }
    }
  }
  //cout << endl;
  vector_cpy(f_out, f_in);
}

void defmatrix(type_coeff_reffrac n){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int z = 0; z < sizeZ; z++){
        n[i][j][z] = 1;
      }
    }
  }
}


int main( int argc, char **argv ) {
  allocate();
  define_fin(f_in);
  defmatrix(tabl_n);
  defmatrix(beta);
  double vi[q+1][3] = {{0,0,0},{v,0,0},{0,v,0},{-v,0,0},{0,-v,0},{0,0,v},{0,0,-v}};
  tabl_n[5][5][5] = 0.5;
  for (int i = 1; i <= 5;i++){
    rho_max = 0;
    foutComputation(tabl_n,v,vi,f_in,i);
    afficher(f_in, 4);
  }

  return 0;
}
