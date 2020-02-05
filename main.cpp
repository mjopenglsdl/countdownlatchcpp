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