#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <GL/glut.h>
#include <cstdlib>

using std::vector;
using namespace std;

const unsigned int W = 1200;
const unsigned int H = 500;

void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    unsigned int data[H][W][3];
    for( size_t y = 0; y < H; ++y )
    {
        for( size_t x = 0; x < W; ++x )
        {
            data[y][x][0] = 0;
            data[y][x][1] = 0;
            data[y][x][2] = ( rand() % 256 ) * 256 * 256 * 256;
            //cout << ( rand() % 256 );
        }

    }

    glDrawPixels( W, H, GL_RGB, GL_UNSIGNED_INT, data );

    glutSwapBuffers();
}

int main( int argc, char **argv )
{
      cout << ( rand() % 256 );
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( W, H );
    glutCreateWindow( "GLUT" );
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    unsigned int data[H][W][3];
    for( size_t y = 0; y < H; ++y )
    {
        for( size_t x = 0; x < W; ++x )
        {
            data[y][x][0] = 0;
            data[y][x][1] = 0;
            data[y][x][2] = ( rand() % 256 ) * 256 * 256 * 256;
            //cout << ( rand() % 256 );
        }

    }

    glDrawPixels( W, H, GL_RGB, GL_UNSIGNED_INT, data );

    glutSwapBuffers();    glutMainLoop();
    return 0;
}
