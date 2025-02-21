#include "pch.h"
#include "NPC.h"

/*
	vs 2022 ���� �����Ͻ� 
	npc1 ��ü �������� ���
	�ڵ� ����ȭ�� ���� �ӽ� ��ü ������ �̷����� �ʰ�, ���� �����ڷ� �ٷ� �Ѿ��.

	npc2 ��ü �������� ����
	npc1�� �޸� ��ü �����ڿ��� �ӽ� ��ü�� ������� �ʰ�, ��������� npc1 �� ����ϱ� ������
	�����Ϸ��� ���� �ڵ� ����ȭ���� �ʰ�, ��������� ���� �����ڰ� ȣ��Ǵ� ���� Ȯ���� �� �ִ�.	
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
	vs 2022 ���� �����Ͻ� npc6 ��ü �������� ���
	�ڵ� ����ȭ�� ���� �ӽ� ��ü ������ �̷����� �ʰ�, ���� �����ڷ� �ٷ� �Ѿ��.	
*/
TEST(ConstructorTest, TestName3)
{
	NPC npc6 = NPC(12, "Orge3");

	EXPECT_EQ(npc6._NPCCode, 12);
	EXPECT_EQ(npc6._Name, "Orge3");
}

/*
	npc8 ��ü �������� ���
	R������ ���� R ���� �����ڰ� ȣ��ȴ�.
*/
TEST(ConstructorTest, TestName4)
{
	NPC npc7; NPC npc8;
	npc8 = std::move(npc7);
}