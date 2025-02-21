#pragma once

#include <string>
#include <string_view>

/*
	c++ compiler �� ����Ʈ ������ �� �ٸ� ������(�����ִ�)�� �ϳ��� �����ϸ�
	����Ʈ �����ڸ� ���������� �ڵ� �������� �ʴ´�.

	�ֳ��ϸ� �����ڰ� ����Ʈ ������ ���� ���� �ִ� �����ڸ� ������ٸ�,
	����Ʈ �����ڸ� ������� �ʰڴٴ� ������ ���� �Ŷ�� �߷��ϱ� �����̴�.
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
