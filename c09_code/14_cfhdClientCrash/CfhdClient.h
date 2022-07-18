#pragma once
class CfhdClient
{
public:
	CfhdClient(size_t width, size_t height);
	CfhdClient(const CfhdClient& src);
	~CfhdClient();

	CfhdClient& operator=(const CfhdClient& rhs);

	void setCellAt(size_t x, size_t y, const int value);
	int getCellAt(size_t x, size_t y);

	friend void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

private:
	void verifyCoordinate(size_t x, size_t y) const;

	size_t mWidth = 0;
	size_t mHeight = 0;
	int** mCells = nullptr;
};

