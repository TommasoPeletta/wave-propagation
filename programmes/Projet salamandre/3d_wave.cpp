#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using std::vector;
using namespace std;

/*
For Executing the code :
g++ 3d_wave.cpp -o 3d_wave
./3d_wave
*/



//constant declaration
const int q = 6; // number of lattice directions along which the population f i can move (7 dimensions, start from 0)
const double deltaX = 5*pow(10,-9); // lattice spacing [m]
const double v = pow((q/2),0.5)*3*pow(10,8); // the velocity of wave propagation [m/s]
const double deltaT = deltaX/v;  // time step [s]
const double pi = 3.14159265358979323846;
const double size_c = 40; // distance from the edge of matrix from where the attenuation of the wave start


//type declaration
typedef double ****type_F;
typedef double ***type_coeff_reffrac;
typedef double vecteur[3];


// global variables declaration
int sizeX;
int sizeY;
int sizeZ;
bool ifHynobius = true;
double rho_max;
double Ampl_max;
type_F f_in; // 4d matrix containing the fi entering the site (for i = 0..q)
type_F f_out; // 4d matrix containing the fi exiting the site (for i = 0..q)
type_coeff_reffrac tabl_n; // matrix containg the refraction index for each point of the space
type_coeff_reffrac beta; // attenuation coefficient
type_coeff_reffrac tabl_amplitude; // matrix containg the maximum amplitude for each point of the space
type_coeff_reffrac tabl_rho; // matrix containg the sum of the fi entering the site for each point of the space



// Allocation of all matrix that are used by the program.
void allocate(){
  if (ifHynobius){
    sizeX = 100;
    sizeY = 100;
    sizeZ = 50;
    tabl_n = (double***)malloc(sizeX * sizeof(double **));
    for (int index = 0;index < sizeX; index++){
      tabl_n[index] = (double **)malloc(sizeY*sizeof(double*));
      for (int i = 0; i < sizeY;i++){
        tabl_n[index][i] = (double *)malloc(sizeZ*sizeof(double));
      }
    }
  }

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



  beta = (double***)malloc(sizeX * sizeof(double **));
  for (int index = 0;index < sizeX; index++){
    beta[index] = (double **)malloc(sizeY*sizeof(double*));
    for (int i = 0; i < sizeY;i++){
      beta[index][i] = (double *)malloc(sizeZ*sizeof(double));
    }
  }


  tabl_amplitude = (double***)malloc(sizeX * sizeof(double **));
  for (int index = 0;index < sizeX; index++){
    tabl_amplitude[index] = (double **)malloc(sizeY*sizeof(double*));
    for (int i = 0; i < sizeY;i++){
      tabl_amplitude[index][i] = (double *)malloc(sizeZ*sizeof(double));
    }
  }

  tabl_rho = (double***)malloc(sizeX * sizeof(double **));
  for (int index = 0;index < sizeX; index++){
    tabl_rho[index] = (double **)malloc(sizeY*sizeof(double*));
    for (int i = 0; i < sizeY;i++){
      tabl_rho[index][i] = (double *)malloc(sizeZ*sizeof(double));
    }
  }

}

//initialize a type_F variable with 0
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


//product between two 3d vectors
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



// product between a scalar and a 3d vector
void scalar_prod(vecteur x, double y){
  for (int i = 0; i < 3; i++){
    x[i] = x[i] * y;
  }
}



// sum between two 3d vectors
void vector_sum(vecteur x, vecteur y){
  for (int i = 0; i < 3; i++){
    x[i] = x[i] + y[i];
  }
}



/****************************************************************
Function for computing the J,
jComputation take as parameters:
-res of type vecteur that will contain the result J
-vi a matrix of dimension q+1 x 3 that contain all lattice's velocity directions
-f_in of type type_F that contain the fi entering the site
-x, y and z that represent de point that is being processing
*****************************************************************/
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



