#include<iostream>
#include<mutex>
#include<chrono>
#include<thread>
using namespace std;
using namespace chrono;
/*
    ���̱߳�̻���ֶ�ͬһ���ڴ��д�Ĳ�����
    ͬʱд���У�ͬʱ��дҲ����
    Ҫ��֤���Բ�����Ϊ�˱����̻߳��ң�Ҫ���߳̽���ͬ��
    �߳�ͬ���������̰߳����Ⱥ�˳����ʹ�����Դ
    mutex�ǻ����������Ա�֤ͬһʱ��ֻ��һ���߳��ܷ���
    ע�����
        1.�����������������ʹ��try_lock()����
        2.ʹ��lock_guard()�����Խ����ֹ���ǽ����������ܽ����������ͬһ�߳����μ����������������⣬������ָ��һ��
        3.ʹ��recursive_mutex(�ݹ黥����)�����������,���Խ����������
        ��ռ������ֻ����һ��
     
*/
class Base
{
public:
    void increment(int count)
    {
        for (int i = 0; i < count; i++)
        {
            // mx.lock();
            {//�Ӹ������������򣬿����޶�guard����������
                lock_guard<recursive_mutex> lg(mx);
                ++number;
                cout <<"++number:"<<number<<endl;
            }
           // mx.unlock();
            this_thread::sleep_for(chrono::milliseconds(500));//����0.5��
        }
        
    }

    void decrement(int count)
    {
        for (int i = 0; i < count; i++)
        {
            // mx.lock();
            {
                lock_guard<recursive_mutex> lg(mx);
                increment(2);
                --number;
                cout <<"--number:"<<number<<endl;
            }
           // mx.unlock();
            this_thread::yield();//�߳��ò�,������̬��Ϊ����̬������������ʱ��Ƭ��Ϊ����̬�������������ʱ��Ƭ�������п�����һ�ֻ�����ӵ��ʱ��Ƭ����������
        }
        
    }
    void work()
    {
        while(true)
        {
            if(tmx.try_lock_for(chrono::milliseconds(100)))
            {
                count++;
                this_thread::sleep_for(chrono::milliseconds(500));
                cout<<"�����˻���������Ȩ���߳�ID:"<<this_thread::get_id()<<endl;
                tmx.unlock();
                break;//��������������Ȩ������ѭ��
            }
            else
            {
                cout<<"û����������������Ȩ���߳�id:"<<this_thread::get_id()<<endl;
                this_thread::sleep_for(chrono::milliseconds(50));
            }
        }
        //���õ���������Դ����true�������100ms��û�õ��ͷ���false������һֱ������ȥ
   }
private:
    int number = 999; 
    int count = 0;
    timed_mutex tmx;
    recursive_mutex mx;//��ͬһ����Դ��������ʹ��ͬһ����
};
int main()
{
    Base b;
    thread t1(&Base::work,&b);
    thread t2(&Base::work,&b);
    t1.join();
    t2.join();


    return 0;
}
