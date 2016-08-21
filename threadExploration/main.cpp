// This program should be compiled on http://cpp.sh
// http://www.tutorialspoint.com/compile_cpp_online.php does not support threads

#include <iostream>       // endl not supported in cpp.sh
#include <thread>         // std::thread not supported on tutorialspoint
#include <mutex>

#define THREAD_COUNT 5    // require that much threads

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
  bool lock = true ;       // change for testing
  
  int repetitions = 10 ;
  int value = 0;
  
  std::thread threads [THREAD_COUNT];
  
  for (int threadId = 0; threadId < THREAD_COUNT; ++threadId)
     threads[threadId] = std::thread (printValue, lock, repetitions, threadId, &value);
    
  for (auto & th : threads) 
     th.join();

  return 0;
}
