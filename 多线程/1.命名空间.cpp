#include<thread>
#include<iostream>
using namespace std;
//this_thread
//get_id(), sleep_for,sleep_until,yield
void func()
{
    cout<<"���̣߳�" << this_thread::get_id() << endl;
};
int main()
{
    cout<<"���̣߳�" << this_thread::get_id() << endl;
    thread t(func);
    t.join();
}