#include <deque>
#include <functional>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond; // 条件遍量确保线程的正确执行顺序

//数据的生产者
void function_1() {
    int count = 10;
    while (count > 0) {
        std::unique_lock<std::mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        //cond.notify_one(); // 激活一个等待这个条件的线程
        cond.notify_all();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count--;
    }
}
//数据的消费者
void function_2() {
    int data = 0;
    while (data!=1) {
        std::unique_lock<std::mutex> locker(mu);
        //函数2可能会被伪激活，因此，传入lambda表达式作为第二个参数进行控制
        cond.wait(locker, []() {return !q.empty(); });
        data = q.back();
        q.pop_back();
        locker.unlock();
        std::cout << "t2 got a value from t1: " << data << std::endl;
    }
}

int main() {
    std::thread t1(function_1);
    std::thread t2(function_2);
    t1.join();
    t2.join();

}