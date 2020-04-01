#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <unistd.h>
#include <atomic>
#include <memory>

using namespace std;


void vec_size_t(const vector<int>& vec, atomic<int>& vec_size, int idxStart, int idxStop){
  for(int i = idxStart; i <= idxStop; i++){
    int vec_size_temp = vec_size.load(memory_order_relaxed);
  }
}

void max_elem_t(vector<int>& vec, atomic<int>& max, int idxStart, int idxStop){
  for(int i = idxStart; i <= idxStop; i++){
    if(vec[i] > max){
      int max_temp = max.load(memory_order_relaxed);
      max.compare_exchange_strong(max_temp, vec[i]);
    }
  }
}

void min_elem_t(vector<int>& vec, atomic<int>& min, int idxStart, int idxStop){
  for(int i = idxStart; i <= idxStop; i++){
    if(vec[i] < min){
      int min_temp = min.load(memory_order_relaxed);
      min.compare_exchange_strong(min_temp, vec[i]);
    }
  }
}

void vec_size(const vector<int>& vec, atomic<int>& vec_size){
  thread threads[3];
  threads[0] = thread(vec_size_t, ref(vec), ref(vec_size), 0, vec.size()/3);
  threads[1] = thread(vec_size_t, ref(vec), ref(vec_size), vec.size()/3, 2*vec.size()/3);
  threads[2] = thread(vec_size_t, ref(vec), ref(vec_size), 2*vec.size()/3, vec.size());
  for(int i = 0; i < 3; i++){
    threads[i].join();
  }
}

void max_elem(vector<int>& vec, atomic<int>& max){
  max = vec[0];
  thread threads[3];
  threads[0] = thread(max_elem_t, ref(vec), ref(max), 0, vec.size()/3);
  threads[1] = thread(max_elem_t, ref(vec), ref(max), vec.size()/3, 2*vec.size()/3);
  threads[2] = thread(max_elem_t, ref(vec), ref(max), 2*vec.size()/3, vec.size());
  for(int i = 0; i < 3; i++){
    threads[i].join();
  }
}

void min_elem(vector<int>& vec, atomic<int>& min){
  min = vec[0];
  thread threads[3];
  threads[0] = thread(min_elem_t, ref(vec), ref(min), 0, vec.size()/3);
  threads[1] = thread(min_elem_t, ref(vec), ref(min), vec.size()/3+1, 2*vec.size()/3);
  threads[2] = thread(min_elem_t, ref(vec), ref(min), 2*vec.size()/3+1, vec.size()-1);
  for(int i = 0; i < 3; i++){
    threads[i].join();
  }
}

void sum_numbers(const vector<int>& vec, int idxStart, int idxEnd){
  for(int i = idxStart; i <= idxEnd; i++){
    //multiSum += vec[i];
  }
}

int main(){
  srand(time(NULL));

  vector<int> vec;
  atomic<int> arr_size, max, xor_num;
  atomic<int> min;

  for(int i = 0; i < 15; i++){
    vec.push_back(rand()%1000+23);
  }

  for(int i = 0; i < vec.size(); i++){
    cout << vec[i] << " ";
  }
  max_elem(vec, max);
  min_elem(vec, min);

  
  cout << endl;
  cout << max << " " << min << endl;

  return 0;
}