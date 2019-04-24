#include <iostream>
#include <thread>
#include <string>

void function_1() {
    std::cout << "www.oxox.work" << std::endl;
}

class Fctor {
public:
    void operator()(std::string& msg ) { //引用形式的参数
        std::cout << "From t1: " << msg << std::endl;
        msg = "I love xuhuandaxue";

    }
};

int main() {

    std::string s = "I love www.oxox.work";

    //在线程t1中传入类的第一种方式
    /*Fctor fct;
    std::thread t1(fct,s);*/

    //在线程t1中传入类的第二种方式,与第一种等效

    //std::thread t1((Fctor()),s); //字符串s为值传递
    std::thread t1((Fctor()), std::ref(s)); //字符串s为引用传递

    std::cout << "From main: " << s << std::endl;

    try {
        for (int i = 0; i < 5; i++)
        {
            std::cout << "From main: " << i << std::endl;
        }

    }
    catch (...) {
        t1.join();  //此行调用join()
        throw;
    }

    t1.join(); //此行也要写join()，否则会出现 absort()错误

    return 0;
}
