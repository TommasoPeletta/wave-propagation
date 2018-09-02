#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include "GraphicsInterface.hh"
#include <fstream>

using std::vector;
using namespace std;

//For Executing the code : make wave
//                      ./wave

GraphicsInterface window;       //initialisation of windows for the graphic part
Matrix<unsigned char> image;
GraphicsInterface window_Amp;
Matrix<unsigned char> image_Amp;

//constant declaration
const int sizeX = 400;
const int sizeY = 600;
const int q = 4; // number of lattice directions along which the population f i can move (5 dimensions, start from 0)
const double deltaX = 5*pow(10,-9); // lattice spacing [m]
const double v = sqrt(2)*3*pow(10,8); // the velocity of wave propagation [m/s]
const double deltaT = deltaX/v; // time step [s]
const double pi = 3.14159265358979323846;
const double size_c = 40; // distance from the edge of matrix from where the attenuation of the wave start


// type declaration
typedef double ***type_F;
typedef double **type_coeff_reffrac;
typedef double vecteur[2];


// global variables declaration
double rho_max;
double Ampl_max;
int alpha; // plots' colour
type_F f_in; // 3d matrix containing the fi entering the site (for i = 0..q)
type_F f_out; // 3d matrix containing the fi exiting the site (for i = 0..q)
type_coeff_reffrac tabl_n; // matrix containg the refraction index for each point of the space
type_coeff_reffrac tabl_rho; // matrix containg the sum of the fi entering the site for each point of the space
type_coeff_reffrac tabl_amplitude; // matrix containg the maximum amplitude for each point of the space
type_coeff_reffrac beta; // attenuation coefficient


// Allocation of the different matrix which be use by the program.
void allocate(){
  //allocation f_in
  f_in = (double***)malloc(sizeX * sizeof(double **));
  for (int index = 0;index < sizeX; index++){
    f_in[index] = (double **)malloc(sizeY*sizeof(double*));
    for (int i = 0; i < sizeY;i++){
      f_in[index][i] = (double *)malloc((q+1)*sizeof(double));
    }
  }

  //allocation f_out
  f_out = (double***)malloc(sizeX * sizeof(double **));
  for (int index = 0;index < sizeX; index++){
    f_out[index] = (double **)malloc(sizeY*sizeof(double*));
    for (int i = 0; i < sizeY;i++){
      f_out[index][i] = (double *)malloc((q+1)*sizeof(double));
    }
  }

  //allocation tabl_n
  tabl_n = (double **) malloc (sizeof(double **)*sizeX);
  for (int i = 0; i < sizeX; i++) {
    tabl_n[i] = (double *) malloc(sizeof(double)*sizeY);
  }

  //allocation tabl_rho
  tabl_rho = (double **) malloc (sizeof(double **)*sizeX);
  for (int i = 0; i < sizeX; i++) {
    tabl_rho[i] = (double *) malloc(sizeof(double)*sizeY);
  }

  //allocation tabl_amplitude
  tabl_amplitude = (double **) malloc (sizeof(double **)*sizeX);
  for (int i = 0; i < sizeX; i++) {
    tabl_amplitude[i] = (double *) malloc(sizeof(double)*sizeY);
  }

  //allocation beta
  beta = (double **) malloc (sizeof(double **)*sizeX);
  for (int i = 0; i < sizeX; i++) {
    beta[i] = (double *) malloc(sizeof(double)*sizeY);
  }
}

// function that initializes a matrix of type_F with zeros
void define_fin(type_F f){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int k = 0; k < q+1; k++){
        f[i][j][k] = 0;
      }
    }
  }
}

// product between two 2d vectors
double vectors_prod(vecteur x,vecteur y){
    double res = 0.0;
    for (int i = 0; i < 2; i++)
    {
        res += x[i] * y[i];
    }
    return res;
}

// product between a 2d vector and a scalar
void scalar_prod(vecteur x, double y){
  for (int i = 0; i < 2; i++){
    x[i] = x[i] * y;
  }
}

// sum between two 2d vectors
void vector_sum(vecteur x, vecteur y){
  for (int i = 0; i < 2; i++){
    x[i] = x[i] + y[i];
  }
}


