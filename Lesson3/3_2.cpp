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
    void shared_print(std::string id, int value){
        std::lock_guard<std::mutex> locker(m_mutex);
        f << "From"<< id << ": "<< value << std::endl;
    }
private:
    std::mutex m_mutex;
    std::ofstream f;
};

void function_1(LofFile& log) {
    for (int i = 0; i > -5; i--)
        log.shared_print("From t1: ",i);
}

/*在debug版本中依然会出现部分顺序错乱的现象，
但在release版本则完全正常，本人猜测是因为release中运算速度最优*/
int main() {
    LofFile log;
    std::thread t1(function_1, std::ref(log));

    for (int i = 0; i < 15; i++)
        log.shared_print("main: ", i);
    t1.join();
    return 0;
}