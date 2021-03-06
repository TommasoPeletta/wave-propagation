#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <GL/glut.h>
#include <cstdlib>

using std::vector;
using namespace std;

//Pour lancer le code : g++ 2d_wave.cpp -o lookAtThis -lglut -lGL
//                      ./lookAtThis


const int sizeX = 400;
const int sizeY = 400;
const int q = 4;
const double deltaX = 75;
const double v = pow((q/2),1/2)*3*pow(10,8);
const double deltaT = deltaX/v;
const double pi = 3.14159265358979323846;
const double size_c = 40;
double beta[sizeX][sizeY];
double rho_max;

typedef double type_F[sizeX][sizeY][q+1];
typedef double type_coeff_reffrac[sizeX][sizeY];
typedef double vecteur[2];
type_F f_in = {{{0}}};
type_coeff_reffrac tabl_n;




double vectors_prod(vecteur x,vecteur y)
{
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
                      }
                      break;
            case 3 : if (j != 0) {
                      f_in[i][j-1][k] =beta[i][j] * f_out[i][j][k];
                    }
                    break;
            case 4 : if (i != (sizeX-1)) {
                      f_in[i+1][j][k] =beta[i][j] * f_out[i][j][k];
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






void foutComputation(type_coeff_reffrac n, double v, double vi[q+1][2], type_F f_in, int iteration){
  type_F f_out;
  double rho;
  for (int i = 0; i < sizeX; i++){
    for (int j = 0; j < sizeY; j++){
      if (n[i][j]>=1) {
        rho = rhoComputation(f_in,i,j);
        if (abs(rho)>rho_max){
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
        double Amplitude = 100;
        double phase = 0;
        double facteur = 0.04;
        double frequence = 2*pow(10,5);
        for (int k = 0; k<=q ; k++){
          f_out[i][j][k] = Amplitude*sin(2*pi*frequence*iteration*deltaT);
        }
      } else {
        f_out[i][j][0] = -f_in[i][j][0];
        f_out[i][j][1] = -f_in[i][j][3];
        f_out[i][j][2] = -f_in[i][j][4];
        f_out[i][j][3] = -f_in[i][j][1];
        f_out[i][j][4] = -f_in[i][j][2];
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





void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    unsigned int data[sizeX][sizeY][3];
    for( size_t x = 0; x < sizeX; ++x )
    {
        for( size_t y = 0; y < sizeY; ++y )
        {
              if (tabl_n[x][y] < 0){
                data[x][y][0] = (0.99 *  256) * 256 *256 *256;
                data[x][y][1] = 0;
                data[x][y][2] = 0;
              }else{
          /*  if (rhoComputation(f_in,x,y) == 0) {
              data[x][y][0] = 128;
              data[x][y][1] = 0;
              data[x][y][2] = 0;
            }else if (rhoComputation(f_in,x,y) < 0) {*/
              data[x][y][0] = 0;
              data[x][y][1] = 0;
              data[x][y][2] = (int)((rhoComputation(f_in,x,y)/rho_max) *  128+ 128) * 256 *256 *256;
              // data[x][y][2] = (int)((abs(rhoComputation(f_in,x,y))/rho_max) *  256) * 256 *256 *256;
          /*  } else {
              data[x][y][0] = (int)(abs(rhoComputation(f_in,x,y)/50) *  256) * 256 *256 *256;
              data[x][y][1] = 0;
              data[x][y][2] = 0;
            }*/
          }
        }
    }

    glDrawPixels( sizeX, sizeY, GL_RGB, GL_UNSIGNED_INT, data );

    glutSwapBuffers();
}


void fill_space(type_coeff_reffrac matrix, double in) {
  for (int x = 0; x < sizeX; x++){
    for (int y = 0; y < sizeY; y++){
        matrix[x][y] = in;
      }
    }
  }



  int main( int argc, char **argv ) {
    fill_space(tabl_n,1);
    fill_matrix_n_in(tabl_n,100,50,250,50,-1);
    fill_matrix_n_in(tabl_n,300,50,250,50,-1);
    fill_matrix_n(beta,size_c,sizeY - (2*size_c),size_c,sizeX - (2*size_c), 0.995 , 1);
    double vi[q+1][2] = {{0,0},{v,0},{0,v},{-v,0},{0,-v}};



    /*for (int i = 0; i < sizeX; i++){
      for (int j = 0; j < sizeY; j++){
          if (i<size_c) {
            beta[i][j] = 1 - (size_c - i)/size_c;
            beta[i][j] = 0.995;
          } else if (sizeX - i < size_c ){
            beta[i][j] = 1 - (size_c - (sizeX - i)) / size_c;
            beta[i][j] = 0.995;
          } else if (sizeY - j < size_c ){
            beta[i][j] = 1 - (size_c - (sizeY - j)) / size_c;
            beta[i][j] = 0.995;
          } else if (j < size_c ){
            beta[i][j] = 1 - (size_c - j) / size_c;
            beta[i][j] = 0.995;
            //cout << "beta" << beta[i][j] << " ";
          } else {
            beta[i][j] = 1;
          }
        }
    }*/



  /*  for (int z=0; z < sizeX; z++){
       tabl_n[200][100] = 0.5;
       int f = 20;
       tabl_n[z][(int)(100-f + (1.0/(4*f))*(pow((z-200),2)))] = -1;        // parabole
    }*/


    //Source
   for (int z=0; z < sizeX; z++){
      tabl_n[45][z] = 0.5;
  }

    // iteration
    for (int i = 1; i <= 700;i++){
      rho_max = 0;
      foutComputation(tabl_n,v,vi,f_in,i);
    }



    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( sizeX, sizeY );
    glutCreateWindow( "GLUT" );
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;

}