/****************************************************************
Function for computing the J,
jComputation take as parameters:
-res of type vecteur that will contain the result J
-vi a matrix of dimension q+1 x 2 that contain all lattice's velocity directions
-f_in of type type_F that contain the fi entering the site
-x and y that represent de point that is being processing
*****************************************************************/
void jComputation(vecteur res,double vi[q+1][2], type_F f_in ,int x ,int y){
  res[0] = 0;
  res[1] = 0;
  vecteur v_aux;
  for (int i = 1; i < q+1; i++){
    v_aux[0] = vi[i][0];
    v_aux[1] = vi[i][1];
    scalar_prod(v_aux, f_in[x][y][i]);
    vector_sum(res,v_aux);
  }
}


/***********************************************************************************************
Function for converting the fi exiting the site into the fi entering the site in next iteration.
This function take in consideration the coefficient of attenuation beta.
The border are also implemented in the fonction.
vector_cpy take as parameters:
-f_out of type type_F representing the fi exiting the site in the current iteration
-f_in of type_F will contain the fi entering the site for the next iteration
************************************************************************************************/
void vector_cpy(type_F f_out, type_F f_in){
    for (int i = 0; i < sizeX; i++){
      for (int j = 0; j < sizeY; j++){
        for (int k = 0; k < q+1; k++){
          switch (k) {
            case 0 : f_in[i][j][k] = beta[i][j] * f_out[i][j][k];
                      break;
            case 1 : if (j != (sizeY-1)) {
                      f_in[i][j+1][k] = beta[i][j] * f_out[i][j][k];
                    }                                                           //here the top and bottom border are ignored. It is only possible with an attenuation for those borders
                      break;
            case 2 : if (i != 0) {
                        f_in[i-1][j][k] = beta[i][j] * f_out[i][j][k];
                      }else{                                                    //here the right and left border are periodic
                        f_in[sizeX-1][j][k] = beta[i][j] * f_out[i][j][k];
                      }
                      break;
            case 3 : if (j != 0) {
                      f_in[i][j-1][k] =beta[i][j] * f_out[i][j][k];
                    }
                    break;
            case 4 : if (i != (sizeX-1)) {
                      f_in[i+1][j][k] =beta[i][j] * f_out[i][j][k];
                    }else{                                                      // left and right periodicity
                      f_in[0][j][k] = beta[i][j] * f_out[i][j][k];
                    }
                    break;
          }
        }
      }
    }
}


/***************************************************************************
This function compute and return the sum of the fi entering the site for a given point known as rho.
rhoComputation take as parameters:
-matrix of type type_F representing the fi entering the site.
-i and j representing the point that is being processing.
***************************************************************************/
double rhoComputation(type_F matrix, int i, int j) {
  double sum = 0;
  for (int k = 0; k < q+1; k++){
    sum = sum + matrix[i][j][k];
  }
  double rho = sum;
  return rho;
}

/*********************************
**********************************/
void afficher(type_F matrix) {
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      double r = rhoComputation(matrix,x,y);
      cout << r << "    ";
    }
    cout << endl;
  }
  cout << endl;
}
/******************************************************************
*******************************************************************/
void afficher2D(type_coeff_reffrac matrix) {
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      double r = matrix[x][y];
      cout << r << "    ";
    }
    cout << endl;
  }
  cout << endl;
}



/******************************************************************
This function update the global variable tabl_amplitude with the
new maximum amplitudes if they are reached at the iteration from where
the function is called.
******************************************************************/
void AmplitudeComputation(){
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      if(abs(tabl_rho[x][y])> tabl_amplitude[x][y]){
        tabl_amplitude[x][y] = abs(tabl_rho[x][y]);
        if(Ampl_max < tabl_amplitude[x][y]){
          Ampl_max = tabl_amplitude[x][y];
        }
      }
    }
  }

}
/**********************************************************************
This function update the global variable compute the max amplitude of the
site in a specific region delimited by the parameters SX, SY, FX, FY
***********************************************************************/
double AmplitudeMax(int SX, int SY, int FX, int FY){
  double Ampl_max_freq = 0;
  for (int x = SX; x < FX; x++){
    for (int y = SY; y < FY; y++){
      if(abs(tabl_rho[sizeX/2][y])> Ampl_max_freq){
        Ampl_max_freq = abs(tabl_rho[sizeX/2][y]);
      }
    }
  }

  return Ampl_max_freq;
}



