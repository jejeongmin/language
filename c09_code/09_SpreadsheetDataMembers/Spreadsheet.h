#pragma once

#include <cstddef>
#include "SpreadsheetCell.h"

class SpreadsheetApplication; // forward declaration

class Spreadsheet
{
public:
	Spreadsheet(size_t width, size_t height,
		const SpreadsheetApplication& theApp);
	Spreadsheet(const Spreadsheet& src);
	~Spreadsheet();
	Spreadsheet& operator=(const Spreadsheet& rhs);

	void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(size_t x, size_t y);

	size_t getId() const;

	friend void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

	static const size_t kMaxHeight = 100;
	static const size_t kMaxWidth = 100;

private:
	void verifyCoordinate(size_t x, size_t y) const;

	size_t mId = 0;
	size_t mWidth = 0;
	size_t mHeight = 0;
	SpreadsheetCell** mCells = nullptr;

	const SpreadsheetApplication& mTheApp;

	// static 멤버를 inline 으로 선언하고, 선언에서 초기화 하면 구현 함수에서 초기화 선언하지 않아도 된다.
	static inline size_t sCounter = 0;
};
