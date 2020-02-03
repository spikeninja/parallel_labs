#include <iostream>
#include <thread>
#include <vector>

#include "Matrix.h"

using namespace std;

const int N = 10;
const int M = 10;

const int NUMBER_THREADS = 1;


int main(){
  srand(time(NULL));
  
  Matrix a(10,10);

  cout << a;

  return 0;
}
