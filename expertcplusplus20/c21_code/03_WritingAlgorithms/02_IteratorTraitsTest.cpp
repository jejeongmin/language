#include <vector>
#include <iterator>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

/*
	�˰����� �����ϴ� ���� �ݺ��ڿ� ���� �߰� ������ �ʿ��� ���� �ִ�.
	���� ��� �ݺ��ڰ� �����ϴ� ������ Ÿ���� �˾ƾ� �ӽð��� ������ ���� �ְ�, �ݺ��ڰ� ��������� �ƴϸ� ���� ���� ������� �˾ƾ� �� ���� �ִ�.
	c++ �� �̷��� ������ ã�� �� �ֵ��� iterator_traits ��� Ŭ���� ���ø��� �����Ѵ�.
	iterator_traits Ŭ���� ���ø��� ���ϴ� �ݺ����� Ÿ���� �����ؼ� �ν��Ͻ��� �����
	value_type, difference_type, iterator_category, pointer, reference ��� �ټ� ���� Ÿ�� �ٸ�� �� �ϳ��� ������ �� �ִ�.
	�� ���������� IteratorType Ÿ���� �ݺ��ڰ� �����ϴ� Ÿ������ �ӽ� ������ �����Ѵ�.
	���⼭ iterator_traits �� ���� ���� �տ� typename Ű���带 ������.
	�� �� �̻��� ���ø� �Ű������� ����� Ÿ�Կ� ������ ���� �ݵ�� typename Ű���带 ��������� �����ؾ� �Ѵ�.
	�� ���������� ���ø� �Ű������� IteratorType ���� value_type �̶� Ÿ�Կ� �����Ѵ�.
	�������� ���� �̸��� 'tyename' ���ξ�� �Բ� ����ؾ� �Ѵ�.
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
