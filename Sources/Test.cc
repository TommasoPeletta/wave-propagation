#include <iostream>
using namespace std;

//Pour lancer le code : g++ Test.cc -o Test
//                      ./Test
const int sizeX = 10;
const int sizeY = 10;
const int q = 4;

int main()
{
    double f_in[10][10];
    for (int x = 0; x < 10; x++){
      for (int y = 0; y < 10; y++){
        cout << f_in[x][y] << "    ";
        if (f_in[x][y] > 0) {
          cout << "COUSCOUS !!!";
        }
      }
      cout << endl;
    }
    cout << endl;
    cout << "Hello, World!\n";
    return 0;
}
