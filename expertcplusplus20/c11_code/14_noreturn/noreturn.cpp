#include <cstdlib>
#include <iostream>

/*
	어트리뷰트란 특정 밴더에서만 제공하는 정보나 옵션을 소스 코드에 추가하는 매커니즘이다.
	c++ 표준에 어트리뷰트가 추가되기 전에는 밴더마다 __attribute, __declspec, __fallthough 같은 속성을 나름대로 정의했었다.
	c++11부터는 이러한 속성을 모두 이중 대괄호를 이용하여 표기하도록 표준화했다.

	[[noreturn]]		: 함수가 호출한 측으로 제어를 의도적으로 리턴하지 않는다는 것을 의미
	[[deprecated]]		: 더 이상 권장하지 않는 대상을 지정할 때 사용
	[[fallthrough]]		: switch 문에서 의도적으로 fallthough 를 적용하고 싶을 때 사용(break 지정하지 않음을 의미)
	[[nodiscard]]		: 함수를 이용하는 코드에서 리턴 값을 사용하지 않을 때 경고 메시지가 발생, ex) [[nodiscard]] int func()
	[[maybe_unused]]	: 사용하지 않는 매개변수 코드를 발견해도 경고 메시지를 출력하지 말라고 컴파일러에 지시할 때 사용, ex) int func([[maybe_unused]] int param)
*/

[[noreturn]] void forceProgramTermination()
{
	std::exit(1);
}

bool isDongleAvailable()
{
	bool isAvailable = false;
	// 라이센싱 동글을 사용할 수 있는지 확인한다.
	return isAvailable;
}

bool isFeatureLicensed(int /*featureId*/)
{
	if (!isDongleAvailable()) {
		// 라이센싱 동글을 발견하지 못했다면 프로그램을 중단한다.
		forceProgramTermination();
	} else {
		bool isLicensed = false;
		// 사용할 수 있는 동글이 있다면 주어진 기능에 대해 라이센스가 있는지 확인한다.
		return isLicensed;
	}
}

int main()
{
	bool isLicensed = isFeatureLicensed(42);
	std::cout << isLicensed << std::endl;
}