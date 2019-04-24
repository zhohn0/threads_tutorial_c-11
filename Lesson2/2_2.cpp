#include <iostream>
#include <thread>
#include <string>

void function_1() {
    std::cout << "www.oxox.work" << std::endl;
}

class Fctor {
public:
    void operator()(std::string& msg ) { //引用形式的参数
        for (int i = 0; i > -5; i--) {
            std::cout << "From t1: " << msg << std::endl;
            msg = "I love xuhuandaxue";
        }
    }
};

int main() {

    std::string s = "I love www.oxox.work";

    std::cout << std::this_thread::get_id() << std::endl;

    std::thread t1((Fctor()),std::ref(s) ); //字符串s为引用传递

    /* 下行代码在vs2017 community中调试时报错，
    显示没有相应的重载函数，暂未找出原因*/
    //std::thread t1((Fctor()),std::move(s) ); 

    std::cout << t1.get_id() << std::endl;

    std::thread t2 = std::move(t1);
    std::cout << t2.get_id() << std::endl; //id 依然与t1中相同，因为已经移进去

    t2.join();

    /*hardware_concurrency()，返回基于CPU数目或者CPU内核数目的
同一时刻在物理机器上运行的线程数*/
    std::cout <<"This PC has: " << std::thread::hardware_concurrency()
              << std::endl;
    return 0;
}