#include "Grid.h"
#include <stdexcept>
#include <utility>

template <typename T>
Grid<T>::Grid(size_t width, size_t height)
	: mWidth(width)
	, mHeight(height)
{
	mCells.resize(mWidth);
	for (auto& column : mCells) {
		column.resize(mHeight);
	}
}

template <typename T>
void Grid<T>::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= mWidth || y >= mHeight) {
		throw std::out_of_range("");
	}
}

template <typename T>
const std::optional<T>& Grid<T>::at(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return mCells[x][y];
}

template <typename T>
std::optional<T>& Grid<T>::at(size_t x, size_t y)
{
	return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}


// 인스턴스화를 허용할 타입을 명시적으로 나열한다.
// 이렇게 명시적으로 인스턴스화 해두면 여기에 나온 타입에 대해서만 빌드하기 때문에
// 앞에 나온 Grid 클래스 타입을 다른 타입으로는 인스턴스화 할 수 없게 된다.
template class Grid<int>;
template class Grid<double>;
template class Grid<std::vector<int>>;
