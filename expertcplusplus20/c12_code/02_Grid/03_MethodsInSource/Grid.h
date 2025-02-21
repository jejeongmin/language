#pragma once

#include <cstddef>
#include <vector>
#include <optional>

template <typename T>
class Grid
{
public:
	explicit Grid(size_t width = kDefaultWidth, size_t height = kDefaultHeight);
	virtual ~Grid() = default;

	// 복제 생성자와 대입 연산자를 명시적으로 디폴트로 지정한다.
	Grid(const Grid& src) = default;
	Grid<T>& operator=(const Grid& rhs) = default;

	// 이동 생성자와 대입 연산자를 명시적으로 디폴트로 지정한다.
	Grid(Grid&& src) = default;
	Grid<T>& operator=(Grid&& rhs) = default;

	std::optional<T>& at(size_t x, size_t y);
	const std::optional<T>& at(size_t x, size_t y) const;

	size_t getHeight() const { return mHeight; }
	size_t getWidth() const { return mWidth; }

	static const size_t kDefaultWidth = 10;
	static const size_t kDefaultHeight = 10;

private:
	void verifyCoordinate(size_t x, size_t y) const;

	std::vector<std::vector<std::optional<T>>> mCells;
	size_t mWidth, mHeight;
};

// 템플릿 정의는 아래 방식으로 cpp 를 include 할 수도 있다.
// 단 이 경우 Grid.cpp 를 프로젝트에 포함하지 말아야 한다.
// 책에서는 프로젝트에 추가할 방법도 없고, 컴파일할 방법도 없다고 설명하는데, 후자만 맞는 말이다.
// 번역이 잘못된 건가? 왜 추가할 방법이 없다고 된거지?
#include "Grid.cpp"