/**********************************************************************************************
This function compute the fi exiting the site knowing the fi entering the site.
It also handle the source of the wave.
foutComputation take as parameters:
-n of type type_coeff_reffrac that contains the refraction index of each point
-v of type double is the velocity of wave propagation
-vi a matrix of dimension q+1 x 2 that contain all lattice's velocity directions
-f_in of type type_F the fi entering the site
-iteratioon of type int the current iteration of the system
***********************************************************************************************/
void foutComputation(type_coeff_reffrac n, double v, double vi[q+1][2], type_F f_in, int iteration){
  double rho;
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      if (n[i][j]>=1) {
        rho = rhoComputation(f_in,i,j);//rho computation
        tabl_rho[i][j] = rho;
        if (abs(rho)>rho_max && iteration == 50){
          rho_max = rho; //rho_max used for balancing the colour of the plot
        }
        vecteur j_sum = {0,0};
        jComputation(j_sum,vi,f_in,i,j); //j computation

        for (int k = 0; k < q+1; k++){
          vecteur vi_aux;
          vi_aux[0] = vi[k][0];
          vi_aux[1] = vi[k][1];
          double vj = vectors_prod(vi_aux,j_sum);
          if (k != 0){
            f_out[i][j][k] = 2/(pow(n[i][j],2)* 4) * rho + (1/pow(v,2)) * vj - f_in[i][j][k]; //fi exiting the site computation i <> 0
          } else {
            f_out[i][j][k] = 2*(pow(n[i][j],2) - 1)/(pow(n[i][j],2)) * rho - f_in[i][j][k]; //fi exiting the site computation i = 0
          }
        }
      } else if(n[i][j]>0 &&  n[i][j]<1){       //sources are represented by a refraction coefficient between 0 and 1
        double Ampl = 0.01;
        double lambda = 6*pow(10,-7); //nanometers
        double phase = 0;
        double frequence = 3*pow(10,8)/lambda;
        for (int k = 0; k<=q ; k++){
          f_out[i][j][k] = Ampl*sin(2*pi*frequence*iteration*deltaT); //source computation
        }
      } else {  //total reflection case
        f_out[i][j][0] = -f_in[i][j][0] * abs(tabl_n[i][j]);
        f_out[i][j][1] = -f_in[i][j][3] * abs(tabl_n[i][j]);
        f_out[i][j][2] = -f_in[i][j][4] * abs(tabl_n[i][j]);
        f_out[i][j][3] = -f_in[i][j][1] * abs(tabl_n[i][j]);
        f_out[i][j][4] = -f_in[i][j][2] * abs(tabl_n[i][j]);
      }
    }
  }
  vector_cpy(f_out, f_in);
}



/*******************************************************************
fill the matrix with the value in inside the area delimited by
startY,width,startX,height and with the value out outside this area
********************************************************************/
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



//fill the matrix with the value in inside the area delimited by startY,width,startX,height
void fill_matrix_n_in(type_coeff_reffrac matrix, int startY, int width,int startX, int height, double in) {
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      if (y >= startY && y < (startY+width) && x >= startX && x < (startX+height)) {
        matrix[x][y] = in;
      }
    }
  }
}


// fill all the matrix with the value in
void fill_space(type_coeff_reffrac matrix, double in){
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
        matrix[x][y] = in;
      }
    }
  }


//put a layer with n = 3 at y = 50 of size = 25 (plane wave)
void singleLayer(){
    fill_matrix_n(tabl_n,sizeY/2,25,0,sizeX,1.00029,3);
    for (int z=0; z < sizeX; z++){
       tabl_n[z][50] = 0.5;
     }
     alpha = 1;

}


  //put a mirror with parabolic shape, the source is on the focus
  void parabole(){
      fill_space(tabl_n,1);
      tabl_n[200][100] = 0.5;
      int f = 20;
      for (int z=0; z < sizeX; z++){
        for (int i = 0; i < 10; i++){    //pour avoir un miroir de 10 d'épaisseur
          tabl_n[z][(int)(100-i-f + (1.0/(4*f))*(pow((z-200),2)))] = -1;
        }
     }
     alpha = 3;
  }

// put a diagonal layer with n = 1.7
  void diag(){
      fill_space(tabl_n,1);
      for (int z=0; z < sizeX; z++){
         tabl_n[z][40] = 0.5;
         for (int i = 0; i < 20; i++){
           tabl_n[z][z+80+i] = 1.7;
         }
       }
       alpha = 1;
  }


// put a central source
  void source_Centre(){
      fill_space(tabl_n,1);
      tabl_n[sizeX/2][sizeY/2] = 0.5;
      alpha = 3;
  }

