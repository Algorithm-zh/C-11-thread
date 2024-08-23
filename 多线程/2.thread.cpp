#include<iostream>
#include<thread>
using namespace std;

void func1()
{
     cout<<"���߳�1"<<endl;
}
void func2(string name, int age)
{
    cout<<"���߳�2, name: "<<name<<" age:"<<age<<this_thread::get_id()<<endl;
}


void test1()
{
    cout<<"���߳�id:"<<this_thread::get_id()<<endl;
    //1.�����յ��̶߳���
    thread t1;
    //2.����һ�����õ����߳�
    thread t2(func1);

    thread t3(func2, "����", 18);

    thread t4([=](int id){
        cout<<"arg id: "<<id<<" thread id : "<<this_thread::get_id()<<endl;
    },1001);

    thread&& t5 = move(t4);
    //ִ��join�������̣߳���ֹ���߳̽��������߳�����ռ䱻�ͷ�
    t2.join();
    t3.join();

    // t5.detach();
    // cout << t5.get_id() << " =========== " << endl;
    // t5.join();//����֮��������������߳���
    //�������߳��˳������̻߳��ǻ���ʧ
    t5.join();
}
class Person
{
    // public:
    
};
int main()
{
    thread t1;//t1û�����񣬺����߳�û�й���
    cout << "t1 joinable: " << t1.joinable() << endl;
    thread t2(func1);

    cout << "before t2 joinable: " << t2.joinable() << endl;
    t2.join();//t2����������ͻᱻ���߳��ͷţ��ͷź�t2�ͺ����߳�û�й�����
    cout << "after t2 joinable: " << t2.joinable() << endl;

    thread t3(func1);
    t3.detach();//ʧȥ����
    cout << "t3 joinable: " << t3.joinable() << endl;

    int num = thread::hardware_concurrency();
    cout << "CPU number: " << num << endl;//��ȡCPU������

    return 0;
}