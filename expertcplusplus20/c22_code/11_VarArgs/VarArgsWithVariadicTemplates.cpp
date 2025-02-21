#include <iostream>
#include <string>
#include <string_view>

using namespace std;

void handleValue(int value)
{
	cout << "Integer: " << value << endl;
}
void handleValue(double value)
{
	cout << "Double: " << value << endl;
}
void handleValue(string_view value)
{
	cout << "String: " << value << endl;
}


// �� ���� ����� �̿��ϴ� ù ��° ����
void processValues()	// ���̽� ���̽�
{
	// ���̽� ���̽��� ���ؼ� Ư���� �� ���� ����.
}

template<typename T1, typename... Tn>
void processValues(T1 arg1, Tn... args)		// ������ ... �� �Ű����� ���� ǥ��
{
	handleValue(arg1);
	processValues(args...);		// ... �� ���� ���� �Ű����� �� Ǯ�� �����̴�.
}


// ������ ���۷��� ���� ����� �̿��ϴ� �� ��° ����
/*
	���� processValues �� ��������� ȣ���� ��, �Ű����� ������ �������鼭 ���� ������ ���� �� �ִ�.
	���۷����� Ȱ���ϸ� �� ������ ������ �� �ִ�.
	const ���۷����� �����ϸ�, ���ͷ� ���� ���ؼ��� ���۷����� ����� �� ������
	non-const ���۷����� ����ϸ鼭 ���ͷ� ���� ����ϰ� �Ϸ��� forward reference �� ����ϸ� �ȴ�.
	�Ʒ� �ڵ�� ������ ���۷����� T&& �� ����߰�, ��� �Ű������� ���� ����Ʈ �������� �����ϵ��� std::forward()�� ����ߴ�.
	���⼭ perfect fowarding �̶� processValue()�� ������rvalue �� ���޵Ǹ� ������ ���۷����� ������ǰ�,
	�������̳� ������ ���۷����� ���޵Ǹ� ������ ���۷����� ������ȴٴ� ���̴�.
*/

void processValuesRValueRefs()	// ���̽� ���̽�
{
	// ���̽� ���̽��� ���� Ư���� �� ���� ����.
}

template<typename T1, typename... Tn>
void processValuesRValueRefs(T1&& arg1, Tn&&... args)
{
	handleValue(std::forward<T1>(arg1));

	// �Ʒ� �ڵ�� �Ű� ���� �ѿ� �ִ� �� �μ��� std::forward()�� ȣ���ϰ�, �׵��� �ĸ��� �����ؼ� �и��Ѵ�.
	processValuesRValueRefs(std::forward<Tn>(args)...);

	// �Ű����� ���� ����ϴ� �Լ��� �ٵ� �ȿ��� �� �ѿ� ��� �μ��� ������ �˾Ƴ��� ���
	int numOfArgs = sizeof...(args);
}


/*
	�Ϲ������� ���ø��� �Ű������� ������ �����Ǿ� �ִ�.
	������ ���� �μ� ���ø��� ���ø� �Ű� ������ ������ ������ ���� �ʴ�.
	���� ��� ������ ���� ���ø� �Ű������� ������ �������� �ʰ� ������ �� �ִ�.
	�̶� Types ��� �Ű����� ��(parameter pack)�� ����Ѵ�.

	template<typename... Types> class MyVariadicTemplate {};

	typename �ڿ� ���� ... �� ���ڰ� �ƴ϶� ���� �μ� ���ø��� ���� �Ű����� ���� �����ϴ� �����̴�.
	�Ű����� ���� �پ��� ���� �μ��� ���� �� �ִ�. �� �� ���� ���̳� �ڿ� ������ �־ �ȴ�.
*/


int main()
{
	processValues(1, 2, 3.56, "test", 1.1f);
	cout << endl;
	processValuesRValueRefs(1, 2, 3.56, "test", 1.1f);

	return 0;
}
