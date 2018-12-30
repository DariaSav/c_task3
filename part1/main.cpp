#include <iostream>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>


int main() {
  size_t count = 0;
 // bool done = false;
  std::queue<int> items;
  std::mutex m;
  std::atomic_bool done(false);
  
  std::thread producer([&]() {

    
    for (int i = 0; i < 10000; ++i) {
      // ... some code may be here ...

      m.lock();
      items.push(i);
     // std::cout << "push" << std::endl;
      count++;
      m.unlock();
    }

    done = true;
  });

  std::thread consumer([&]() {

    while (!done) {
      while (!items.empty()) {

        m.lock();
        items.pop();
        //std::cout << "pop" << std::endl;
        // ...
        count--;
        m.unlock();
      }
    }
      while (!items.empty()) {

        m.lock();
        items.pop();
       // std::cout << "pop" << std::endl;
        // ...
        count--;
        m.unlock();
      }
  });

  producer.join();
  consumer.join();
  std::cout << count << std::endl;
}
