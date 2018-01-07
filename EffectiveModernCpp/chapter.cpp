#include "stdafx.h"
#include "chapter.h"
#include "chapter01.h"
#include "chapter02.h"
#include "chapter03.h"
#include "chapter04.h"
#include "chapter05.h"
#include "chapter06.h"
#include "chapter07.h"
#include "chapter08.h"
#include "chapter09.h"
#include "chapter10.h"
#include "chapter11.h"
#include "chapter12.h"
#include "chapter13.h"
#include "chapter14.h"
#include "chapter15.h"
#include "chapter16.h"
#include "chapter17.h"
#include "chapter18.h"
#include "chapter19.h"
#include "chapter20.h"
#include "chapter21.h"
#include "chapter22.h"
#include "chapter23.h"
#include "chapter24.h"
#include "chapter25.h"

std::shared_ptr<chapter> chapter::makeChapter(int index)
{
	switch (index)
	{
	case 1:
		return std::make_shared<chapter01>();
	case 2:
		return std::make_shared<chapter02>();
	case 3:
		return std::make_shared<chapter03>();
	case 4:
		return std::make_shared<chapter04>();
	case 5:
		return std::make_shared<chapter05>();
	case 6:
		return std::make_shared<chapter06>();
	case 7:
		return std::make_shared<chapter07>();
	case 8:
		return std::make_shared<chapter08>();
	case 9:
		return std::make_shared<chapter09>();
	case 10:
		return std::make_shared<chapter10>();
	case 11:
		return std::make_shared<chapter11>();
	case 12:
		return std::make_shared<chapter12>();
	case 13:
		return std::make_shared<chapter13>();
	case 14:
		return std::make_shared<chapter14>();
	case 15:
		return std::make_shared<chapter15>();
	case 16:
		return std::make_shared<chapter16>();
	case 17:
		return std::make_shared<chapter17>();
	case 18:
		return std::make_shared<chapter18>();
	case 19:
		return std::make_shared<chapter19>();
	case 20:
		return std::make_shared<chapter20>();
	case 21:
		return std::make_shared<chapter21>();
	case 22:
		return std::make_shared<chapter22>();
	case 23:
		return std::make_shared<chapter23>();
	case 24:
		return std::make_shared<chapter24>();
	case 25:
		return std::make_shared<chapter25>();
	default:
		return nullptr;
	}

	return nullptr;
}