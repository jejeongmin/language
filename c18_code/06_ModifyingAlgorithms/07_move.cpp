#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

using namespace std;

/*
	move 연산을 수행하는 동안에는 원본 객체 중 일부는 유효한 상태에 있고 나머지는
	불확실한 상태에 있게 된다.
	아래의  예제에 vecSrc 에 대해 move 연산을 수행한 뒤 여기에 담긴 모든 원소를
	불확실한 객체로 만들지 않았다면 그 원소를 사용하면 안된다.
	예를 들어 아무 사전 조건 없이 그 객체에 대해 setString()과 같은
	메서드를 호출하면 안된다.
*/
class MyClass
{
public:
	MyClass() = default;
	MyClass(const MyClass& src) = default;
	MyClass(string_view str) : mStr(str) {}
	virtual ~MyClass() = default;
	
	// 이동 대입 연산자
	MyClass& operator=(MyClass&& rhs) noexcept {
		if (this == &rhs)
			return *this;
		mStr = std::move(rhs.mStr);
		cout << "Move operator= (mStr=" << mStr << ")" << endl;
		return *this;
	}
	
	void setString(string_view str) { mStr = str; }
	string_view getString() const { return mStr; }

private:
	string mStr;
};

int main()
{
	vector<MyClass> vecSrc{ MyClass("a"), MyClass("b"), MyClass("c") };
	vector<MyClass> vecDst(vecSrc.size());
	move(begin(vecSrc), end(vecSrc), begin(vecDst));
	for (const auto& c : vecDst) { cout << c.getString() << " "; }

	return 0;
}
