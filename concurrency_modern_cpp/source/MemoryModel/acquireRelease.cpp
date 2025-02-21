// acquireRelease.cpp

#include <atomic>
#include <thread>
#include <iostream>
#include <string>

using namespace std;
 
atomic<string*> ptr;
int data;
atomic<int> atoData;
 
void producer(){
    string* p  = new string("C++11");
    data = 2011;
    atoData.store(2014, memory_order_relaxed);
    ptr.store(p, memory_order_release);
}
 
/*
	���� �Ʒ� ���� memory_order_acquire �� memory_order_consume �� ���
	�Ʒ� �ּ� ó���� �κб��� Ȱ��ȭ�Ǿ�� �� �ڵ�� ��Ȯ�� ���ư��� �ڵ���.

	memory_order_acquire �� memory_order_consume �� ���̸� �巯���� �κ�.

	memory_order_consume �� t1, t2 �� ������ �ڵ� ���� Ư�� ���� ����ȭ��
	������������ �� ����ȭ �ڵ带 ���ķ� �� �ڵ� ������ ���������� �ʴ´�.
*/
void consumer(){
    string* p2;
	//int		data2;
    while (!(p2 = ptr.load(memory_order_acquire)));
	//while (!(data2 = atoData.load(memory_order_acquire)));
    cout << "*p2: " << *p2 << endl;
    cout << "data: " << data << endl;
	//cout << "data: " << data2 << endl;
    cout << "atoData: " << atoData.load(memory_order_relaxed) << endl;
}
 
int main(){
    
    cout << endl;
    
    thread t1(producer);
    thread t2(consumer);
    
    t1.join();
    t2.join();
    
    cout << endl;
    
}
