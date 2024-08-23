#include<iostream>
#include<thread>
#include<atomic>

using namespace std;
/*
    atomic支持bool，char，int，long，指针等，不支持浮点类型和复合类型
    不支持拷贝
*/
struct Base
{
public:
    Base(int n, string s):age(n), name(s){}
    int age;
    string name;
};


struct Counter
{
    void increment()
    {
        for (int i = 0; i < 100; ++i)
        {
            m_value++;
            cout << "increment number: " << m_value
                << ", theadID: " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }

    void decrement()
    {
        for (int i = 0; i < 100; ++i)
        {
            m_value--;
            cout << "decrement number: " << m_value
                << ", theadID: " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    // atomic<int> == atomic_int
    atomic<int> m_value{0};
};


int main()
{

 //   atomic<char> c('a');
    //atomic_char c1('a');
//    atomic<int> b;
    //atomic_init(&b,10);

    //c1 = 'd';
//    b.store(88);

    //char ccc = c.exchange('e');///ccc记录的是原来的值
    //Base base(123,"luffy");
    //atomic<Base*> atc_base(&base);//原子变量存不了复合类型，但可以存指针

////三种取值方式
    //cout <<"c value:" << c << endl;
    //cout <<"ccc value:"<<ccc<<endl;
    //cout<<"b value:"<<b.load()<<endl;
    //Base* tmp = atc_base;
    //cout<<"name :"<<tmp->name<<", age: "<<tmp->age<<endl;
    //b = 12;
    Counter c;
    thread t1(&Counter::increment, &c);
    thread t2(&Counter::decrement, &c);
    t1.join();
    t2.join();

    return 0;
}