#include <iostream>
#include <windows.h>
#include "Checkers.h"
#include <gdiplus.h> // Include for GDI+ (Handles JPEG and PNG)
#pragma comment (lib,"Gdiplus.lib")

using namespace std;

/* ||      CONST          || */

const int COLOMN = 8;
const int ROWS = 8;
const int cellSize = 50;
const int WhiteCheckers = 1;
const int WhiteLady = 2;
const int BlackCheckers = -1;
const int BlackLady = -2;

const int BlackPlit = -5;
const int WhitePlit = 5;
const int RadiusCheckers = 16;

const int windowShift = 15;

const int White = 1;
const int Black = -1;

/* ||      CONST          || */

/* || PROGRAMMING TOOLS    ||*/

Checkers Board[ROWS][COLOMN];
bool FlagComplCheckers = false;
bool flagChoiseCheckers = false;
bool ChoiseCheckers = false;

HDC hdc;
HBITMAP hBitmap = NULL;

/* || PROGRAMMING TOOLS ||*/

/* ||       GAME        ||*/

int move;
int ChoiseLine; //Choise Plit
int ChoiseColomn;

int TempChoiseLine;//Temp Choise plit
int TempChoiseColomn;
int TempChoiseColor;

/* ||       GAME        ||*/

void ComplCheckers() {

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLOMN; x++) {
            Board[y][x].posY = y;
            Board[y][x].posX = x;
            if ((y + x) % 2 != 0) {
                if (y < 3) {
                    Board[y][x].Checker = true;
                    Board[y][x].value = BlackCheckers;
                    Board[y][x].color = Black;
                }
                else if (y > 4) {
                    Board[y][x].Checker = true;
                    Board[y][x].value = WhiteCheckers;
                    Board[y][x].color = White;
                }
                else {
                    Board[y][x].value = BlackPlit;
                    Board[y][x].Plot = true;
                }
            }
            else {
                Board[y][x].value = WhitePlit;
                Board[y][x].Plot = true;
            }
        }
    }
    FlagComplCheckers = true;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"CheckersClass";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // Create Window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Checkers",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        //size Window
        CW_USEDEFAULT, CW_USEDEFAULT, COLOMN * (cellSize + 10), ROWS * (cellSize + 10),

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

//void DrawCrown(HDC hdc, int Line, int Colomn, int posY, int posX);

