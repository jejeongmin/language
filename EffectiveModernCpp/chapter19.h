#pragma once

#include <functional>
#include <memory>


/*********************************************************
	std::shared_ptr �� ũ��� raw pointer �� 2 ���̴�.
	���� Ƚ���� ���� �޸𸮸� �ݵ�� �������� �Ҵ��ؾ� �Ѵ�.
	���� ȸ���� ������ ���Ұ� �ݵ�� ������ �����̾�� �Ѵ�.
**********************************************************/

using namespace std;

class Widget : public std::enable_shared_from_this<Widget>
{
public:
	void process();
};

class chapter19 : public chapter
{
	virtual int chapterMain()
	{
		auto longgingDel = [](Widget *pw)
							{
								// make log entry
								delete pw;
							};

		// Ŀ���� �������� ������ ������ ������ �Ϻθ� �̷��.
		std::unique_ptr<Widget, decltype(longgingDel)> upw(new Widget, longgingDel);

		// Ŀ���� �������� ������ ������ ������ �Ϻΰ� �ƴϴ�.
		std::shared_ptr<Widget> spw(new Widget, longgingDel);

		// shared_ptr �� Ŀ���� �������� ������ ������ ���Ŀ� ���Ե��� �ʱ� ������, �Ʒ��� ���� ���� �ٸ�
		// Ŀ���� �����ڸ� ���� �� ������ Ÿ���� ���� �����̳ʿ� ��� ���� �����ϴ�. �� �� �����ϴ�.
		auto customDeleter1 = [](Widget* pw) { /* doing A */ };
		auto customDeleter2 = [](Widget* pw) { /* doing B */ };

		std::shared_ptr<Widget> pw1(new Widget, customDeleter1);
		std::shared_ptr<Widget> pw2(new Widget, customDeleter2);

		std::vector<std::shared_ptr<Widget>> vpw{ pw1, pw2 };

		// ���� ȸ���� ���� ���(control block)�̶�� �θ��� �� ū �ڷᱸ���� �Ϻ��̴�.
		// std::shared_ptr �� �����ϴ� ��ü�� �ϳ��� �������� �����Ѵ�.
		// std::shared_ptr ���� �� Ŀ���� �����ڸ� �����ߴٸ�, ���� Ƚ���� �Բ� 
		// �� Ŀ���� �������� ���纻�� ���� ��Ͽ� ����.

		// ���� ����� �Ʒ��� ���� ��Ģ�� ���� �����ȴٰ� ������ ���ߵȴ�.
		// 1. std::make_shared �� �׻� ���� ����� �����Ѵ�.
		// 2. ���� ������ ������ ( std::unique_ptr �̳� std::auto_ptr ) �κ��� std::shared_ptr ��ü�� �����ϸ� ���� ����� �����ȴ�.
		// 3. raw pointer �� std::shared_ptr �����ڸ� ȣ���ϸ� ���� ����� �����ȴ�.

		// �� ��Ģ�� ���ϸ� �Ʒ� �ڵ�� ���� �߸��Ǿ���.
		auto aw = new Widget;

		std::shared_ptr<Widget> spw1(aw);
		std::shared_ptr<Widget> spw2(aw);

		// �� �ڵ忡 ���ϸ� aw �� spw1, spw2 �� ���� �� ���� �������� �����Ѵ�.
		// �ϳ��� ��ü�� ���� �� ���� ���� ȸ���� ������, aw �� �ı��� 2�� �õ��ȴ�.
		// �̴� ����� ���ǵ��� ���� �ൿ�̴�.
		// �̸� ���ϱ� ���ؼ��� std::shared_ptr �����ڿ� raw pointer �� �Ѱ��ִ� ���� ���ϰų�,
		// �̸� ���� �� ���ٸ�, �Ʒ��� �ڵ�� ���� ���� new �� ����� ���� �����϶�� ���̴�.
		std::shared_ptr<Widget> spw3(new Widget);

		return 0;
	}
};

std::vector<std::shared_ptr<Widget>> processedWidgets;

