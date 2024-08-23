#include<iostream>
#include<thread>
using namespace std;

void func1()
{
     cout<<"子线程1"<<endl;
}
void func2(string name, int age)
{
    cout<<"子线程2, name: "<<name<<" age:"<<age<<this_thread::get_id()<<endl;
}


void test1()
{
    cout<<"主线程id:"<<this_thread::get_id()<<endl;
    //1.创建空的线程对象
    thread t1;
    //2.创建一个可用的子线程
    thread t2(func1);

    thread t3(func2, "漩涡", 18);

    thread t4([=](int id){
        cout<<"arg id: "<<id<<" thread id : "<<this_thread::get_id()<<endl;
    },1001);

    thread&& t5 = move(t4);
    //执行join阻塞主线程，防止主线程结束，子线程虚拟空间被释放
    t2.join();
    t3.join();

    // t5.detach();
    // cout << t5.get_id() << " =========== " << endl;
    // t5.join();//分离之后就阻塞不了主线程了
    //但是主线程退出后子线程还是会消失
    t5.join();
}
class Person
{
    // public:
    
};
int main()
{
    thread t1;//t1没有任务，和主线程没有关联
    cout << "t1 joinable: " << t1.joinable() << endl;
    thread t2(func1);

    cout << "before t2 joinable: " << t2.joinable() << endl;
    t2.join();//t2阻塞结束后就会被主线程释放，释放后t2就和主线程没有关联了
    cout << "after t2 joinable: " << t2.joinable() << endl;

    thread t3(func1);
    t3.detach();//失去关联
    cout << "t3 joinable: " << t3.joinable() << endl;

    int num = thread::hardware_concurrency();
    cout << "CPU number: " << num << endl;//获取CPU核心数

    return 0;
}