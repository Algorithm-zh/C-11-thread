#include<iostream>
#include<thread>
#include<functional>
using namespace std;

void func1()
{
     cout<<"���߳�1"<<endl;
}
void func2(string name, int age)
{
    cout<<"���߳�2, name: "<<name<<" age:"<<age<<' '<<this_thread::get_id()<<endl;
}
class Base
{
public:
    void showMsg(string name, int age)
    {
        cout << "���߳�1, name: " << name << " age:" << age << ' ' << this_thread::get_id() << endl;
    }
    static void message()
    {
        cout << "���߳�2" << endl;
    }
};
int main()
{
    thread t1(func1);

    //���ݾ�̬�ĳ�Ա����
    thread tt(&Base::message);
    
    //���ݷǾ�̬��Ա����
    Base b;
    //ָ���Ǿ�̬������ַ��ָ�������ĸ���������Ҫ��ʵ��
    thread t2(&Base::showMsg, &b, "����", 20);
    thread t3(&Base::showMsg, b, "����", 20);//���ݵ�ַ���߶��󶼿���
    //���ð����󶨳�Ա�����Ͷ���
    thread t4(bind(&Base::showMsg, &b, "����", 20));
    thread t5(bind(&Base::showMsg, b, "����", 20));
    // thread t4(&Base::showMsg, &b, "����", 20);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0; 
}