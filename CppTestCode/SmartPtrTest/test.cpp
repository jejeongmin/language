#include "pch.h"
#include "Dummy.h"


void AutoPtrFunction(auto_ptr<CDummy>& ptr)
{
	ptr->print();
}

/*
	raw pointer로 객체를 리턴하면 해당 smart ptr 로써의 기능을 버리는 것임..
	이라고 써놨으나, VS 2010 ~ VS2017 에서는 raw pointer 리턴 뒤에도 잘 동작함.
	아마 VS2008 이전이나, Boost 에서는 그랬으리라 짐작함
	auto_ptr 자체가 이제 deprecated spec 이어서 더 찾아볼 필요는 못느낌
*/
TEST(SmartPtrTest, AutoPtrTest)
{
	auto_ptr<CDummy> ptr1(new CDummy);
	auto_ptr<CDummy> ptr2;
	CDummy* ptr3 = NULL;

	ptr1->print();	// 호출 잘 됨

	AutoPtrFunction(ptr1);	// 참조형으로 함수를 선언하지 않으면 이 함수 호출이 끝난 시점에서 ptr1 은 유효성을 상실하고 만다.

	ptr3 = ptr1.get();

	EXPECT_TRUE(ptr1.get() != nullptr);
	ptr1->print();	// 호출 잘 됨

	EXPECT_TRUE(ptr3 != nullptr);
	ptr3->print();	// 호출 잘 됨

	EXPECT_TRUE(ptr2.get() == nullptr);

	ptr2 = ptr1;	// ptr2 로 소유권 이전, 이 순간부터 ptr1 은 invalid

	EXPECT_TRUE(ptr2.get() != nullptr);
	ptr2->print();	// 호출 잘 됨

	EXPECT_TRUE(ptr1.get() == nullptr);	// 이미 invalid 한 포인터 이므로 실패

	ptr2.reset();
	EXPECT_TRUE(ptr2.get() == nullptr);	// 포인터를 초기화 해버렸으니 호출 안 됨
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

	for each (auto i in dummys)	// 모든 shared_ptr에 대해서 동일한 원본에 대한 참조 와 소유권이 유지가 됨
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

	ptr2 = move(ptr1);			// ptr1 이 무효화 됨
	EXPECT_TRUE(ptr1.get() == nullptr);
	EXPECT_TRUE(ptr2.get() != nullptr);
	ptr2->print();				// 호출 성공

	ptr2.reset();				// ptr2 도 무효화 됨

	EXPECT_TRUE(ptr1.get() == nullptr);	// 호출 실패
	EXPECT_TRUE(ptr2.get() == nullptr);	// 호출 실패
}
