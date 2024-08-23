#include<iostream>
#include<thread>
#include<queue>
#include<condition_variable>
#include<mutex>
using namespace std;
 


//任务队列类
class TaskQueue
{
public:
    //添加数据
    void put(int task)
    { 
        //unique_lock<mutex> locker(myMutex);//unique_lock和lock_guard差不多，可以自动解锁，管理独占的互斥锁
        // while(taskQueue.size() == maxSize))
        // {
            //notFull.wait(locker);//wait阻塞之前会释放自己拥有的互斥锁资源，然后再阻塞在wait处，解除阻塞后会重新去抢互斥锁，抢到之后才会继续向下执行
           
        // }   
        unique_lock<mutex> locker(myMutex);
        notFull.wait(locker, [=](){
            return taskQueue.size() != maxSize;//直接将判断函数写到wait函数内就不需要写判断了，因为wait函数会自动判断
        });

        taskQueue.push(task);
        cout<<"添加任务：" << task << ", 线程ID： " << this_thread::get_id() << endl;
        //唤醒一个消费者
        notEmpty.notify_one();
    }
    void take()
    {
        //unique_lock<mutex> locker(myMutex);
        //while(taskQueue.empty())
        //{
            //notEmpty.wait(locker);
        //}

        unique_lock<mutex> locker(myMutex);
        notEmpty.wait(locker, [=](){
            return !taskQueue.empty();//返回true不阻塞，返回false阻塞
        });
        int node = taskQueue.front();
        taskQueue.pop();
        cout<<"删除任务：" << node << ", 线程ID： " << this_thread::get_id() << endl;
        //唤醒全部生产者(唤醒全部或者一个是无所谓的，因为全部唤醒之后也会进行阻塞)
        notFull.notify_all();
    }
    bool isFull()
    {
        lock_guard<mutex> locker(myMutex);
        if(maxSize == taskQueue.size())
        {
            return true;
        }
        return false;
    }
    bool isEmpty()
    {
        lock_guard<mutex> locker(myMutex);
        if(taskQueue.size() == 0)
        {
            return true;
        }
        return false;
    }
    int taskSize()
    {
        lock_guard<mutex> locker(myMutex);
        return taskQueue.size();
    }
    
private:
    int maxSize = 100;
    queue<int> taskQueue;
    mutex myMutex;
    condition_variable notFull; //生产者
    condition_variable notEmpty; //消费者
};
//互斥锁保证不会同时访问，条件变量解决阻塞一类线程


int main()
{

    thread t1[5];
    thread t2[5];
    TaskQueue TaskQ;
    for (int i = 0; i < 5; i++)
    {
        t1[i] = thread(&TaskQueue::put, &TaskQ, 100 + i);
        t2[i] = thread(&TaskQueue::take, &TaskQ); 
    }
    for (int i = 0; i < 5; i++)
    {
        t1[i].join();
        t2[i].join();
    }
     
    return 0;
}