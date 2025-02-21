#include "namespaces.h"

using namespace mycode;

/*
	CrossFire 서버 만들면서 실수했다고 생각하는 내용 중 하나가 namespace 의 남용이다.
	이전에 플랫폼 쪽에서 라이브러리나 기반 프레임워크를 만들면서 namespace 를 통해
	기능을 분류하던 개발 습관을 관성적으로 따라갔다.

	다른 부서에 기능 코드를 제공할 일도 없고, 다른 부서로부터 기능 코드를 제공 받을 일도 없어
	name conflict 를 걱정할 필요도 없고, namespace 없이 충분히 제어 가능한데,
	괜히 서버나 기능 별로 namespace 를 쓴 탓에 불필요한 코딩량만 많아졌다.
*/

int main()
{
	mycode::foo();	// mycode 네임스페이스에 있는 "foo" 함수를 호출한다.
	foo();			// mycode::foo(); 와 같다.
	return 0;
}
