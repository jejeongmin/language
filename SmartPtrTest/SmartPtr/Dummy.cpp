#include "StdAfx.h"
#include "Dummy.h"


CDummy::CDummy(void) : _arg1(0)
{
	cout << "constructor" << endl;
	memset(_buf, 0, sizeof(_buf));
}


CDummy::~CDummy(void)
{
	cout << "destructor" << endl;
}

void CDummy::print()
{
	cout << "dummy" << endl;
	cout << _arg1 << endl;
}