/***********************************************************************************************
Function for converting the fi exiting the site into the fi entering the site in next iteration.
This function take in consideration the coefficient of attenuation beta.
vector_cpy take as parameters:
-f_out of type type_F representing the fi exiting the site in the current iteration
-f_in of type_F will contain the fi entering the site for the next iteration
************************************************************************************************/
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
                      } else {
                        f_in[i][0][z][k] = beta[i][j][z] * f_out[i][j][k][z];
                      }
                      break;

            case 2 :  if (i != 0) {
                        f_in[i-1][j][z][k] = beta[i][j][z] * f_out[i][j][z][k];
                      } else {
                        f_in[sizeX-1][j][z][k] = beta[i][j][z] * f_out[i][j][k][z];
                      }
                      break;

            case 3 :  if (j != 0) {
                        f_in[i][j-1][z][k] =beta[i][j][z] * f_out[i][j][z][k];
                      } else {
                        f_in[i][sizeY-1][z][k] = beta[i][j][z] * f_out[i][j][k][z];
                      }
                      break;

            case 4 :  if (i != (sizeX-1)) {
                        f_in[i+1][j][z][k] =beta[i][j][z] * f_out[i][j][z][k];
                      } else {
                        f_in[0][j][z][k] = beta[i][j][z] * f_out[i][j][k][z];
                      }
                      break;

            case 5 :  if (z != 0) {
                        f_in[i][j][z-1][k] =beta[i][j][z] * f_out[i][j][z][k];
                      } else {
                        f_in[i][j][sizeZ-1][k] = beta[i][j][z] * f_out[i][j][k][z];
                      }
                      break;

            case 6 :  if (z != (sizeZ-1)) {
                        f_in[i][j][z+1][k] =beta[i][j][z] * f_out[i][j][z][k];
                      } else {
                        f_in[i][j][0][k] = beta[i][j][z] * f_out[i][j][k][z];
                      }
                      break;
          }
        }
      }
    }
  }
}


/***************************************************************************
This function compute and return the sum of the fi entering the site for a given point known as rho.
rhoComputation take as parameters:
-matrix of type type_F representing the fi entering the site.
-i, j and z representing the point that is being processing.
***************************************************************************/
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


/******************************************************************
This function update the global variable tabl_amplitude with the
new maximum amplitudes if they are reached at the iteration from where
the function is called.
******************************************************************/
void AmplitudeComputation(){
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      for (int z = 0; z < sizeZ; z++){
        if(abs(tabl_rho[x][y][z])> tabl_amplitude[x][y][z]){
          tabl_amplitude[x][y][z] = abs(tabl_rho[x][y][z]);
          if(Ampl_max < tabl_amplitude[x][y][z]){Ampl_max = tabl_amplitude[x][y][z];}
        }
      }
    }
  }

}


/**********************************************************************************************
This function compute the fi exiting the site knowing the fi entering the site.
It also handle the source of the wave.
foutComputation take as parameters:
-n of type type_coeff_reffrac that contains the refraction index of each point
-v of type double is the velocity of wave propagation
-vi a matrix of dimension q+1 x 3 that contain all lattice's velocity directions
-f_in of type type_F the fi entering the site
-iteratioon of type int the current iteration of the system
***********************************************************************************************/
void foutComputation(type_coeff_reffrac n, double v, double vi[q+1][3], type_F f_in, int iteration){
  double rho;
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int z = 0; z < sizeZ; z++){
        if (n[i][j][z]>=1) {
          rho = rhoComputation(f_in,i,j,z);
          tabl_rho[i][j][z] = rho;
          if (abs(rho)>rho_max && iteration == 3){
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
          double Amplitude = 0.01;
          double lambda = 6*pow(10,-7);
          double facteur = 0.04;
          double frequence = 3*pow(10,8)/lambda;
          for (int k = 0; k < q+1 ; k++){
            f_out[i][j][z][k] = Amplitude*sin(2*pi*frequence*iteration*deltaT);
          }
        } else {    //reflecting surfaces represented by a negative refraction coefficient
          for (int k = 0; k < q+1; k++){
            f_out[i][j][z][0] = -f_in[i][j][z][0] * abs(tabl_n[i][j][z]);
            f_out[i][j][z][1] = -f_in[i][j][z][3] * abs(tabl_n[i][j][z]);
            f_out[i][j][z][2] = -f_in[i][j][z][4] * abs(tabl_n[i][j][z]);
            f_out[i][j][z][3] = -f_in[i][j][z][1] * abs(tabl_n[i][j][z]);
            f_out[i][j][z][4] = -f_in[i][j][z][2] * abs(tabl_n[i][j][z]);
            f_out[i][j][z][5] = -f_in[i][j][z][6] * abs(tabl_n[i][j][z]);
            f_out[i][j][z][6] = -f_in[i][j][z][5] * abs(tabl_n[i][j][z]);
          }
        }
      }
    }
  }
  vector_cpy(f_out, f_in);
}

