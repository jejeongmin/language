#pragma once

/*
	https://jangpd007.tistory.com/89

	SAFE_DELETE �� ���� ��ũ�θ� �����ؼ� ��µ�, ������ �׷��� �� �ʿ� ����.
	nullptr �� ���� delete �� SAFE �ϴ�.

	c++98 ���� �ȱ׷��µ� �������� �̷��� ����?
*/


int main()
{
	char	*pTest = nullptr;

	// if (pTest)	delete pTest;

	delete pTest;

	return 0;
}