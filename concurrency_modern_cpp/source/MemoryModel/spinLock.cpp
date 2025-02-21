// spinLock.cpp

#include <atomic>
#include <thread>

/*
	std::atomic<bool> �� ��ü���� ����
*/

class Spinlock{
  std::atomic_flag flag;	// c++11 �����̾ deprecated ��
public:
  Spinlock(): flag(ATOMIC_FLAG_INIT){}

  void lock(){
    while( flag.test_and_set() );
  }

  void unlock(){
    flag.clear();
  }
};

Spinlock spin;

void workOnResource(){
  spin.lock();
  // shared resource
  spin.unlock();
}


int main(){

  std::thread t(workOnResource);
  std::thread t2(workOnResource);

  t.join();
  t2.join();

}

