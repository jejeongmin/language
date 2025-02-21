#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <optional>
#include <utility>
#include <algorithm>

/*
	operator+ 를 특정한 타입 T 에 대해 인스턴스화 한 함수 템플릿 선언이, T 타입에 대한 Grid 템플릿 인스턴스의 friend 로 선언되어야 한다.
	다르게 다시 한번 말하자면
	Grid 템플릿을 T 타입으로 인스턴스화한 것에 대해 operator+ 를 T 타입으로 인스턴스화 한 것이 friend 가 되어야 한다.
*/

// Grid 템플릿에 대한 전방 선언
template <typename T> class Grid;

// 템플릿화한 operator+에 대한 프로토타입
template<typename T>
Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs);

template <typename T>
class Grid
{
public:
	explicit Grid(size_t width = kDefaultWidth, size_t height = kDefaultHeight);
	virtual ~Grid() = default;

	// 복제 생성자와 복제 대입 연산자를 명시적으로 디폴트로 지정한다.
	Grid(const Grid& src) = default;
	Grid<T>& operator=(const Grid& rhs) = default;

	// 이동 생성자와 이동 대입 연산자를 명시적으로 디폴트로 지정한다.
	Grid(Grid&& src) = default;
	Grid<T>& operator=(Grid&& rhs) = default;

	std::optional<T>& at(size_t x, size_t y);
	const std::optional<T>& at(size_t x, size_t y) const;

	size_t getHeight() const { return mHeight; }
	size_t getWidth() const { return mWidth; }

	static const size_t kDefaultWidth = 10;
	static const size_t kDefaultHeight = 10;

	friend Grid<T> operator+ <T>(const Grid<T>& lhs, const Grid<T>& rhs);

private:
	void verifyCoordinate(size_t x, size_t y) const;

	std::vector<std::vector<std::optional<T>>> mCells;
	size_t mWidth, mHeight;
};

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

template <typename T>
Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs)
{
	size_t minWidth = std::min(lhs.getWidth(), rhs.getWidth());
	size_t minHeight = std::min(lhs.getHeight(), rhs.getHeight());

	Grid<T> result(minWidth, minHeight);
	for (size_t y = 0; y < minHeight; ++y) {
		for (size_t x = 0; x < minWidth; ++x) {
			const auto& leftElement = lhs.mCells[x][y];
			const auto& rightElement = rhs.mCells[x][y];
			if (leftElement.has_value() && rightElement.has_value())
				result.at(x, y) = leftElement.value() + rightElement.value();
		}
	}

	return result;
}
