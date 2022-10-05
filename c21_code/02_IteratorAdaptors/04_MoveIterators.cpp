#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

class MoveableClass
{
public:
	MoveableClass() {
		cout << "Default constructor" << endl;
	}
	MoveableClass(const MoveableClass& /* src */) {
		cout << "Copy constructor" << endl;
	}
	MoveableClass(MoveableClass&& /* src */) noexcept {
		cout << "Move constructor" << endl;
	}
	MoveableClass& operator=(const MoveableClass& /* rhs */) {
		cout << "Copy assignment operator" << endl;
		return *this;
	}
	MoveableClass& operator=(MoveableClass&& /* rhs */) noexcept {
		cout << "Move assignment operator" << endl;
		return *this;
	}
};

int main()
{
	vector<MoveableClass> vecSource;
	MoveableClass mc;					// 디폴트 생성자를 사용해서 MoveableClass 인스턴스인 mc를 생성한다.
	vecSource.push_back(mc);			// 첫번째 push_back 이 호출되면 복제(copy) 생성자를 불러서 mc 를 vector 로 복제한다.		
	vecSource.push_back(mc);			// 두번째 push_back 이 호출되면,
										// 두번째로 추가할 원소에 대한 공간을 확보하도록 vector 의 크기를 조정한다.
										// 이때 크기가 변경된 새 vector 에 기존 vector 의 원소를 이동시키기 위해 이동(move) 생성자가 호출된다.
										// 그리고 나서 mc 를 vector 의 두번째로 복제하도록 복제(copy) 생성자가 호출된다.
										// 이동 생성자와 복제 생성자의 호출 순서는 컴파일러의 vector 구현에 따라 달라질 수 있다.
	cout << "----" << endl;

	// vecSource의 원소를 vecOne으로 이동한다.
	vector<MoveableClass> vecOne(cbegin(vecSource), cend(vecSource));
	cout << "----" << endl;
	
	// vecSource의 원소를 vecTwo로 이동한다.
	vector<MoveableClass> vecTwo(make_move_iterator(begin(vecSource)),
								 make_move_iterator(end(vecSource)));

	// C++17의 생성자에 대한 템플릿 인수 추론 기능을 적용한 코드
	//vector<MoveableClass> vecTwo(move_iterator(begin(vecSource)),
	//							 move_iterator(end(vecSource)));

	cout << "----" << endl;

	return 0;
}