//initialize a type_coeff_reffrac matrix with 1
void defmatrix(type_coeff_reffrac n){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int z = 0; z < sizeZ; z++){
        n[i][j][z] = 1;
      }
    }
  }
}


// read from a log file all the refraction indexes computed by the python script.
// set the size of the matrix and fill tabl_n with the read data
void Hynobius(){
  ifHynobius = false;
  char *buffer = 0;
  char* aux;
//  chdir("./TraitementImage");
  FILE *f = fopen("logfile.txt","r");
  if (f)
  {
    fseek (f, 0, SEEK_END);
    long length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer =(char*) malloc (length);
    printf("%d\n", length);
    printf("buffer : %s\n", buffer);
    if (buffer){
      fread (buffer, 1, length, f);
    }
    fclose (f);
  }
  printf("%s\n", buffer);

  if (buffer){
    //printf("%s\n", buffer );
    aux = strtok(buffer, "\n");
    aux = strtok(NULL, " ");
    sizeX = atoi(aux);
    aux = strtok(NULL, " ");
    sizeY = atoi(aux);
    aux = strtok(NULL, " ");
    sizeZ = atoi(aux);
    aux = strtok(NULL, "\n");
    aux = strtok(NULL, "\n");
    aux = strtok(NULL, "\n");
    aux = strtok(NULL, " ");
    tabl_n = (double***)malloc(sizeX * sizeof(double **));
    for (int index = 0;index < sizeX; index++){
      tabl_n[index] = (double **)malloc(sizeY*sizeof(double*));
      for (int i = 0; i < sizeY;i++){
        tabl_n[index][i] = (double *)malloc(sizeZ*sizeof(double));
      }
    }
    for (int i = 0; i < sizeZ; i++){
      for (int j = 0; j < sizeY; j++){
        for (int k = 0; k < sizeX; k++){
           //if( aux != NULL ) {
           if (k != sizeX-2 && !(k == sizeX-1 && j == sizeY-1)){
            tabl_n[k][j][i] =(double) atof(aux);
            aux = strtok(NULL, " ");
          }else if(k == sizeX-2){
            tabl_n[k][j][i] =(double) atof(aux);
            if (i != sizeZ-1 || (i == sizeZ-1 && j != sizeY-1)){
              aux = strtok(NULL, "\n");
            }else {
              cout << "i " << i << endl;
              aux = strtok(NULL, "\n");
              cout << aux << endl;
            }
          }else if(k == sizeX-1 && j == sizeY-1){
            tabl_n[k][j][i] =(double) atof(aux);
            //cout << aux << endl;
          //  aux = strtok(NULL, "\n");
            //cout << aux << endl;
            if (i != sizeZ-1){
              aux = strtok(NULL,"\n");
            //  cout << aux << endl;
              aux = strtok(NULL, " ");
            }
          //  cout << aux << endl;
        }

        }
      }
    //aux2 = strtok(NULL,"\n");
    }

    cout << "data extracted from logfile"<< endl << "sizeX = " << sizeX << ", sizeY = " << sizeY << ", sizeZ = "<< sizeZ << endl ;
    for (int i = 0; i < sizeZ; i++){
      for (int j = 0; j < sizeY; j++){
        for (int k = 0; k < sizeX; k++){
          printf("%f",tabl_n[k][j][i]);
          printf("%s", " ");
        }
        printf("%s%d\n", "ligne ", j);
      }
      printf("%d\n", i);
    }
    cout << "Fini affichage" << endl;
  } else {
    cout << "else" << endl;
  }
  buffer = NULL;
  cout << "FINI FINI" << endl;
}


int main( int argc, char **argv ) {
  Hynobius();
  cout << "fini Hynobius" << endl;

  allocate();

  define_fin(f_in);

  defmatrix(beta);

  double vi[q+1][3] = {{0,0,0},{v,0,0},{0,v,0},{-v,0,0},{0,-v,0},{0,0,v},{0,0,-v}};
  //tabl_n[5][5][4] = 0.5;
             // this line would create a source point and erase the refraction coefficient of the point [5][5][4]
  for (int i = 1; i <= 1;i++){
    rho_max = 0;
    //foutComputation(tabl_n,v,vi,f_in,i);
  }

  //afficher(f_in, 4);

  return 0;
}
