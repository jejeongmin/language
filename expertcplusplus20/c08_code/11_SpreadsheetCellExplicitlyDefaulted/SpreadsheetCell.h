#pragma once

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;		// default 생성자 자동 생성 키워드
	//SpreadsheetCell() = delete;		// 명시적으로 삭제된 생성자 개념도 지원한다.
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);

	void setValue(double inValue);
	double getValue() const;

	void setString(std::string_view inString);
	std::string getString() const;

private:
	std::string doubleToString(double inValue) const;
	double stringToDouble(std::string_view inString) const;

	double mValue = 0;
};
