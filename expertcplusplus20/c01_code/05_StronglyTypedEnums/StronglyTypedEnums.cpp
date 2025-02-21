#include <iostream>

// 열거형 타입을 엄격히 관리하고 싶다면, enum 이 아니라 enum class 를 사용한다.
enum class PieceType
{
	King = 1,
	Queen,
	Rook = 10,
	Pawn
};

int main()
{
	PieceType piece = PieceType::King;

	if (piece == PieceType::King)
	{
		std::cout << "piece type is king" << std::endl;
	}

	return 0;
}
