#include <windows.h>
#include <__pink/pinkwin.h>
#include <__pink/pbitmap.h>

LRESULT (__attribute__((__stdcall__)) WndProc) (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

int __attribute__((__stdcall__)) WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const char _P_win_class_[]="_P_win_class_";

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize	=sizeof(WNDCLASSEX);
	wc.style	=0;
	wc.lpfnWndProc	=WndProc;
	wc.cbClsExtra	=0;
	wc.cbWndExtra	=0;
	wc.hInstance	=hInstance;
	wc.hIcon	=LoadIcon(hInstance, MAKEINTRESOURCE(PI_WH));
	wc.hCursor	=LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground=CreateSolidBrush(pRGB(0xffffff));
	wc.lpszMenuName	=MAKEINTRESOURCE(PM_STDM);
	wc.lpszClassName=_P_win_class_;
	wc.hIconSm	=LoadIcon(hInstance, MAKEINTRESOURCE(PI_WH));

	RegisterClassEx(&wc);
	__ReportError(NULL, 0, 0);

	hwnd=CreateWindowEx(
		WS_EX_CLIENTEDGE,
		_P_win_class_,
		"WhiteHat - WinAPI 1.01",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1025, 525,
		NULL, NULL, hInstance, NULL);
	__ReportError(NULL, 0, 1);

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}
//end WinMain

#define TimerID 1
#define Live2d_MOVE_DELTA 1
HBITMAP hbmLive2d=NULL;
HBITMAP hbmMask=NULL;
ANIMINFO animinfo;

LRESULT (__attribute__((__stdcall__)) WndProc) (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_CREATE:
		{
			BITMAP bm;

			hbmLive2d=pLoadBMP(BMP_live2d);
			hbmMask=pMaskBMP(hbmLive2d, pRGB(0));
			GetObject(hbmLive2d, sizeof(bm), &bm);

			animinfo.width=bm.bmWidth;
			animinfo.height=bm.bmHeight;
			animinfo.x=0;
			animinfo.y=0;
			animinfo.dx=Live2d_MOVE_DELTA;
			animinfo.dy=Live2d_MOVE_DELTA;

			SetTimer(hwnd, TimerID, 10, NULL);
		}
			__ReportError(hwnd, WM_CREATE, 0);
		break;
		case WM_PAINT:
		{
			RECT rect;
			PAINTSTRUCT ps;
			HDC hdc=BeginPaint(hwnd, &ps);

//			pRectInit(rect, animinfo.x, animinfo.y, animinfo.x+animinfo.width, animinfo.y+animinfo.height);

			GetClientRect(hwnd, &rect);
			pDrawAnim(hdc, hbmLive2d, hbmMask, &animinfo, &rect);
			EndPaint(hwnd, &ps);
		}
			__ReportError(hwnd, WM_PAINT, 0);
		break;
		case WM_TIMER:
		{
			RECT rect;PAINTSTRUCT ps;
			HDC hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rect);

			pUpdateAnim(&animinfo, &rect, Live2d_MOVE_DELTA);
			pDrawAnim(hdc, hbmLive2d, hbmMask, &animinfo, &rect);

			ReleaseDC(hwnd, hdc);
		}
			SetLastError(0);
		break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;
		case WM_DESTROY:
			KillTimer(hwnd, TimerID);
			DeleteObject(hbmLive2d);
			DeleteObject(hbmMask);
			PostQuitMessage(0);
		break;
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

