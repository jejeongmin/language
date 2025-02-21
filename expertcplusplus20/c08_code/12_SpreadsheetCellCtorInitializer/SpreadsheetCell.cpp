#include "SpreadsheetCell.h"

using namespace std;

/*
	��ü�� ũ�Ⱑ Ŭ ��� ���� �����ں��� ���� �����ڰ� �Ϲ������� ���� ȿ���� �� ����. ���� �����ڸ� ���� �����ϴ� �� ��õ�Ѵ�.
*/
SpreadsheetCell::SpreadsheetCell(double initialValue)
	: mValue(initialValue)		// �̷��� ȣ���� ��쿡�� ���� ������ ���� ���� �����ڸ� �̿��� �����Ѵ�.
{
	//mValue = initialValue;	// �̷��� ȣ���� ��쿡�� ���� ������ ���� ���� �����ڸ� �̿��� �����Ѵ�.
}

SpreadsheetCell::SpreadsheetCell(string_view initialValue)
	: mValue(stringToDouble(initialValue))
{
}

void SpreadsheetCell::setValue(double inValue)
{
	mValue = inValue;
}

double SpreadsheetCell::getValue() const
{
	return mValue;
}

void SpreadsheetCell::setString(string_view inString)
{
	mValue = stringToDouble(inString);
}

string SpreadsheetCell::getString() const
{
	return doubleToString(mValue);
}

string SpreadsheetCell::doubleToString(double inValue) const
{
	return to_string(inValue);
}

double SpreadsheetCell::stringToDouble(string_view inString) const
{
	return strtod(inString.data(), nullptr);
}
