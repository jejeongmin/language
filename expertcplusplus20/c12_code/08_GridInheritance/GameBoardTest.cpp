#include "GameBoard.h"

using namespace std;

class ChessPiece
{
};

/*
	구현을 확장하거나 다형성을 지원하려면 상속을 사용하고
	특정한 타입에 대한 템플릿 구현을 커스터마이즈하고 싶다면 특수화를 사용한다.
*/
int main()
{
	GameBoard<ChessPiece> chessBoard(8, 8);

	ChessPiece pawn;
	chessBoard.at(0, 0) = pawn;
	chessBoard.move(0, 0, 0, 1);

	return 0;
}
