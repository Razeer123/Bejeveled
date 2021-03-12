// child.cpp : Defines the entry point for the application.
//

#include "Bejeweled.h"

#include <vector>
#include <windowsx.h>
#include "framework.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND hChild;
HMENU hMenu;
int squareSize = 80;
int boardNumber = 8;
int boardWidth = boardNumber * squareSize + (boardNumber - 1) * 10 + 25;
int boardHeight = boardNumber * squareSize + (boardNumber - 1) * 10 + 37 + (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) +
	GetSystemMetrics(SM_CXPADDEDBORDER));

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcChild(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

auto calculateBoardSize(int boardSize)
{
	int size;
	if (boardSize == 8)
	{
		size = 80;
	} else if (boardSize == 10)
	{
		size = 70;
	} else
	{
		size = 60;
	}
	squareSize = size;
	switch(boardSize)
	{
	case 8:
		boardWidth = 8 * size + (boardSize - 1) * 10 + 25;
		boardHeight = 8 * size + (boardSize - 1) * 10 + 37 + (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) +
			GetSystemMetrics(SM_CXPADDEDBORDER));
		boardNumber = 8;
		break;
	case 10:
		boardWidth = 10 * size + (boardSize - 1) * 10 + 25;
		boardHeight = 10 * size + (boardSize - 1) * 10 + 37 + (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) +
			GetSystemMetrics(SM_CXPADDEDBORDER));
		boardNumber = 10;
		break;
	case 12:
		boardWidth = 12 * size + (boardSize - 1) * 10 + 25;
		boardHeight = 12 * size + (boardSize - 1) * 10 + 37 + (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) +
			GetSystemMetrics(SM_CXPADDEDBORDER));
		boardNumber = 12;
		break;
	default:
		break;
	}
}

BOOL CALLBACK DestoryChildCallback(
	HWND   hwnd,
	LPARAM lParam
)
{
	if (hwnd != NULL) {
		DestroyWindow(hwnd);
	}

	return TRUE;
}

