#include <iostream>
#include <string>
#include <string_view>

using namespace std;

class Person
{
public:
	Person();
	Person(string_view firstName, string_view lastName, int age);
	Person(const Person& rhs);
	virtual ~Person();

	string_view getFirstName() const { return mFirstName; }
	string_view getLastName() const { return mLastName; }
	int getAge() const { return mAge; }

private:
	string mFirstName, mLastName;
	int mAge = 0;
};

Person::Person()
{
	cout << "Default Ctor" << endl;
}

Person::Person(string_view firstName, string_view lastName, int age)
	: mFirstName(firstName), mLastName(lastName), mAge(age)
{
	cout << "Ctor" << endl;
}

Person::~Person()
{
	cout << "dtor" << endl;
}

Person::Person(const Person& rhs)
	: mFirstName(rhs.mFirstName), mLastName(rhs.mLastName), mAge(rhs.mAge)
{
	cout << "Copy ctor" << endl;
}

ostream& operator<<(ostream& ostr, const Person& p)
{
	ostr << p.getFirstName() << " " << p.getLastName() <<
		" " << p.getAge() << endl;

	return ostr;
}


/*
void processPerson(Person p)
{
    // Person 타입 객체를 처리한다.
}
*/

void processPerson(const Person& /*p*/)
{
	// Person 타입 객체를 처리한다.
	// 그러나 레퍼런스 타입으로 받아 처리하기 때문에 인수전달 과정에서 성능손실이 없다.
}

Person createPerson()
{
	Person newP("Marc", "Gregoire", 38);
	return newP;
}

int main()
{
	Person me("Marc", "Gregoire", 38);
	processPerson(me);
	
	cout << "-----" << endl;

	cout << createPerson();

	cout << "-----" << endl;

	/*
		아래와 같은 호출의 경우, 리턴값을 받는 변수가 없어도, 임시객체가 생성되어 리턴값이 반환된다.
		그러나 컴파일러가 최적화 과정에서 불필요한 복제나 이동 연산을 최소화화기 위해 임시 변수를 제거한다.
		이와 같은 최적화를 RVO ( Return  Value Optimization ) 이라고 한다.
		이 예제를 Debug / Release 로 각각 빌드해서 실행 결과를 보면 그 차이를 확인할 수 있다.
	*/
	createPerson();

	return 0;
}
