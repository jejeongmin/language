#include "pch.h"
#include "Dummy.h"


void AutoPtrFunction(auto_ptr<CDummy>& ptr)
{
	ptr->print();
}

/*
	raw pointer�� ��ü�� �����ϸ� �ش� smart ptr �ν��� ����� ������ ����..
	�̶�� �������, VS 2010 ~ VS2017 ������ raw pointer ���� �ڿ��� �� ������.
	�Ƹ� VS2008 �����̳�, Boost ������ �׷������� ������
	auto_ptr ��ü�� ���� deprecated spec �̾ �� ã�ƺ� �ʿ�� ������
*/
TEST(SmartPtrTest, AutoPtrTest)
{
	auto_ptr<CDummy> ptr1(new CDummy);
	auto_ptr<CDummy> ptr2;
	CDummy* ptr3 = NULL;

	ptr1->print();	// ȣ�� �� ��

	AutoPtrFunction(ptr1);	// ���������� �Լ��� �������� ������ �� �Լ� ȣ���� ���� �������� ptr1 �� ��ȿ���� ����ϰ� ����.

	ptr3 = ptr1.get();

	EXPECT_TRUE(ptr1.get() != nullptr);
	ptr1->print();	// ȣ�� �� ��

	EXPECT_TRUE(ptr3 != nullptr);
	ptr3->print();	// ȣ�� �� ��

	EXPECT_TRUE(ptr2.get() == nullptr);

	ptr2 = ptr1;	// ptr2 �� ������ ����, �� �������� ptr1 �� invalid

	EXPECT_TRUE(ptr2.get() != nullptr);
	ptr2->print();	// ȣ�� �� ��

	EXPECT_TRUE(ptr1.get() == nullptr);	// �̹� invalid �� ������ �̹Ƿ� ����

	ptr2.reset();
	EXPECT_TRUE(ptr2.get() == nullptr);	// �����͸� �ʱ�ȭ �ع������� ȣ�� �� ��
}

TEST(SmartPtrTest, SharedPtrTest)
{
	shared_ptr<CDummy> ptr1(new CDummy);
	vector<shared_ptr<CDummy>> dummys;

	EXPECT_TRUE(ptr1.get() != nullptr);
	ptr1->print();

	dummys.push_back(ptr1);
	dummys.push_back(ptr1);
	dummys.push_back(ptr1);

	for each (auto i in dummys)	// ��� shared_ptr�� ���ؼ� ������ ������ ���� ���� �� �������� ������ ��
	{
		EXPECT_TRUE(i.get() != nullptr);
		(*i).print();
	}
}

TEST(SmartPtrTest, UniquePtrTest)
{
	unique_ptr<CDummy>	ptr1(new CDummy);
	unique_ptr<CDummy>	ptr2;

	EXPECT_TRUE(ptr1.get() != nullptr);
	ptr1->print();

	ptr2 = move(ptr1);			// ptr1 �� ��ȿȭ ��
	EXPECT_TRUE(ptr1.get() == nullptr);
	EXPECT_TRUE(ptr2.get() != nullptr);
	ptr2->print();				// ȣ�� ����

	ptr2.reset();				// ptr2 �� ��ȿȭ ��

	EXPECT_TRUE(ptr1.get() == nullptr);	// ȣ�� ����
	EXPECT_TRUE(ptr2.get() == nullptr);	// ȣ�� ����
}
