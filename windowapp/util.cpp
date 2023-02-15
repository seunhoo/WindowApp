#include "stdafx.h"
#include "util.h"

HWND hTextBox = NULL;
HWND hwndTextButton = NULL;
HWND hwndBackButton = NULL;
HWND hwndImageButton = NULL;
HWND hwndClickButton = NULL;

atomic<bool> bWhile(false);

void ClickerThread() {
	while (bWhile) {
		POINT p;
		GetCursorPos(&p);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, p.x, p.y, 0, 0);
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void SetWidthHeight(HWND hwnd)
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    iWidth = rect.right - rect.left;
    iHeight = rect.bottom - rect.top;
}

void KeyMapping(HWND hwnd, WPARAM wParam)
{
	switch (wParam)
	{
	case VK_ESCAPE:
	{
		DestroyWindow(hwnd);
		break;
	}	
	case VK_F5:
	{
		if (!bWhile.load())
		{
			bWhile = (true);
			thread t(ClickerThread);
			t.detach();
		}
		break;
	}
	case VK_F6:
	{
		bWhile = false;
		bWhile.store(false);
		break;
	}
	default:
		break;
	}
}

void ChangeBackGroundColor(HWND hwnd, COLORREF crf)
{
	HDC hdc = GetDC(hwnd);
	HBRUSH hBrush = CreateSolidBrush(crf);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
	RECT rect;
	GetClientRect(hwnd, &rect);
	FillRect(hdc, &rect, hBrush);
	//SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
	SelectObject(GetDC(hwnd), hOldBrush);
	DeleteObject(hBrush);
	ReleaseDC(hwnd, hdc);
}

void MakeImage(HWND hwnd, LPCWSTR imagename, int x , int y)
{
	Gdiplus::Graphics graphics(hwnd);
	Image image(imagename);
	graphics.DrawImage(&image, x, y, image.GetWidth(), image.GetHeight());
}

void MakeText(HWND hwnd, LPCWSTR text, int x, int y)
{
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	HDC hdc = BeginPaint(hwnd, &ps);
	GetTextMetrics(hdc, &tm);

	int a_x = (x - tm.tmAveCharWidth * _tcslen(text));
	int a_y = (y - tm.tmHeight);

	TextOut(hdc, a_x, a_y, text, _tcslen(text));
	EndPaint(hwnd, &ps);
}

void GetTextBoxText()
{
	int length = GetWindowTextLengthW(hTextBox) + 1;
	wchar_t* buffer = new wchar_t[length];
	GetWindowTextW(hTextBox, buffer, length);
	MessageBoxW(NULL, buffer, L"내가 입력한", MB_OK);
	delete[] buffer;
}



void MakeMainControl(HWND hwnd)
{
	// 타이머 설정 
	SetTimer(hwnd, 1, 1000, NULL);
	SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, DEFAULT_X, DEFAULT_Y, SWP_NOZORDER | SWP_NOMOVE);

	// textbox 컨트롤 생성
	hTextBox = CreateWindowEx(0, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, TEXTBOX_X, TEXTBOX_Y, hwnd, (HMENU)ID_TEXTBOX, GetModuleHandle(NULL), NULL);
	SetWindowPos(hTextBox, HWND_TOP, (iWidth - TEXTBOX_X) / 2, (iHeight - TEXTBOX_Y) / 2 - 50, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// 버튼 컨트롤 생성 ( textbox 연계 )
	hwndTextButton = CreateWindowW(L"BUTTON", L"입력한거", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_TEXT_BUTTON, NULL, NULL);
	SetWindowPos(hwndTextButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// 버튼 컨트롤 생성 ( 배경 바꾸기 )
	hwndBackButton = CreateWindowW(L"BUTTON", L"배경바꾸기", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_BACK_COLOR_BUTTON, NULL, NULL);
	SetWindowPos(hwndBackButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2 + 60, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// 버튼 컨트롤 생성 ( 이미지 출력 )
	hwndImageButton = CreateWindowW(L"BUTTON", L"이미지출력", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_IMAGE_BUTTON, NULL, NULL);
	SetWindowPos(hwndImageButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2 + 120, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// 버튼 컨트롤 생성 ( 클릭 횟수 출력 )
	hwndClickButton = CreateWindowW(L"BUTTON", L"클릭!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_CLICK_BUTTON, NULL, NULL);
	SetWindowPos(hwndClickButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2 + 180, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

}
