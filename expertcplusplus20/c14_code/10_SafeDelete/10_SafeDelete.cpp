#pragma once

/*
	https://jangpd007.tistory.com/89

	SAFE_DELETE 와 같은 매크로를 선언해서 썼는데, 이제는 그렇게 할 필요 없다.
	nullptr 에 대한 delete 는 SAFE 하다.

	c++98 에는 안그랬는데 언제부터 이랬던 거지?
*/


int main()
{
	char	*pTest = nullptr;

	// if (pTest)	delete pTest;

	delete pTest;

	return 0;
}