//
// Created by TolgaSanli on 09.01.2023.
//

#include "Semaphore.h"

Semaphore Semaphores(3);
void Semaphore::acquire() {
    unique_lock<mutex> a(mutexO);
    while(count == 0){
        conditionVariable.wait(a);
    }
    count--;
}

void Semaphore::release() {
    lock_guard<mutex> b(mutexO);
    count++;
    if(count > 0){
        conditionVariable.notify_one();
    }
}