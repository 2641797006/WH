#include <windows.h>
#include <stdio.h>
#include <__pink/pinkwin.h>
#include <C:/Users/26417/Desktop/pinkwfun.h>

HDC hdc;
HWND hwndc;
PAINTSTRUCT ps;
HFONT hfont=NULL;
HINSTANCE hInstance=NULL;
int x, y, fontstr_=0, fontdx_=3, italic=0, pCM, textRGB[8]={0, 0xdf85a0, 0xf44336, 0xffc107, 0x8bc349, 0x2095f3, 0x9c27c4, 0x9d91ca}, textRGB_=0;
char s[1024];
char *fontstr[5]={"Courier New", "Times New Roman", "Verdana", "SimHei", "KaiTi"};
float fontdx[15]={0.35, 0.40, 0.45, 0.49, 0.55,
		  0.60, 0.65, 0.70, 0.75, 0.80,
		  0.90, 1.00, 1.15, 1.33, 2.50};

pinkcfun(BOOL,AskAuthorProc)
{
	switch(Message)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case 1:
					EndDialog(hwnd, 1);
			}
		break;
		default:;
	}
	return 0;
}

pinkfunc()
{
	switch(Message)
	{
		case WM_CREATE:
			CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_ACCEPTFILES, "EDIT", "判断闰年：",
				WS_CHILD|WS_VISIBLE|WS_BORDER|ES_LEFT|ES_MULTILINE|ES_AUTOVSCROLL|WS_VSCROLL|ES_NOHIDESEL,
				10, 10, 1000, 500,
				hwnd, (HMENU)1001, hInstance, NULL);
/*			CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_STATICEDGE, "BUTTON", "scanf",
				WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON,
				800, 43, 100, 50,
				hwnd, (HMENU)2001, hInstance, NULL);
*//*			sprintf(s,"%s","This Font is SYSTEM_FONT\nThis is an easy win32 GUI app.\nJust for test\nIt can only 判断 whether a year is leap year\nIt may not be beautiful");
			CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_STATICEDGE, "STATIC", s,
				WS_CHILD|WS_VISIBLE|WS_BORDER,
				200, 200, 612, 100,
				hwnd, (HMENU)3001, hInstance, NULL);
*/			pHeightCM(pCM);
			hfont=CreateFont(pCM*fontdx[fontdx_], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");
			pSetRadio3(hwnd, 2, 3, 0, 6, 0);
			pSetRadio3(hwnd, 2, 4, 0, 14, fontdx_);
			pSetRadio3(hwnd, 2, 5, 0, 7, textRGB_);
			pSetCwinFont(hwnd, 1001, hfont);
/*			CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_STATICEDGE, "STATIC", "",
				WS_CHILD|WS_VISIBLE|WS_BORDER,
				50, 50, 150, 50,
				hwnd, (HMENU)3002, hInstance, NULL);
*/		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case 2001:
					switch(HIWORD(wParam))
					{
						case BN_CLICKED:
							hwndc=GetDlgItem(hwnd,1001);
							s[0]=1;
							GetWindowText(hwndc,s+1,1000);
							if( sscanf(s,"%*[^0-9]%d",&y)!=1 ){
								MessageBox(hwndc,"Failed to read data","Error",MB_ABORTRETRYIGNORE|MB_ICONSTOP);
								break;
							}
							if(leap(y)==1){
								sprintf(s,"%d年是闰年",y);
								MessageBox(hwndc,s,"The result",MB_OK);
							}
							else{
								sprintf(s,"%d年不是闰年",y);
								MessageBox(hwndc,s,"The result",MB_OK|MB_ICONWARNING);
							}
						break;
						default:;
					}
				break;
				case STDM_FILE_1:
					SetDlgItemText(hwnd,3002,"判断闰年");
				break;
				case STDM_FILE_2:
					SetDlgItemText(hwnd,3002,"判断质数");
				break;
				case STDM_SHTU_1:
					if(pSetChecked(hwnd, 2, 0)!=MF_CHECKED)
						pSetToTop(hwnd);
					else{
						pSetNoTop(hwnd);
						pSetUnchecked(hwnd, 2, 0);
					}
					pReportError(hwnd, STDM_SHTU_1);
				break;
				case STDM_SHTU_2:
					SetLastError(0x7456);
					pReportError(hwnd, STDM_SHTU_2);
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
					pSetCwinFont(hwnd, 1001, hfont);
					pReportError(hwnd, LOWORD(wParam));
				break;
				case STDM_SHTU_3C6:
					if( pChooseFont(hwnd, &hfont, pCM*fontdx[fontdx_], &textRGB[textRGB_]) ){
						pSetCwinFont(hwnd, 1001, hfont);
						pSetRadio3(hwnd, 2, 3, 0, 6, 6);
					}
					pReportError(hwnd, STDM_SHTU_3C6);
				break;
				case STDM_SHTU_4C1: case STDM_SHTU_4C2: case STDM_SHTU_4C3: case STDM_SHTU_4C4: case STDM_SHTU_4C5:
				case STDM_SHTU_4C6: case STDM_SHTU_4C7: case STDM_SHTU_4C8: case STDM_SHTU_4C9: case STDM_SHTU_4C10:
				case STDM_SHTU_4C11:case STDM_SHTU_4C12:case STDM_SHTU_4C13:case STDM_SHTU_4C14:case STDM_SHTU_4C15:
					DeleteObject(hfont);
					fontdx_=LOWORD(wParam)-STDM_SHTU_4C1;
					pSetRadio3(hwnd, 2, 4, 0, 14, fontdx_);
					hfont=CreateFont(pCM*(fontdx[fontdx_]+0.04*italic), 0, 0, 0, 0, italic, 0, 0, 0, 0, 0, 0, 0, fontstr[fontstr_]);
					pSetCwinFont(hwnd, 1001, hfont);
					pReportError(hwnd, LOWORD(wParam));
				break;
				case STDM_SHTU_5C1: case STDM_SHTU_5C2: case STDM_SHTU_5C3: case STDM_SHTU_5C4:
				case STDM_SHTU_5C5: case STDM_SHTU_5C6: case STDM_SHTU_5C7: case STDM_SHTU_5C8:
					hwndc=GetDlgItem(hwnd,1001);
					textRGB_=LOWORD(wParam)-STDM_SHTU_5C1;
					hdc=BeginPaint(hwndc, &ps);
					SetTextColor(hdc, textRGB[textRGB_]);

					EndPaint(hwndc, &ps);
					pSetRadio3(hwnd, 2, 5, 0, 7, textRGB_);
					pReportError(hwnd, LOWORD(wParam));
				break;
				case STDM_EXIT_1:
					ShowWindow(hwnd, SW_MINIMIZE);
				break;
				case STDM_EXIT_2:
					PostQuitMessage(0);
				break;
				case STDM_EXIT_3:
					LockWorkStation();
					pReportError(hwnd, STDM_EXIT_3);
				break;
				case STDM_INIT_1:
					ShellExecute(hwnd, "open", "cmd.exe", NULL, NULL, SW_SHOWNORMAL);
					pReportError(hwnd, STDM_INIT_1);
				break;
				case STDM_INIT_2:
					p2Key(VK_LWIN, 'D');
				break;
				case STDM_INIT_3C1C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-s -t 60", NULL, SW_HIDE);
					pReportError(hwnd, STDM_INIT_3C1C1);
				break;
				case STDM_INIT_3C2C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-f -s -t 0", NULL, SW_HIDE);
					pReportError(hwnd, STDM_INIT_3C2C1);
				break;
				case STDM_INIT_3C3C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-h", NULL, SW_HIDE);
					pReportError(hwnd, STDM_INIT_3C3C1);
				break;
				case STDM_INIT_4C1C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-r -t 60", NULL, SW_HIDE);
					pReportError(hwnd, STDM_INIT_4C1C1);
				break;
				case STDM_INIT_4C2C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-f -r -t 0", NULL, SW_HIDE);
					pReportError(hwnd, STDM_INIT_4C2C1);
				break;
				case STDM_INIT_5C1C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-o -r -t 60", NULL, SW_HIDE);
					pReportError(hwnd, STDM_INIT_5C1C1);
				break;
				case STDM_INIT_5C2C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-o -r -t 0", NULL, SW_HIDE);
					pReportError(hwnd, STDM_INIT_5C2C1);
				break;
				case STDM_INIT_6C1C1:
					ShellExecute(hwnd, "open", "shutdown.exe", "-l", NULL, SW_HIDE);
					pReportError(hwnd, STDM_INIT_6C1C1);
				break;
				case STDM_HELP_1:
					ShellExecute(hwnd, "open", "http://www.baidu.com/", NULL, NULL, SW_SHOWNORMAL);
					pReportError(hwnd, STDM_HELP_1);
				break;
				case STDM_HELP_2:
					ShellExecute(hwnd, "open", "http://www.bing.com/", NULL, NULL, SW_SHOWNORMAL);
					pReportError(hwnd, STDM_HELP_2);
				break;
				case STDM_HELP_3:
					ShellExecute(hwnd, "open", "http://www.google.com/", NULL, NULL, SW_SHOWNORMAL);
					pReportError(hwnd, STDM_HELP_3);
				break;
				case STDM_HELP_4:
					x=DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(PD_Ask_Author), hwnd, AskAuthorProc);
					if(x==1)
						MessageBox(hwnd, "The Author is Coding... You can send messages to the author through the mail yongxxone@gmail.com", "Contact the author", MB_OK);	
				break;
				case STDM_HELP_5:
					ShellExecute(hwnd, "open", "mailto:yongxxone@gmail.com?subject=错误反馈(WH6.66)&body=┻━┻︵╰(‵□′)╯︵┻━┻%0d%0a出错啦啊啊啊!!!%0d%0a此处填写错误:%0d%0a%0d%0a%0d%0a%0d%0a", NULL, NULL, SW_SHOWNORMAL);
					pReportError(hwnd, STDM_HELP_5);
				break;
				case STDM_ADMIN_1:
					pGetAdmin();
				break;
				case STDM_ADMIN_2C1:
					sprintf(s,"/c del ");
					pExeName(s+7);
					ShellExecute(hwnd, "open", "cmd.exe", s, NULL, SW_HIDE);
					pReportError(hwnd, STDM_ADMIN_2C1);
					PostQuitMessage(0);
				break;
				default:;
			}
		break;
/*		case WM_PAINT:
hwndc=GetDlgItem(hwnd,1001);
					{
						HDC hdc=GetDC(hwndc);
						SetTextColor(hdc, textRGB[textRGB_]);
						ReleaseDC(hwndc, hdc);
					}
		break;
*/		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;
		case WM_DESTROY:
			DeleteObject(hfont);
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}

pinkwinA();