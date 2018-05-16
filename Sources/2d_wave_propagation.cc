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
typedef double type_coeff_reffrac[sizeX][sizeY];
typedef double vecteur[2];



// !!!! A FAIRE !!!!!

// tabl_n initialisation
// Afficahge stylé


double vectors_prod(double x[2],double y[2])
{
    double res = 0.0;
    int i;
    for (i = 0; i < 2; i++)
    {
        res += x[i] * y[i];
    }
    return res;
}

void scalar_prod(double x[2], double y){
  for (int i = 0; i < 2; i++){
    x[i] = x[i] * y;
  }
}

void vector_sum(double x[2], double y[2]){
  for (int i = 0; i < 2; i++){
    x[i] = x[i] + y[i];
  }
}

void jComputation(double res[2],double vi[q+1][2], double f_in[sizeX][sizeY][q+1],int x ,int y){
  res[0] = 0;
  res[1] = 0;
  double v_aux[2];
  for (int i = 1; i < q+1; i++){
    v_aux[0] = vi[i][0];
    v_aux[1] = vi[i][1];
    scalar_prod(v_aux, f_in[x][y][i]);
    vector_sum(res,v_aux);
  }
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

int rhoComputation(double matrix[sizeX][sizeY][q+1], int i, int j) { //Calcule du rho
  int sum = 0;
  for (int k = 0; k < q+1; k++){
    sum = sum + matrix[i][j][k];
  }
  int rho = sum;
  return rho;
}


void afficher(type_F matrix) { //Fonction pour afficher une matrice
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      cout << rhoComputation(matrix, x, y) << "    ";
    }
    cout << endl;
  }
  cout << endl;
}

void foutComputation(double n[sizeX][sizeY], double v, double vi[q+1][2], double f_in[sizeX][sizeY][q+1] ){
  type_F f_out;
  //calcul de vj = vi * j
  double rho;
  double vj = 2; //!!!!!
  double nn = 0.4; //!!!!!!
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      rho = rhoComputation(f_in,i,j);
      double j_sum[2];
      jComputation(j_sum,vi,f_in,i,j);

      for (int k = 0; k < q+1; k++){
        double vi_aux[2];
        vi_aux[0] = vi[k][0];
        vi_aux[1] = vi[k][1];
        vj = vectors_prod(vi_aux,j_sum);
        if (k != 0){
          f_out[i][j][k] = 2/(pow(n[i][j],2)* q) * rho + (1/v) * vj - f_in[i][j][k];//+ (1/v) * vj
          //f_out[i][j][k] = 2/(pow(nn,2)* q) * rho - f_in[i][j][k];
        } else {
          f_out[i][j][k] = 2*(pow(n[i][j],2) - 1)/(pow(n[i][j],2)) * rho - f_in[i][j][k];
          //f_out[i][j][k] = 2*(pow(nn,2) - 1)/(pow(nn,2)) * rho - f_in[i][j][k];
        }
      }
    }
  }
  vector_cpy(f_out, f_in);
}

void fill_matrix_n(type_coeff_reffrac matrix, int startY, int width,int startX, int height, double out, double in) {
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      if (y >= startY && y < (startY+width) && x >= startX && x < (startX+height)) {
        matrix[x][y] = in;
      } else {
        matrix[x][y] = out;
      }
    }
  }
}

int main() {
    type_F f_in = {{{0}}};
    type_coeff_reffrac tabl_n;
    fill_matrix_n(tabl_n,4,2,2,7,1.2,1.2);
    /*for (int x = 0; x < sizeX; x++){
      for (int y = 0; y < sizeY; y++){
        cout << tabl_n[x][y] << "    ";
      }
      cout << endl;
    }
    cout << endl;*/
    double deltaX = 2;
    double deltaT = 3;
    double v = deltaX/deltaT;
    double vi[q+1][2] = {{0,0},{v,0},{0,v},{-v,0},{0,-v}};

    f_in[2][3][0] = 0;
    f_in[2][3][1] = 0;
    f_in[2][3][2] = 0;
    f_in[2][3][3] = 0;
    f_in[2][3][4] = 100;
    afficher(f_in);
    for (int i = 1; i <= 4;i++){
      foutComputation(tabl_n,v,vi,f_in);
      afficher(f_in);
    }
    cout << tabl_n[2][2] << "\n";
    cout << rhoComputation(f_in,2,3)  << "\n";
    cout << f_in[5][5][4] << "\n";
    //cout << vi[4][1]  << "\n";
    //cout << sizeof(y)  << "\n";
    //cout << z  << "\n";
    //cout << typeof(y)  << "\n";
    return 0;
}
