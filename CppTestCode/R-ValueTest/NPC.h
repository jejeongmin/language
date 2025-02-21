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
		cout << "�⺻������" << endl;
	}

	NPC(int NpcCode, string Name)
	{
		cout << "�����ִ»�����" << endl;
		_NPCCode = NpcCode;
		_Name = Name;
	}

	NPC(NPC& other)
	{
		cout << "���������" << endl;
		_NPCCode = other._NPCCode;
		_Name = other._Name;
	}

	NPC& operator=(const NPC& npc)
	{
		cout << "���Կ�����" << endl;
		_NPCCode = npc._NPCCode;
		_Name = npc._Name;
		return *this;
	}

	NPC(NPC&& other)
	{
		cout << "Move ������" << endl;
	}

	NPC& operator=(const NPC&& npc)
	{
		cout << "Move ������" << endl;
		_NPCCode = npc._NPCCode;
		_Name = npc._Name;
		return *this;
	}
};