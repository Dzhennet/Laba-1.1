# Laba-1.1
#include "framework.h"

#define MAX_LOADSTRING 10
class Vector2D {
public:
	int x, y;
	Vector2D() {
		x = 0;
		y = 0;
	}
	Vector2D(int _x, int _y) {
		x = _x;
		y = _y;
	}
	~Vector2D() {}
	friend Vector2D operator+(const Vector2D v1, const Vector2D v2) {
		return Vector2D(v1.x + v2.x, v1.y + v2.y);
	}
	friend Vector2D operator*(Vector2D v, int a) {
		return Vector2D(v.x * a, v.y * a);
	}
	
	Vector2D& operator=(const Vector2D& v) {
		if (this == &v)
			return *this;
		this->x = v.x;
		this->y = v.y;
		return *this;
	}
};
// Глобальные переменные:

HINSTANCE hInst; // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING]; // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING]; // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Инициализация глобальных строк

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));
	MSG msg;
	// Цикл основного сообщения:

	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

// ФУНКЦИЯ: MyRegisterClass()

// ЦЕЛЬ: Регистрирует класс окна.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}


// ФУНКЦИЯ: InitInstance(HINSTANCE, int)

// ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно

// В этой функции маркер экземпляра сохраняется в глобальной переменной, а также

// создается и выводится главное окно программы.

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

// ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)


// ЦЕЛЬ: Обрабатывает сообщения в главном окне.



// WM_COMMAND - обработать меню приложения

// WM_PAINT - Отрисовка главного окна

// WM_DESTROY - отправить сообщение о выходе и вернуться

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);

		// Разобрать выбор в меню:

		switch (wmId) {

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
	case WM_PAINT: {

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		// dXY, w использованы для адекватного сдвига, чтобы фигуры не накладывались друг на друга при изменении dXY

		int dXY = 100; // Т.к эллипс определяется ограничивающим прямоугольником,

		//dXY = 150; // координаты диагональной точки равны dXY.

		int w = 0; // Если менять значение w, то между окружностями будут расстояния. w>=0

		Vector2D p(10, 20); // Исходная точка
		Vector2D vR(dXY + w, 0); // Сдвиг вправо
		Vector2D vD(0, dXY + w); // Сдвиг вниз

		// +w чтобы увеличивать расстояния. При w = 0 окружности касаются

		Vector2D p2;
		p2 = p; // Делаю копию точки p для дальнейшего использования

		// 3 на 3 понял как "квадрат" из 9 окружностей

		for (int i = 0; i < 3; i++)	{
			p = p + vD * i; // Сдвиги вниз. Изначально при i=0: p=p, p(10, 20)

			// При i=1: p=p+vD*1, p(10, 120)

			// При i=2: p=p+vD*2, p(10, 220)

			// vD*i - Увеличение i дает новую строку из окружностей

			for (int j = 0; j < 3; j++) // Рисуем по 3 окружности
			{
				Ellipse(hdc, p.x,
					p.y,
					p.x + dXY, // Т.к эллипс определяется ограничивающим прямоугольником,
					p.y + dXY); // добавляю в данном случае dXY, чтобы был квадрат, а значит будут рисоваться окружности
				p = p + vR; // Сдвиг вправо
			}
			// В данный момент нужно перейти на новую строку, но после последней окружности в строке в p сейчас p(210, 20)

			// и если не присвоить p=p2 ( p2(10, 20) ), то последующие строки из окружностей сместятся относительно координат p(210, 20)

			p = p2;
		}
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
