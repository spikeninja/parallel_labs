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
  
  Matrix a(N,M), b(N, M);
  // Sequential addition
  chrono::time_point <chrono::system_clock> t1_seq = chrono::high_resolution_clock::now();
  Matrix c = a + b;
  chrono::time_point <chrono::system_clock> t2_seq = chrono::high_resolution_clock::now();
  auto delta = chrono::duration_cast<chrono::microseconds>(t2_seq - t1_seq).count();
  cout << "Sequential adding: " << delta << " microsecond" << endl; 

  //cout << a;

  //thread threads[NUMBER_THREADS];

   

  return 0;
}
