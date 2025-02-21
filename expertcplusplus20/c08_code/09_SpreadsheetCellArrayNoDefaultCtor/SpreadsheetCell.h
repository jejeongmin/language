#pragma once

#include <string>
#include <string_view>

/*
	c++ compiler 는 디폴트 생성자 나 다른 생성자(인자있는)를 하나라도 선언하면
	디폴트 생성자를 묵시적으로 자동 생성하지 않는다.

	왜냐하면 개발자가 디폴트 생성자 없이 인자 있는 생성자를 만들었다면,
	디폴트 생성자를 허용하지 않겠다는 목적이 있을 거라고 추론하기 때문이다.
*/

class SpreadsheetCell
{
public:
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);

	void setValue(double inValue);
	double getValue() const;

	void setString(std::string_view inString);
	std::string getString() const;

private:
	std::string doubleToString(double inValue) const;
	double stringToDouble(std::string_view inString) const;

	double mValue;
};
