#include<iostream>
#include<thread>
#include<queue>
#include<condition_variable>
#include<mutex>
using namespace std;
 


//���������
class TaskQueue
{
public:
    //�������
    void put(int task)
    { 
        //unique_lock<mutex> locker(myMutex);//unique_lock��lock_guard��࣬�����Զ������������ռ�Ļ�����
        // while(taskQueue.size() == maxSize))
        // {
            //notFull.wait(locker);//wait����֮ǰ���ͷ��Լ�ӵ�еĻ�������Դ��Ȼ����������wait������������������ȥ��������������֮��Ż��������ִ��
           
        // }   
        unique_lock<mutex> locker(myMutex);
        notFull.wait(locker, [=](){
            return taskQueue.size() != maxSize;//ֱ�ӽ��жϺ���д��wait�����ھͲ���Ҫд�ж��ˣ���Ϊwait�������Զ��ж�
        });

        taskQueue.push(task);
        cout<<"�������" << task << ", �߳�ID�� " << this_thread::get_id() << endl;
        //����һ��������
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
            return !taskQueue.empty();//����true������������false����
        });
        int node = taskQueue.front();
        taskQueue.pop();
        cout<<"ɾ������" << node << ", �߳�ID�� " << this_thread::get_id() << endl;
        //����ȫ��������(����ȫ������һ��������ν�ģ���Ϊȫ������֮��Ҳ���������)
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
    condition_variable notFull; //������
    condition_variable notEmpty; //������
};
//��������֤����ͬʱ���ʣ����������������һ���߳�


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