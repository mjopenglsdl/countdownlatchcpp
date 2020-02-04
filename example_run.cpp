#include <unistd.h>
#include <thread>
#include <vector>
#include <iostream>
#include "countdown_latch.hpp"


void fun(clatch::CountdownLatch *cl) 
{
    cl->await();
    std::cout << "Wait is over " << std::endl;
}

int main(int argc, char* argv[]) 
{
    clatch::CountdownLatch cl(10);

    int i = 0;
    std::vector<std::thread*> ts;
    while (i++ < 2) {
        std::thread *t  = new std::thread(fun, &cl);
        ts.push_back(t);
    }

    i = 0;
    while (i++ < 10) {
        sleep(1);
        cl.count_down();
    }
    i = 0;

    while (i < 2) {
        ts[i++]->join();
    }
    i = 0;

    while (i < 2) {
        delete ts[i++];
    }

    return 0;
}
