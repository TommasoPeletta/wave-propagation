#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <string.h>
#include "GraphicsInterface.hh"
#include <fstream>

using std::vector;
using namespace std;

//Pour lancer le code : make multilayers
//                      ./multilayers

GraphicsInterface window;
Matrix<unsigned char> image;
GraphicsInterface window_Amp;
Matrix<unsigned char> image_Amp;

const int sizeX = 1;
const int sizeY = 4000;
const int q = 4;
const double deltaX = 0.5;
const double v = sqrt(q/2)*3*pow(10,8);
const double deltaT = deltaX/v;
const double pi = 3.14159265358979323846;
const double size_c = 40;
//double beta[sizeX][sizeY];
double rho_max;
double Ampl_max;
double lambda = 600; // longueur d'onde passée en argument


int alpha; //affichage
typedef double ***type_F;
typedef double **type_coeff_reffrac;
typedef double vecteur[2];
type_F f_in;
type_F f_out;
type_coeff_reffrac tabl_n;
type_coeff_reffrac tabl_rho;
type_coeff_reffrac tabl_amplitude;
type_coeff_reffrac beta;



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


void define_fin(type_F f){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      for (int k = 0; k < q+1; k++){
        f[i][j][k] = 0;
      }
    }
  }
}


double vectors_prod(vecteur x,vecteur y) {
    double res = 0.0;
    int i;
    for (i = 0; i < 2; i++)
    {
        res += x[i] * y[i];
    }
    return res;
}




void scalar_prod(vecteur x, double y){
  for (int i = 0; i < 2; i++){
    x[i] = x[i] * y;
  }
}





void vector_sum(vecteur x, vecteur y){
  for (int i = 0; i < 2; i++){
    x[i] = x[i] + y[i];
  }
}





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






  void vector_cpy(type_F f_out, type_F f_in){
    for (int i = 0; i < sizeX; i++){
      for (int j = 0; j < sizeY; j++){
        for (int k = 0; k < q+1; k++){
          switch (k) {
            case 0 : f_in[i][j][k] = beta[i][j] * f_out[i][j][k];
                      break;
            case 1 : if (j != (sizeY-1)) {
                      f_in[i][j+1][k] = beta[i][j] * f_out[i][j][k];
                    }
                      break;
            case 2 : if (i != 0) {
                        f_in[i-1][j][k] = beta[i][j] * f_out[i][j][k];
                      } else {
                        f_in[sizeX-1][j][k] = beta[i][j] * f_out[i][j][k];
                      }
                      break;
            case 3 : if (j != 0) {
                      f_in[i][j-1][k] =beta[i][j] * f_out[i][j][k];
                    }
                    break;
            case 4 : if (i != (sizeX-1)) {
                      f_in[i+1][j][k] =beta[i][j] * f_out[i][j][k];
                    } else {
                      f_in[0][j][k] = beta[i][j] * f_out[i][j][k];
                    }
                    break;
          }
        }
      }
    }
  }






double rhoComputation(type_F matrix, int i, int j) {
  double sum = 0;
  for (int k = 0; k < q+1; k++){
    sum = sum + matrix[i][j][k];
  }
  double rho = sum;
  return rho;
}





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

void AmplitudeComputation(){
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      if(abs(tabl_rho[x][y])> tabl_amplitude[x][y]){
        tabl_amplitude[x][y] = abs(tabl_rho[x][y]);
        if(Ampl_max < tabl_amplitude[x][y]){Ampl_max = tabl_amplitude[x][y];}
      }
    }
  }

}




void foutComputation(type_coeff_reffrac n, double v, double vi[q+1][2], type_F f_in, int iteration){
  double rho;
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      if (n[i][j]>=1) {
        rho = rhoComputation(f_in,i,j);
        tabl_rho[i][j] = rho;
        if (abs(rho)>rho_max && iteration == 300){
          rho_max = rho;
        }
        vecteur j_sum;
        jComputation(j_sum,vi,f_in,i,j);

        for (int k = 0; k < q+1; k++){
          vecteur vi_aux;
          vi_aux[0] = vi[k][0];
          vi_aux[1] = vi[k][1];
          double vj = vectors_prod(vi_aux,j_sum);
          if (k != 0){
            f_out[i][j][k] = 2/(pow(n[i][j],2)* q) * rho + (1/pow(v,2)) * vj - f_in[i][j][k];
          } else {
            f_out[i][j][k] = 2*(pow(n[i][j],2) - 1)/(pow(n[i][j],2)) * rho - f_in[i][j][k];
          }
        }
      } else if(n[i][j]>0){       //in this programme, sources are represented by a refraction coefficient between 0 and 1
        double Ampl = 100;
        double phase = 0;
        double frequence = 3*pow(10,8)/lambda;

        for (int k = 0; k<=q ; k++){
          //if(iteration < 500){
            f_out[i][j][k] = Ampl*sin(2*pi*frequence*iteration*deltaT);
          //} else {
          //  f_out[i][j][k] = 0;
          //}
        }
      } else {
        f_out[i][j][0] = -f_in[i][j][0] * abs(tabl_n[i][j]);
        f_out[i][j][1] = -f_in[i][j][3] * abs(tabl_n[i][j]);
        f_out[i][j][2] = -f_in[i][j][4] * abs(tabl_n[i][j]);
        f_out[i][j][3] = -f_in[i][j][1] * abs(tabl_n[i][j]);
        f_out[i][j][4] = -f_in[i][j][2] * abs(tabl_n[i][j]);
      }
    }
  }
  //cout << endl;
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