/*
	std::shared_ptr �� �����Ǵ� �����̳ʿ� this �� �̿��ؼ�, emplace_back - ���� �� ���� - �ϴ� ����� �߸��� ����̴�.
	�� �ڵ�� �������� ������, raw pointer �� this �� �̿��ؼ� std::shared_ptr ���� �����̳ʿ� �Ѱ��شٴ� �������� �ִ�.
	�� ������ ����Ī�� Widget ��ü ���� �� ���� ����� ��������� �ǰ�, �̴� �߸��� ���� ī������ ������ �ȴ�.

	shared_ptr API ���� �ٷ� �̷� ��Ȳ�� Ư���� ������ �����ϰ� �ִ�.
	std::enable_shared_from_this ��� ���ø��ε�, �� Ŭ������ this �����ͷκ��� std::shared_ptr �� �����ϰ� �����Ϸ���
	�� ���ø��� �� Ŭ������ ��� Ŭ������ ������ �ȴ�.
	std::enable_shared_from_this �� ���� ��ü�� ����Ű�� std::shared_ptr �� �����ϵ� ���� ����� ���������� �ʴ� ��� �Լ� �ϳ��� �����Ѵ�.
	�� ��� �Լ��� �̸��� shared_from_this() �̴�.
*/
void Widget::process()
{
	//processedWidgets.emplace_back(this);				// �߸��� ��
	processedWidgets.emplace_back(shared_from_this());	// �ٸ� ��
}

/*
	shared_ptr �� ���� ����� ��� ���� ������, �̵��� �����ϸ� �� ����� ����� �����Ҹ��ϴ�.
	�׷����� �ұ��ϰ� ����� �����ȴٸ�, �켱�� ������ ������ �� �ʿ��������� �����غ� �ʿ䰡 �ִ�.
	���� ������(unique_ptr) �� ����ϴٸ�, ������� �ݵ�� ������� �ʴ��ϴ����
	unique_ptr �� �صθ� shared_ptr �� '���׷��̵�' �ϱ�� ����.
	�ٸ� �� �ݴ�� ���� �ƴϹǷ�, ������ �ʿ䰡 �ִ�.

	�׸��� shared_ptr �� �� �� ���� �Ϸδ� �迭 ������ �ִ�.
	std::unique_ptr ���� �� �ٸ� ��������, std::shared_ptr �� API �� ���� ��ü�� ����Ű�� �����͸�
	���ο� �ΰ� ����Ǿ��ٴ� ����̴�. std::shared_ptr<T[]> ���� �� ����.
	�̷� ��� ���� �迭�� ���� �پ��� ��� - �̸��׸� array, vector, string - �� �����Ѵ�.
	array �� ��� �ʿ��� �� �;�����, shared_ptr �� ����� ����ϴ� ��쿡�� �迭��� ����
	��ʰ� �� �� �ְڴ�.

	std::shared_ptr �� ������ ���� �ڿ��� ������ ���ϰ� (�������÷��ǿ� �ñ� ����ŭ�̳�) ������ �� �ִ� ������ �����Ѵ�.

	��ü�� std::shared_ptr ��ü�� �� ũ�Ⱑ std::unique_ptr ��ü�� �� ���̸�, ���� ��Ͽ� ���õ� �߰� �δ��� �����ϸ�,
	������ ���� Ƚ�� ������ �䱸�Ѵ�.

	�ڿ��� �⺻������ delete �� ���� �ı��ǳ�, Ŀ���� �����ڵ� �����ȴ�. �������� ������ std::shared_ptr ��
	���Ŀ��� �ƹ��� ���⵵ ��ġ�� �ʴ´�.

	raw pointer ������ �����κ��� std::shared_ptr �� �����ϴ� ���� ���ؾ� �Ѵ�.

	by jeongminje
	
	shared_ptr �� by ref �� ������ ���� ref count �� �������� �ʴ´�.
	�ܼ� �����ϴ� ��쿡�� �ӵ��� ���ؼ��� �̰� �ּ��̳�, �������� �����ϱ� ���ؼ� �ѱ� ����
	�ݵ�� by copy �� ���� �Ѱܾ� �Ѵ�.

	shared_ptr �� ���� ī���� ��ü(�� ��Ȯ���� ������� ���ؼ�)�� ���ؼ��� ��Ƽ�����带 �����ϳ�,
	�����Ǵ� ��ü ��ü�� ���� ��Ƽ������ ������ �����ϴ� �� �ƴϴ�. ( 2017.12 ���� ����, c++20 ������ ���� ���� )

	https://www.slideshare.net/zzapuno/multithread-sharedptr
	http://en.cppreference.com/w/cpp/memory/shared_ptr
	https://stackoverflow.com/questions/44552738/race-condition-in-shared-ptr-doesnt-happen
*/