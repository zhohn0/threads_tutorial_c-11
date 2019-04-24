#include <iostream>
#include <string>
#include <thread>
#include <mutex>
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

std::deque<std::packaged_task<int()>> task_q;
std::mutex mu;
/*由于task_q定义为全局，会存在主线程和子线程的数据竞争，所以需要引入条件变量进行保护*/
std::condition_variable cond;

void thread_1() {
    std::packaged_task<int()> t;
    {   //引入条件变量时，对应的所对象则应改为unique_lock
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, []() {return !task_q.empty(); });
        t = std::move(task_q.front());
    }
    t();
}

int main() {
    std::thread t1(thread_1);
    //形参类型要删除，将int(int)改为int()
    std::packaged_task<int()> t(std::bind(factorial, 6));
    std::future<int> ret = t.get_future();
    {
        std::lock_guard<std::mutex> locker(mu);
        task_q.push_back(std::move(t));
    }
    cond.notify_one();
    int value = ret.get();
    t1.join();
    return 0;
}

