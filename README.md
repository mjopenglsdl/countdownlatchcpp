CountdownLatch for C++ multi-threaded programming
================================================

**CountdownLatch in C++**

-----------------------
countdownlatch is a C++ library providing similar functionalities as availble with standard Java
CountdownLatch class. It's main usage is: it allows one or more threads to wait until a set of
operations being performed on other threads completes.


**Below is an example regarding how to use the library**

---

```c++
#include <thread>
#include <vector>
#include <iostream>

#include "countdown_latch.hpp"

using namespace std;


void test_fun(std::shared_ptr<CountdownLatch> p_patch, size_t sleep_sec) 
{
    // count down after thread finished
    std::this_thread::sleep_for(std::chrono::seconds(sleep_sec));
    cout<<"!!! counts: "<<p_patch->get_count()<<endl;
    p_patch->count_down();
}


int main(int argc, char* argv[]) 
{
    std::vector<std::thread> v_thds;

    constexpr size_t kThdCount = 5;
    std::shared_ptr<CountdownLatch> p_patch = std::make_shared<CountdownLatch>(kThdCount);

    // push 2 threads
    for(size_t i = 0; i < kThdCount; ++i){
        v_thds.push_back( std::thread(test_fun, p_patch, i) );
    }
    
    // wait here
    p_patch->await();
    cout << "Wait is over " << endl;

    // final join
    for(size_t i = 0; i < kThdCount; ++i){
        v_thds[i].join();
    }

    return 0;
}

```