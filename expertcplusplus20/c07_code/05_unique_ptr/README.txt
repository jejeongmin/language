unique_ptr 은 단독 소유권을 표현하기 때문에 복사할 수 없다.
std::move 를 이용한 이동은 가능하다.

reset() 을 이용하면, unique_ptr 내부 포인터를 해제하고, 필요하다면 이를 다른 포인터로 변경할수 있다.
ex)
mysimplePtr.reset();
mysimplePtr.reset(new Simple());

release() 를 이용하면, unique_ptr 와 내부 포인터의 관계를 끊을 수 있다.
Simple* ptr = mysimplePtr.reset();
delete ptr;
ptr = nullptr;