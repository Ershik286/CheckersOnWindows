#pragma once
class Checkers {
public:
	int color = 0;
	int posY;
	int posX;
	bool Plot = false;
	bool Checker = false;
	bool Lady = false;
	int value;
	void Move(Checkers Board[8][8], int newPlotLine, int newPlotColomn, int& MOVE);
private:
	int CheckMove(Checkers Board[8][8], int newPlotLine, int newPlotColomn);
	int CheckChop(Checkers Board[8][8], int allyColor);
	int CheckDiagonal(Checkers Board[8][8], int y, int x, int color);
	int CheckDiagonalChop(Checkers Board[8][8], int y, int x, int color, int newY, int newX);
};
