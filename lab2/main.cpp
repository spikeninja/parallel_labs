#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <unistd.h>

using namespace std;

class Process{
  private:
    int num;
  public:
    Process(int num=0){
      this->num = num;
    };
    ~Process(){

    }

    void increase(){
      this->num++;
    }

    int getNum() const {
      return this->num;
    }

    /* Incapsulation breaking!
    int &getProcess(){
      return this->num;
    }*/
};

void action(Process &p){
  p.increase();
}

class CPU{
  private:
    int id;

  public:
    CPU(int id){
      this->id = id;
    }
    ~CPU(){

    }

    void takeProcess(Process &p){
      thread t1(action, ref(p));
      t1.join();
    }
};



int main(){
  srand(time(NULL));
  CPU cpu1(1);
  CPU cpu2(2);
  CPU cpu3(3);

  Process p1(0);

  cout << p1.getNum() << endl;
  action(p1);
  cout << p1.getNum() << endl;
  cpu1.takeProcess(p1);
  cout << p1.getNum() << endl;

  return 0;
}