#include <cstdlib>
#include <iostream>

/*
	��Ʈ����Ʈ�� Ư�� ��������� �����ϴ� ������ �ɼ��� �ҽ� �ڵ忡 �߰��ϴ� ��Ŀ�����̴�.
	c++ ǥ�ؿ� ��Ʈ����Ʈ�� �߰��Ǳ� ������ ������� __attribute, __declspec, __fallthough ���� �Ӽ��� ������� �����߾���.
	c++11���ʹ� �̷��� �Ӽ��� ��� ���� ���ȣ�� �̿��Ͽ� ǥ���ϵ��� ǥ��ȭ�ߴ�.

	[[noreturn]]		: �Լ��� ȣ���� ������ ��� �ǵ������� �������� �ʴ´ٴ� ���� �ǹ�
	[[deprecated]]		: �� �̻� �������� �ʴ� ����� ������ �� ���
	[[fallthrough]]		: switch ������ �ǵ������� fallthough �� �����ϰ� ���� �� ���(break �������� ������ �ǹ�)
	[[nodiscard]]		: �Լ��� �̿��ϴ� �ڵ忡�� ���� ���� ������� ���� �� ��� �޽����� �߻�, ex) [[nodiscard]] int func()
	[[maybe_unused]]	: ������� �ʴ� �Ű����� �ڵ带 �߰��ص� ��� �޽����� ������� ����� �����Ϸ��� ������ �� ���, ex) int func([[maybe_unused]] int param)
*/

[[noreturn]] void forceProgramTermination()
{
	std::exit(1);
}

bool isDongleAvailable()
{
	bool isAvailable = false;
	// ���̼��� ������ ����� �� �ִ��� Ȯ���Ѵ�.
	return isAvailable;
}

bool isFeatureLicensed(int /*featureId*/)
{
	if (!isDongleAvailable()) {
		// ���̼��� ������ �߰����� ���ߴٸ� ���α׷��� �ߴ��Ѵ�.
		forceProgramTermination();
	} else {
		bool isLicensed = false;
		// ����� �� �ִ� ������ �ִٸ� �־��� ��ɿ� ���� ���̼����� �ִ��� Ȯ���Ѵ�.
		return isLicensed;
	}
}

int main()
{
	bool isLicensed = isFeatureLicensed(42);
	std::cout << isLicensed << std::endl;
}