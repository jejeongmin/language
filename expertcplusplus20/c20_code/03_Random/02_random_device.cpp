#include <iostream>
#include <random>

using namespace std;

/*
	random_device 엔진은 소프트웨어 기반이 아니다.
	컴퓨터에 특수 하드웨어가 장착돼 있어야 쓸 수 있는 비결정적 무작위수 발생기이다.
	다이오드, 사운드 카드 등과 같은 하드웨어의 물리적인 노이즈를 이용해 무작위수를 발생시킨다.
	심지어 방사성 동위 원소의 자연 붕괴를 이용한 장치도 있다.

	random_device 의 규격을 보면 현재 사용하는 컴퓨터에 특수 하드웨어가 없을 때는
	소프트웨어 알고리즘 중 지원되는 것을 적용하게 되어 있다.

	무작위수 발생기의 성능은 entropy 로 측정한다.
	소프트웨어 기반일 때는 0 을, 하드웨어 장치를 이용할 때는 0 이 아닌 값을 반환한다.

	random_device 는 대체로 의사 무작위수를 생성 엔진보다 느리다.
	그래서 생성해야 할 무작위수가 아주 많다면, 의사 무작위수 생성 엔진을 사용하고
	random_device 는 이 엔진의 시드를 생성하는 데만 사용한느 것이 좋다.
*/
int main()
{
	random_device rnd;
	cout << "Entropy: " << rnd.entropy() << endl;
	cout << "Min value: " << rnd.min()
		<< ", Max value: " << rnd.max() << endl;
	cout << "Random number: " << rnd() << endl;

	return 0;
}
