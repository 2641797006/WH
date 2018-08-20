//C”Ô—‘, WinAPI
//±‡“Î∆˜: MinGW-w64(x86_64, posix, seh)

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <__pink/pinkwin.h>
#include <C:/Users/26417/Desktop/pinkwfun.h>

HDC hdc;
RECT rect;
HWND hwndc, hwndEdit, hwndStatic;
HBRUSH hbrush;
HMODULE hmodule;
PAINTSTRUCT ps;
HFONT hfont, hfontc, hfont1, hfont2;
HINSTANCE hInst;
int x, y, fontstr_=0, fontdx_=3, italic=0, pCM, textRGB[8]={0, 0xdf85a0, 0xf44336, 0xffc107, 0x8bc349, 0x2095f3, 0x9c27c4, 0x9d91ca}, textRGB_=1;
char s[2048];
char *fontstr[5]={"Courier New", "Times New Roman", "Verdana", "SimHei", "KaiTi"};
float fontdx[15]={0.35, 0.40, 0.45, 0.49, 0.55,
		  0.60, 0.65, 0.70, 0.75, 0.80,
		  0.90, 1.00, 1.15, 1.33, 2.50};

pinkfunc()
{
	switch(Message)
	{
		case WM_CREATE:
			hwndEdit=CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
				"EDIT", "∆’Õ®±‡º≠øÿº˛ Type here: ",
				ES_MULTILINE | ES_AUTOVSCROLL | ES_NOHIDESEL | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VSCROLL,
				120, 15, 765, 200,
				hwnd, (HMENU)1001, hInst, NULL);
			__ReportError(hwnd, WM_CREATE, 0x100);
			sprintf(s,"jleap.exe(WH)\r\n\r\n ◊≤‚”√¿˝: ≈–∂œ»ÚƒÍ\r\nª∂”≠∑¥¿°BUG: ≤Àµ•-> Help-> ¥ÌŒÛ∑¥¿°");
			hwndStatic=CreateWindowEx(WS_EX_DLGMODALFRAME, "EDIT", s,
				ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL | ES_CENTER | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VSCROLL,
				120, 250, 765, 200,
				hwnd, (HMENU)2001, hInst, NULL);
			__ReportError(hwnd, WM_CREATE, 0x200);
			CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, "STATIC", "≈–∂œ»ÚƒÍ",
				SS_CENTER | SS_CENTERIMAGE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP,
				10, 95, 100, 36,
				hwnd, (HMENU)2002, hInst, NULL);
			CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, "STATIC", "printf",
				SS_CENTER | SS_CENTERIMAGE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP,
				10, 320, 100, 36,
				hwnd, (HMENU)2003, hInst, NULL);
			CreateWindowEx(0, "BUTTON", "scanf",
				BS_PUSHBUTTON | BS_FLAT | WS_VISIBLE | WS_CHILD | WS_TABSTOP,
				895, 95, 100, 36,
				hwnd, (HMENU)3001, hInst, NULL);
			__ReportError(hwnd, WM_CREATE, 0x300);
			pHeightCM(pCM);
			hfont=CreateFont(pCM*fontdx[fontdx_], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");
			hfont1=CreateFont(pCM*0.50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");
			hfontc=CreateFont(pCM*0.55, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
			SendMessage(hwndEdit, WM_SETFONT, (WPARAM)hfont, (LPARAM)0);
			SendDlgItemMessage(hwnd, 2001, WM_SETFONT, (WPARAM)hfont1, (LPARAM)0);
			SendDlgItemMessage(hwnd, 2002, WM_SETFONT, (WPARAM)hfont1, (LPARAM)0);
			SendDlgItemMessage(hwnd, 2003, WM_SETFONT, (WPARAM)hfontc, (LPARAM)0);
			SendDlgItemMessage(hwnd, 3001, WM_SETFONT, (WPARAM)hfontc, (LPARAM)0);
			pSetRadio3(hwnd, 2, 3, 0, 6, 0);
			pSetRadio3(hwnd, 2, 4, 0, 14, fontdx_);
			pSetRadio3(hwnd, 2, 5, 0, 7, textRGB_);
			hbrush=GetStockObject(WHITE_BRUSH);
			__ReportError(hwnd, WM_CREATE, 0x400);
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case 3001:
					switch(HIWORD(wParam))
					{
						case BN_CLICKED:
							s[0]=1; x=-1;
							GetWindowText(hwndEdit,s+1,1000);
							if( sscanf(s,"%*[^0-9]%d",&y)!=1 )
								MessageBox(hwndEdit,"Failed to read data","Error",MB_ABORTRETRYIGNORE|MB_ICONSTOP);
							else{
								x=leap(y);
								if(x==1){
									sprintf(s,"%dƒÍ «»ÚƒÍ",y);
									MessageBox(hwndEdit,s,"The result",MB_OK);
								}
								else{
									sprintf(s,"%dƒÍ≤ª «»ÚƒÍ",y);
									MessageBox(hwndEdit,s,"The result",MB_OK|MB_ICONWARNING);
								}
							}
							Leap_Static(hwndStatic, x, y, s);
							GetScrollRange(hwndStatic, SB_VERT, &x, &y);
							__ReportError(hwnd, 3001, 0);
							SendMessage(hwndStatic, WM_VSCROLL, (WPARAM)pHLWORD(y, SB_THUMBPOSITION), (LPARAM)NULL);
							SetLastError(0);
						break;
						default:;
					}
				break;
				case STDM_SHTU_1:
					if(pSetChecked(hwnd, 2, 0)!=MF_CHECKED)
						pSetToTop(hwnd);
					else{
						pSetNoTop(hwnd);
						pSetUnchecked(hwnd, 2, 0);
					}
					__ReportError(hwnd, STDM_SHTU_1, 0);
				break;
				case STDM_SHTU_2:
					SetLastError(0x7456);
					__ReportError(hwnd, STDM_SHTU_2, 0x7456);
				break;
				case STDM_SHTU_3C1: case STDM_SHTU_3C2: case STDM_SHTU_3C3: case STDM_SHTU_3C4: case STDM_SHTU_3C5:
					DeleteObject(hfont);
					switch(LOWORD(wParam))
					{
						case STDM_SHTU_3C2:
							italic=1;
						break;
						default:
							italic=0;
					}
					fontstr_=LOWORD(wParam)-STDM_SHTU_3C1;
					pSetRadio3(hwnd, 2, 3, 0, 6, fontstr_);
					hfont=CreateFont(pCM*(fontdx[fontdx_]+0.04*italic), 0, 0, 0, 0, italic, 0, 0, 0, 0, 0, 0, 0, fontstr[fontstr_]);
					pSetWinFont(hwndEdit, hfont);
					__ReportError(hwnd, LOWORD(wParam), 0);
				break;
				case STDM_SHTU_3C6:
					if( pChooseFont(hwnd, &hfont, pCM*fontdx[fontdx_], &textRGB[textRGB_]) ){
						pSetWinFont(hwndEdit, hfont);
						pSetRadio3(hwnd, 2, 3, 0, 6, 6);
					}
					__ReportError(hwnd, STDM_SHTU_3C6, 0);
				break;
				case STDM_SHTU_4C1: case STDM_SHTU_4C2: case STDM_SHTU_4C3: case STDM_SHTU_4C4: case STDM_SHTU_4C5:
				case STDM_SHTU_4C6: case STDM_SHTU_4C7: case STDM_SHTU_4C8: case STDM_SHTU_4C9: case STDM_SHTU_4C10:
				case STDM_SHTU_4C11:case STDM_SHTU_4C12:case STDM_SHTU_4C13:case STDM_SHTU_4C14:case STDM_SHTU_4C15:
					DeleteObject(hfont);
					fontdx_=LOWORD(wParam)-STDM_SHTU_4C1;
					pSetRadio3(hwnd, 2, 4, 0, 14, fontdx_);
					hfont=CreateFont(pCM*(fontdx[fontdx_]+0.04*italic), 0, 0, 0, 0, italic, 0, 0, 0, 0, 0, 0, 0, fontstr[fontstr_]);
					pSetWinFont(hwndEdit, hfont);
					__ReportError(hwnd, LOWORD(wParam), 0);
				break;
				case STDM_SHTU_5C1: case STDM_SHTU_5C2: case STDM_SHTU_5C3: case STDM_SHTU_5C4:
				case STDM_SHTU_5C5: case STDM_SHTU_5C6: case STDM_SHTU_5C7: case STDM_SHTU_5C8:
					textRGB_=LOWORD(wParam)-STDM_SHTU_5C1;
					pSetWinFont(hwndEdit, hfont);
					pSetRadio3(hwnd, 2, 5, 0, 7, textRGB_);
					SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (long)CreateSolidBrush( pRGB(textRGB[ textRGB_+NY3(textRGB_)*5 ]) ) );
					InvalidateRect(hwnd, NULL, TRUE);
					__ReportError(hwnd, LOWORD(wParam), 0);
				break;
				case STDM_INIT_1:
					ShellExecute(hwnd, "open", "cmd.exe", NULL, NULL, SW_SHOWNORMAL);
					__ReportError(hwnd, STDM_INIT_1, 0);
				break;
				case STDM_INIT_2:
					p2Key(VK_LWIN, 'D');
				break;
				case STDM_INIT_3C1C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-s -t 60", NULL, SW_HIDE);
					__ReportError(hwnd, STDM_INIT_3C1C1, 0);
				break;
				case STDM_INIT_3C2C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-f -s -t 0", NULL, SW_HIDE);
					__ReportError(hwnd, STDM_INIT_3C2C1, 0);
				break;
				case STDM_INIT_3C3C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-h", NULL, SW_HIDE);
					__ReportError(hwnd, STDM_INIT_3C3C1, 0);
				break;
				case STDM_INIT_4C1C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-r -t 60", NULL, SW_HIDE);
					__ReportError(hwnd, STDM_INIT_4C1C1, 0);
				break;
				case STDM_INIT_4C2C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-f -r -t 0", NULL, SW_HIDE);
					__ReportError(hwnd, STDM_INIT_4C2C1, 0);
				break;
				case STDM_INIT_5C1C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-o -r -t 60", NULL, SW_HIDE);
					__ReportError(hwnd, STDM_INIT_5C1C1, 0);
				break;
				case STDM_INIT_5C2C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-o -r -t 0", NULL, SW_HIDE);
					__ReportError(hwnd, STDM_INIT_5C2C1, 0);
				break;
				case STDM_INIT_6C1C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-l", NULL, SW_HIDE);
					__ReportError(hwnd, STDM_INIT_6C1C1, 0);
				break;
				case STDM_INIT_7:
					LockWorkStation();
					__ReportError(hwnd, STDM_INIT_6C1C1, 0);
				break;
				case STDM_HELP_1:
					ShellExecute(hwnd, "open", "http://www.baidu.com/", NULL, NULL, SW_SHOWNORMAL);
					__ReportError(hwnd, STDM_HELP_1, 0);
				break;
				case STDM_HELP_2:
					ShellExecute(hwnd, "open", "http://www.bing.com/", NULL, NULL, SW_SHOWNORMAL);
					__ReportError(hwnd, STDM_HELP_2, 0);
				break;
				case STDM_HELP_3:
					ShellExecute(hwnd, "open", "http://www.google.com/", NULL, NULL, SW_SHOWNORMAL);
					__ReportError(hwnd, STDM_HELP_3, 0);
				break;
				case STDM_HELP_5:
					ShellExecute(hwnd, "open", "mailto:yongxxone@gmail.com?subject=¥ÌŒÛ∑¥¿°(WH6.66)&body=©ﬂ©•©ﬂ¶‡®t(®F°ı°‰)®s¶‡©ﬂ©•©ﬂ%0d%0a≥ˆ¥Ì¿≤∞°∞°∞°!!!%0d%0a¥À¥¶ÃÓ–¥¥ÌŒÛ:%0d%0a%0d%0a%0d%0a%0d%0a", NULL, NULL, SW_SHOWNORMAL);
					__ReportError(hwnd, STDM_HELP_5, 0);
				break;
				case STDM_ADMIN_1:
					pGetAdmin();
				break;
				case STDM_ADMIN_2C1:
					sprintf(s,"/c del ");
					pExeName(s+7);
					ShellExecute(hwnd, "open", "cmd.exe", s, NULL, SW_HIDE);
					__ReportError(hwnd, STDM_ADMIN_2C1, 0);
					DestroyWindow(hwnd);
				break;
				case STDM_ADMIN_3:
					ShellExecute(hwnd, "open", "https://github.com/2641797006/WH/tree/master/6.66/", NULL, NULL, SW_SHOWNORMAL);
					__ReportError(hwnd, STDM_ADMIN_3, 0);
				default:;
			}
		break;
		case WM_CTLCOLOREDIT:
			SetTextColor((HDC)wParam, pRGB(textRGB[textRGB_]));
			return (LRESULT)hbrush;
		break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;
		case WM_DESTROY:
			DeleteObject(hfont);
			DeleteObject(hfontc);
			DeleteObject(hfont1);
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}

pinkwinA();