// EffectiveModernCpp.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "chapter.h"


int main()
{
	int		chaterNumber;

	std::cout << "input chater number : ";
	std::cin >> chaterNumber;

	auto chapter = chapter::makeChapter(chaterNumber);

	if (chapter != nullptr)
	{
		chapter->chapterMain();
	}
	
    return 0;
}

