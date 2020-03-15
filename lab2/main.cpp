#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <unistd.h>

using namespace std;

mutex mtx;

class Process{
  private:
    int id;
    int num;
  public:
    Process(int num=0, int id=0){
      this->num = num;
      this->id = id;
    };
    ~Process(){

    }

    void increase(){
      this->num++;
    }

    int getNum() const {
      return this->num;
    }

    int getId(){
      return this->id;
    }
   

    /* Incapsulation breaking!
    int &getProcess(){
      return this->num;
    }*/
};



class CPU{
  private:
    int id;
    int count;
    bool busy;

  public:
    CPU(int id){
      this->id = id;
      this->busy = false;
    }
    ~CPU(){

    }

    void takeProcess(Process &p){
      this->busy = true;
      int random = rand()%100000;
      usleep(random);
      mtx.lock();
      cout << "Process " << p.getId() << " has been taken by " << this->id <<  " CPU with " << random << " time" << endl;
      mtx.unlock();
      this->busy = false;
    }

    void tryProcess(Process &p){
        if(!this->busy){
            takeProcess(p);
        }
    }

    bool isBusy(){
        return this->busy;
    }
};

void increaseAll(float *arr, int N){
  for(int i = 0; i < N; i++){
    arr[i]++;
  }
}

void printArray(float *arr, int N){
  for(int i = 0; i < N; i++){
    cout << arr[i] << " ";
  }
}

void action(CPU &c, Process &p){
  //p.increase();
  c.takeProcess(p);
}

void stub(){

}

int main(){
  srand(time(NULL));
  CPU cpu1(1);
  CPU cpu2(2);
  CPU cpu3(3);

  Process p1(0, 1), p2(-100, 2), p3(445, 3);

  // Checking methods and funcs 
  //cout << p1.getNum() << endl;
  //action(p1);
  //cout << p1.getNum() << endl;
  //cpu1.takeProcess(p1);
  //cout << p1.getNum() << endl;

  // Infinity loop
  float counts[3] = {0.0};
  float processed[3] = {0.0};

  thread threads[3];
  
// all go to CPU1
  for(int j = 0; j < 100; j++){
    counts[0]++;
    counts[1]++;
    counts[2]++;
    if(!cpu1.isBusy()){
      threads[0] = thread(action, ref(cpu1), ref(p1));
      processed[0]++;
    }else{
      threads[0] = thread(stub);
    }
    if(!cpu1.isBusy()){
      threads[1] = thread(action, ref(cpu1), ref(p2));
      processed[1]++;
    }else{
      threads[1] = thread(stub);
    }
    if(!cpu1.isBusy()){
      threads[2] = thread(action, ref(cpu1), ref(p3));
      processed[2]++;
    }else{
      threads[2] = thread(stub);
    }
    for(int i = 0; i < 3; i++){
      threads[i].join();
    }
  }

  // another
  /*
  for(int j = 0; j < 100; j++){
    counts[0]++;
    counts[1]++;
    counts[2]++;
    if(!cpu1.isBusy()){
      threads[0] = thread(action, ref(cpu1), ref(p1));
      processed[0]++;
    }else{
      threads[0] = thread(stub);
    }
    if(!cpu2.isBusy()){
      threads[1] = thread(action, ref(cpu2), ref(p2));
      processed[1]++;
    }else{
      threads[1] = thread(stub);
    }
    if(!cpu1.isBusy()){
      threads[2] = thread(action, ref(cpu1), ref(p3));
      processed[2]++;
    }else{
      threads[2] = thread(stub);
    }
    for(int i = 0; i < 3; i++){
      threads[i].join();
    }
  }
  
  
  */
  cout << endl;
  //printArray(processed, 3);
  //cout << endl;
  printArray(counts, 3);
  cout << endl;
  printArray(processed, 3);
  cout << endl;

  return 0;
}