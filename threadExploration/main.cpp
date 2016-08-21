// This program should be compiled on http://cpp.sh
// http://www.tutorialspoint.com/compile_cpp_online.php does not support threads

#include <iostream>       // endl not supported in cpp.sh
#include <thread>         // std::thread not supported on tutorialspoint
#include <mutex>

std::mutex mtx;           // mutex for critical section

void printValue (bool lock, int repetitions, int threadId, int *value) 
{
  // critical section (exclusive access to std::cout signaled by locking mtx):
  
  if (lock)
    mtx.lock();
  
  for (int i=0 ; i < repetitions; ++i) 
  {
      ++(*value) ;
      std::cout << threadId << " " << *value << " " << '\n' ;
  }
  std::cout << '\n' ;
  
  if (lock)
    mtx.unlock();
}

int main ()
{
  bool lock = false ;       // change for testing
  
  int repetitions = 200 ;
  int value = 0;
  
  std::thread th1 (printValue, lock, repetitions, 1, &value);
  std::thread th2 (printValue, lock, repetitions, 2, &value);

  th1.join();
  th2.join();

  return 0;
}
