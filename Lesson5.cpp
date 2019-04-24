#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

class LofFile {
public:
    LofFile() {
        //f.open("log.txt");
    }

    //延迟初始化( Lazy Initialization )
    void shared_print(std::string id, int value) {
        /*	{
                std::unique_lock<std::mutex> locker(m_mutex_open);
                if (!f.is_open()) {
                    f.open("log.txt");
                }
            }
    */
        /*当共享数据只有在初始化时才需要并发访问的保护，但在此之后却不需要显式同步时使用。
        此方法可以避免二次检查锁定（Double-Checked Locking)*/
        std::call_once( m_flag, [&]() {f.open("log.txt"); }); //

        //方便加解锁，但性能不如lock_guard
        std::unique_lock<std::mutex> locker(m_mutex,std::defer_lock);
        //....
        locker.lock();
        f << "From" << id << ": " << value << std::endl;
        locker.unlock();
        //.....

        //移动:在作用域之间转移锁的所有权
        std::unique_lock<std::mutex> locker2 = std::move(locker);

    }

private:
    std::mutex m_mutex;
    //std::mutex m_mutex_open;
    std::once_flag m_flag;
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
        log.shared_print("From main: ", i);

    t1.join();

    return 0;
}