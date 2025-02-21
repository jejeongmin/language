#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <list>
#include <regex>

/*********************************************************
emplace_back �Լ��� �־��� �μ��� �̿��ؼ� std::vector �ȿ��� ���� std::string �� �����Ѵ�.
�� ������ ���ܳ��� �ӽð�ü�� ����.

�̷� ���� ����(emplacement) �Լ����� ���� �Լ��麸�� ������ �پ �����
�������̽��� �� �����ϴٴ� ���̴�. ���� �Լ����� ������ ��ü�� ������
���� ���� �Լ��� ������ ��ü�� �����ڵ��� ���� �μ����� �޴´�.
�̷��� ���� ������ ���� ���� �Լ����� ���� �Լ������� �� �ʿ��� �� �ִ�
�ӽ� ��ü�� ������ �ı��� ���Ѵ�.
**********************************************************/

using namespace std;

class chapter42 : public chapter
{
	class Widget
	{
	};

	virtual int chapterMain()
	{
		std::vector<std::string>	vs;
	
		// �Ʒ� �������� �Լ����� ���� �����Լ��� ���� �Լ����� �� ���� ������ �� �ִ� ���ǵ��� �����Ѵ�.
		// ���ǵ��� �Ʒ� ���� ����� ������ ��
		vs.emplace_back("xyzzy");
		vs.emplace_back(50, 'x');


		std::list<std::shared_ptr<Widget>>	ptrs;

		// push_back �ϸ鼭 shared_ptr ��ü�� �ӽ÷� �����ȴ�.
		// ���� �������� Widget �� ���� �޸� �Ҵ��� �����ϴ��� out of memory ���ܰ� ���ĵǸ鼭
		// �ӽð�ü�� �ı��ǰ� �ڵ����� �����Ǵ� widget ��ü�� �����ȴ�.
		ptrs.push_back(std::shared_ptr<Widget>(new Widget, [](Widget* pWidget) {}));

		// ���� list �� ���Ե� ������, shared_ptr �� �������� �ʴ´�.
		// Widget ��ü�� ���� �����Ǵµ�, �̶� out of memory ���ܰ� �߻��Ѵٸ�,
		// Widget ��ü�� �������� �� ������ ����.
		// emplace �迭 �Լ��� out of memory ���� �������� �������� ������ �ִ�.
		ptrs.emplace_back(new Widget, [](Widget* pWidget) {});

		// �� ������ �ذ��� ������ �Ʒ��� ����.
		// �ᱹ �������� �Լ� ������ �뵵�� ���� ����, �������� �Ἥ ������ ���ذ��ǵ�..
		// �̷� �ٿ� emplace_ �迭 �Լ��� out of memory �� ������ �� �ִ� ����� ���� Ÿ�Կ� ���ؼ���
		// �ƿ� �Ⱦ��� �� ���� �ʳ�.. �ϱ� ���α׷� ¥�鼭 out of memory �޴� ���� �󸶳� �ȴٰ�..
		std::shared_ptr<Widget> spw1(new Widget);
		ptrs.emplace_back(std::move(spw1));

		// �׸��� ���� ���� ���ٴ� �Ʒ� ������ �� �����ϴ�.
		std::shared_ptr<Widget> spw2 = make_shared<Widget>();
		ptrs.emplace_back(std::move(spw2));

		std::vector<std::regex>	regexes;

		// ����������� c style ���ڿ��κ��� std::regex �� �����Ϸ��� ���� ū ����� �ʿ��� �� �����Ƿ�
		// const char* �� �޴� std::regex �����ڴ� explicit �� ����Ǿ� �ִ�. �׷��� �Ʒ� �ڵ�� �������� �ȵȴ�. 
		//std::regex	r = nullptr;
		//std::regex	r = "[A-Z]+";
		//regexes.push_back(nullptr);
		//regexes.push_back("[A-Z]+");

		// �Ʒ� �ڵ�� �����ϵ�����, �����ϴ� �ڵ�� �ƴϴ�.
		// emplace �� Ư���� regex �� ������ �μ��� ������ ���̴�.
		regexes.emplace_back(nullptr);
		regexes.emplace_back("[A-Z]+");

		// �����ڸ� ���� �����ʱ�ȭ(direct initialization) �� ���縦 ���� ���� �ʱ�ȭ(copy initialization)��
		// ���� ���еǾ� ������, explicit �� ���� �ʱ�ȭ�� �����Ѵ�.
		// emplace �迭 �Լ��� �����ʱ�ȭ�� �ϱ� ������ explicit �� ���� ������ ���� �ʰ� �����ϵǴ� ���̴�.
		std::regex	r1("[A-Z]+");
		//std::regex	r1 = "[A-Z]+";

		return 0;
	}
};

/*
	�̷�������, ���� ���� �Լ����� ���� �ش� ���� �������� �� ȿ�����̾�� �ϸ�,
	�� ȿ������ ���� ����� ����� �Ѵ�. -> �׷��� ǥ�� �����ڵ鿡 ���� �׷� ���� �߻��Ѵ�.

	����������, ����
		1) �߰��ϴ� ���� �����̳ʷ� �����Ǵ� ���� �ƴ϶� �����ǰ�,
		2) �μ� ����(��)�� �����̳ʰ� ��� ���İ� �ٸ���
		3) �� ���� �ߺ��� ���̾ �����̳ʰ� �ź����� �ʴ´ٸ�,
	���� �����Լ��� ���� �Լ����� ���� ���ɼ��� ���� ũ��.

	���� ���� �Լ��� ���� �Լ���� �źδ����� ���� ��ȯ���� ������ �� �ִ�.
*/