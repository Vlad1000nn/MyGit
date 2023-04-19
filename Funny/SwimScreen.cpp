#include <Windows.h>


//Выбрать разрядность системы,собрать и запустить exe из папки release

int scrWidth;
int scrHeight;
int interval = 100;

LRESULT CALLBACK Melt(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		HDC desktop = GetDC(HWND_DESKTOP);
		HDC window = GetDC(hwnd);
		BitBlt(window, 0, 0, scrWidth, scrHeight, desktop, 0, 0, SRCCOPY);
		ReleaseDC(hwnd, window);
		ReleaseDC(HWND_DESKTOP, desktop);
		SetTimer(hwnd, 0, interval, 0);
		ShowWindow(hwnd, SW_SHOW);
		break;
	}
	case WM_PAINT: 
	{
		ValidateRect(hwnd, 0);
		break;
	}
	case WM_TIMER: 
	{
		HDC wndw = GetDC(hwnd);
		int x = (rand() % scrWidth) - (200 / 2);
		int y = (rand() % 15);

		int width = (rand() % 200);
		
		BitBlt(wndw, x, y, width, scrHeight, wndw, x, 0, SRCCOPY);

		ReleaseDC(hwnd, wndw);
		break;
	}
	case WM_DESTROY: 
	{
		KillTimer(hwnd, 0);
		PostQuitMessage(0);
		break;
	}
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}//Метод плывущего экрана



//Выйти с этой программы можно будет либо с помощью диспетчера задач либо alt+F4

int APIENTRY main(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int showCmd)
{
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);
	//Получаем размеры поля
	WNDCLASS wndClass{ 0, Melt,0, 0,inst, 0,LoadCursorW(0,IDC_ARROW),0,0,L"ScreenMelting" };

	if (RegisterClass(&wndClass))//Создадим новый экран который будет плыть и перекрывать наш
	{
		HWND hwnd = CreateWindowExA(WS_EX_TOPMOST, "ScreenMelting", 0, WS_POPUP, 0, 0, scrWidth, scrHeight,
			HWND_DESKTOP, 0, inst, 0);
		if (hwnd)
		{
			srand(GetTickCount64());

			MSG msg = { 0 };
			//Теперь запускаем плывущий экран
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}

	}
}