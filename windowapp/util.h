#pragma once

#ifndef __UTIL_H__
#define __UTIL_H__

void SetWidthHeight(HWND hwnd);

void MakeMainControl(HWND hwnd);
void MakeImage(HWND hwnd, LPCWSTR imagename, int x, int y);
void MakeText(HWND hwnd, LPCWSTR text, int x, int y);


void KeyMapping(HWND hwnd, WPARAM wParam);

void ChangeBackGroundColor(HWND hwnd, COLORREF crf);

void GetTextBoxText();



static int iWidth = 0, iHeight = 0;
static int iCount = 0;


class util
{
};


#endif // !__UTIL_H__