void DrawBoard(HDC hdc, HWND hwnd) {

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLOMN; x++) {
            RECT cellRect;
            cellRect.left = x * cellSize + windowShift;
            cellRect.right = (x + 1) * cellSize + windowShift;
            cellRect.top = y * cellSize + windowShift;
            cellRect.bottom = (y + 1) * cellSize + windowShift;
            FrameRect(hdc, &cellRect, (HBRUSH)GetStockObject(BLACK_BRUSH));//Black grid
            if ((y + x) % 2 != 0) {
                FillRect(hdc, &cellRect, (HBRUSH)GetStockObject(BLACK_BRUSH));//Black plit
            }
            else {
                FillRect(hdc, &cellRect, (HBRUSH)GetStockObject(LTGRAY_BRUSH)); //White plit
            }
            if (y == ChoiseLine && x == ChoiseColomn) { //green grid, Choise plit
                FrameRect(hdc, &cellRect, (HBRUSH)GetStockObject(RGB(0, 128, 0)));
            }

            //Draw checker
            if (Board[y][x].Plot != true) {
                int posY = (cellSize * y) + 25 + windowShift;//Center Checker
                int posX = (cellSize * x) + 25 + windowShift;
                HGDIOBJ checkerBrush = NULL; // Initialize to NULL
                if (Board[y][x].value == WhiteCheckers) {
                    checkerBrush = GetStockObject(WHITE_BRUSH);
                }
                else if (Board[y][x].value == BlackCheckers) {
                    checkerBrush = CreateSolidBrush(RGB(50, 50, 50));
                }
                else {
                    continue; // Skip if the cell is empty
                }
                HGDIOBJ oldBrush = SelectObject(hdc, checkerBrush);
                //the down part of the checker
                Ellipse(hdc, posX - RadiusCheckers, posY - RadiusCheckers, posX + RadiusCheckers, posY + RadiusCheckers);

                //the upper part of the checker
                Ellipse(hdc, posX - RadiusCheckers / 2, posY - RadiusCheckers / 2, posX + RadiusCheckers / 2, posY + RadiusCheckers / 2);

                //Draw Lady
                //DrawCrown(hdc, y, x, posY, posX);
                SelectObject(hdc, oldBrush);
                DeleteObject(checkerBrush);
            }
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static int sX, sY;
    switch (uMsg) {
    case WM_SIZE:
        sX = LOWORD(lParam);
        sY = LOWORD(wParam);
    case WM_PAINT://Paint Window
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        if (FlagComplCheckers == false) { ComplCheckers(); }
        DrawBoard(hdc, hwnd);
        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_LBUTTONDOWN://Left Click Button
    {
        int xPos = LOWORD(lParam);  // horizontal position of cursor
        int yPos = HIWORD(lParam);  // vertical position of cursor

        if (yPos > (cellSize * ROWS + windowShift)) { // Use ROWS here, not cellSize * cellSize

            InvalidateRect(hwnd, NULL, TRUE);  // Force a redraw
        }
        else {
            int col = (xPos - windowShift) / cellSize;
            int row = (yPos - windowShift) / cellSize;

            // Validate row and col to prevent out-of-bounds access
            if (col >= 0 && col < COLOMN && row >= 0 && row < ROWS) {
                ChoiseLine = row;
                ChoiseColomn = col;
                if (Board[row][col].Plot != true) { //Choise checkers
                    TempChoiseColomn = col;
                    TempChoiseLine = row;
                    flagChoiseCheckers = true;
                }
                else {
                    if (flagChoiseCheckers == true) {
                        Board[TempChoiseLine][TempChoiseColomn].Move
                        (Board[ChoiseLine][ChoiseColomn], Board, ChoiseLine, ChoiseColomn);
                        flagChoiseCheckers = false;

                        //char buffer[256]; // Буфер для форматирования текста
                        //sprintf_s(buffer, 256, "error, Checker: %d, Color: %d, Plot: %d", Board[ChoiseLine][ChoiseColomn].Checker, Board[ChoiseLine][ChoiseColomn].color, Board[ChoiseLine][ChoiseColomn].Plot); // Форматируем строку

                        //MessageBoxA(NULL, buffer, "Debug Values", MB_OK); // Отображаем MessageBox

                        InvalidateRect(hwnd, NULL, TRUE); //Update Areal Window
                    }
                }
                InvalidateRect(hwnd, NULL, TRUE); //Update Areal Window
            }
        }
        break;
    }
    return 0;

    case WM_RBUTTONDOWN: //RKM
    {
        int xPos = LOWORD(lParam);  // horizontal position of cursor
        int yPos = HIWORD(lParam);  // vertical position of cursor

        int col = (xPos - windowShift) / cellSize;
        int row = (yPos - windowShift) / cellSize;

        InvalidateRect(hwnd, NULL, TRUE);
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//HBITMAP LoadBitmapFromFile(const WCHAR* filename) {
//    Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(filename);
//    if (bitmap == nullptr) {
//        return nullptr;
//    }
//
//    Gdiplus::Status status = bitmap->GetLastStatus();
//    if (status != Gdiplus::Ok) {
//        delete bitmap;
//        return nullptr;
//    }
//
//    HBITMAP hBitmap = NULL; // Local hBitmap to return
//    status = bitmap->GetHBITMAP(Gdiplus::Color::Transparent, &hBitmap);
//    if (status != Gdiplus::Ok) {
//        delete bitmap;
//        return nullptr;
//    }
//
//    delete bitmap;
//    return hBitmap;
//}

//void DrawCrown(HDC hdc, int Line, int Colomn, int posY, int posX) {
//    int SmallRadius = 8;
//    HBITMAP hBitmap = NULL; // Local hBitmap
//
//    if (Board[Line][Colomn].color == White) {
//        hBitmap = LoadBitmapFromFile(L"resource/BlackCrown.png"); // Assign a result
//    }
//    else {
//        hBitmap = LoadBitmapFromFile(L"C:\\Nikita\\source\\repos\\Checkers\\resource\\WhiteCrown.png"); // Assign a result
//    }
//
//    if (hBitmap == NULL) {
//        //The loading failed. There are no errors, then most likely it cannot access the function.
//        return;
//    }
//
//    BITMAP bm;
//    GetObject(hBitmap, sizeof(BITMAP), &bm); //Get bitmap metadata.
//    int width = bm.bmWidth;
//    int height = bm.bmHeight;
//
//    // Create a compatible memory DC
//    HDC hMemDC = CreateCompatibleDC(hdc);
//    if (hMemDC != NULL) {
//        // Select the bitmap into the memory DC
//        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
//
//        // Copy the bitmap to the window at the desired location
//        BitBlt(hdc, posY - 4, posX - 4, width, height, hMemDC, 0, 0, SRCCOPY);
//
//        // Restore the old bitmap and delete the memory DC
//        SelectObject(hMemDC, hOldBitmap);
//        DeleteDC(hMemDC);
//    }
//    DeleteObject(hBitmap);   //Delete object to prevent memory leaks
//}
