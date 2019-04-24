#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <future>

int factorial(int N) {
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;
    std::cout << "Result is: " << res << std::endl;

    return res;
}

int main() {
    int x;
    /*std::thread t1(factorial, 4);*/

    //从子线程获取变量到主线程
    //std::future<int> fu = std::async(std::launch::async|std::launch::deferred, factorial, 4);
    std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
    x = fu.get();//get()函数会等待子线程结束，然后将返回值传给x.并且future对象只能被调用一次

    return 0;
}

