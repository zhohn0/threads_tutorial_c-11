#include <iostream>
#include <thread>

void function_1() {
    std::cout << "www.oxox.work" << std::endl;
}

int main() {
    std::thread t1(function_1);
    t1.detach();

    if (t1.joinable()) {
        t1.join();
    }

    return 0;
}