// put a lens with n = 1.4 (plane wave)
  void lentille(){
      fill_space(tabl_n,1);
      for (int z=0; z < sizeX; z++){
         tabl_n[z][40] = 0.5;
         for (int y=0; y < sizeY ; y++){
           if(y<sqrt(pow(250,2) - pow(z-200,2)) and y>-sqrt(pow(250,2) - pow(z-200,2))+300){
             tabl_n[z][y] = 1.4;
           }
         }
       }
       alpha = 1;
  }

// difraction experiment
  void Diffraction(){
    fill_space(tabl_n,1);
    for (int z=0; z < sizeY; z++){
       tabl_n[45][z] = 0.5;
   }
   for (int z=0; z < sizeY; z++){
     if (z != 250){
       tabl_n[200][z] = -0.1;
     }
   }
   alpha = 1;
  }

//double slit experiment (young)
  void fente(){
      int d = 40;
      fill_space(tabl_n,1);
      tabl_n[200][50] = 0.5;
      for (int z=0;z< sizeX; z++){
        tabl_n[z][300] = -0.1;
        tabl_n[z][301] = -0.1 ;
        tabl_n[z][302] = -0.1;
        tabl_n[z][303] = -0.1 ;
        tabl_n[z][304] = -0.1;
      }
      for (int z= 0; z<4;z++){
        for (int y =0;y <5;y++){
        tabl_n[200+d+z][300+y]  = 1;
        tabl_n[200-d-z][300+y]  = 1;
      }
      }
      alpha = 50;
    }






  int main( int argc, char **argv ) {

    fstream outfile1;                                                   // initialisation of an outfile for data extraction
    outfile1.open("ampl.txt", fstream::out | fstream::trunc);          //
    outfile1.precision(6);                                              //


    window_Amp.open(sizeY,sizeX);
    image_Amp.setDimension(sizeY,sizeX);
    window.open(sizeY,sizeX);
    image.setDimension(sizeY,sizeX);
    char title[100]; // nom pour la souvegarde d'image
    allocate();
    define_fin(f_in); //Put every positions of the matrix equals to 0.

    //fill_matrix_n(beta,size_c,sizeY - 2*size_c,size_c,sizeX - 2*size_c, 0.95 , 1);   //initialize beta for an attenuation on all 4 borders
    fill_matrix_n(beta,size_c,sizeY - (2*size_c),0,sizeX, 0.9 , 1);                 //initialize beta for an attenuation on the top and bottom border (left and right border are periodic or reflictive)

    double vi[q+1][2] = {{0,0},{v,0},{0,v},{-v,0},{0,-v}};

/******************************************************
choose the matrix initialisation for each experience
******************************************************/
    //parabole();
    //diag();
    //source_Centre();
    //lentille();
    //Diffraction();
    //fente();
    singleLayer();

    // iteration
    for (int i = 0; i <= 4000;i++){


      foutComputation(tabl_n,v,vi,f_in,i);
      for (int k = 0; k < sizeX; k++){
        for (int j = 0; j < sizeY; j++){
          if (tabl_n[k][j]<0){
            image.set(j,k,(unsigned char) (1));
          }else{
            image.set(j,k,(unsigned char) (alpha * (tabl_rho[k][j]/rho_max) *  33 + 164));
          }
        }
      }
      window.drawMatrix(image);


      AmplitudeComputation();
      for (int k = 0; k < sizeX; k++){
        for (int j = 0; j < sizeY; j++){
          if (tabl_n[k][j]<0){image.set(j,k,(unsigned char) (1));}else{
            image_Amp.set(j,k,(unsigned char) ((tabl_amplitude[k][j]/rho_max) *  33 + 164));
          }
        }
      }
      window_Amp.drawMatrix(image_Amp);

      /*
      if(i%10 == 0){                code for the extraction of the values of certains points in ampl.txt
          outfile1<<fixed<< i<<"   "<<fixed<<tabl_rho[0][283]<<"   "<<fixed<<tabl_rho[0][sizeY/2 + 12]<<"   "<<fixed<<tabl_rho[0][sizeY/2 + 60]<<endl; 
      }*/
      /*
      if(i%10 == 0){                  // code for printing snapshot of the wave
        sprintf(title, "%d", i);
        window.printInto(title,image);
      }*/
    }

    window.close();
    window_Amp.close();



    outfile1.close();
    return 0;

}
