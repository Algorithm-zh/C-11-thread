#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
once_flag g_flag;

/*
    call_once是用mutex加锁实现的，所以是线程安全的
    被它修饰的函数只能使用一次
    void call_once( std::once_flag& flag, Callable&& f, Args&&... args );
    第一个参数保证这个对象能够被多个线程同时访问，不然就无法保证线程安全
    第二个参数是回调函数，由call_once调用，
    第三个参数是回调函数的参数
*/

//编写一个单例模式的类-->懒汉模式

class Base
{
public:
    Base(const Base& obj) = delete;
    Base& operator=(const Base& obj) = delete;
    static Base* getInstance()
    {
        //使用call_once包装创建实例，让其只能执行一次，实现单例模式
        call_once(g_flag, [&](){
            obj = new Base();
            cout << "实例对象被创建" << endl;     
        });
        return obj;
    }
    void set(string name)
    {
        this->name = name;
    }
    string get()
    {
        return name;
    }
private:
    Base() = default;
    static Base* obj;
    string name;
};
Base* Base::obj = nullptr;

void myFunc(string name)
{
    Base::getInstance()->set(name);
    cout << Base::getInstance()->get() << endl;
}
int main()
{

    thread t1(myFunc, "路费");
    thread t2(myFunc, "埃斯");
    thread t3(myFunc, "牛逼");

    t1.join();
    t2.join();
    t3.join();
	return 0;
}