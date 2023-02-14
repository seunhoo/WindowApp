#include "stdafx.h"
#include "util.h"

HWND hwndTextButton = NULL;
HWND hwndBackButton = NULL;
HWND hTextBox = NULL;

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
		DestroyWindow(hwnd);
		break;
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

void MakeMainControl(HWND hwnd)
{
	// Ÿ�̸� ���� 
	SetTimer(hwnd, 1, 1000, NULL);
	SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, DEFAULT_X, DEFAULT_Y, SWP_NOZORDER | SWP_NOMOVE);

	// textbox ��Ʈ�� ����
	hTextBox = CreateWindowEx(0, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, TEXTBOX_X, TEXTBOX_Y, hwnd, (HMENU)ID_TEXTBOX, GetModuleHandle(NULL), NULL);
	SetWindowPos(hTextBox, HWND_TOP, (iWidth - TEXTBOX_X) / 2, (iHeight - TEXTBOX_Y) / 2 - 50, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// ��ư ��Ʈ�� ���� ( textbox ���� )
	hwndTextButton = CreateWindowW(L"BUTTON", L"Ŭ��!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_TEXT_BUTTON, NULL, NULL);
	SetWindowPos(hwndTextButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// ��ư ��Ʈ�� ���� ( ��� �ٲٱ� )
	hwndBackButton = CreateWindowW(L"BUTTON", L"���ٲٱ�", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_BACK_COLOR_BUTTON, NULL, NULL);
	SetWindowPos(hwndBackButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2 + 60, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// ��ư ��Ʈ�� ���� ( �̹��� ��� )
	hwndBackButton = CreateWindowW(L"BUTTON", L"�̹������", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 0, BUTTON_X, BUTTON_Y, hwnd, (HMENU)ID_IMAGE_BUTTON, NULL, NULL);
	SetWindowPos(hwndBackButton, HWND_TOP, (iWidth - BUTTON_X) / 2, (iHeight - BUTTON_Y) / 2 + 120, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

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
	MessageBoxW(NULL, buffer, L"���� �Է���", MB_OK);
	delete[] buffer;
}
