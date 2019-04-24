#include <iostream>
#include <string>
#include <thread>
#include <mutex>

/*method1 & method2中都要用到的互斥对象的定义*/
std::mutex mu;

/*通过互斥对象同步cout，但如果输出异常，mu将永远地锁住，不推荐使用*/
void shared_print(std::string msg, int id) {
    mu.lock();
    std::cout << msg << id << std::endl;
    mu.unlock();
}

/*通过lock_guard同步cout,无论是否发生异常，函数调用结束后，mu对象都能自动地被解锁。
但cout作为全局变量，并没有完全在mu的保护下，仍然会被其他线程在不加锁的情况下调用*/
/*
void shared_print(std::string msg, int id) {
    std::lock_guard<std::mutex> guard(mu);
    std::cout << msg << id << std::endl;
}
*/

void function_1() {
    for (int i = 0; i > -100; i--) {
        shared_print("From t1: ", i);
    }
}

int main() {
    std::thread t1(function_1);
    for (int i = 0; i < 100; i++) {
        shared_print("From main: ", i);
    }
    t1.join();
    return 0;
}