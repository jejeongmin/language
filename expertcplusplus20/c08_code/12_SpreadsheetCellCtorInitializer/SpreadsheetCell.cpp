#include "SpreadsheetCell.h"

using namespace std;

/*
	객체의 크기가 클 경우 대입 연산자보다 복제 생성자가 일반적으로 성능 효율이 더 좋다. 복제 생성자를 통해 복사하는 걸 추천한다.
*/
SpreadsheetCell::SpreadsheetCell(double initialValue)
	: mValue(initialValue)		// 이렇게 호출할 경우에는 내부 변수에 대해 복제 생성자를 이용해 복사한다.
{
	//mValue = initialValue;	// 이렇게 호출할 경우에는 내부 변수에 대해 대입 연사자를 이용해 복사한다.
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
