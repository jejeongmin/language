#include "GameBoard.h"

using namespace std;

class ChessPiece
{
};

/*
	������ Ȯ���ϰų� �������� �����Ϸ��� ����� ����ϰ�
	Ư���� Ÿ�Կ� ���� ���ø� ������ Ŀ���͸������ϰ� �ʹٸ� Ư��ȭ�� ����Ѵ�.
*/
int main()
{
	GameBoard<ChessPiece> chessBoard(8, 8);

	ChessPiece pawn;
	chessBoard.at(0, 0) = pawn;
	chessBoard.move(0, 0, 0, 1);

	return 0;
}
