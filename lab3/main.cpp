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
    vec_size++;
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

void xor_sum_t(vector<int>& vec, atomic<int>& xor_sum, int idxStart, int idxStop){
  for(int i = idxStart; i <= idxStop; i++){
      xor_sum ^= vec[i];
  }
}

void vec_size(const vector<int>& vec, atomic<int>& vec_size){
  vec_size = 0;
  thread threads[3];
  threads[0] = thread(vec_size_t, ref(vec), ref(vec_size), 0, vec.size()/3);
  threads[1] = thread(vec_size_t, ref(vec), ref(vec_size), vec.size()/3+1, 2*vec.size()/3);
  threads[2] = thread(vec_size_t, ref(vec), ref(vec_size), 2*vec.size()/3+1, vec.size()-1);
  for(int i = 0; i < 3; i++){
    threads[i].join();
  }
}

void max_elem(vector<int>& vec, atomic<int>& max){
  max = vec[0];
  thread threads[3];
  threads[0] = thread(max_elem_t, ref(vec), ref(max), 0, vec.size()/3);
  threads[1] = thread(max_elem_t, ref(vec), ref(max), vec.size()/3, 2*vec.size()/3);
  threads[2] = thread(max_elem_t, ref(vec), ref(max), 2*vec.size()/3, vec.size()-1);
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

void xor_sum(vector<int>& vec, atomic<int>& xor_sum){
  xor_sum = vec[0];
  thread threads[3];
  threads[0] = thread(xor_sum_t, ref(vec), ref(xor_sum), 0, vec.size()/3);
  threads[1] = thread(xor_sum_t, ref(vec), ref(xor_sum), vec.size()/3+1, 2*vec.size()/3);
  threads[2] = thread(xor_sum_t, ref(vec), ref(xor_sum), 2*vec.size()/3+1, vec.size()-1);
  for(int i = 0; i < 3; i++){
    threads[i].join();
  }
}


int main(){
  srand(time(NULL));
  const int N = 20;

  vector<int> vec;
  atomic<int> v_size, max, min, xor_num;

  for(int i = 0; i < N; i++){
    vec.push_back(rand()%1000+23);
  }

  for(int i = 0; i < vec.size(); i++){
    cout << vec[i] << " ";
  }
  max_elem(vec, max);
  min_elem(vec, min);
  vec_size(vec, v_size);
  xor_sum(vec, xor_num);
  
  cout << endl;
  cout << "max_elem: " << max << endl;
  cout << "min_elem: " << min << endl;
  cout << "v_size: " << v_size << " vec.size(): " << vec.size() << endl;
  cout << "xor_sum: " << xor_num << endl;

  return 0;
}