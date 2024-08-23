#include<iostream>
#include<thread>
#include<atomic>

using namespace std;
/*
    atomic֧��bool��char��int��long��ָ��ȣ���֧�ָ������ͺ͸�������
    ��֧�ֿ���
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

    //char ccc = c.exchange('e');///ccc��¼����ԭ����ֵ
    //Base base(123,"luffy");
    //atomic<Base*> atc_base(&base);//ԭ�ӱ����治�˸������ͣ������Դ�ָ��

////����ȡֵ��ʽ
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