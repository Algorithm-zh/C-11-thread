#include<iostream>
#include<mutex>
#include<chrono>
#include<thread>
using namespace std;
using namespace chrono;
/*
    多线程编程会出现对同一块内存读写的操作，
    同时写不行，同时读写也不行
    要保证线性操作，为了避免线程混乱，要对线程进行同步
    线程同步就是让线程按照先后顺序访问共享资源
    mutex是互斥锁，可以保证同一时间只有一个线程能访问
    注意事项：
        1.容易造成死锁，可以使用try_lock()方法
        2.使用lock_guard()，可以解决防止忘记解锁（但不能解决死锁，即同一线程两次加锁不解锁）的问题，和智能指针一样
        3.使用recursive_mutex(递归互斥锁)，可以锁多次,可以解决死锁问题
        独占互斥锁只能锁一次
     
*/
class Base
{
public:
    void increment(int count)
    {
        for (int i = 0; i < count; i++)
        {
            // mx.lock();
            {//加个大括号作用域，可以限定guard锁的作用域
                lock_guard<recursive_mutex> lg(mx);
                ++number;
                cout <<"++number:"<<number<<endl;
            }
           // mx.unlock();
            this_thread::sleep_for(chrono::milliseconds(500));//休眠0.5秒
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
            this_thread::yield();//线程让步,从运行态变为就绪态，但是它放弃时间片变为就绪态后会立马重新抢时间片，所以有可能下一轮还是它拥有时间片，概率问题
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
                cout<<"抢到了互斥锁所有权，线程ID:"<<this_thread::get_id()<<endl;
                tmx.unlock();
                break;//抢到互斥锁所有权，跳出循环
            }
            else
            {
                cout<<"没有抢到互斥锁所有权，线程id:"<<this_thread::get_id()<<endl;
                this_thread::sleep_for(chrono::milliseconds(50));
            }
        }
        //能拿到互斥锁资源返回true，如果到100ms还没拿到就返回false，不会一直阻塞下去
   }
private:
    int number = 999; 
    int count = 0;
    timed_mutex tmx;
    recursive_mutex mx;//对同一个资源加锁必须使用同一个锁
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
