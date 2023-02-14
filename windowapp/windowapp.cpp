// windowapp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
#include "stdafx.h"

#define MAX_LOADSTRING 100

// 전역 변수:
const wstring g_szClassName = L"WindowApp";
HBRUSH g_hbrBackground = CreateSolidBrush(RGB(255, 255, 0));

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hwndTextButton;
HWND hwndBackButton;
HWND hTextBox;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void				Initialize();
//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWAPP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	DWORD Style = 0;
	Style = WS_OVERLAPPEDWINDOW;
	//Style = WS_POPUP | WS_EX_TOPMOST;
	//HWND hWnd = CreateWindowW(szWindowClass, szTitle, Style, 0, 0, 1920, 1080, nullptr, nullptr, hInstance, nullptr);
	HWND hWnd = CreateWindow(szWindowClass, szTitle, Style, 0, 0, 1920, 1080, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	//ShowWindow(hWnd, nCmdShow);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	return TRUE;
}
// 정보 대화 상자의 메시지 처리기입니다.
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

void Initialize()
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Initialize();
	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWAPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWAPP));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

		}
	}

	return (int)msg.wParam;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//CImage image;
	static int iWidth = 0, iHeight = 0;
	static int iCount = 0;
	GetWidthHeight(hwnd, &iWidth, &iHeight);


	switch (message)
	{
	case WM_CREATE:
	{
		//이미지를 생성

		//image.Load(_T("./image/image.png"));

		// 타이머 설정 
		SetTimer(hwnd, 1, 1000, NULL);
		SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, DEFAULT_X, DEFAULT_Y, SWP_NOZORDER | SWP_NOMOVE);

		// textbox 컨트롤 생성
		hTextBox = CreateWindowEx(0, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, TEXTBOX_X, TEXTBOX_Y, hwnd, (HMENU)ID_TEXTBOX, GetModuleHandle(NULL), NULL);
		SetWindowPos(hTextBox, HWND_TOP, (iWidth - TEXTBOX_X) / 2, (iHeight - TEXTBOX_Y) / 2 - 50, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

		// 버튼 컨트롤 생성 ( textbox 연계 )
		hwndTextButton = CreateWindowW(L"BUTTON", L"클릭!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_TEXT_BUTTON, NULL, NULL);
		SetWindowPos(hwndTextButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

		// 버튼 컨트롤 생성 ( 배경 바꾸기 )
		hwndBackButton = CreateWindowW(L"BUTTON", L"배경바꾸기", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_BACK_COLOR_BUTTON, NULL, NULL);
		SetWindowPos(hwndBackButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2 + 60, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

		// 버튼 컨트롤 생성 ( 이미지 출력 )
		hwndBackButton = CreateWindowW(L"BUTTON", L"이미지출력", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_IMAGE_BUTTON, NULL, NULL);
		SetWindowPos(hwndBackButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2 + 120, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

		// 이미지 컨트롤 생성 ?
		

	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:

		switch (wmId)
		{
		case ID_TEXT_BUTTON:
		{
			int length = GetWindowTextLengthW(hTextBox) + 1;
			wchar_t* buffer = new wchar_t[length];
			GetWindowTextW(hTextBox, buffer, length);
			MessageBoxW(NULL, buffer, L"Entered text", MB_OK);
			delete[] buffer;
		}
		break;
		case ID_TEXTBOX:
			break;
		case ID_BACK_COLOR_BUTTON:
		{
			HDC hdc = GetDC(hwnd);
			HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc,(HBRUSH)GetStockObject(NULL_BRUSH));
			RECT rect;
			GetClientRect(hwnd, &rect);
			FillRect(hdc, &rect, hBrush);
			SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(GetDC(hwnd), hOldBrush);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		break;
		case ID_IMAGE_BUTTON:
		{
			Gdiplus::Graphics graphics(hwnd);
			Image image(L"image.png");
			graphics.DrawImage(&image, rand() % DEFAULT_X, rand() % DEFAULT_Y,  image.GetWidth(), image.GetHeight());
		}
		break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CTLCOLORBTN:
	{
		HDC hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(255, 255, 255));
		return (LRESULT)g_hbrBackground;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		TEXTMETRIC tm;
		HDC hdc = BeginPaint(hwnd, &ps);
		GetTextMetrics(hdc, &tm);
		//// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		auto text = _T("안녕하세요!");
		int x = (iWidth - tm.tmAveCharWidth * _tcslen(text) * 1.7) / 2;
		int y = (iHeight - tm.tmHeight) / 2 - 70;
		TextOut(hdc, x, y, text, _tcslen(text));
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_CLOSE:
	{
		KillTimer(hwnd, 1);

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