void fill_matrix_n_in(type_coeff_reffrac matrix, int startY, int width,int startX, int height, double in) {
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      if (y >= startY && y < (startY+width) && x >= startX && x < (startX+height)) {
        matrix[x][y] = in;
      }
    }
  }
}


void beta_initialization(){
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      if(/*i==0 or i == sizeX-1 or */j==0 or j == sizeY-1){
        beta[i][j] = 0;
        break;
      }
        double x = 1;
        /*
        if (i<size_c and i < j and i < sizeY - j) {
          x =  1 - (size_c - i)/size_c;

        } else if (sizeX - i < size_c  and sizeX - i < j and sizeX - i < sizeY - j){
          x = 1 - (size_c - (sizeX - i)) / size_c;
        } else */if (sizeY - j < size_c ){
          x = 1 - (size_c - (sizeY - j)) / size_c;
        } else if (j < size_c ){
          x = 1 - (size_c - j) / size_c;
          //cout << "beta" << beta[i][j] << " ";
        }
        //beta[i][j] = 2*x-pow(x,2);
         //beta[i][j] = 8*pow(x,3) - 17 * pow(x,2) + 10;
         beta[i][j] = 1-1/1000/x;

      }
  }
}


void fill_space(type_coeff_reffrac matrix, double in) {
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
      matrix[x][y] = in;
    }
  }
}





  void parabole(){
      fill_space(tabl_n,1);
      tabl_n[200][100] = 0.5;
      //tabl_n[150][200] = 0.5;
      int f = 20;
      for (int z=0; z < sizeX; z++){
        for (int i = 0; i < 10; i++){    //pour avoir un miroir de 10 d'épaisseur
          tabl_n[z][(int)(100-i-f + (1.0/(4*f))*(pow((z-200),2)))] = -1;
        }
     }
     alpha = 3;
  }

  void diag(){
      fill_space(tabl_n,1);
      for (int z=0; z < sizeX; z++){
         tabl_n[z][40] = 0.5;
         for (int i = 0; i < 20; i++){
           tabl_n[z][z+80+i] = 1.7;
         }
         //tabl_n[z][z+100] = -1;
       }
       alpha = 1;
  }

  void source_Centre(){
      fill_space(tabl_n,1);
      tabl_n[sizeX/2][sizeY/2] = 0.5;
      alpha = 3;
  }

  void lentille(){
      fill_space(tabl_n,1);
      for (int z=0; z < sizeX; z++){
         tabl_n[z][40] = 0.5;
         for (int y=0; y < sizeY ; y++){
           //if(y<250 and y>150){

           if(y<sqrt(pow(250,2) - pow(z-200,2)) and y>-sqrt(pow(250,2) - pow(z-200,2))+300){

             tabl_n[z][y] = 1.4;
             //tabl_amplitude[z][y] = 10;
           }
         }
         //tabl_n[z][z+100] = -1;
       }
       alpha = 1;
  }

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
      for (int z= 0; z<2;z++){
        for (int y =0;y <5;y++){
        tabl_n[200+d+z][300+y]  = 1;
        tabl_n[200-d-z][300+y]  = 1;
      }
      }
      alpha = 200;
    }


  void multicouche(){

        double na = 3;   //first refraction indice
        double nb = 3;    // second refraction indice
        double d = 125;     //size of two layers (a and b)
        int nl = 1;         // number of double layers

        fill_space(tabl_n,1);
        for (int z=0; z < sizeX; z++){
           tabl_n[z][50] = 0.5;
           ///*
           for (int n=0; n < nl ; n++){
             for (int e = 0 ; e<d/deltaX; e++){
               if(e<(d/(1 + na/nb)/deltaX)+0.5){
                 tabl_n[z][650+(int)(d/deltaX)*n+e] = na;
               }else{
                 tabl_n[z][650+(int)(d/deltaX)*n+e] = nb;
               }
             }
             //if(y<250 and y>150){


           }
           //*/
           //tabl_n[z][z+100] = -1;
         }
         cout << "d : "<< d/deltaX << "\n";
         cout << "da : "<< d/(1 + na/nb)/deltaX << "\n";
         cout << "db : "<< d/(1 + nb/na)/deltaX << "\n";

         /*for (int y = 0; y <sizeY; y ++){
           cout << y << " : "<< tabl_n[100][y] << "\n";
         }*/
         alpha = 1;
  }


  int main( int argc, char **argv ) {
    if (argc > 1){
      lambda =atof(argv[1]);
    }


    fstream outfile;                                                   // pour l'extraction de valeurs pour créer des graphes
    outfile.open("ampl2.txt", fstream::out | fstream::trunc);          //
    outfile.precision(6);

    //window_Amp.open(sizeY,sizeX);
    //image_Amp.setDimension(sizeY,sizeX);



    //window.open(sizeY,sizeX);
    //image.setDimension(sizeY,sizeX);

    window_Amp.open((int)(sizeY/4),sizeX);
    image_Amp.setDimension((int)(sizeY/4),sizeX);

    window.open((int)(sizeY/4),sizeX);
    image.setDimension((int)(sizeY/4),sizeX);

    allocate();
    define_fin(f_in);
  //  fill_space(tabl_amplitude,0);


    //fill_matrix_n_in(tabl_n,100,50,250,50,-1);
    //fill_matrix_n_in(tabl_n,300,50,250,50,-1);
    //fill_matrix_n(beta,size_c,sizeY - (2*size_c),size_c,sizeX - (2*size_c), 0.95 , 1);
    fill_matrix_n(beta,size_c,sizeY - (2*size_c),0,sizeX, 0.95 , 1);
    //beta_initialization();

    double vi[q+1][2] = {{0,0},{v,0},{0,v},{-v,0},{0,-v}};

    //parabole();
    //diag();
    //source_Centre();
    //lentille();
    //Diffraction();
    //fente();
    multicouche();

    // iteration
    double ampl_incident = 0;
    double ampl1 = 0;
    double nb1 = 0;
    double ampl2 = 0;

    char title[100]; // nom pour la souvegarde d'image



    for (int i = 1; i <= 10000;i++){

      //rho_max = 0;
      foutComputation(tabl_n,v,vi,f_in,i);
      for (int k = 0; k < sizeX; k++){
        for (int j = 0; j < (int)(sizeY/4); j++){
          if (tabl_n[k][4*j]<0){image.set(j,k,(unsigned char) (1));}else{
            image.set(j,k,(unsigned char) (alpha * (tabl_rho[k][4*j]/rho_max) *  33 + 164));
          }
        }
      }

      if(i%10 == 0){
          outfile<<fixed<< i<<"   "<<fixed<<tabl_rho[0][350]<<endl; //écrire dans le fichier text les valeurs à plot

      }

      //window.drawMatrix(image);



      double m = 0;
      int my = 0;
      for (int y = 0 ; y < 599 ; y++){

        if(abs(tabl_rho[0][51+y])>m){
          m = abs(tabl_rho[0][51+y]);
          my = y;
        }
      }
      if(m>ampl1){
        if(nb1 > 5){
          cout << ampl1 << " : " << nb1 << "    y = " << my << "    iteration : " << i << "\n";
        }
        ampl1 = m;
        nb1 = 0;
      }

      nb1 = nb1 + 1;

      if(abs(tabl_rho[0][1400])>ampl2){
        ampl2 = abs(tabl_rho[0][1400]);
      }

      window.drawMatrix(image);
      if(i == (int)(lambda/deltaX)){ampl_incident = ampl1;}

      if(i>1200){
        AmplitudeComputation();
        for (int k = 0; k < sizeX; k++){
          for (int j = 0; j < sizeY/4; j++){
            if (tabl_n[k][4*j]<0){image.set(j,k,(unsigned char) (1));}else{
              //image_Amp.set(j,k,(unsigned char) (5*(tabl_amplitude[k][j]/Ampl_max) *  33 + 164));
              image_Amp.set(j,k,(unsigned char) (5*(tabl_amplitude[k][4*j]/Ampl_max) *  33 + 164));
            }
          }
        }
      }
      window_Amp.drawMatrix(image_Amp);

      if ( i == 500 || i == 4900 ){
        sprintf(title, "%d", i);
        window.printInto(title,image);
        //strcat(title, conc);
      }


    }
    window.close();
    window_Amp.close();

    outfile.close();

    cout << ampl1 << " : " << nb1 << "\n";
    cout <<"                              " << ampl2  << "\n";
    cout <<"Amplitude de l'onde incidente (caculée après "<< (int)(lambda/deltaX)<< " itérations : "<< ampl_incident << "\n";
    cout << "reflexivité : " << ampl1/ampl_incident - 1 << "\n";


    //system("gnuplot -p -e \"plot 'ampl2.txt'\"");
    return 0;

}
