#pragma once

template <typename T>
class Pointer
{
public:
	Pointer(T* ptr);
	virtual ~Pointer();

	// 대입과 값 전달 방식을 허용하지 않는다.
	Pointer(const Pointer<T>& src) = delete;
	Pointer<T>& operator=(const Pointer<T>& rhs) = delete;

	T& operator*();
	const T& operator*() const;
	
	T* operator->();
	const T* operator->() const;

	// () 변환 연산은 void* 로 반환하는 게, bool 로 반환하는 것보다 좋다.
	// bool 은 NULL 과는 비교과 되지만, nullptr 과는 비교가 되지 않는다.
	// 그리고 bool 로 반환이 가능하면, int, double 등의 값으로 의도치 않게 캐스팅 되는 결과를 초래한다.
	operator void*() const;

private:
	T* mPtr = nullptr;
};

template <typename T>
Pointer<T>::Pointer(T* ptr) : mPtr(ptr)
{
}

template <typename T>
Pointer<T>::~Pointer()
{
	delete mPtr;
	mPtr = nullptr;
}

template <typename T>
T& Pointer<T>::operator*()
{
	return *mPtr;
}

template <typename T>
const T& Pointer<T>::operator*() const
{
	return *mPtr;
}

template <typename T>
T* Pointer<T>::operator->()
{
	return mPtr;
}

template <typename T>
const T* Pointer<T>::operator->() const
{
	return mPtr;
}

template <typename T>
Pointer<T>::operator void*() const
{
	return mPtr;
}
