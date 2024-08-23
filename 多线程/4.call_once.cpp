#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
once_flag g_flag;

/*
    call_once����mutex����ʵ�ֵģ��������̰߳�ȫ��
    �������εĺ���ֻ��ʹ��һ��
    void call_once( std::once_flag& flag, Callable&& f, Args&&... args );
    ��һ��������֤��������ܹ�������߳�ͬʱ���ʣ���Ȼ���޷���֤�̰߳�ȫ
    �ڶ��������ǻص���������call_once���ã�
    �����������ǻص������Ĳ���
*/

//��дһ������ģʽ����-->����ģʽ

class Base
{
public:
    Base(const Base& obj) = delete;
    Base& operator=(const Base& obj) = delete;
    static Base* getInstance()
    {
        //ʹ��call_once��װ����ʵ��������ֻ��ִ��һ�Σ�ʵ�ֵ���ģʽ
        call_once(g_flag, [&](){
            obj = new Base();
            cout << "ʵ�����󱻴���" << endl;     
        });
        return obj;
    }
    void set(string name)
    {
        this->name = name;
    }
    string get()
    {
        return name;
    }
private:
    Base() = default;
    static Base* obj;
    string name;
};
Base* Base::obj = nullptr;

void myFunc(string name)
{
    Base::getInstance()->set(name);
    cout << Base::getInstance()->get() << endl;
}
int main()
{

    thread t1(myFunc, "·��");
    thread t2(myFunc, "��˹");
    thread t3(myFunc, "ţ��");

    t1.join();
    t2.join();
    t3.join();
	return 0;
}