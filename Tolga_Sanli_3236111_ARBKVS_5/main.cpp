#include <iostream>
#include <thread>
#include <mutex>
#include <process.h>
#include "Semaphore.h"

using namespace std;

//Class mutex mit dem Objekt mutex0, Prozess mit wechselseitiger Ausschluss -> Process t, block, process t2...
mutex mutexO;
//Class Semaphore mit dem Objekt semaphore, Prozess mit multithreads. D.h. mehrere threads können gleichzeitig bedient werden
Semaphore semaphore(3);

void t1(){
    mutexO.lock( );
    for(char chars = 'a'; chars <= 'z'; chars++){
        cout << chars << " ";
    }
    cout << " " << endl;
    mutexO.unlock();
}
void t2(){
    mutexO.lock();
    for(int i = 0; i < 33; i++){
        cout << i << " ";
    }
    cout << " " << endl;
    mutexO.unlock();
}
void t3(){
    mutexO.lock();
    for(char chars = 'A'; chars <= 'Z'; chars++){
        cout << chars << " ";
    }
    cout << " " << endl;
    mutexO.unlock();
}
void mutexProcess(){
    thread mutexT1(t1);
    thread mutexT2(t2);
    thread mutexT3(t3);
    mutexT1.join();
    mutexT2.join();
    mutexT3.join();
}

void semaphoreT1(){
    semaphore.acquire();
    for(char chars = 'a'; chars <= 'z'; chars++){
        cout << chars << " ";
    }
    cout << " " << endl;
    semaphore.release();
}
void semaphoreT2(){
    semaphore.acquire();
    for(int i = 0; i < 33; i++){
        cout << i << " ";
    }
    cout << " " << endl;
    semaphore.release();
}
void semaphoreT3(){
    semaphore.acquire();
    for(char chars = 'A'; chars <= 'Z'; chars++){
        cout << chars << " ";
    }
    cout << " " << endl;
    semaphore.release();
}

void semaphoreProcess(){
    thread semaphoreT1p(semaphoreT1);
    thread semaphoreT2p(semaphoreT2);
    thread semaphoreT3p(semaphoreT3);
    semaphoreT1p.join();
    semaphoreT2p.join();
    semaphoreT3p.join();
}

void unsynchront1(){
    for(char chars = 'a'; chars <= 'z'; chars++){
        cout << chars << " ";
    }
    cout << " " << endl;
}
void unsynchront2(){
    for(int i = 0; i < 33; i++){
        cout << i << " ";
    }
    cout << " " << endl;
}
void unsynchront3(){
    for(char chars = 'A'; chars <= 'Z'; chars++){
        cout << chars << " ";
    }
    cout << " " << endl;
}

void unsynchronProcess(){
    thread unsynchronT1p(unsynchront1);
    thread unsynchronT2p(unsynchront2);
    thread unsynchronT3p(unsynchront3);
    unsynchronT1p.join();
    unsynchronT2p.join();
    unsynchronT3p.join();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    cout << "unsynchron threads:" << endl;
    unsynchronProcess();
    cout << "mutex threads:" << endl;
    mutexProcess();
    cout << "semaphor threads:" << endl;
    semaphoreProcess();

    return 0;
}
