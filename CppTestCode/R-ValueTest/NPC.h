#pragma once


#include <string>
#include <iostream>

using namespace std;

class NPC
{
public:
	int		_NPCCode = 0;
	string	_Name = "";

	NPC()
	{
		cout << "기본생성자" << endl;
	}

	NPC(int NpcCode, string Name)
	{
		cout << "인자있는생성자" << endl;
		_NPCCode = NpcCode;
		_Name = Name;
	}

	NPC(NPC& other)
	{
		cout << "복사생성자" << endl;
		_NPCCode = other._NPCCode;
		_Name = other._Name;
	}

	NPC& operator=(const NPC& npc)
	{
		cout << "대입연산자" << endl;
		_NPCCode = npc._NPCCode;
		_Name = npc._Name;
		return *this;
	}

	NPC(NPC&& other)
	{
		cout << "Move 생성자" << endl;
	}

	NPC& operator=(const NPC&& npc)
	{
		cout << "Move 연산자" << endl;
		_NPCCode = npc._NPCCode;
		_Name = npc._Name;
		return *this;
	}
};