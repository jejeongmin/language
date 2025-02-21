#pragma once

#include <cstddef>
#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	
	void set(double inValue);
	void set(std::string_view inString);

	double getValue() const { mNumAccesses++; return mValue; }
	std::string getString() const { mNumAccesses++; return doubleToString(mValue); }
	
	// double getValue() const;
	// std::string getString() const;

	static std::string doubleToString(double inValue);
	static double stringToDouble(std::string_view inString);

private:
	double mValue = 0;
	mutable size_t mNumAccesses = 0;	// mutable 로 선언해두면 const 함수 호출이라도 값 변경할 수 있음
};

/*
inline double SpreadsheetCell::getValue() const
{
	mNumAccesses++;
	return mValue;
}

inline std::string SpreadsheetCell::getString() const
{
	mNumAccesses++;
	return doubleToString(mValue);
}
*/
