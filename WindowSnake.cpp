#include <Windows.h>
#include "skinSnake.h"
#include "foodSnake.h"
#include <ctime>
#include "resource1.h"

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

Snake snake;
Food food;
const int CELL_SIZE = 20;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWNDClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Snake", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 250, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGcolor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) { 
	WNDCLASS NWC = { 0 };
	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.lpszClassName = Name;
	NWC.hInstance = hInst;
	NWC.hbrBackground = BGcolor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	PAINTSTRUCT ps;
	static HDC hdc;
	int width;
	int height;
	static int timerID = 1;
	switch (msg) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 200, NULL);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		POINT h_position = snake.GetHeadPosition();
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		width = clientRect.right/ CELL_SIZE;
		height = clientRect.bottom/ CELL_SIZE;
		if (h_position.x >= width) {
			h_position.x = 0;
		}
		else if (h_position.x < 0) {
			h_position.x = width - 1;
		}

		if (h_position.y >= height) {
			h_position.y = 0;
		}
		else if (h_position.y < 0) {
			h_position.y = height - 1;
		}
		snake.setHeadPosition(h_position);
		snake.Move();
		if (food.CheckEat(snake.GetHeadPosition())) {
			snake.Grow();
			food.SpawnNew(snake.GetHeadPosition(), snake.GetBody(), width, height);
		}
		if (snake.IsDead()) {
			MessageBox(hWnd, L"Game Over", L"Snake", MB_OK);
			snake.Dead();
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		food.Draw(hdc);
		snake.drawSnake(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wp) {
		case VK_LEFT: snake.ChangeDirection(2); break; //left
		case VK_RIGHT: snake.ChangeDirection(0); break; //right
		case VK_UP: snake.ChangeDirection(1); break;    //up
		case VK_DOWN: snake.ChangeDirection(3); break;  //down
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
	return 0;
}