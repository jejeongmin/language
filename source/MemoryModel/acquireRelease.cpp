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
	만약 아래 행의 memory_order_acquire 가 memory_order_consume 인 경우
	아래 주석 처리된 부분까지 활성화되어야 이 코드는 정확히 돌아가는 코드임.

	memory_order_acquire 와 memory_order_consume 의 차이를 드러내는 부분.

	memory_order_consume 은 t1, t2 두 스레드 코드 간의 특정 지점 동기화는
	보장해주지만 그 동기화 코드를 전후로 한 코드 순서를 보장해주진 않는다.
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
