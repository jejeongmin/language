#include <iostream>

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
