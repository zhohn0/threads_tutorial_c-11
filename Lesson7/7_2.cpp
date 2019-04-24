#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <future>

int factorial(std::future<int>& f) {
    int res = 1;
    int N = f.get();
    for (int i = N; i > 1; i--)
        res *= i;
    std::cout << "Result is: " << res << std::endl;

    return res;
}

int main() {
    int x;
    std::promise<int> p; //想要从主线程中传入子线程的变量
    std::future<int> f = p.get_future();

    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

    p.set_value(4);
    x = fu.get();
    std::cout << "Result from Child: " << x << std::endl;

    return 0;
}
