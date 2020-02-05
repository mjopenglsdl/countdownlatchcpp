#include <chrono>
#include "countdown_latch.hpp"

#include <iostream>

using namespace std;


CountdownLatch::CountdownLatch(uint32_t count) : count_(count)
{

}

CountdownLatch::~CountdownLatch()
{
    cout<<"CountdownLatch::~CountdownLatch()"<<endl;
}


void CountdownLatch::await(uint64_t nanosecs) 
{
    std::unique_lock<std::mutex> lck(mtx_);
    if (0 == count_){
        return;
    }

    if (nanosecs > 0) {
       cv_.wait_for(lck, std::chrono::nanoseconds(nanosecs));

    } else {
        while (count_ > 0)
        {
            cv_.wait(lck);
        }
    }
}

uint32_t CountdownLatch::get_count() 
{
    std::lock_guard<std::mutex> lck(mtx_);
    return count_;
}

void CountdownLatch::count_down() 
{
    std::unique_lock<std::mutex> lck(mtx_);
    if (0 == count_) {
        return;
    }

    --count_;

    if (0 == count_) {
        cv_.notify_all();
    }
}