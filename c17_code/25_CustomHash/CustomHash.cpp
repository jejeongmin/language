#include <cstddef>
#include <unordered_set>
#include <functional>
#include <iostream>

using namespace std;

class IntWrapper
{
public:
	IntWrapper(int i) : mWrappedInt(i) {}
	int getValue() const { return mWrappedInt; }

private:
	int mWrappedInt;
};

/*
	비정렬 연관 컨테이너에서는 키에 대한 operator== 연산을 반드시 제공해야 한다.
*/
bool operator==(const IntWrapper& lhs, const IntWrapper& rhs)
{
	return lhs.getValue() == rhs.getValue();
}

/*
	IntWrapper 에 대한 해시 함수는 std::hasp 템플릿을 IntWrapper 에 대해 특수화하는 방식으로 구현한다.
*/
namespace std
{
	template<> struct hash<IntWrapper>
	{
		using argument_type = IntWrapper;
		using result_type = size_t;

		result_type operator()(const argument_type& f) const {
			return std::hash<int>()(f.getValue());
		}
	};
}

int main()
{
	unordered_set<IntWrapper> s;
	s.insert(IntWrapper(1));
	s.insert(IntWrapper(2));

	for (const auto& element : s) {
		cout << element.getValue() << endl;
	}

	return 0;
}
