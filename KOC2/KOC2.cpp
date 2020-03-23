// KOC2.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "KOC2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.


    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KOC2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KOC2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//  ФУНКЦИЯ: MyRegisterClass()
//  ЦЕЛЬ: Регистрирует класс окна.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KOC2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KOC2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HDC hdc, hdcm;
int lx, ly; // координаты конца экрана
int sx, sy; // размеры экрана
HBITMAP hbm; // дескриптор изображения
HBRUSH hbr; // дескриптор кисти

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_SIZE:
		sx = LOWORD(lParam); // ширина активного экрана
		sy = HIWORD(lParam); // высота активного экрана
		break;
	case WM_CREATE:
	{
		hdc = GetDC(hWnd); // получаем контекст устройства окна hWnd
		lx = GetSystemMetrics(SM_CXSCREEN); // ширина экрана
		ly = GetSystemMetrics(SM_CYSCREEN); // высота экрана
		// создать в памяти контекст устройства hdcm, совместимый с текущим контекстом устройства вывода hdc.
		hdcm = CreateCompatibleDC(hdc); 
		hbm = CreateCompatibleBitmap(hdc, lx, ly); // Создать изображение в памяти заданного размера
		SelectObject(hdcm, hbm); // установить в контексте hdcm устройства изображение hbm
		hbr = (HBRUSH)GetStockObject(WHITE_BRUSH); // установить цвет кисти белый
		SelectObject(hdcm, hbr); // установить в контексте hdcm устройства изображение hbm
		// закрашивает прямоугольную область с координатами(x, y), шириной width
		// и высотой height, используя текущую кисть и растровую операцию dwRaster
		PatBlt(hdcm, 0, 0, lx, ly, PATCOPY); // PATCOPY - область заполняется текущей кистью;
		// объявляет недействительным прямоугольник *lpRect в окне hWnd
		InvalidateRect(hWnd, 0, false); // перерисовать все окно, если true перерисовать фон окна
	}
	break;
	// при нажатии левой кнопки мыши
	case WM_LBUTTONDOWN: {
		int Left = 0, 
			Right = 40,
			Top = 0,			
			Bottom = 40;
		int i = 1;

		hbr = (HBRUSH)GetStockObject(BLACK_BRUSH); // установить цвет кисти черный
		SelectObject(hdcm, hbr); // установить в контексте hdcm устройства изображение hbm

		for (; Bottom < sy; Top += 40, Bottom += 40) {
			Left = 0, Right = 40;

			for (;  Right < sx; Left += 40, Right += 40) {
				Rectangle(hdcm, Left, Top, Right, Bottom); // Функция создания прямоугольника
				if (i % 2 == 0) {
					hbr = (HBRUSH)GetStockObject(BLACK_BRUSH); // установить цвет кисти черный
					SelectObject(hdcm, hbr); // установить в контексте hdcm устройства изображение hbm
				}
				else {
					hbr = (HBRUSH)GetStockObject(WHITE_BRUSH); // установить цвет кисти белый
					SelectObject(hdcm, hbr); // установить в контексте hdcm устройства изображение hbm
				}
				i++;
	
			}
		}
		InvalidateRect(hWnd, 0, false);
			break;
	}

		
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
			BitBlt(hdc, 0, 0, lx, ly, hdcm, 0, 0, SRCCOPY);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
