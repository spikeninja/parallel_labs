#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#include "Matrix.h"

using namespace std;

const int N = 10;
const int M = 10;

const int NUMBER_THREADS = 1;


int main(){
  srand(time(NULL));
  
  Matrix a(10,10);
  Matrix b(10,10);
  Matrix c = a + b;

  cout << a;

//  thread threads[NUMBER_THREADS];

  //cout << this_thread::get_id() << endl;

   

  return 0;
}
