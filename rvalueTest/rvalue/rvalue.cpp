// rvalue.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class NPC
{
public:
	int NPCCode;
	string Name;

	NPC() { cout << "기본생성자" << endl; }
	NPC( int _NpcCode, string _Name ) { cout << "인자있는생성자" << endl; }
	NPC(NPC& other) { cout << "복사생성자" << endl; }
	NPC& operator=(const NPC& npc) { cout << "대입연산자" << endl; return *this; }
	NPC(NPC&& other) { cout << "Move 생성자" << endl; }
	NPC& operator=(const NPC&& npc) { cout << "Move 연산자" << endl; return *this; }
};

int main()
{
	/*
		아래 1번코드는 VS2010 나왔던 당시에 작성했던 코드이다.
		인자 있는 생성자 -> Move 생성자 순으로 호출되는 게 당시 코드인데,
		VS2017 에 이르러서는 컴파일러에서 코드 레벨의 최적화가 이뤄진 듯 하다.
		인자 있는 생성자 만 호출되고 Move 생성자가 호출되지  않는다.
	*/
	cout << "1" << endl;
	NPC npc1( NPC( 10,"Orge1") );

	cout << endl << "2" << endl;
	NPC npc2(11,"Orge2");
	NPC npc3 = npc2;

	cout << endl << "3" << endl;
	NPC npc4; NPC npc5;
	npc5 = npc4;

	cout << endl << "4" << endl;
	NPC npc6 = NPC(12, "Orge3");

	cout << endl << "5" << endl;
	NPC npc7; NPC npc8;
	npc8 = std::move(npc7);

	getchar();
	return 0;
}



