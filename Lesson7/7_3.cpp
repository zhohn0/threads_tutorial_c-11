#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <future>

int factorial(std::shared_future<int> f) {
    int res = 1;
    int N = f.get();
    for (int i = N; i > 1; i--)
        res *= i;
    std::cout << "Result is: " << res << std::endl;

    return res;
}

int main() {
    std::promise<int> p; //想要从主线程中传入子线程的变量
    std::future<int> f = p.get_future();
    std::shared_future<int> sf = f.share();//shared_future可以被拷贝

    std::future<int> fu = std::async(std::launch::async,factorial,sf);
    std::future<int> fu2 = std::async(std::launch::async,factorial, sf);
    std::future<int> fu3 = std::async(std::launch::async,factorial, sf);

    p.set_value(4);

    return 0;
}