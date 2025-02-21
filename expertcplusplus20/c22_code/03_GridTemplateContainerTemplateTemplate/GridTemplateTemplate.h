#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <optional>
#include <utility>

/*
	템플릿 매개변수로, 템플릿 그 자체를 받으려면 템플릿 템플릿 매개변수 ( template template parameter ) 라는 
	특수 매개 변수를 사용해야 한다.

	template <typename T,
	template <typename E, typename Allocator = std::allocator<E>> class Container = std::vector>
	c++17 이전에는 템플릿템플릿 매개변수에서 class 키워드만 지원하고, typename 은 지원하지 않았다.
	이제 와서 옛날 컴파일러 쓸 일은 없겠지만, 혹시 모르니 적어둠
*/
template <typename T,
	template <typename E, typename Allocator = std::allocator<E>> typename Container = std::vector>
class Grid
{
public:
	explicit Grid(size_t width = kDefaultWidth, size_t height = kDefaultHeight);
	virtual ~Grid() = default;

	// 복제 생성자와 복제 대입 연산자를 명시적으로 디폴트로 지정한다.
	Grid(const Grid& src) = default;
	Grid<T, Container>& operator=(const Grid& rhs) = default;

	// 이동 생성자와 이동 대입 연산자를 명시적으로 디폴트로 지정한다.
	Grid(Grid&& src) = default;
	Grid<T, Container>& operator=(Grid&& rhs) = default;

	std::optional<T>& at(size_t x, size_t y);
	const std::optional<T>& at(size_t x, size_t y) const;

	size_t getHeight() const { return mHeight; }
	size_t getWidth() const { return mWidth; }

	static const size_t kDefaultWidth = 10;
	static const size_t kDefaultHeight = 10;

private:
	void verifyCoordinate(size_t x, size_t y) const;

	std::vector<Container<std::optional<T>>> mCells;
	size_t mWidth = 0, mHeight = 0;
};

template <typename T, template <typename E, typename Allocator = std::allocator<E>> typename Container>
Grid<T, Container>::Grid(size_t width, size_t height)
	: mWidth(width)
	, mHeight(height)
{
	mCells.resize(mWidth);
	for (auto& column : mCells) {
		column.resize(mHeight);
	}
}

template <typename T, template <typename E, typename Allocator = std::allocator<E>> typename Container>
void Grid<T, Container>::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= mWidth || y >= mHeight) {
		throw std::out_of_range("");
	}
}

template <typename T, template <typename E, typename Allocator = std::allocator<E>> typename Container>
const std::optional<T>& Grid<T, Container>::at(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return mCells[x][y];
}

template <typename T, template <typename E, typename Allocator = std::allocator<E>> typename Container>
std::optional<T>& Grid<T, Container>::at(size_t x, size_t y)
{
	return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}
