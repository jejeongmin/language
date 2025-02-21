#include "pch.h"
#include "NPC.h"

/*
	vs 2022 에서 컴파일시 
	npc1 객체 생성자의 경우
	코드 최적화에 의해 임시 객체 생성이 이뤄지지 않고, 인자 생성자로 바로 넘어간다.

	npc2 객체 생성자의 경우는
	npc1과 달리 객체 생성자에서 임시 객체를 사용하지 않고, 명시적으로 npc1 을 사용하기 때문에
	컴파일러에 의해 자동 최적화되지 않고, 명시적으로 복사 생성자가 호출되는 것을 확인할 수 있다.	
*/
TEST(ConstructorTest, CopyConstructorTest)
{
	NPC npc1(NPC(10, "Orge1"));

	NPC npc2(npc1);
		
	EXPECT_EQ(npc1._NPCCode, 10);
	EXPECT_EQ(npc1._Name, "Orge1");
}

TEST(ConstructorTest, AssignmentConstructorTest)
{
	NPC npc2(11, "Orge2");
	NPC npc3 = npc2;

	EXPECT_EQ(npc2._NPCCode, 11);
	EXPECT_EQ(npc2._NPCCode, npc3._NPCCode);

	EXPECT_EQ(npc2._Name, "Orge2");
	EXPECT_EQ(npc2._Name, npc3._Name);
}

TEST(ConstructorTest, DefaultConstructorTest)
{
	NPC npc4; NPC npc5;
	npc5 = npc4;

	EXPECT_EQ(npc4._NPCCode, 0);
	EXPECT_EQ(npc4._NPCCode, npc5._NPCCode);

	EXPECT_EQ(npc4._Name, "");
	EXPECT_EQ(npc4._Name, npc5._Name);
}

/*
	vs 2022 에서 컴파일시 npc6 객체 생성자의 경우
	코드 최적화에 의해 임시 객체 생성이 이뤄지지 않고, 인자 생성자로 바로 넘어간다.	
*/
TEST(ConstructorTest, TestName3)
{
	NPC npc6 = NPC(12, "Orge3");

	EXPECT_EQ(npc6._NPCCode, 12);
	EXPECT_EQ(npc6._Name, "Orge3");
}

/*
	npc8 객체 생성자의 경우
	R참조에 의해 R 참조 생성자가 호출된다.
*/
TEST(ConstructorTest, TestName4)
{
	NPC npc7; NPC npc8;
	npc8 = std::move(npc7);
}