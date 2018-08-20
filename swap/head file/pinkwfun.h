#ifndef _PINKWFUN_H_
#define _PINKWFUN_H_

#define QY3(x) ( (x+999)/1000 )
#define NY3(x) ( ( QY3(x)+1 )%2 )

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
	cf.rgbColors = 0xa085df;

	int x=ChooseFont(&cf);
	if(x){
		lf.lfHeight=height;
		*p_hfont=CreateFontIndirect(&lf);
	}
	else
		SetLastError(0);
	return x;
}

int Leap_Static(HWND hwnd, int x, int y, char* s)
{
	int n=0;
	char *ps=s, ss[64];
	time_t t;
	struct tm* ptm;
	GetWindowText(hwnd, s, 1000);
	n=GetWindowTextLength(hwnd);
//	for(; (ps=strchr(ps, '\n'))!=NULL ;n++,ps++){}
	t=time(NULL);
	ptm=localtime(&t);
	strftime(ss, sizeof(ss), "\r\n%H:%M:%S - ", ptm);
	if(x==-1)
		strcat(ss, "读取年份数据失败");
	else if(x==0)
		sprintf(ss+strlen(ss), "%d年不是闰年", y);
	else
		sprintf(ss+strlen(ss), "%d年是闰年", y);
	strcat(s, ss);
	if(n<1800)
		SetWindowText(hwnd, s);
	else{
		ps=strchr(s, '\n');
		SetWindowText(hwnd, ps+1);
	}
	return 0;
}


#undef LL

#endif