auto uncheckAll(HWND hwnd)
{
	CheckMenuItem(hMenu, ID_BOARDSIZE_SMALL, MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_BOARDSIZE_MEDIUM, MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_BOARDSIZE_BIG, MF_UNCHECKED);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BEJEWELED, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BEJEWELED));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex, child;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_BEJEWELED));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_BEJEWELED);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	child.cbSize = sizeof(WNDCLASSEX);

	child.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	child.lpfnWndProc = WndProcChild;
	child.cbClsExtra = 0;
	child.cbWndExtra = 0;
	child.hInstance = hInstance;
	child.hIcon = NULL;
	child.hCursor = LoadCursor(NULL, IDC_ARROW);
	child.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	child.lpszMenuName = NULL;
	child.lpszClassName = _T("ChildWindow");
	child.hIconSm = NULL;

	RegisterClassEx(&child);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	// int array[2] = calculateBoardSize()
	
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, L"BeWindowed 2021 a.k.a. powoli dostaje depresji przez studia", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		(GetSystemMetrics(SM_CXSCREEN) - boardWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - boardHeight) / 2, boardWidth, boardHeight, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	
	hMenu = GetMenu(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	int size = 80;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:

		for (int i = 0; i < boardNumber; i++)
		{
			for (int j = 0; j < boardNumber; j++)
			{
				hChild = CreateWindow(_T("ChildWindow"), nullptr, WS_OVERLAPPED | WS_VISIBLE | WS_CHILD, 5 + i * (squareSize + 10), 5 + j * (squareSize + 10), squareSize, squareSize, hWnd, NULL, hInst, NULL);
			}
		}

		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_NEWGAME:
			// do sth
			break;
		case ID_BOARDSIZE_SMALL:
			uncheckAll(hWnd);
			CheckMenuItem(hMenu, ID_BOARDSIZE_SMALL, MF_CHECKED);
			calculateBoardSize(8);
			EnumChildWindows(hWnd, DestoryChildCallback, NULL);
			for (int i = 0; i < boardNumber; i++)
			{
				for (int j = 0; j < boardNumber; j++)
				{
					hChild = CreateWindow(_T("ChildWindow"), nullptr, WS_OVERLAPPED | WS_VISIBLE | WS_CHILD, 5 + i * (squareSize + 10), 5 + j * (squareSize + 10), squareSize, squareSize, hWnd, NULL, hInst, NULL);
				}
			}
			SetWindowPos(hWnd, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - boardWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - boardHeight) / 2, boardWidth, boardHeight, SWP_SHOWWINDOW);
			break;
		case ID_BOARDSIZE_MEDIUM:
			uncheckAll(hWnd);
			CheckMenuItem(hMenu, ID_BOARDSIZE_MEDIUM, MF_CHECKED);
			calculateBoardSize(10);
			EnumChildWindows(hWnd, DestoryChildCallback, NULL);
			for (int i = 0; i < boardNumber; i++)
			{
				for (int j = 0; j < boardNumber; j++)
				{
					hChild = CreateWindow(_T("ChildWindow"), nullptr, WS_OVERLAPPED | WS_VISIBLE | WS_CHILD, 5 + i * (squareSize + 10), 5 + j * (squareSize + 10), squareSize, squareSize, hWnd, NULL, hInst, NULL);
				}
			}
			SetWindowPos(hWnd, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - boardWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - boardHeight) / 2, boardWidth, boardHeight, SWP_SHOWWINDOW);
			break;
		case ID_BOARDSIZE_BIG:
			uncheckAll(hWnd);
			CheckMenuItem(hMenu, ID_BOARDSIZE_BIG, MF_CHECKED);
			calculateBoardSize(12);
			EnumChildWindows(hWnd, DestoryChildCallback, NULL);
			for (int i = 0; i < boardNumber; i++)
			{
				for (int j = 0; j < boardNumber; j++)
				{
					hChild = CreateWindow(_T("ChildWindow"), nullptr, WS_OVERLAPPED | WS_VISIBLE | WS_CHILD, 5 + i * (squareSize + 10), 5 + j * (squareSize + 10), squareSize, squareSize, hWnd, NULL, hInst, NULL);
				}
			}
			SetWindowPos(hWnd, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - boardWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - boardHeight) / 2, boardWidth, boardHeight, SWP_SHOWWINDOW);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	enum TimerId { TimerId_MouseHover = 1 };
	static const UINT HoverTimeoutInMs = 10;
	static int PrevX = INT_MIN;
	static int PrevY = INT_MIN;
	static bool IsMouseOutside = true;
	static bool IsMouseHovered = false;
	RECT rc;
	static int increaseSize = 4;
	static int decreaseSize = 1;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		break;

	/* case WM_MOUSEMOVE:
		{
		if (IsMouseOutside) {
			TRACKMOUSEEVENT tme = { sizeof(tme) };
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			::TrackMouseEvent(&tme);
			IsMouseOutside = false;
		}

		int CurrX = GET_X_LPARAM(lParam);
		int CurrY = GET_Y_LPARAM(lParam);
		if ((CurrX != PrevX) || (CurrY != PrevY)) {
			// Mouse moved -> reset timer
			::SetTimer(hWnd, TimerId_MouseHover, HoverTimeoutInMs, nullptr);
			PrevX = CurrX;
			PrevY = CurrY;
			IsMouseHovered = false;
			// For testing only:
			::InvalidateRect(hWnd, nullptr, FALSE);
		}
		return 0;
		}

	case WM_MOUSELEAVE:
		::KillTimer(hWnd, TimerId_MouseHover);
		IsMouseOutside = true;
		PrevX = INT_MIN;
		PrevY = INT_MIN;
		return 0;

	case WM_TIMER:
		if (wParam == TimerId_MouseHover) {
			// The mouse hasn't been moved for the specified timeout:
			// This is a hover event
			IsMouseHovered = true;
			GetWindowRect(hChild, &rc);
			int currentSize = max(rc.right - rc.left, rc.bottom - rc.top);
			currentSize += increaseSize;
			for (int i = 0; i < 4; i++)
			{
				Sleep(50);
				currentSize -= 1;
			}
			return 0;
		}
		else {
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		} */

		
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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