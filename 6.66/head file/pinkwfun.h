#ifndef _PINKWFUN_H_
#define _PINKWFUN_H_

#ifndef _STDIO_H
# include <stdio.h>
#endif

#define LL long long

int leap(LL year)
{
	if(year%400==0)
		return 1;
	else if(year%4==0&&year%100!=0)
		return 1;
	else
		return 0;
}

int pChooseFont(HWND hwnd, HFONT* p_hfont, int height, int* p_textRGB)
{
	CHOOSEFONT cf = {sizeof(CHOOSEFONT)};
	LOGFONT lf;

	GetObject(*p_hfont, sizeof(LOGFONT), &lf);

	cf.Flags = CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
	cf.hwndOwner = hwnd;
	cf.lpLogFont = &lf;
	cf.rgbColors = 0xdf85a0;

	pReportError(hwnd, 0xf250);
	int x=ChooseFont(&cf);
	if(x){
		lf.lfHeight=height;
		*p_hfont=CreateFontIndirect(&lf);
	}
	else
		SetLastError(0);
	return x;
}

#undef LL

#endif