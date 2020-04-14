#include<windows.h>
#include"resource.h"
#include"tchar.h"

//定义ID
#define IDC_BTN_LEFT  5884
#define IDC_BTN_RIGHT 5886

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
//自定义字体
void MakeFont(HDC hdc);
HWND hwnd,hwnd1,hwnd2;
HBITMAP hBm;
BITMAP bm;
int iWindowWidth;
int iWindowHeight;
HDC hDC;
HDC hdcmem;
PAINTSTRUCT ps;
HINSTANCE hInstance_1;
int x,y;
int x1=450,y1=300;
int x2=450,y2=150;
int x3=200,y3=200;
int x4=30,y4=160;
int x5=540,y5=200;
int t1,t2;
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInst,
                   LPSTR     lpszCmdLine,
                   int       nCmdShow)
{
    //HWND hwnd;
    MSG Msg;

    //用HBITMAP指向资源内的图片
	hBm = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
    //读取该图片到BITMAP结构体中
    GetObject(hBm,sizeof(BITMAP),&bm);
    //根据图片大小获取窗口大小
    iWindowWidth = bm.bmWidth;
    iWindowHeight = bm.bmHeight;

    WNDCLASS wndclass;
    char lpszClassName[]="窗口";
    char lpszTitle[]="biubiu";


    wndclass.style=0;
    wndclass.lpfnWndProc=WndProc;
    wndclass.cbClsExtra=0;
    wndclass.cbWndExtra=0;
    wndclass.hInstance=hInstance;
	wndclass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
    wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName=NULL;
    wndclass.lpszClassName=lpszClassName;
    if(! RegisterClass(&wndclass))
    {
        MessageBeep(0);
        return FALSE;
    }
    hwnd=CreateWindow(lpszClassName,
        lpszTitle,
		WS_EX_TOOLWINDOW|WS_POPUP,
        /*WS_CAPTION  |WS_SYSMENU ,*/
       
	   350,150,
       // iWindowWidth,iWindowHeight,
		600,400,
        NULL,
        NULL,
        hInstance,
        NULL);
    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);
	
    while(GetMessage(&Msg,NULL,0,0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return (int)Msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM
                         lParam)
{
	x=LOWORD(lParam);
	y=HIWORD(lParam);
    switch(message)
    {
    case WM_CREATE:
		hwnd1=CreateWindow(_T("Button"), _T("爱"), BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,

									350, 300 , 60, 30, hwnd, HMENU(IDC_BTN_LEFT), hInstance_1, NULL);
		hwnd2=CreateWindow(_T("Button"), _T("不爱"), BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,

									470, 300 , 60, 30, hwnd, HMENU(IDC_BTN_RIGHT), hInstance_1, NULL);
        //获取设备描述表
        hDC = GetDC(hwnd);
        //在内存中创建与hDC相同的设备描述表
        hdcmem = CreateCompatibleDC(hDC);
        //释放设备描述表
        ReleaseDC(hwnd,hDC);
        break;
	case WM_MOUSEMOVE:
		if(((x>=x1-25)&&(x<=x1+65))&&((y>=y1-25)&&(y<=y1+45)))
		{
		MoveWindow(hwnd2,x2,y2,60,30,true);
		
		t1=x1;
		t2=y1;
		x1=x2;
		y1=y2;
		x2=x3;
		y2=y3;
		x3=x4;
		y3=y4;
		x4=x5;
		y4=y5;
		x5=t1;
		y5=t2;
		}
		break;
	case WM_COMMAND:

		if(LOWORD(wParam) == IDC_BTN_LEFT)
		{
			MessageBox(hwnd,"果然，你是爱我的","hahaha",MB_OK);
			Sleep(1000);
			PostQuitMessage(0);
		}
		if(LOWORD(wParam) == IDC_BTN_RIGHT)
		{
			MessageBox(hwnd,"不爱是不可能的，这辈子是不可能不爱的"/*"不小心被点到了，但是没用哈哈哈"*/,"哎呦",MB_OK);
		}

		break;
    case WM_PAINT:
    {
        hDC = BeginPaint(hwnd, &ps);
        //选择用图片进行绘制
        SelectObject(hdcmem, hBm);
        //显示图片从hdcmem到hDC
        BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);
        MakeFont(hDC);
        TextOut(hDC, 270, 100, "小姐姐你爱不爱我?", 18/*"小姐姐做我女朋友好不好",22*/);
        HFONT hFont = CreateFont
        (

            20, 0,    //高度20, 宽取0表示由系统选择最佳值
            0, 0,    //文本倾斜，与字体倾斜都为0
            FW_HEAVY,    //粗体
            0, 0, 0,        //非斜体，无下划线，无中划线
            GB2312_CHARSET,    //字符集
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,        //一系列的默认值
            DEFAULT_PITCH | FF_DONTCARE,
            (TCHAR*)"黑体"    //字体名称
        );
        SendMessage(hwnd1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
        SendMessage(hwnd2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
        EndPaint(hwnd, &ps);
    }
        
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
    default:
        return DefWindowProc(hwnd,message,wParam,lParam);
    }
	return (0);
}


//自定义字体
void MakeFont(HDC hdc)
		{

			 HFONT hFont;    //字体句柄

			 hFont = CreateFont

                        (

                            30,13,    //高度20, 宽取0表示由系统选择最佳值

                            0, 0,    //文本倾斜，与字体倾斜都为0

                            FW_HEAVY,    //粗体

                            0,1,0,        //非斜体，无下划线，无中划线

                            GB2312_CHARSET,    //字符集

                            OUT_DEFAULT_PRECIS,        

                            CLIP_DEFAULT_PRECIS,        

                            DEFAULT_QUALITY,        //一系列的默认值

                            DEFAULT_PITCH | FF_DONTCARE,    

                           // (TCHAR*)"华文细黑"    //字体名称

						   (TCHAR*)"黑体"
                        );

			 SelectObject(hdc, hFont);

		}
