#include <chrono>
#include "countdown_latch.hpp"


clatch::CountdownLatch::CountdownLatch(uint32_t count) {
   this->count_ = count; 
}

void clatch::CountdownLatch::await(uint64_t nanosecs) {
    std::unique_lock<std::mutex> lck(mtx_);
    if (0 == count_){
        return;
    }
    if (nanosecs > 0) {
       cv.wait_for(lck, std::chrono::nanoseconds(nanosecs));
    } else {
       cv.wait(lck);
    }
}

uint32_t clatch::CountdownLatch::get_count() {
    std::unique_lock<std::mutex> lck(mtx_);
    return count_;
}

void clatch::CountdownLatch::count_down() {
    std::unique_lock<std::mutex> lck(mtx_);
    if (0 == count_) {
        return;
    } 
    --count_;
    if (0 == count_) {
        cv.notify_all();
    }
}
