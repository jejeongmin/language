#pragma once

template <typename T>
class Pointer
{
public:
	Pointer(T* ptr);
	virtual ~Pointer();

	// ���԰� �� ���� ����� ������� �ʴ´�.
	Pointer(const Pointer<T>& src) = delete;
	Pointer<T>& operator=(const Pointer<T>& rhs) = delete;

	T& operator*();
	const T& operator*() const;
	
	T* operator->();
	const T* operator->() const;

	// () ��ȯ ������ void* �� ��ȯ�ϴ� ��, bool �� ��ȯ�ϴ� �ͺ��� ����.
	// bool �� NULL ���� �񱳰� ������, nullptr ���� �񱳰� ���� �ʴ´�.
	// �׸��� bool �� ��ȯ�� �����ϸ�, int, double ���� ������ �ǵ�ġ �ʰ� ĳ���� �Ǵ� ����� �ʷ��Ѵ�.
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
