#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <future>
#include <deque>

int factorial(int N) {
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;
    std::cout << "Result is: " << res << std::endl;
    return res;
}

int main() {
    //实现对线程的时间限制
    std::thread t1(factorial, 6);
    //std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
    std::this_thread::sleep_until(tp);

    ////实现对timed_mutex的时间限制
    std::timed_mutex mu;
    if (mu.try_lock_for(std::chrono::milliseconds(3)))
    {
        std::cout << "try lock: " << std::endl;
        mu.unlock();
    }

    if (mu.try_lock_until(tp))
    {
        std::cout << "lock until: " << std::endl;
        mu.unlock();
    }

    //实现对条件变量的时间限制
    std::mutex mu2;
    std::unique_lock<std::mutex> locker2(mu2);
    std::condition_variable cond;
    cond.wait_for(locker2, std::chrono::milliseconds(3));
    cond.wait_until(locker2, tp);

    //实现对future的时间限制
    std::promise<int> p;
    std::future<int> f = p.get_future();
    f.wait_for(std::chrono::milliseconds(3));
    f.wait_until(tp);

    t1.join();

    return 0;
}

