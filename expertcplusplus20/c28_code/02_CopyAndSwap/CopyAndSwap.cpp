#include "CopyAndSwap.h"
#include <utility>

CopyAndSwap::~CopyAndSwap()
{
	// �Ҹ��� ���� �ڵ�
}

CopyAndSwap::CopyAndSwap(const CopyAndSwap& src)
{
	// �� ���� �����ڴ� ���� �ʿ��� ���ҽ� �Ҵ� �۾��� ���� �����ڿ� �����Ѵ�.
	// �ڼ��� ������ 9���� Spreadsheet ���� �ڵ带 �����Ѵ�.

	// ������ ����� ��� �����Ѵ�.
}

void swap(CopyAndSwap& first, CopyAndSwap& second) noexcept
{
	using std::swap;  // <utility>�� ��Ŭ����ؾ� �Ѵ�.

	// ������ ����� ��� �¹ٲ۴�. ���� ��� ������ ���� �ۼ��Ѵ�.
	// swap(first.mData, second.mData);
}

/*
	���� �� �¹ٲٱ� �������� ó���ؾ� �����ϴ�.
	������ ���� ������ ���� �¹ٲ� �ӽ� ������ �����. �� �������� ����(����)�� ����� ������ ����Ǵ��� ���� ��ü�� ����� ������ ����.
	���ܰ� �߻����� ���� ���길���� swap �� �Ѵ�. swap �� noexcept �� �����ؾ� �ϸ�, �׷��� �ٸ� ǥ�ض��̺귯���� ȣȯ�� ����� �� �ִ�.
	chapter 9 �� ���õ� ������ ������ �� �ڼ��� �����Ƿ� ������ ��
*/
CopyAndSwap& CopyAndSwap::operator=(const CopyAndSwap& rhs)
{
	// �ڱ� �ڽ� ���� ���� Ȯ��
	if (this == &rhs) {
		return *this;
	}

	auto copy(rhs);  // ��� �۾��� �ӽ� �ν��Ͻ����� ó���Ѵ�.
	swap(*this, copy); // �ͼ����� ������ �ʴ� �������θ� �۾� ����� �ݿ��Ѵ�.
	return *this;
}


int main()
{
	CopyAndSwap myFirstInstance;
	CopyAndSwap mySecondInstance;
	mySecondInstance = myFirstInstance;

	return 0;
}
