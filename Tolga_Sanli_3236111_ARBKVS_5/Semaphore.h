//
// Created by TolgaSanli on 09.01.2023.
//

#ifndef TOLGA_SANLI_3236111_ARBKVS_5_SEMAPHORE_H
#define TOLGA_SANLI_3236111_ARBKVS_5_SEMAPHORE_H

#include <mutex>
#include <condition_variable>
#include <atomic>
using namespace std;

class Semaphore {
private:
    atomic<int> count;
    mutex mutexO;
    condition_variable conditionVariable;

public:
    Semaphore(int a) : count(a){}
    void acquire();
    void release();

};


#endif //TOLGA_SANLI_3236111_ARBKVS_5_SEMAPHORE_H
