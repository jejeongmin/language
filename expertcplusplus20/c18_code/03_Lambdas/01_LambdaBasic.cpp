#include <iostream>

using namespace std;

int main()
{
	// ���� ������ ���� ǥ����
	auto basicLambda = []{ cout << "Hello from Lambda" << endl; };
	basicLambda();

	// �Ű������� �ִ� ���� ǥ����
	auto parametersLambda = [](int value){ cout << "The value is " << value << endl; };
	parametersLambda(42);

	// ���� �����ϴ� ���� ǥ����
	auto returningLambda = [](int a, int b) -> int { return a + b; };
	int sum = returningLambda(11, 22);
	cout << "The result is " << sum << endl;

	// ���� �����ϴ� ���� ǥ����, ���� Ÿ���� ����
	auto returningLambda2 = [](int a, int b) { return a + b; };
	sum = returningLambda2(11, 22);
	cout << "The result is " << sum << endl;

	// ������ ������ ĸó�ϴ� ���� ǥ����
	double data = 1.23;
	auto capturingVLambda = [data]{ cout << "Data = " << data << endl; };
	capturingVLambda();

	// ���� ǥ������ �̸� ���� functor �� ��ȯ�ȴ�. �׸��� �� functor �� operator() �� �⺻������ const �� �����ȴ�.
	// ������ ���ĵ� ���� ǥ������ ������ �ᱹ �� functor ��ü�� ��� ������ �Ǵµ� �̸� �����ϱ� ���ؼ��� mutable ������ �Ǿ� �־�� non const �� ȣ�� �����ϰ� �ȴ�.
	// mutable �� �����ϴ� ��쿡�� �Ű������� ������ �ݵ�� () �Ұ�ȣ�� ����� �Ѵ�.
	auto capturingVLambda2 = [data] () mutable { data *= 2; cout << "Data = " << data << endl; };
	capturingVLambda2();

	// ������ ���۷����� ĸó�ϴ� ���� ǥ����
	auto capturingRLambda = [&data]{ data *= 2; };
	capturingRLambda();
	cout << "Data = " << data << endl;

	return 0;
}
