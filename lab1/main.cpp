#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#include "Matrix.h"

using namespace std;

const int N = 10;
const int M = 10;

const int NUM_OF_THREADS = 1;


int main(){
  srand(time(NULL));
  
  Matrix a(N,M), b(N, M);
  // Sequential addition
  chrono::time_point <chrono::system_clock> t1_seq = chrono::high_resolution_clock::now();
  Matrix c = a + b;
  chrono::time_point <chrono::system_clock> t2_seq = chrono::high_resolution_clock::now();
  auto delta = chrono::duration_cast<chrono::microseconds>(t2_seq - t1_seq).count();
  cout << "Sequential adding: " << delta << " microsecond" << endl; 

  // Parallel addition

  vector<thread> threads;
  Matrix d(N, M);
  chrono::time_point <chrono::system_clock> t1_par = chrono::high_resolution_clock::now();

  for(int i = 0; i < NUM_OF_THREADS; i++){
    threads.push_back(thread(d.parallel_addition,d,a,b,i * (N / NUM_OF_THREADS),(i + 1) * (N / NUM_OF_THREADS)));
  }

  for(auto &thread : threads){
    thread.join();
  }

  chrono::time_point <chrono::system_clock> t2_par = chrono::high_resolution_clock::now();
  auto duration_par = std::chrono::duration_cast<std::chrono::microseconds>(t2_par - t1_par).count();
  std::cout << "Parallel (" << NUM_OF_THREADS << " threads) addition of vectors - execution time: " << duration_par << "us" << std::endl;
   

  return 0;
}
