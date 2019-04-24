#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

class LofFile {
public:
    LofFile() {
        f.open("log.txt");
    }
    // 如果两个lock顺序不一样可能会发生死锁
    // 解决1：保证lock顺序一致
    // 解决2: 内置避免的解决方案， C++标准库
    void shared_print(std::string id, int value) {
        std::lock(m_mutex, m_mutex2);
        std::lock_guard<std::mutex> locker(m_mutex,std::adopt_lock);
        std::lock_guard<std::mutex> locker2(m_mutex2, std::adopt_lock);
        std::cout<< "From" << id << ": " << value << std::endl;
    }

    void shared_print2(std::string id, int value) {
        std::lock(m_mutex, m_mutex2);
        std::lock_guard<std::mutex> locker2(m_mutex2, std::adopt_lock);
        std::lock_guard<std::mutex> locker(m_mutex, std::adopt_lock);
        std::cout << "From" << id << ": " << value << std::endl;
    }

private:
    std::mutex m_mutex;
    std::mutex m_mutex2;
    std::ofstream f;
};

void function_1(LofFile& log) {
    for (int i = 0; i > -5; i--)
        log.shared_print("From t1: ", i);
}

int main() {
    LofFile log;
    std::thread t1(function_1, std::ref(log));
    for (int i = 0; i < 5; i++)
        log.shared_print2("From main: ", i);
    t1.join();
    return 0;
}