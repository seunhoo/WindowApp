#include "framework.h"
#include "util.h"

void GetWidthHeight(HWND hwnd, int* width, int* height)
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    *width = rect.right - rect.left;
    *height = rect.bottom - rect.top;
}
