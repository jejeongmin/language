#include <vector>
#include <iterator>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

/*
	알고리즘을 구현하다 보면 반복자에 대한 추가 정보가 필요할 때가 있다.
	예를 들어 반복자가 참조하는 원소의 타입을 알아야 임시값을 저장할 수도 있고, 반복자가 양방향인지 아니면 임의 접근 방식인지 알아야 할 수도 있다.
	c++ 은 이러한 정보를 찾을 수 있도록 iterator_traits 라는 클래스 템플릿을 제공한다.
	iterator_traits 클래스 템플릿에 원하는 반복자의 타입을 지정해서 인스턴스를 만들면
	value_type, difference_type, iterator_category, pointer, reference 라는 다섯 가지 타입 앨리어스 중 하나에 접근할 수 있다.
	이 예제에서는 IteratorType 타입의 반복자가 참조하는 타입으로 임시 변수를 선언한다.
	여기서 iterator_traits 가 나온 문장 앞에 typename 키워드를 적었다.
	한 개 이상의 템플릿 매개변수에 기반한 타입에 접근할 때는 반드시 typename 키워드를 명시적으로 지정해야 한다.
	이 예제에서는 템플릿 매개변수인 IteratorType 으로 value_type 이란 타입에 접근한다.
	종속적인 형식 이름은 'tyename' 접두어와 함께 사용해야 한다.
*/
template <typename IteratorType>
void iteratorTraitsTest(IteratorType it)
{
	typename std::iterator_traits<IteratorType>::value_type temp = *it;
	//auto temp = *it;
	cout << temp << endl;
}

int main()
{
	vector<int> v{ 5 };
	iteratorTraitsTest(cbegin(v));

	return 0;
}
