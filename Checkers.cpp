#include "Checkers.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void Checkers::Move(Checkers NewPlot, Checkers Board[8][8], int newPlotLine, int newPlotColomn) {
	int check = 0;
	check = CheckMove(NewPlot, Board);
	if (check == 1){
		char buffer[256]; // Буфер для форматирования текста
		sprintf_s(buffer, 256, "error"); // Форматируем строку

		MessageBoxA(NULL, buffer, "Debug Values", MB_OK); // Отображаем MessageBox

		Sleep(5000);
		return;
	}
	Board[newPlotLine][newPlotColomn].color = color;
	Board[newPlotLine][newPlotColomn].Checker = Checker;

	//char buffer[256]; // Буфер для форматирования текста
	//sprintf_s(buffer, 256, "error, Checker: %d, Color: %d", Checker, color); // Форматируем строку

	//MessageBoxA(NULL, buffer, "Debug Values", MB_OK); // Отображаем MessageBox

	//Sleep(5000);

	Plot = true;
	Checker = false;
	Lady = false;
	Board[newPlotLine][newPlotColomn].Plot = false;
}

int Checkers::CheckMove(Checkers NewPlot, Checkers Board[8][8]) {

	/*One Check*/

	//if ((NewPlot.posY + NewPlot.posX) % 2 == 0) {
	//	//Sleep(5000);
	//	return 1; // White Plit
	//}
	//if (NewPlot.Plot != false) {
	//	//Sleep(5000);
	//	return 1; //no Null Plot
	//}

	/*Two Check*/

	int stepY = posY - NewPlot.posY;
	int stepX = posX - NewPlot.posX;

	//if (stepY == 0 || stepX == 0) {
	//	char buffer[256]; // Буфер для форматирования текста
	//	sprintf_s(buffer, 256, "stepY: %d, stepX: %d, posY : %d, posX: %d, NewPlot.posY: %d, NewPlot.posX: %d ", stepY, stepX, posY, posX, NewPlot.posY, NewPlot.posX); // Форматируем строку

	//	MessageBoxA(NULL, buffer, "Debug Values", MB_OK); // Отображаем MessageBox

	//	Sleep(5000);
	//	return 1;
	//}
	//if (abs(posY - NewPlot.posY) > 0 && abs(posX - NewPlot.posX) > 0) {
	//	Sleep(5000); 
	//	return 1;
	//}

	//if (Lady == true) {//Lady Move

	//}
	//if (Checker == true) {
	//	if (abs(stepY) == 1 && abs(stepX) == 1) {//Step == 2, than standart move, 
	//		//check Move and possible logging
	//		if (CheckChop(Board, Board[posY][posX].color) == 1) {
	//			//Sleep(5000);
	//			return 1;
	//		}
	//	}
	//	if (abs(stepY) > 1 && abs(stepX) > 1 && abs(stepY) == abs(stepX)) {//i step > 2, that Chop
	//		if (CheckChop(Board, Board[posY][posX].color) == 1) {
	//			char buffer[256];
	//			sprintf_ы();
	//			return 1;
	//		}
	//		
	//	}
	//	if (abs(stepY) + abs(stepX) < 2) {
	//		return 1;//Error
	//	}
	//}

	//if (Plot == true) {//Error, zero Plit
	//	return 1;
	//}
	return 0;
}

int Checkers::CheckChop(Checkers Board[8][8], int allyColor){

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (Board[y][x].Checker == true || Board[y][x].Lady == true 
				&& Board[y][x].color == allyColor) {
				//CheckDiagonal
				if (CheckDiagonal(Board, y, x, Board[y][x].color) == 1) return 1;
			}
		}
	}

	return 0;
}

int Checkers::CheckDiagonal(Checkers Board[8][8], int y, int x, int color){

	int posY = y + 1;
	int posX = x + 1;

	//main diagonal, y increases, x increases
	while (posY < 8 && posX < 8) {
		//enemy color and nearby position
		if (Board[posY][posX].Plot == true || Board[posY][posX].color == color) continue;
		if (abs(posY - y) + abs(posX - x) == 2) {
			if (Board[posY][posY].Checker == true || Board[posY][posX].Lady == true) 
				return 1;//Chock
		}
		if ((abs(posY - y) + abs(posX - x)) > 2) {
			if (Board[posY][posX].Lady == true) return 1;//Chock
		}
	}
	posY = y + 1;
	posX = x - 1;

	//additional diagonal, y increases, x decreases
	while (posY < 8 && posX > -1) {
		//enemy color and nearby position
		if (Board[posY][posX].Plot == true || Board[posY][posX].color == color) continue;
		if (abs(posY - y) + abs(posX - x) == 2) {
			if (Board[posY][posY].Checker == true || Board[posY][posX].Lady == true)
				return 1;//Chock
		}
		if ((abs(posY - y) + abs(posX - x)) > 2) {
			if (Board[posY][posX].Lady == true) return 1;//Chock
		}
	}

	return 0;
}

int Checkers::CheckDiagonalChop(Checkers Board[8][8], int y, int x, int color, int newY, int newX){

	//if (Board[y][x].Lady == true) {
	//	while ()
	//}
	//if (Board[y][x].Checker == true) {
	//	if ()
	//}

	return 0;
}
