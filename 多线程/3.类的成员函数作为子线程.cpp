#include<iostream>
#include<thread>
#include<functional>
using namespace std;

void func1()
{
     cout<<"子线程1"<<endl;
}
void func2(string name, int age)
{
    cout<<"子线程2, name: "<<name<<" age:"<<age<<' '<<this_thread::get_id()<<endl;
}
class Base
{
public:
    void showMsg(string name, int age)
    {
        cout << "子线程1, name: " << name << " age:" << age << ' ' << this_thread::get_id() << endl;
    }
    static void message()
    {
        cout << "子线程2" << endl;
    }
};
int main()
{
    thread t1(func1);

    //传递静态的成员函数
    thread tt(&Base::message);
    
    //传递非静态成员函数
    Base b;
    //指定非静态函数地址，指定属于哪个对象，所需要的实参
    thread t2(&Base::showMsg, &b, "张三", 20);
    thread t3(&Base::showMsg, b, "张三", 20);//传递地址或者对象都可以
    //可用绑定器绑定成员函数和对象
    thread t4(bind(&Base::showMsg, &b, "李四", 20));
    thread t5(bind(&Base::showMsg, b, "李四", 20));
    // thread t4(&Base::showMsg, &b, "张三", 20);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0; 
}