#include <iostream>
#include <windows.h>

using namespace std;

const int colomn = 8;
const int rows = 8;
const int cellSize = 50;
const int WhiteCheckers = 1;
const int WhiteLady = 2;
const int BlackCheckers = -1;
const int BlackLady = -2;

const int BlackPlit = -5;
const int WhitePlit = 5;
const int RadiusCheckers = 15;

int Board[rows][colomn];
bool FlagComplCheckers = false;

const int White = 0;
const int Black = 1;

struct checkers {
    int rows;
    int colomn;
    int Radius = 15;
    int color;
};

void ComplCheckers() {
    for (int y = 0; y < rows; y++) { //комплектуем поле
        for (int x = 0; x < colomn; x++) {
            if ((y + x) % 2 != 0) { 
                Board[y][x] = y < 3 ? BlackCheckers : Board[y][x];
                Board[y][x] = y > 4 ? WhiteCheckers : Board[y][x];
            }
            else { Board[y][x] = 5; }
        }
    }
    FlagComplCheckers = true;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Регистрация класса окна
    const wchar_t CLASS_NAME[] = L"CheckersClass";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Задаём курсор
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Цвет фона окна

    RegisterClass(&wc);

    // Создание окна
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Checkers",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        //размер окна
        CW_USEDEFAULT, CW_USEDEFAULT, colomn * (cellSize + 10), rows * (cellSize + 10),

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Цикл обработки сообщений
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void DrawCheckers(HDC hdc);

void DrawBoard(HDC hdc, HWND hwnd) {//отрисовка окна

    int PosCheckersY;
    int PosCheckersX;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < colomn; x++) {
            RECT cellRect;
            cellRect.left = x * cellSize;
            cellRect.right = (x + 1) * cellSize;
            cellRect.top = y * cellSize;
            cellRect.bottom = (y + 1) * cellSize;
            FrameRect(hdc, &cellRect, (HBRUSH)GetStockObject(BLACK_BRUSH));//черная рамка
            if ((y + x) % 2 != 0) { //черная клетка
                FillRect(hdc, &cellRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            else { //белая клетка
                FillRect(hdc, &cellRect, (HBRUSH)GetStockObject(LTGRAY_BRUSH));
            }
            PosCheckersY = y + 0.5;//определяем позицию шашки на доске
            PosCheckersX = x + 0.5;
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static int sX, sY;
    switch (uMsg) {
    case WM_SIZE:
        sX = LOWORD(lParam);
        sY = LOWORD(wParam);
    case WM_PAINT://часть для отрисовки
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        if (FlagComplCheckers == false) { ComplCheckers(); }
        DrawBoard(hdc, hwnd);
        DrawCheckers(hdc);
        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_LBUTTONDOWN://функциональность мыши
    {
        int xPos = LOWORD(lParam);  // horizontal position of cursor
        int yPos = HIWORD(lParam);  // vertical position of cursor

        int row = yPos / cellSize;
        int col = xPos / cellSize;

        //cout << "Клик: Строка " << row << ", Столбец " << col << endl; // Отладочный вывод

        //Добавьте здесь логику обработки нажатия кнопки мыши
        //Например, revealCell(row, col);  и InvalidateRect(hwnd, NULL, TRUE);

        InvalidateRect(hwnd, NULL, TRUE); //Перерисовать окно
    }
    return 0;

    case WM_RBUTTONDOWN: //Правая кнопка
    {
        int xPos = LOWORD(lParam);  // horizontal position of cursor
        int yPos = HIWORD(lParam);  // vertical position of cursor

        int row = yPos / cellSize;
        int col = xPos / cellSize;

        //cout << "Правый клик: Строка " << row << ", Столбец " << col << endl; // Отладочный вывод
        //Добавьте здесь логику для установки/снятия флага

        InvalidateRect(hwnd, NULL, TRUE); //Перерисовать окно
    }

    case WM_DESTROY://закрытие окна
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void DrawCheckers(HDC hdc) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < colomn; x++) {
            int posY = y + 25;
            int posX = x + 25;
            HBRUSH checkerBrush;
            if (Board[y][x] == WhiteCheckers) {
                // Белая шашка
                checkerBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
            }
            if (Board[y][x] == BlackCheckers) {
                // Черная шашка
                checkerBrush = CreateSolidBrush(RGB(50, 50, 50)); // Темно-серый
            }

            HGDIOBJ oldBrush = SelectObject(hdc, &checkerBrush); //Сохраняем старую кисть

            Ellipse(hdc, posX - RadiusCheckers, posY - RadiusCheckers, posX + RadiusCheckers, posY + RadiusCheckers);

            SelectObject(hdc, oldBrush); // Восстанавливаем старую кисть
            DeleteObject(checkerBrush); // Удаляем кисть, если она была создана
        }
    }
}

