

//#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE ((DPI_AWARENESS_CONTEXT)-2)

//test 
//#define VAL_MINESWEEPER_FAST_MOUSE 1

#define Mouse_leftclick(){mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0,0,0);}
#define Title(s) SetConsoleTitleA(s)

#define ctocp(ch) ((char*)ch.c_str())
#define GetPhysicalCursorPos(p) GetCursorPos(p) 
#define SetPhysicalCursorPos(x,y) SetCursorPos(x,y)
#define SHOW(a) cout << #a << ": " << (a) << "   "<<endl;
#define SHOWf(a,b) b << #a << ": "<< (a) << endl;
#define SHOWb(a,b) SHOW(a); b << #a << ": "<< (a) << endl;
#define GLOBALSLEEP();// Sleep(1200);
#define ctoint(s) atoi(s.c_str())

#define ShowConsole() ShowWindow(GetConsoleWindow(),SW_SHOW);
#define HideConsole() ShowWindow(GetConsoleWindow(),SW_HIDE);



#include <complex.h>
#include <ctgmath>
#include <windows.h>
#include <iostream>   
#include <iomanip> 
#include <fstream>
#include <conio.h>
#include <string.h> 
#define _OPEN_SYS_ITOA_EXT
#include<stdio.h> 
#include<stdlib.h>
using namespace std;
void pause();
string ctostr(int i);
string creftostr(COLORREF a);
#include"valtimer.h"
#include <GdiPlus.h>
#pragma comment( lib, "gdiplus" )
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    using namespace Gdiplus;
    UINT  num = 0;          // number of image encoders
    UINT  size = 0;         // size of the image encoder array in bytes

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;  // Failure

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;  // Failure

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }
    }

    free(pImageCodecInfo);
    return 0;
}
/*
void gdiscreen()
{
	using namespace Gdiplus;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	{
		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = ::GetDC(0);
		int Height = GetSystemMetrics(SM_CYSCREEN);
		int Width = GetSystemMetrics(SM_CXSCREEN);
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		HBITMAP hOldBitmap =(HBITMAP) SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);

		Gdiplus::Bitmap bitmap(membit, NULL);
		CLSID clsid;
		GetEncoderClsid(L"image/jpeg", &clsid);
		bitmap.Save(L"D:\\screen.jpeg", &clsid);

		SelectObject(memdc, hOldBitmap);

		DeleteObject(memdc);

		DeleteObject(membit);

		::ReleaseDC(0,scrdc);
	}

	GdiplusShutdown(gdiplusToken);
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	using namespace Gdiplus;
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}

	free(pImageCodecInfo);
	return 0;
}*/
WCHAR* ctolpwstr(string& s);
void gdiSaveHbitmapjpg(HBITMAP& membit, string fname)
{
    using namespace Gdiplus;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    {

        Gdiplus::Bitmap bitmap(membit, NULL);
        CLSID clsid;
        GetEncoderClsid(L"image/jpeg", &clsid);

        bitmap.Save(ctolpwstr(fname), &clsid);

    }

    GdiplusShutdown(gdiplusToken);
}
void gdiSaveHbitmappng(HBITMAP& membit, string fname)
{
    using namespace Gdiplus;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    {

        Gdiplus::Bitmap bitmap(membit, NULL);
        CLSID clsid;
        GetEncoderClsid(L"image/png", &clsid);

        bitmap.Save(ctolpwstr(fname), &clsid);

    }

    GdiplusShutdown(gdiplusToken);
}

void gdiSaveHbitmap(HBITMAP &membit, string fname, string type="jpg")
{

        if(type=="jpg")gdiSaveHbitmapjpg(membit, fname);
        else if(type=="png")gdiSaveHbitmappng(membit, fname);

}

//void GDIPtext(HBITMAP& bitm, string text) {
//    using namespace Gdiplus;
//    GdiplusStartupInput gdiplusStartupInput;
//    ULONG_PTR gdiplusToken;
//    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
//
//    {
//        Gdiplus::Bitmap bitmap(bitm, NULL);
//        Image* img = new Image();
//        Image::fromHbitmap
//        Graphics* gdipx = new Graphics(img);
//        FontFamily  fontFamily(L"Times New Roman");
//        Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
//        PointF      pointF(30.0f, 10.0f);
//        SolidBrush  solidBrush(Color(255, 0, 0, 255));
//    }
//}

int BIG_x = -1, BIG_y = -1;// cell offsets to boarder pixels for easy access

int	Mine_window_offset_x, Mine_window_offset_y, Mine_window_width, Mine_window_height;
HHOOK Hook, Hook2;
static bool DO_PAUSE = false, SHIFT_DOWN = false, CONTROL_DOWN = false, KEYBOARD_PROCESSING = false;
static bool F9FLAG = false, F8FLAG = false, F7FLAG = false, F6FLAG = false, F5FLAG = false, F4FLAG = false, F3FLAG = false;
int startx[3], starty[3];



#define Boarder_color_left Boarder_color[0]    
#define Boarder_color_top Boarder_color[0]
#define Boarder_color_right Boarder_color[1]  
#define Boarder_color_down Boarder_color[1]
#define board_gather_offset 35 
#define BGA board_gather_offset 
#define _MWOx Mine_window_offset_x
#define _MWOy Mine_window_offset_y
#define _MWw  Mine_window_width
#define _MWh  Mine_window_height  

/*land color RGB          int conversion
land 192,192,192          12632256
bomb 0,0,0                0
corner 255,255,255        16777215
1-0,0,255;                16711680
2-0,128,0;                32768
3-255,0,0;                255

4-0,0,128                 8388608
5-128,0,0                 128
6-0,128,128               8421376 

    x=12;  y=55; w=480;  h=256; // unstretched minewindow HWND offsets for mineboard

    HWNDrect board offsets: _MWOx+=20;  _MWOy+=128;  _MWw-=39;  _MWh-= 147;
*/
/***************************************macros and redefs *****************************************************/


// global compile options
#define Y_CONSOLE_START_POS 2  // this sets where clrscr starts clearing for varout
#define Y_CONSOLE_VAROUT_POS 1
#define Y_CONSOLE_VAROUT_DEPTH 1


static int CLICK_TYPE = 0;
short OPUS_DOGUESSES = 0;


static int GLOBAL_SLEEP_VALUE = 0;

void gotoxy(int x, int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { (short)x, (short)y };
    SetConsoleCursorPosition(handle, position);
}
void getxy(int& x, int& y) {
    _CONSOLE_SCREEN_BUFFER_INFOEX info;
    GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    x = info.dwCursorPosition.X;
    y = info.dwCursorPosition.Y;
}

void clrscr() {
    gotoxy(0, Y_CONSOLE_START_POS);
    HANDLE hOut; COORD Position; DWORD Written;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0; Position.Y = Y_CONSOLE_START_POS; 

    FillConsoleOutputCharacter(hOut, ' ', 18000, Position, &Written);
    gotoxy(0, Y_CONSOLE_START_POS);
}

WCHAR* ctolpwstr(string& s) {
    char* a = (char*)s.c_str();
    WCHAR* p;
    int len = MultiByteToWideChar(CP_ACP, 0, a, -1, NULL, 0);
    p = new WCHAR[len];
    MultiByteToWideChar(CP_ACP, 0, a, -1, (LPWSTR)p, len);

    return p;
}




int random(int a) {
    return rand() % a;
}
HWND GetConsoleHwnd(void) { 
    return GetConsoleWindow();
}
ValStopwatch GLOBAL_RUNTIMER;  // main must include GLOBAL_RUNTIMER.lapunpause();
void pause() {
    GLOBAL_RUNTIMER.LapPause();
    if (KEYBOARD_PROCESSING) {
        cout << "press f10 to unpause" << endl;
        //Title("paused");
        DO_PAUSE = true;
        while (DO_PAUSE)Sleep(7);
    }
    else system("Pause");
    GLOBAL_RUNTIMER.LapUnPause();

}
//string ctostr(int i) {
//    char a[38];
//    _itoa_s(i, a, 10);
//    return a;
//}

//string creftostr(COLORREF a) {
//    string ret = ctostr((unsigned int)GetRValue(a));
//    ret += ",";
//    ret += ctostr((unsigned int)GetGValue(a));
//    ret += ",";
//    ret += ctostr((unsigned int)GetBValue(a));
//    return ret;
//}
bool OPUS_trainer_Normalized = true;
bool OPUS_trainer_safeclicks = true;
bool OPUS_trainer_flags = true;
bool OPUS_trainer_guesses = true;
bool OPUS_MAGNUMB_drawdomains = false;
#include "minemath_emu.h"
#include "ValScreenwrapper.h" 
#include "opus.h"
/*********************windowed mode stuff*********************************/
#include <windows.h>
#include<windowsx.h>
#include <winuser.h> 
#include "shellscalingapi.h"
#include <ctime>
#include <cmath> 
#include <iostream>   
#include <iomanip> 
#include <sys/timeb.h>
#include <fstream>
#include <process.h> 
#include <conio.h>
#include <string> 
#include<stdio.h>  
#include<fcntl.h>
#include<io.h> 
#include"ValWindowManager.h"
bool neo_loginfunc(string uname, string pw, string** status) {//needed for hypervisor bs.
    return false;
}

/*end windowed mode stuff*/
void opus_output_info(string fname);
void opus_output_vs(); 
void opus_reset_opusvs();
bool TOGGLE_OPUS_KBD = true;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    int x = 0, y = 2;
    if (nCode == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* lpm = (KBDLLHOOKSTRUCT*)lParam;

            switch (lpm->vkCode) {
            case VK_F1:
                //cout <<"\n\n\n"<< GetKeyState(VK_LSHIFT) << "\n\n\n";
                if (GetKeyState(VK_OEM_3) < 0) OPUS_MAGNUMB_drawdomains = !OPUS_MAGNUMB_drawdomains;
                else if (GetKeyState(VK_LSHIFT)<0)OPUS_trainer_Normalized = !OPUS_trainer_Normalized;
                else if (GetKeyState(VK_LCONTROL)<0) OPUS_trainer_flags = !OPUS_trainer_flags;
                else OPUS_trainer_safeclicks = !OPUS_trainer_safeclicks;


            break;
            case VK_F2:
                if (GetAsyncKeyState(VK_LCONTROL)) {
                    ShowConsole();
                }
                else HideConsole();
                break;
            case VK_F3:
                F3FLAG = !F3FLAG;
                (OPUS_DOGUESSES > 1 ? OPUS_DOGUESSES = 0 : OPUS_DOGUESSES++);
                //OPUS_DOGUESSES = !OPUS_DOGUESSES;
                gotoxy(2, Y_CONSOLE_VAROUT_POS); SHOW(OPUS_DOGUESSES);
                break;
            case VK_F4:
                (CLICK_TYPE > 1 ? CLICK_TYPE = 0 : CLICK_TYPE++);
                getxy(x, y);
                gotoxy(22, Y_CONSOLE_VAROUT_POS); SHOW(CLICK_TYPE);
                gotoxy(x, y);
                break;
            case VK_F5: 
                clrscr();
                if (TOGGLE_OPUS_KBD) {
                    opus_output_vs();
                    MagnumbFrontiers_output("magnumbinfo.txt");
                    opus_color_out();
                    opus_output_info("opusinfo.txt");  
                    opus_saveboard_analyzer_format(1, "f5out");
                }
                F5FLAG = !F5FLAG;
                break;
            case VK_F6:
                F6FLAG = !F6FLAG;
                if (TOGGLE_OPUS_KBD)opus_reset();
                break;
            case VK_F7:
                F7FLAG = !F7FLAG;
                (!GLOBAL_SLEEP_VALUE ? GLOBAL_SLEEP_VALUE = 0 : GLOBAL_SLEEP_VALUE -= 10);
                getxy(x, y);
                gotoxy(55, Y_CONSOLE_VAROUT_POS); SHOW(GLOBAL_SLEEP_VALUE);
                gotoxy(x, y);

                break;
            case VK_F8:
                F8FLAG = !F8FLAG;
                GLOBAL_SLEEP_VALUE += 10;
                getxy(x, y);
                gotoxy(55, Y_CONSOLE_VAROUT_POS); SHOW(GLOBAL_SLEEP_VALUE);
                gotoxy(x, y);
                break;
            case VK_F9:
                F9FLAG = !F9FLAG;
                if (TOGGLE_OPUS_KBD)opus_reset_opusvs();
                break;
            case VK_F11:
                clrscr();
                break;

            case VK_F10:
                if (DO_PAUSE = !DO_PAUSE)Title("paused");
                else Title("running");
                break;
            case VK_F12:
                CallNextHookEx(Hook2, nCode, wParam, lParam);
                exit(0);
                break;
            }
        }
    }
    return CallNextHookEx(Hook2, nCode, wParam, lParam);
}
void StayOnTop(HWND mywn, bool reverse = false) {
    LPRECT rect = new RECT;
    GetWindowRect(mywn, rect);
    int wi = rect->right - rect->left;
    int hi = rect->bottom - rect->top;

    ::SetWindowPos(mywn,       // handle to window
        (reverse ? HWND_NOTOPMOST : HWND_TOPMOST),  // placement-order handle
        rect->left,     // horizontal position
        rect->top,      // vertical position
        wi,  // width
        hi, // height
        SWP_SHOWWINDOW);// window-positioning options);
}
HWND IDLE_HWND = NULL;
BOOL MOUSE_WHEELT = false, FULL_EQUIPS=false;
LRESULT CALLBACK KeyboardProc_idleslayer(int nCode, WPARAM wParam, LPARAM lParam) {
    int x = 0, y = 2;
    if (nCode == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* lpm = (KBDLLHOOKSTRUCT*)lParam;

            switch (lpm->vkCode) {
            case VK_F2:
                if (GetAsyncKeyState(VK_LCONTROL)) {
                    ShowConsole();
                }
                else HideConsole();
                break;
            case VK_F3:
                F3FLAG = !F3FLAG;
                cout << "f3flag = " << (F3FLAG ? "true" : "false") << "\n";
                break;
            case VK_F4:
                F4FLAG = !F4FLAG;
                cout << "f4flag = " << (F4FLAG ? "true" : "false") << "\n";
                break;
            case VK_F5:
                F5FLAG = !F5FLAG;
                cout << "f5flag = " << (F5FLAG ? "true" : "false") << "\n";
                clrscr();
                break;
            case VK_F6:
                F6FLAG = !F6FLAG;
                break;
            case VK_F7:
                F7FLAG = !F7FLAG;
                break;
            case VK_F8:
                F8FLAG = !F8FLAG;
                FULL_EQUIPS = !FULL_EQUIPS;
                cout << "set fullequips to " << (FULL_EQUIPS ? "true\n" : "false\n");
                break;
            case VK_F9:
                F9FLAG = !F9FLAG;
                MOUSE_WHEELT = !MOUSE_WHEELT;
                cout << "testing mousewheel, press f10 to continue\n";
                break;
            case VK_F11:
                clrscr();
                break;

            case VK_F10:
                if (DO_PAUSE = !DO_PAUSE)Title("paused");
                if (IDLE_HWND != NULL)StayOnTop(IDLE_HWND, DO_PAUSE);
                else Title("running");
                break;
            case VK_F12:
                CallNextHookEx(Hook2, nCode, wParam, lParam);
                exit(0);
                break;
            }
        }
    }
    return CallNextHookEx(Hook2, nCode, wParam, lParam);
}


void setFontSize(int FontSize)
{
    CONSOLE_FONT_INFOEX info = { 0 };
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = FontSize; // leave X as zero
    info.FontWeight = FW_NORMAL;
    wcscpy_s(info.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &info);
}


void StayOnTop(int right = 500, int bottom = 75) {
    LPRECT rect = new RECT;
    HWND mywn = GetConsoleHwnd();
    GetWindowRect(mywn, rect);
    rect->left = 0;
    rect->top = 0;
    rect->right = right;
    rect->bottom = bottom;

    int wi = rect->right - rect->left;
    int hi = rect->bottom - rect->top;

    ::SetWindowPos(mywn,       // handle to window
        HWND_TOPMOST,  // placement-order handle
        rect->left,     // horizontal position
        rect->top,      // vertical position
        wi,  // width
        hi, // height
        SWP_SHOWWINDOW);// window-positioning options);
}


/*
notes on long scale pattern recognition heuristic:
moved to deltainfiniti.com/long_pattern.txt

*/


void Hwnd_slide(HWND hwnd, int xx, int yy, int xs, int ys, int delay = 200) {
    SetCursorPos(xx, yy);
    Sleep(50);
    SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(xx, yy));
    if (delay)Sleep(delay);
    SetCursorPos(xx+xs, yy+ys);
    Sleep(50);
    SendMessage(hwnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(xx+xs, yy+ys));

}

void Hwnd_lclick(HWND hwnd, int xx, int yy, int delay = 0) {
    SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(xx, yy));
    if (delay)Sleep(delay);
    SendMessage(hwnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(xx, yy));

}
void Hwnd_rclick(HWND hwnd, int xx, int yy, int delay = 0) {
    SendMessage(hwnd, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(xx, yy));
    if (delay)Sleep(delay);
    SendMessage(hwnd, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(xx, yy));

}
const int IS_CHEST_SIZE = 34;
int IS_chestsx[IS_CHEST_SIZE];
int IS_chestsy[IS_CHEST_SIZE];
void fill_chests() {
    int xt=320, yt=560;
    for (int x = 0; x < 8; x++) {
        xt =320 +(x*180);
        yt = 560;
        for (int y = 0; y < 4; y++) {
            if (y == 3) {
                if (x >= 6)continue;
                xt += 175;
            }
            IS_chestsx[(y*8)+x] = xt;
            IS_chestsy[(y * 8) + x] = yt;
            yt += 190;
        }
    }
    //IS_chestsx[30] = IS_chestsx[27];// swap 27 to give popup time to close
    //IS_chestsy[30] = IS_chestsy[27];
    //IS_chestsx[27] = 950;// close random popup <bugremoval
    //IS_chestsy[27] = 1150;

    IS_chestsx[33] = 950;// close random popup <bugremoval
    IS_chestsy[33] = 1150;
    IS_chestsx[31] = 933;// silver chests activation
    IS_chestsy[31] = 1323;
    IS_chestsx[32] = 930; // chest hunt end button
    IS_chestsy[32] = 70;

    IS_chestsx[30] = 1865;// inventory exit button
    IS_chestsy[30] = 1414;
    for (int i = 0; i < 32; i++) {
        cout << "ischests:" << i << ":x,y: " << IS_chestsx[i] << " " << IS_chestsy[i] << endl;
    }
}
void test_mousewheel(HWND hwnd, short spd, int x = 0, int y = 0) {
    POINT pt;
    if (x != 0 || y != 0) {
        pt.x = x; pt.y = y;
        SetCursorPos(x, y);
    }
    else    GetCursorPos((LPPOINT)&pt);
    cout << "pt.x,pt.y:" << pt.x << "," << pt.y << "\n";
    HWND test = WindowFromPoint(pt);
    int i = 0;
    //for (int i = 0; i < 150000; i++) {
        LRESULT a = SendMessage(test, WM_MOUSEWHEEL, MAKEWPARAM(0, 120), MAKELPARAM(pt.x, pt.y));
        cout << a<<":"<<i << endl;
        cout << GetLastError() << endl;
        a = SendMessage(test, WM_MOUSEWHEEL, MAKEWPARAM(0, 120), MAKELPARAM(50, 50));
        cout << a << ":" << i << endl;
        cout << GetLastError() << endl;
    //}
    //SendMessageA(hwnd, WM_MOUSEWHEEL, MAKEWPARAM(0,WHEEL_DELTA), MAKELPARAM(pt.x, pt.y));
    //mouse_event(MOUSEEVENTF_WHEEL, pt.x, pt.y, DWORD(-WHEEL_DELTA), 0);

}
HWND idleslayer_hwnd;
int idleslayer_x = 0, idleslayer_y = 0; 
void IS_CL(int x, int y, int delay=10, bool left = true ) {
    SetCursorPos(idleslayer_x + x, idleslayer_y + y);
    if(left)Hwnd_lclick(idleslayer_hwnd, x, y, delay);
    else Hwnd_rclick(idleslayer_hwnd, x, y, delay);
    
}
void IS_SC(int x, int y, int scrolls, bool down = true, int delay = 0) {
    x += idleslayer_x;
    y += idleslayer_y;
    SetCursorPos(x, y);
    DWORD sval = DWORD(WHEEL_DELTA * (down ? -1 : 1));
    while(scrolls-- >0)
        mouse_event(MOUSEEVENTF_WHEEL, x, y, sval, 0);
    Sleep(delay);

}
void idleslayer_equips(bool full,bool half=false) {
    //1700,1250 open bag
    IS_CL(1700, 1250);Sleep(300);
    //1300,1375 equips tab
    IS_CL(1300, 1375); Sleep(400);
    //1800,1250 buy max
    IS_CL(1800, 1250); Sleep(400);
    // scroll down to the bottom
    IS_SC(1750, 1100, 50); Sleep(400);
    //bottom item in bag 1750,1100
    IS_CL(1750, 1120); Sleep(25);
    IS_CL(1750, 920); Sleep(25);
    IS_CL(1750, 720); Sleep(25);
    if (half) {
        IS_CL(1750, 520); Sleep(25);
        IS_CL(1750, 320); Sleep(200);
    }
    for (int i = 0; i < 20 && full; i++) {
        IS_SC(1750, 320, 1, false); Sleep(50);
        IS_CL(1000, 300, 200);
        IS_CL(1750, 320); Sleep(100);
    }
    //1800,1350 close button
    IS_CL(1800, 1350);
    IS_CL(1800, 1350);
    Sleep(300);

}
void idleslayer_minions() {

    //open ascension menu
    IS_CL(150, 180); Sleep(300);
    //480 1375 open minions tab
    IS_CL(480, 1375); Sleep(100);
    //730,393 bonus/autocollect|send button
    IS_CL(730, 353); Sleep(50);
    IS_CL(730, 353); Sleep(50);
    IS_CL(730, 355); Sleep(50);
    //700, 600 840 1120
    IS_SC(700, 1120, 0, false); Sleep(200);
    IS_CL(700, 600); Sleep(30);
    IS_CL(700, 600); Sleep(30);
    IS_CL(700, 800); Sleep(30);
    IS_CL(700, 800); Sleep(30);
    IS_CL(700, 1120); Sleep(30);
    IS_CL(700, 1120); Sleep(30);

    IS_SC(700, 1120, 1, false); Sleep(200);
    IS_CL(700, 600); Sleep(30);
    IS_CL(700, 600); Sleep(30);
    IS_CL(700, 800); Sleep(30);
    IS_CL(700, 800); Sleep(30);
    IS_CL(700, 1120); Sleep(30);
    IS_CL(700, 1120); Sleep(30);

    //825 1375 close asc menu
    IS_CL(825, 1375); Sleep(300);
}
void idleslayer_upgrades() {
    //1700,1250 open bag
    IS_CL(1700, 1250); Sleep(300);
    //1300,1375 upgrades tab
    IS_CL(1400, 1355); Sleep(400);
    //1800,1250 buy all upgrades
    IS_CL(1550, 1250); Sleep(400);
    //1800,1350 close button
    IS_CL(1800, 1350);
    IS_CL(1800, 1350);
    Sleep(300);
}
void idleslayer_quests() {
    //1700,1250 open bag
    IS_CL(1700, 1250); Sleep(300);
    //1300,1375 equips tab
    IS_CL(1500, 1350); Sleep(400);
    // scroll down to the bottom
    IS_SC(1750, 1100, 50); Sleep(400);
    //bottom item in bag 1750,1100
    IS_CL(1750, 1120); Sleep(25);

    IS_CL(1750, 920); Sleep(25);
    IS_CL(1750, 720); Sleep(25);
    IS_CL(1750, 520); Sleep(25);
    //IS_CL(1750, 320); Sleep(200);

    for (int i = 0; i < 5; i++) {
        IS_SC(1750, 520, 1, false); Sleep(50);
        IS_CL(1000, 300,200);
        IS_CL(1750, 520); Sleep(100);
    }
    //1800,1350 close button
    IS_CL(1800, 1350);
    IS_CL(1800, 1350);
    Sleep(300);

}


void idleslayer_thread(void* a) {
    cout << WHEEL_DELTA << endl;
    int incr = 0;
    int plc = 0;
    while (1) {
        if (MOUSE_WHEELT) {
            /*DO_PAUSE = true;
            cout << "pausing...\n";
            while (DO_PAUSE)Sleep(1000);
            cout << "doing it...\n";
            test_mousewheel(idleslayer_hwnd, 120 );


            continue;
            */
            MOUSE_WHEELT = false;
            cout << "doing equips\n";
            idleslayer_equips(FULL_EQUIPS);
        }
        
        plc = incr % IS_CHEST_SIZE;
        SetCursorPos(idleslayer_x + IS_chestsx[plc], idleslayer_y + IS_chestsy[plc]);
        
        
        while(DO_PAUSE)Sleep(1000);
        
        Hwnd_lclick(idleslayer_hwnd, 100, 100, 0);
        Sleep(50);
        Hwnd_rclick(idleslayer_hwnd, 100, 100, 0);
        Sleep(50);
        
        if (incr % 200 == 0) {
            Hwnd_slide(idleslayer_hwnd,idleslayer_x+710,idleslayer_y+1210,500,0,0);
            Hwnd_slide(idleslayer_hwnd, idleslayer_x + 1210, idleslayer_y + 1210, -500, 0, 0);
            Hwnd_slide(idleslayer_hwnd, idleslayer_x + 710, idleslayer_y + 1160, 500, 0, 0);
            Hwnd_slide(idleslayer_hwnd, idleslayer_x + 1210, idleslayer_y + 1160, -500, 0, 0);
           
            cout << "\r" << incr << "  ";
        }
        incr++;
    }

}
static ValScheduler IdleSchedule;
void SLA_topEquips(void* a) {
    string myname = "top equips";
    int myid = IdleSchedule.GetId(60, myname);
    while (IdleSchedule.paused)Sleep(100);
    while (1) {
        if (IdleSchedule.Run(myid))break;
        if (F4FLAG) {
            cout << "skipping " << myname << "\n";
            continue;
        }
        cout << "running " << myname << "\n";
        while (DO_PAUSE)Sleep(1000);
        idleslayer_equips(false, false);
    }
    cout << "Exited " << myname << "\n";

}
void SLA_allEquips(void* a) {
    string myname = "all equips";
    int myid = IdleSchedule.GetId(400, myname);
    while (IdleSchedule.paused)Sleep(100);
    while (1) {
        if (IdleSchedule.Run(myid))break;
        if (F3FLAG) {
            cout << "skipping " << myname << "\n";
            continue;
        }
        cout << "running " << myname << "\n";
        while (DO_PAUSE)Sleep(1000);
        idleslayer_equips(true,true);
    }
    cout << "Exited " << myname << "\n";
}
void SLA_upgrades(void* a) {
    string myname = "upgrades";
    int myid = IdleSchedule.GetId(100, myname);
    while (IdleSchedule.paused)Sleep(100);
    while (1) {
        if (IdleSchedule.Run(myid))break;
        if (F3FLAG) {
            cout << "skipping " << myname << "\n";
            continue;
        }
        cout << "running " << myname << "\n";
        while (DO_PAUSE)Sleep(1000);
        idleslayer_upgrades();

    }
    cout << "Exited " << myname << "\n";
}
void SLA_quests(void* a) {
    string myname = "quests";
    int myid = IdleSchedule.GetId(200, myname);
    while (IdleSchedule.paused)Sleep(100);
    while (1) {
        if (IdleSchedule.Run(myid))break;
        if (F3FLAG) {
            cout << "skipping " << myname << "\n";
            continue;
        }
        cout << "running " << myname << "\n";
        while (DO_PAUSE)Sleep(1000);
        idleslayer_quests();

    }
    cout << "Exited " << myname << "\n";
}
void SLA_minions(void* a) {
    string myname = "minions";
    int myid = IdleSchedule.GetId(600, myname);
    while (IdleSchedule.paused)Sleep(100);
    while (1) {
        if (IdleSchedule.Run(myid))break;
        if (F5FLAG) {
            cout << "skipping " << myname << "\n";
            continue;
        }
        cout << "running " << myname << "\n";
        while (DO_PAUSE)Sleep(1000);
        idleslayer_minions();

    }
    cout << "Exited " << myname << "\n";
}
void SLA_dimension(void* a) {
    string myname = "dimension";
    int myid = IdleSchedule.GetId(30000, myname);
    while (IdleSchedule.paused)Sleep(100);
    while (1) {
        if (IdleSchedule.Run(myid))break;
        cout << "running " << myname << "\n";
        while (DO_PAUSE)Sleep(1000);
        //1750,255 ,   750,1150
        //Sleep(5000);

    }
    cout << "Exited " << myname << "\n";
}
void SLA_rage(void* a) {
    string myname = "rage";
    int myid = IdleSchedule.GetId(60, myname);
    while (IdleSchedule.paused)Sleep(100);
    while (1) {
        if (IdleSchedule.Run(myid))break;
        cout << "running " << myname << "\n";
        while (DO_PAUSE)Sleep(1000);
        //1600,250
        IS_CL(1600, 250);
        Sleep(200);

    }
    cout << "Exited " << myname << "\n";
}

void SLA_default(void* a) {
    string myname = "default thread";
    int myid = IdleSchedule.GetId(10, myname);
    IdleSchedule.set_default(myid);
    while (IdleSchedule.paused)Sleep(100);
    int ix = 0; 
    int jump = 0,jplc=0;
    while (1) {
        if (IdleSchedule.Run(myid))break;
        while (DO_PAUSE)Sleep(1000);
        cout << "running " << myname << "                    \r";
        for (int i = IS_CHEST_SIZE-1; i >-1; i--) {
            if (DO_PAUSE)jplc = 0;
            while (DO_PAUSE)Sleep(100);
            SetCursorPos(idleslayer_x + IS_chestsx[i], idleslayer_y + IS_chestsy[i]);
            if (jplc % 8 == 0 && !F6FLAG)jump = 250;
            else jump = 0;
            jplc++;
            Hwnd_lclick(idleslayer_hwnd, 100, 100,jump); Sleep(33);
            Hwnd_rclick(idleslayer_hwnd, 100, 100, 0); Sleep(33);
            //if (jump == 6)Sleep(70);
        }
        if (ix++ == 10) {
            cout << "skipping bonus stage              ";
            Hwnd_slide(idleslayer_hwnd, idleslayer_x + 710, idleslayer_y + 1210, 500, 0, 0);
            Hwnd_slide(idleslayer_hwnd, idleslayer_x + 1210, idleslayer_y + 1210, -500, 0, 0);
            Hwnd_slide(idleslayer_hwnd, idleslayer_x + 710, idleslayer_y + 1160, 500, 0, 0);
            Hwnd_slide(idleslayer_hwnd, idleslayer_x + 1210, idleslayer_y + 1160, -500, 0, 0);
            ix = 0;
        }

    }
    cout << "Exited " << myname << "\n";
}

void idleslayer_unpause(void* a) {
    DO_PAUSE = true;
    while (DO_PAUSE)Sleep(100);
    clrscr();
    Sleep(50);
    IdleSchedule.unpause();
}

void idleslayer_scheduled() {
    IdleSchedule.pause(); 
    IdleSchedule.isevent = true;
    int i = 0;
    cout << i++<<"\n";
    _beginthread(SLA_default, 0, NULL);
    cout << i++ << "\n";
    _beginthread(SLA_topEquips, 0, NULL);
    cout << i++ << "\n";
    _beginthread(SLA_allEquips, 0, NULL);
    cout << i++ << "\n";
    _beginthread(SLA_dimension, 0, NULL);
    cout << i++ << "\n";
    _beginthread(SLA_quests, 0, NULL);
    cout << i++ << "\n";
    _beginthread(SLA_upgrades, 0, NULL);
    cout << i++ << "\n";
    _beginthread(SLA_rage, 0, NULL);
    cout << i++ << "\n";
    _beginthread(SLA_minions, 0, NULL);
    cout << i++ << "\n";
    _beginthread(idleslayer_unpause, 0, NULL);


}
//1938x1487
//double (x/1938.0)* Nx
//double (y/1487.0)* Ny
int main_idleslayer() {
    StayOnTop(800,500);
    char* fn = (char*)malloc(1000);
    int sz = GetModuleFileNameA(NULL, fn, 1000);
    cout << fn << endl;
    fill_chests();
    ValScreen vs;
    int x=0, y=0, w=0, h=0;

    HWND hw = vs.find_Window("Idle Slayer",x, y, w, h);
    StayOnTop(hw);
    RECT rc;
    idleslayer_hwnd = hw;
    GetWindowRect(hw, &rc);
    x = rc.left;
    y = rc.top;
    idleslayer_x = x;
    idleslayer_y = y;
    w = rc.right - x;
    h = rc.bottom - y;
    cout << "x,y,w,h" << x << "," << y << "," << w << "," << h << endl;
    pause();
    clrscr();
    //_beginthread(idleslayer_thread, 0, NULL); 
    idleslayer_scheduled();
    KEYBOARD_PROCESSING = false;
    Sleep(50);
    MSG msg;
    Hook2 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc_idleslayer, GetModuleHandle(NULL), 0);
    KEYBOARD_PROCESSING = true;
//    while (1) {
        
        GetMessage(&msg, NULL, 0, 0);
//        cout << "msg:" << msg.message << endl;
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
    
//    Sleep(10000000000);
    return 0;
     
}
#include<string>
#define foreach(a,b) for(int a=0; a < b; a++)
int main_fine() {//_fineboard2
    //process fineboard copies
    ifstream ifile("boardcopy.txt");
    if (!ifile)cout << "failed\n";
    string temp;
    bool fields[14][17][17];
    short numc = 0;
    cout << "step1\n";
    foreach(i, 14) {
        foreach(n, 17) {
            foreach(x, 17) {
                fields[i][n][x] = true;
            }
        }
    }
    int i = 0, n = 0;
    cout << "step2\n";
    while (!ifile.eof()) {
        getline(ifile, temp);
        if (temp == "0") {
            i++;
            n = 0;
            continue;
        }
        if (temp == "x")break;
        if (n > 16)continue;
        foreach(x, 17) {
            fields[i][n][x] = temp[x] != '-';
        }
        n++;
    }
    i++;
    foreach(ii, i) {
        cout << "this is item number" << ii << "\n";
        foreach(nn, 17) {
            foreach(xx, 17) {
                
                if (fields[ii][nn][xx])cout << 1;
                else cout << "0";
            }
            cout << "\n";
        }
        cout << "\n\n\n";
    }

    cout << "step3 found i count: "<<i <<"\n";
    short fieldsf[17][17];
    foreach(x, 17) {
        foreach(nx, 17) {
            fieldsf[nx][x] = 0;
            foreach(tttt,i){
                if (fields[tttt][nx][x])fieldsf[nx][x]++;
            }
        }
    }
    cout << "     ";
    foreach(bbb, 10) cout << " " << bbb+1<< " ";
    foreach(bbb, 8) cout << " 1" << bbb+1;
    cout << "step4\n";
    foreach(n, 17) {
        cout << n << ": ";
        if (n < 10)cout << " ";
        foreach(i, 17) {
            if (fieldsf[i][n] < 10)cout << "  "<<fieldsf[i][n];
            else cout << " " << fieldsf[i][n];
        }
        cout << "\n";
    }
    pause();
}

int main_fineboardconsole() {
    // board pic to text file lol
    /*land color RGB          int conversion
land 192,192,192          12632256
bomb 0,0,0                0
corner 255,255,255        16777215
1-0,0,255;                16711680
2-0,128,0;                32768
3-255,0,0;                255

4-0,0,128                 8388608
5-128,0,0                 128z
6-0,128,128               8421376

    x=12;  y=55; w=480;  h=256; // unstretched minewindow HWND offsets for mineboard

    HWNDrect board offsets: _MWOx+=20;  _MWOy+=128;  _MWw-=39;  _MWh-= 147;
*/
    //outputs board.bmp as chars to the console for close inspection
    setFontSize(4);
    opus_HWND_move_resize(GetConsoleHwnd(), 60, 50, 1500, 1500);
    ValScreen vs;
    vs.buf_load_file_bmp("board.bmp");
    int w= vs.buf_width, h=vs.buf_height;
    int hold;
    ofstream ofile("board.txt");
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            hold = vs.buf_Get_Pixel(x, y);
            switch (hold) {
            case 12632256:
                cout << "-";
                ofile << "-";
            break;
            case 255:
                cout << 3;
                ofile << 3;
            break;
            case 16777215:
                cout << "n";
                ofile << "n";
                break;
            case 16711680:
                cout << 1;
                ofile << 1;
                break;
            case 32768:
                cout << 2;
                ofile << 2;
                break;

            
            case 8388608:
                cout << 4;
                ofile << 4;
                break;
            case 128:
                cout << 5;
                ofile << 5;
                break;
            case 8421376:
                cout << 6;
                ofile << 6;
                break;
            default:
                cout << "?";
                ofile << "?";
            }

        }
        cout << "\n";
        ofile << "\n";
    }
    pause();


}

#define fast_array_decc(x,y) fast_array_dec(atestingarray[0],10,10,x,y,1)
int atestingarray[10][10];


int main_mutate_test() {
    
    foreach(i, 10)foreach(n, 10)atestingarray[i][n] = 5;

    foreach(i, 10) {
        foreach(n, 10)cout << atestingarray[i][n];
        cout << "\n";
    }
    /*    fast_array_add((int*)atestingarray, 10, 10, 3, 3, 2);
    fast_array_set((int*)atestingarray, 10, 10, 6, 6, 8);
    fast_array_sub((int*)atestingarray, 10, 10, 6, 3, 1);
    int x = 9;
    fast_array_decc(0, 0);
    fast_array_decc(x, 0);
    fast_array_decc(x, x);
    fast_array_decc(0, x);
    x = 5;
    fast_array_decc(x, 0);
    fast_array_decc(x, 9);
    fast_array_decc(0, x);
    fast_array_decc(9, x);
    */
    fast_array_decc(1,1);
    fast_array_decc(8, 8);
    fast_array_decc(1, 8);
    fast_array_decc(8,1);
    //fast_array_decc(3, 3);
    //fast_array_decc(6, 6);
    //mutate fast_array_dec tester
    cout << "\n";    cout << "\n";    cout << "\n";
    foreach(i, 10) {
        foreach(n, 10)cout << atestingarray[i][n];
        cout << "\n";
    }


}
#include <io.h>
void Rename_all_files_in_directory(string ext) {
    char chr[256];
    GetCurrentDirectoryA(256, chr);
    string folder_path = chr;
    _finddata_t file_info;
    string any_file_pattern = folder_path + "\\*";
    intptr_t handle = _findfirst(any_file_pattern.c_str(), &file_info);
    int counter = 1;
    string olds, news;
    do {
        if (file_info.attrib & _A_SUBDIR) continue;
        string fname = file_info.name;
        if (fname.find(ext, 0) == string::npos) continue;
        olds = folder_path + "\\" + fname;
        news = folder_path + "\\" + ctostr(counter) + ext;
        cout << olds <<"-->  "<<news << endl;
        rename(olds.c_str() , news.c_str());
        counter++;
    } while (_findnext(handle, &file_info) == 0);



}
#include<bitset>
string binout(long long int num) {
    std::bitset<64> b(num);
    cout << b;
    return "";
}
int main_emuplayer() {
    G_VS_RANDSEED(getticks());
    MineMath_emulator testemu(30, 16, 99);
    testemu.play();
}
short bitstuff2(unsigned char& in, unsigned long long int& out,short &bitsleft, unsigned short bits, unsigned short outpos) {
    
    unsigned long long int mask=0;
    short i = 0;
    
    for (; i < bits && bitsleft; i++) {
        mask = mask | ((in & 128)?1:0);
        mask = mask << 1;
        in = in << 1;
        bitsleft--;
        //cout << i<<"out: " << out << "  mask: " << mask << " outpos" << outpos << "\n";
    }
    
    short shift = outpos-1; //- (9 - i);
    //cout << "0out: " << out << "  mask: " << mask << " outpos" << outpos << " shift: " <<shift <<"\n";
    if (shift > 0) mask = mask << shift;
    else if(shift < 0) mask = mask >> (shift*-1) ;

    //cout << "out: " << out << "  mask: " << mask << " outpos" << outpos << "\n";
    out = out | (mask );
    return i;
}
short bitstuff(unsigned char& in, unsigned long long int& out, short& bitsleft, unsigned short bits, unsigned short outpos) {

    unsigned long long int mask = 255 & in;
    short btc = (bitsleft > bits ? bits : bitsleft);//  bitsleft - bits : bits - bitsleft);
    mask = (mask >> (8- btc) ) << outpos;
    in = in << btc;
    bitsleft = (bitsleft > bits ? bitsleft - bits : 0);
    out = out | mask;
    return btc;

}

void weirdtest() {

    unsigned long long int one = 4629771061636907008;
    unsigned long long int two = 3467824696330821664;
    unsigned long long int three = 289356293373428736;
    unsigned long long int four = 284773528503041;
    one = one | two | three | four;
    for (int i = 0; i < 8; i++) {
        cout << (char)((one >> (56 - (i * 8))));
    }


}

int main_validate_slidingseeds() {
    StayOnTop(1800, 1800);
    string seeds = "I am a seed string hear me roar";
    valVeryRandom vvr(seeds, 500, 1, 0, 29);
    foreach(i, vvr.randlen) {
        cout << "randseed " << i << ":" << vvr.intseeds[i]<<"\n";
    }
    foreach(i, 15) {
        cout << "value: " << vvr.next() << "\n";
    }
    pause();
    cout << sizeof(short int) << endl;
    unsigned char a = 128;
    unsigned char ta = 255;
    unsigned long long int rec = 64, rec2 = 0, rec3 = 0, rec4 = 0;
    short bitsleft = 8;
 


    rec = 0;
    bitsleft = 0;
    string test = "testing!";
    for (int i = 0; i < 8; i++) {
        a = test[i];
        bitsleft = 8;
        cout << rec << " : " << (int)a << "\n";
        bitstuff(a, rec, bitsleft, 2, 62-(i * 8));
        cout << rec << " : " << (int)a << "\n";
        bitstuff(a, rec2, bitsleft, 2, 60 - (i * 8));
        cout << rec << " : " << (int)a << ":"<<bitsleft<<"\n";
        bitstuff(a, rec3, bitsleft, 2, 58 - (i * 8));
        cout << rec << " : " << (int)a << ":" << bitsleft << "\n";
        bitstuff(a, rec4, bitsleft, 2, 56 - (i * 8));
        cout << rec << " : " << (int)a << ":" << bitsleft << "\n";
    }

    cout << rec << "\n";
    cout << rec2 << "\n";
    cout << rec3 << "\n";
    cout << rec4 << "\n";
    
    std::bitset<64> b(rec),d(rec2),e(rec3),f(rec4);
    cout << b << "\n" << d <<"\n"<< e << "\n" <<f<< "\n";
    short temp = 0;
    rec = rec | rec2 |rec3|rec4;
    std::bitset<64> g(rec);
    cout << g << endl;
    for (int i = 0; i < 8; i++) {
        //cout << (char)( ((char*)(&rec))+i);
        //cout << ((rec>>(i*8))<<64-)
        //temp = 56 - (i * 8);
        //cout << (char)(((rec << temp) >> 64 - temp));
        cout << (char)((rec >> (56-(i * 8))));
    }

    pause();

}

int mainrt(){ // randomness tester
    _beginthread(calibrate_timer_thread, 0, NULL);
    Sleep(1100);
    int loopcount = 100000000;
    const int space = 1000;
    unsigned long long int rset[space];
    foreach(i, space) {
        rset[i] = 0;
    }
    valRandom vrand(getticks());
    string ts = "I am a sufficient seed string";
    valVeryRandom vvr(ts, space, 1, 0, 48);
    vrand.setrandmax(space);
    ValStopwatch stop;
    stop.LapUnPause();
    foreach(i, loopcount) {
        rset[vvr.next()]++;
        //rset[vrand.next()]++;
        //rset[G_VS_Rand5(space)]++;
    }
    stop.Lap();
    
    int low = rset[0];
    int high = rset[0];
    int avg = 0;
    foreach(i, space) {
        cout << rset[i] << "  ";
        if (i % 20 == 0)cout << "\n";
        if (rset[i] > high)high = rset[i];
        if (rset[i] <low)low = rset[i];
        avg += rset[i];
    }
    cout << "expected avg: " << loopcount / space << "\n";
    int disc = (avg / space), rtot = 0;
    cout << "actual: " << disc << "\n";
    foreach(i, space) {
        rtot += abs((long int)(disc - rset[i]));
    }
    cout << "Low: " << low << "\n";
    cout << "high: " << high << "\n";
    cout << "avg discrepency: " << rtot/space << "\n";
    cout << "loopcount: " << loopcount << "\n";
    stop.output("doing random loops x"+ctostr(loopcount));
    pause();
}
#define emutestmethod() testemu.fill_mineboard_seeded1();
int main_emutester() { // emu_tester
    StayOnTop(1800, 1800);
    G_VS_RANDSEED(getticks());
    _beginthread(calibrate_timer_thread, 0, NULL);
    //while (1) {
    //    binout(G_VS_Rand3(G_VS_randMAX));
    //    pause();
    //}
    MineMath_emulator testemu(30, 16, 99);
    //cout << testemu.get_maxd(0, 0) << "  " << testemu.get_maxd(0, 1) << "  " << testemu.get_maxd(30, 16) << "  \n";
    //pause();
    string ts = " I am a sufficient seed string";
    testemu.fill_mineboard_seeded(ts);
    Sleep(2300); 
    //testemu.play();


    ValStopwatch stop,watch;
    watch.LapUnPause();
    for (int x = 0; x < 10000; x++) {
        stop.LapUnPause();
        emutestmethod();
        stop.Lap();
        testemu.reset();
       // cout << x << "\r";
    }
    cout << "            \r";
    watch.Lap();
    watch.output("watch");
    stop.output("filling board");
    testemu.reset();
    short vcheck = 0;
    int tval = (10000 / (99))*480; // 480 * 990;
    for (int x = 0; x < tval; x++) {
        emutestmethod();
        if (!testemu.validate()) {
            vcheck++;
        }
        testemu.reset();
    }


    cout << "total boards validated: " << tval << "\n";
    cout << "total mines set: " << tval * testemu.total_mines << "\n";
    cout << "validate failed: " << vcheck<< "\n";
    cout << "total validate changes: " << testemu.total_validate_changes << "\n";
    cout << "danger_under_Mines average: " << testemu.stats_totaldangerundermines / tval << "\n";
    testemu.console_output_stats();
    testemu.output_validate_stats(); 
    pause();
    
    while (1) {
        stop.LapUnPause();
        emutestmethod();
        stop.Lap();
        testemu.console_output();
        if(!testemu.validate())cout << "validate failed\n";
        stop.output("filling board");
        testemu.reset();
        pause();
    }
    pause();

}

int mainrr() {// minemath2021 WR bot runner 

    //pause();
    //Rename_all_files_in_directory(".mine");
    //pause();
    //
    _beginthread(calibrate_timer_thread, 0, NULL);
    MSG msg;
    cout << "f3-guess type f4-click type f5-output f6-grid_reset f7&f8-sleep:v^ f10-pause  f11-clrscr f12-quit\n\n";
    setFontSize(11);

    gotoxy(0, 3);
    cout << "starting Minemath process" << endl;

    StayOnTop(800, 1800);
    opus_HWND_move_resize(GetConsoleHwnd(), 60, 50, 900, 1000);
    opusvs.create_transparent_window2(840, 60, 1500, 1000);
    KEYBOARD_PROCESSING = false;
    Sleep(50);
    _beginthread(opus_main_thread_info, 0, NULL); //_info

    Hook2 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    KEYBOARD_PROCESSING = true;
    while (1) {
        GetMessage(&msg, NULL, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int mainer() {// emulator runner


    //pause();
    //Rename_all_files_in_directory(".mine");
    //pause();
    //
    _beginthread(calibrate_timer_thread, 0, NULL);
    Sleep(1500);
    MSG msg;
    cout << "f3-guess type f4-click type f5-output f6-grid_reset f7&f8-sleep:v^ f10-pause  f11-clrscr f12-quit\n\n";
    setFontSize(11);

    gotoxy(0, 3);
    cout << "starting Minemath process" << endl;

    StayOnTop(800, 1800);
    opus_HWND_move_resize(GetConsoleHwnd(), 60, 50, 900, 1000);
    MineMath_emulator testemu(30, 16, 99);
    KEYBOARD_PROCESSING = false;

    Sleep(50);
    _beginthread(opus_main_thread_emulator, 0, (void*)&testemu); //_info

    Hook2 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    KEYBOARD_PROCESSING = true;
    while (1) {
        GetMessage(&msg, NULL, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}




int maint() {// minemath2021 trainer main

    _beginthread(calibrate_timer_thread, 0, NULL);
    opusvs.Set(300, 300, 1800, 1800);
    MSG msg;

    setFontSize(11);


    gotoxy(0, 3);
    StayOnTop(800, 1800);
    opus_HWND_move_resize(GetConsoleHwnd(), 60, 50, 800, 1000);
    opus_trainer_hwnd = trainer.create_transparent_window(865, 585, 1800, 1800);//(300,300,800,800);  
    opusvs.condc = GetDC(opus_trainer_hwnd);
    KEYBOARD_PROCESSING = false;
    Sleep(50);
    _beginthread(opus_trainer_thread,0,NULL); 

    Hook2 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    KEYBOARD_PROCESSING = true;
    while (1) {
        GetMessage(&msg, NULL, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
int maintr() {// minemath2021 trainer main

    _beginthread(calibrate_timer_thread, 0, NULL);
    opusvs.Set(300, 300, 1800, 1800);
    MSG msg;

    setFontSize(11);


    gotoxy(0, 3);
    StayOnTop(800, 1800);
    opus_HWND_move_resize(GetConsoleHwnd(), 60, 50, 800, 1000);
    if (OPUS_Testing_noscaling) {
        opus_trainer_hwnd = trainer.create_transparent_window(861, 559, 800, 500);//(300,300,800,800);  
    }
    else opus_trainer_hwnd = trainer.create_transparent_window(865, 585, 800, 500);//(300,300,800,800);  
    //opusvs.condc = GetDC(opus_trainer_hwnd);
    //opusvs.create_transparent_window(840, 60, 730, 590);
    opusvs.create_transparent_window(840, 60, 730, 590);
    KEYBOARD_PROCESSING = false;
    Sleep(50);
    _beginthread(MagnumbFrontiers_trainer_thread, 0, NULL);

    Hook2 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    KEYBOARD_PROCESSING = true;
    while (1) {
        GetMessage(&msg, NULL, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int main_notfunctional() {// minemath2022 screen runner for https://davidnhill.github.io/JSMinesweeper/

    _beginthread(calibrate_timer_thread, 0, NULL);
    opusvs.Set(300, 300, 1800, 1800);
    MSG msg;
    
    setFontSize(11);


    gotoxy(0, 3);
    StayOnTop(800, 1800);
    opus_HWND_move_resize(GetConsoleHwnd(), 60, 50, 800, 1000);
    
    //opus_trainer_hwnd = trainer.create_transparent_window(865, 585, 800, 500);//(300,300,800,800);  
    //opusvs.condc = GetDC(opus_trainer_hwnd);
    //opusvs.create_transparent_window(840, 60, 730, 590);
    opusvs.create_transparent_window(840, 60, 730, 590);
    KEYBOARD_PROCESSING = false;
    Sleep(50);
    _beginthread(MagNumb_screen_calibrate, 0, NULL);
    

    _beginthread(opus_main_thread_screen_info2022, 0, NULL);

    Hook2 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    KEYBOARD_PROCESSING = true;
    while (1) {
        GetMessage(&msg, NULL, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
#include<vector>
BOOL CALLBACK enumcallback(HWND hwnd, LPARAM lParam) {
    const DWORD TITLE_SIZE = 1024;
    WCHAR windowTitle[TITLE_SIZE];

    GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

    int length = ::GetWindowTextLength(hwnd);
    wstring title(&windowTitle[0]);
    if (!IsWindowVisible(hwnd) || length == 0 || title == L"Program Manager") {
        return TRUE;
    }

    // Retrieve the pointer passed into this callback, and re-'type' it.
    // The only way for a C API to pass arbitrary data is by means of a void*.
    std::vector<std::wstring>& titles =
        *reinterpret_cast<std::vector<std::wstring>*>(lParam);
    titles.push_back(title);

    return TRUE;
}
int main_window_find() {
    std::vector<std::wstring> titles;
    EnumWindows(enumcallback, reinterpret_cast<LPARAM>(&titles));
    // At this point, titles if fully populated and could be displayed, e.g.:
    for (const auto& title : titles)
        std::wcout << L"Title: " << title << std::endl;

    ValScreen vshwndsearch;
    int x, y, w, h;
    HWND hw = vshwndsearch.find_Window("Congratulations", x, y, w, h);
    if (hw)cout << "found the window\n";
    else cout << "no window\n";
    cin.get();
    return 0;

}



/*           MS windowed mode start here                                  */
char MS_watchboard[99][99];
short MS_OFFSETx = 15;
short MS_OFFSETy = 60;
#define MS_G_cell_width 16
ValGFX MS_gfx_copybuffer;
void MS_runonce(ValGFX* mygfx,ValGFX* defgfx,short width, short height) {//, ValWindow* wind
    // draw a standard board to mygfx, copy that to defgfx
    // initialize globals 
    defgfx->Get_blank_buffer((width * MS_G_cell_width) + 6, (height * MS_G_cell_width) + 6);
    MS_gfx_copybuffer.Get_blank_buffer((width * MS_G_cell_width) + 6, (height * MS_G_cell_width) + 6);
    mygfx->makecolor(VRGB_GREY_VVLIGHT);

    foreach(x, width+1) {
        if(x<width)mygfx->drawline2(MS_OFFSETx+( x * MS_G_cell_width), MS_OFFSETy-1, height * MS_G_cell_width, 0, 2, VRGB_WHITE);
        if(x>0)mygfx->drawline2(MS_OFFSETx + (x * MS_G_cell_width) - 2, MS_OFFSETy, height * MS_G_cell_width, 0, 2, VRGB_GREY_VLIGHT+(VRGB_111*1));
    }
    foreach(y, height+1) {
        if (y < height )mygfx->drawline2(MS_OFFSETx-1 , (y* MS_G_cell_width)+ MS_OFFSETy , width * MS_G_cell_width, 1, 2, VRGB_WHITE);        cout << "runonce2.1"<<y<<"\n";
        if (y > 0)mygfx->drawline2(MS_OFFSETx,(y * MS_G_cell_width)+ MS_OFFSETy - 2, width * MS_G_cell_width, 1, 2, VRGB_GREY_VLIGHT+(VRGB_111 * 1));
    }
    mygfx->drawline2(MS_OFFSETx -3, MS_OFFSETy, (height * MS_G_cell_width)+3, 0, 3, VRGB_GREY_VLIGHT + (VRGB_111 * 1));
    mygfx->drawline2(MS_OFFSETx-3 , MS_OFFSETy-3, (width * MS_G_cell_width)+6, 1, 3, VRGB_GREY_VLIGHT + (VRGB_111 * 1));

    mygfx->drawline2(MS_OFFSETx + (width* MS_G_cell_width), MS_OFFSETy, height * MS_G_cell_width, 0, 3, VRGB_WHITE);
    mygfx->drawline2(MS_OFFSETx, MS_OFFSETy +(height* MS_G_cell_width), (width * MS_G_cell_width)+3, 1, 3, VRGB_WHITE);
    int xtop, ytop, xbot, ybot;
    foreach(y, height ) {
        foreach(x, width ) {
            
            xtop = MS_OFFSETx + (x * MS_G_cell_width) + (MS_G_cell_width);
            ytop = MS_OFFSETy + (y * MS_G_cell_width);
            xbot = MS_OFFSETx + (x * MS_G_cell_width);
            ybot = MS_OFFSETy + (y * MS_G_cell_width) + (MS_G_cell_width);
            
            mygfx->editpixel(xtop-1,ytop , VRGB_GREY_VLIGHT + (VRGB_111 * 60));
            mygfx->editpixel(xtop - 2, ytop+1, VRGB_GREY_VLIGHT + (VRGB_111 * 60));

            mygfx->editpixel(xbot , ybot-1, VRGB_GREY_VLIGHT + (VRGB_111 * 60));
            mygfx->editpixel(xbot +1, ybot-2, VRGB_GREY_VLIGHT + (VRGB_111 * 60));
            
            mygfx->editpixel(xtop - 1, ytop+1, VRGB_GREY_VLIGHT + (VRGB_111 * 1));
            mygfx->editpixel(xbot, ybot - 2, VRGB_WHITE);
        }
    }
    xtop = MS_OFFSETx + (width * MS_G_cell_width);
    mygfx->editpixel(xtop+2, MS_OFFSETy-3, VRGB_GREY_VLIGHT + (VRGB_111 * 60));
    mygfx->editpixel(xtop+1, MS_OFFSETy - 2, VRGB_GREY_VLIGHT + (VRGB_111 * 60));
    mygfx->editpixel(xtop, MS_OFFSETy - 1, VRGB_GREY_VLIGHT + (VRGB_111 * 60));

    mygfx->editpixel(xtop + 2, MS_OFFSETy - 2, VRGB_WHITE);
    mygfx->editpixel(xtop + 2, MS_OFFSETy - 1, VRGB_WHITE);
    mygfx->editpixel(xtop + 1, MS_OFFSETy - 1, VRGB_WHITE);

    ytop = MS_OFFSETy + (height * MS_G_cell_width) ;
    mygfx->editpixel(MS_OFFSETx - 3, ytop + 2, VRGB_GREY_VLIGHT + (VRGB_111 * 60));
    mygfx->editpixel(MS_OFFSETx - 2, ytop + 1, VRGB_GREY_VLIGHT + (VRGB_111 * 60));
    mygfx->editpixel(MS_OFFSETx - 1, ytop , VRGB_GREY_VLIGHT + (VRGB_111 * 60));

    mygfx->editpixel(MS_OFFSETx - 2, ytop + 2, VRGB_WHITE);
    mygfx->editpixel(MS_OFFSETx - 1, ytop + 2, VRGB_WHITE);
    mygfx->editpixel(MS_OFFSETx - 1, ytop + 1, VRGB_WHITE);
    

    
    //defgfx->CopySectionToGFX(*mygfx, MS_OFFSETx - 3, MS_OFFSETy - 3, (width* MS_G_cell_width) + 8, (height* MS_G_cell_width) + 8, 0, 0);
    //cout << "finished copying" << endl;
    //defgfx->CopyToGFX(*mygfx, 0, 0);

    mygfx->CopySectionToGFX(*defgfx,0,0, (width* MS_G_cell_width) + 8, (height* MS_G_cell_width) + 8, MS_OFFSETx - 3, MS_OFFSETy - 3);
    cout << "finished copying" << endl;
    mygfx->makewhite();
    defgfx->CopyToGFX(*mygfx, MS_OFFSETx, MS_OFFSETy);
    defgfx->CopyToGFX(MS_gfx_copybuffer, 0, 0);

    Opus_vtc.fontdat.lfHeight = 17;
    Opus_vtc.fontdat.lfWeight = 620;

}

bool MS_G_GAME_LOST = false;
bool MS_G_SEEDED_GAME = false;
bool MS_G_firstclick = false;
void MS_reset(void* vwind) {
    string type;
    MS_G_firstclick = false;
    MS_G_GAME_LOST = false;

    cout << "reset1\n";
    ValWindow* wind = (ValWindow*)vwind;
    MineMath_emulator* mm_emu = (MineMath_emulator*)wind->get_associated_data("MBoard_");
    ValGFX* copy_board = (ValGFX*)wind->get_associated_data("BBoard_gfx");
    ValStopwatch* boardtimer = (ValStopwatch*)WindowMan.find_registered_data("BoardTimer", type);
    boardtimer->Stop();
    cout << "reset2\n";
    mm_emu->reset();
    if (MS_G_SEEDED_GAME) mm_emu->fill_mineboard_seeded1_2();
    else mm_emu->fill_mineboard5();
    copy_board->CopyToGFX(wind->mygfx, MS_OFFSETx, MS_OFFSETy);
    //refill board
    //fill window->mygfx with blank board copy
    wind->GFXdraw();
    //render to window
    cout << "reset3\n";
    //reset watchboard
    foreach(xx, mm_emu->width) {
        foreach(yy, mm_emu->height) {
            MS_watchboard[xx][yy] = 0;
        }
    }
    cout << "reset4\n";
    mm_emu->console_output();

}
void MS_resize(ValWindow* wind, short width, short height, short mines) {
    MineMath_emulator* mm_emu = (MineMath_emulator*)wind->get_associated_data("MBoard_");
   // wind->s
    // alter window size to fit new board dims
    // reset all GFX sizes and buffers
    // recall initial draw
    // reset emu, refill board

}
void MS_copy_def(ValGFX* mygfx, ValGFX* defgfx) {


}


void MS_EMU_NUMBERCOLOR(short val) {
    switch (val) {
    case 0: Opus_vtc.SetColor(VRGB_ORANGE); break;
    case 1: Opus_vtc.SetColor(VRGB_BLUE); break;
    case 2: Opus_vtc.SetColor(VRGB_GREEN_LIGHT & VRGB_GREY_LIGHT); break;
    case 3: Opus_vtc.SetColor(VRGB_RED_LIGHT); break;
    case 4: Opus_vtc.SetColor(VRGB_BLUE & VRGB_GREY_VLIGHT); break;
    case 5: Opus_vtc.SetColor(VRGB_RED_DARK); break;
    case 6: Opus_vtc.SetColor(VRGB_PINK); break;
    case 7: Opus_vtc.SetColor(VRGB_PURPLE); break;
    case 8: Opus_vtc.SetColor(VRGB_BLUE_DARK); break;
    case 9: Opus_vtc.SetColor(VRGB_BLUE_DARK); break;
    };

}
void MS_render_board(void* vwind) {
    ValWindow* wind = (ValWindow*)vwind;
    MineMath_emulator* mm_emu = (MineMath_emulator*)wind->get_associated_data("MBoard_");
    ValGFX* mygfx = (ValGFX*) (&(wind->mygfx));
    short val = 0;
    bool latch = false;
    //for loop through mm_emu activeboard

    foreach(xx, mm_emu->width) {
        foreach(yy, mm_emu->height) {
            if (MS_watchboard[xx][yy] != 1) {// if cell is active, and not already in watchboard
                val = mm_emu->getCellValue(xx, yy);
                
                if (val != 9) {
                    
                    
                    if (val == 10) {
                        if (MS_watchboard[xx][yy] == 2)continue;
                        Opus_vtc.content = (char)'f';
                        MS_watchboard[xx][yy] = 2;
                        Opus_vtc.SetColor(0);
                    }
                    else {
                        mygfx->color_section(MS_OFFSETx + (xx * MS_G_cell_width) + 3, MS_OFFSETy + (yy * MS_G_cell_width) + 3, MS_G_cell_width - 1, MS_G_cell_width - 1, VRGB_GREY_VVLIGHT);
                        //mygfx->draw_square(MS_OFFSETx + (xx * MS_G_cell_width), MS_OFFSETy + (yy * MS_G_cell_width)
                        //    , MS_OFFSETx + (xx * MS_G_cell_width) + MS_G_cell_width - 1, MS_OFFSETy + (yy * MS_G_cell_width) + MS_G_cell_width - 1
                        //    , VRGB_GREY_VVLIGHT);//  overwrite cell boarder with grey
                        MS_watchboard[xx][yy] = 1;
                        if (val < 1)continue;
                        Opus_vtc.content = ctostr(val);
                        MS_EMU_NUMBERCOLOR(val);
                    }
                    latch = true;
                    
                    //  draw number or flag in center of tile if nessesary  
                    
                    Opus_vtc.x =2 + MS_OFFSETx + (xx * MS_G_cell_width) + ((MS_G_cell_width - Opus_vtc.getrealtwidth()) / 2);
                    Opus_vtc.y = MS_OFFSETy + (yy * MS_G_cell_width) + 3;
                    
                    Opus_vtc.DIBdraw(wind->myhdc, wind->mygfx.hbmp);
                    
                }
                else if(MS_watchboard[xx][yy] == 2){ // color previously flagged, now un-flagged cell
                    mygfx->color_section(MS_OFFSETx + (xx * MS_G_cell_width) + 6, MS_OFFSETy + (yy * MS_G_cell_width) + 6, MS_G_cell_width - 7, MS_G_cell_width - 6, VRGB_GREY_VVLIGHT);
                    MS_watchboard[xx][yy] = 0;
                }
            }
        }

    }
    if (latch)wind->GFXdraw();//render to window
    
}
void MS_render_board_loss(void* vwind, int x, int y) {
    ValWindow* wind = (ValWindow*)vwind;
    MineMath_emulator* mm_emu = (MineMath_emulator*)wind->get_associated_data("MBoard_");
    ValGFX* mygfx = (ValGFX*)(&(wind->mygfx));
    short val = 0;
    bool latch = false;
    //for loop through mm_emu activeboard

    foreach(xx, mm_emu->width) {
        foreach(yy, mm_emu->height) {
            // check if cell is mine
            if (mm_emu->mineboard[xx][yy] == MM_emu_MINEBOARD_VALUE_MINE) {

                if (mm_emu->activeboard[xx][yy] != MM_emu_ACTIVEBOARD_VALUE_FLAGGED) {
                    //   if mine and not flag, reveal as mine
                    if(x==xx && y==yy) mygfx->color_section(MS_OFFSETx + (xx * MS_G_cell_width) + 4, MS_OFFSETy + (yy * MS_G_cell_width) + 4, MS_G_cell_width - 4, MS_G_cell_width - 4, VRGB_RED);
                    short temp = Opus_vtc.fontdat.lfWeight;
                    //Opus_vtc.fontdat.lfWeight = 10;
                    Opus_vtc.fontdat.lfWidth = 14;
                    Opus_vtc.content = "M";
                    Opus_vtc.x = 3 + MS_OFFSETx + (xx * MS_G_cell_width) + ((MS_G_cell_width - Opus_vtc.getrealtwidth()) / 2);
                    Opus_vtc.y = MS_OFFSETy + (yy * MS_G_cell_width) + 3;
                    Opus_vtc.SetColor(VRGB_RED);
                    Opus_vtc.DIBdraw(wind->myhdc, wind->mygfx.hbmp);
                    Opus_vtc.fontdat.lfWidth = 0;
                    //Opus_vtc.fontdat.lfWeight = temp;
                }
            }
            else if (mm_emu->activeboard[xx][yy] == MM_emu_ACTIVEBOARD_VALUE_FLAGGED) {
                
                Opus_vtc.content = "X";
                short temp = Opus_vtc.fontdat.lfWeight;
                Opus_vtc.fontdat.lfWeight = 400;
                Opus_vtc.x = 3 + MS_OFFSETx + (xx * MS_G_cell_width) + ((MS_G_cell_width - Opus_vtc.getrealtwidth()) / 2);
                Opus_vtc.y = MS_OFFSETy + (yy * MS_G_cell_width) + 2;
                Opus_vtc.SetColor(VRGB_RED);
                Opus_vtc.DIBdraw(wind->myhdc, wind->mygfx.hbmp);
                Opus_vtc.fontdat.lfWeight = temp;
                // else if flag, x out flag 
            }
            
            
        }
    }
    wind->GFXdraw();
}

int capcount = 0;

void MS_mousecapture_process(void* vwind) {

    string type;
    ValWindow* wind = (ValWindow*)vwind;
    MineMath_emulator* mm_emu = (MineMath_emulator*)wind->get_associated_data("MBoard_");
    ValGFX* copy_board= (ValGFX*)wind->get_associated_data("BBoard_gfx");
    ValStopwatch* boardtimer = (ValStopwatch*)WindowMan.find_registered_data("BoardTimer", type);
    int x = wind->mouse_cap->x;
    int y = wind->mouse_cap->y;
    bool click_in_board = false;
    short cell_width = MS_G_cell_width;
    
    //if (x > MS_OFFSETx && y > MS_OFFSETy)click_in_board = true;
    // criticalsect mutex??
    switch (wind->mouse_cap->type) {
    case VW_MOUSECAP_MOVE:
        return;
        break;
    case VW_MOUSECAP_RCLICK:
        if (MS_G_GAME_LOST) return;
        x -= MS_OFFSETx; y -= MS_OFFSETy;
        x /= cell_width;
        y /= cell_width;
        cout << "right click at: " << x << ":" << y << "\n";
        mm_emu->doClick(x, y, true);
        MS_render_board(wind);
        break;

    case VW_MOUSECAP_CLICK:
        if (x > (wind->clientwidth / 2) - 25 && x < (wind->clientwidth / 2) + 25 && y> 5 && y < 55) {
            // reset button clicked
            cout << "reset button clicked" << endl;
            MS_reset(wind);
            return;
        }
        if (MS_G_GAME_LOST) return;
        if(x > MS_OFFSETx&& y > MS_OFFSETy  && (x < MS_OFFSETx+(mm_emu->width*cell_width) && y < MS_OFFSETy + (mm_emu->height * cell_width)) ){
        //if (click_in_board) {
            
            x -= MS_OFFSETx; y -= MS_OFFSETy;
            x /= cell_width;
            y /= cell_width;
            cout << "clicked mine cell at: " << x << ":" << y << "\n";
            if (!mm_emu->doClick(x, y)) {
                
                boardtimer->Stop();
                cout << "game lost" << endl;
                MS_render_board_loss(wind,x,y);
                MS_G_GAME_LOST = true;
                //MS_reset(wind);
            }else if (!MS_G_firstclick) {
                
                boardtimer->Start();
                MS_G_firstclick = true;
            }
            MS_render_board(wind);
        }
        
        break;
    }

    if (mm_emu->checkWin()) {
        
        boardtimer->Stop();
        cout << "game won in " << boardtimer->GetTime() << "ms\n";
        MS_G_GAME_LOST = true; // technically this is 'game over' now, not just lost. but eh.
    }
    wind->GFXdraw();
    

}


void MSGUI_resetbut(void* a) {
    
    ValWindow* controller = WindowMan.fromHWND((HWND)a);
    ValWindow* wind = (ValWindow*)controller->get_associated_data("SweeperVW");
    MineMath_emulator* mm_emu = (MineMath_emulator*)wind->get_associated_data("MBoard_");
    string temp = controller->eval_edit("SeedBox");
    cout << "filled mineboard with seed: " << temp << "\n";
    mm_emu->fill_mineboard_seeded(temp);
    MS_G_SEEDED_GAME = true;
    MS_reset(wind);
    
    
}
void MS_generate_new_seedbut(void* a) {
    
    srand(getticks() & 0x1111111111111111); 
    ValWindow* controller = WindowMan.fromHWND((HWND)a);
    controller->set_editctrl_text("SeedBox", randstr(16));

}

volatile void build_ms_controller(ValWindow* wind) {
    srand(getticks() & 0x1111111111111111);
    string randst = randstr(12);
    cout << "random string: " << randst << "\n";
    wind->AddControl("title=SeedBox,type=VC_EDIT,text=" +randst +",x=55,y=68,w=340,h=26,numblurs=0,transparent=true,nointeract=true,tabname=WidthBox");
    wind->AddControl("title=GenerateBut,type=VC_BUTTON,text=Generate Seeded Board,x=54,y=99,w=340,h=26,dataname=reset_but,needsparent=true");
    wind->AddControl("title=WidthBox,type=VC_EDIT,text=30,x=107,y=32,w=40,h=25,numblurs=0,transparent=true,nointeract=true,tabname=HeightBox");
    wind->AddControl("title=HeightBox,type=VC_EDIT,text=16,x=239,y=32,w=40,h=25,numblurs=0,transparent=true,nointeract=true,tabname=MinesBox");
    wind->AddControl("title=MinesBox,type=VC_EDIT,text=99,x=355,y=32,w=40,h=25,numblurs=0,transparent=true,nointeract=true,tabname=SeedBox");
    wind->AddControl("title=WidLabel,type=VC_LABEL,text=Width,x=59,y=34,w=51,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=HeightLabel,type=VC_LABEL,text=Height,x=187,y=34,w=51,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=MinesLabel,type=VC_LABEL,text=Mines,x=309,y=34,w=51,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=NewSeedBut,type=VC_BUTTON,text=Generate New Seed,x=54,y=130,w=340,h=26,dataname=RandSeedBut,needsparent=true");
    wind->AddControl("type=VC_GLOBAL_STAT_INT,title=status,text=TIME(Ms):*I,x=10,y=-20,w=400,h=18,dataname=boardtimeint");

    wind->calculate_edit_ctrl_tabs();


}
mouse_capture_struct MS_mousecap; 

void MS_boardtimer_thread(void* a) {
    string type;
    ValStopwatch* boardtimer = (ValStopwatch*)WindowMan.find_registered_data("BoardTimer",type);
    int* tt = (int*)WindowMan.find_registered_data("boardtimeint",type);
    while (1) {
        *tt = boardtimer->GetTime();
        //cout << *tt << endl;
        Sleep(7);
    }
}

void MS_thread(void* a) {
    short wid=30, hite=16, mines = 99;
    MineMath_emulator mm_emu(30, 16, 99);
    ValStopwatch BoardTimer(false);
    
    VWM_register_datan(&BoardTimer, "BoardTimer");
    int board_time = 0;
    VWM_register_datan(&board_time, "boardtimeint");

    _beginthread(MS_boardtimer_thread, 0, NULL);


    int clwid = wid * MS_G_cell_width + (MS_OFFSETx*2)+6;
    int clhit = hite * MS_G_cell_width + (MS_OFFSETy +10)+6;
    ValWindow* wind = WindowMan.create_new_windowts("minesweeper_test", 200, 200, clwid, clhit, 1);
 //   wind->AddControl("type=VC_GLOBAL_STAT_INT,title=status,text=TIME:*I,x=10,y=20,w=200,h=18,transparent=false,dataname=boardtimeint");

    ValWindow* controller = WindowMan.create_new_windowts("minesweeper_Controller", 200, 300+clhit, clwid, clhit, 1);
    build_ms_controller(controller);
    wind->is_master = true;
    Sleep(1);
    
    int dd = 0;
    cout << dd++<<"\n";
    opus_vtc_runonce();
    Opus_vtc.SetFont("System");
    Opus_vtc.fontdat.lfQuality= CLEARTYPE_QUALITY;
    ValGFX copy_board,underboard;
    wind->capture_mouse(&MS_mousecap, MS_mousecapture_process);
    cout << dd++ << "\n";
    wind->associate_data((void*)&mm_emu, "MBoard_");
    wind->associate_data((void*)&copy_board, "BBoard_gfx");
    wind->associate_data((void*)&underboard, "BBoard_under");
    controller->associate_data((void*)wind, "SweeperVW");
    cout << dd++ << "\n";
    MS_runonce(&wind->mygfx, &copy_board, 30, 16);
    int width = wind->clientwidth;
    wind->mygfx.draw_box3(((MS_OFFSETx + width) / 2) - 25, 5, ((MS_OFFSETx + width) / 2) + 25, 55, 5, 1, VRGB_GREEN);
    Opus_vtc.content = "new";
    Opus_vtc.x = ((MS_OFFSETx + width) / 2) - ( Opus_vtc.getrealtwidth() / 2);
    Opus_vtc.y = 10;
    Opus_vtc.DIBdraw(wind->myhdc, wind->mygfx.hbmp);
    Opus_vtc.content = "game";
    Opus_vtc.x = ((MS_OFFSETx + width) / 2) - (Opus_vtc.getrealtwidth() / 2);
    Opus_vtc.y = 30;
    Opus_vtc.DIBdraw(wind->myhdc, wind->mygfx.hbmp);
    MS_reset(wind);
    cout << dd++ << "\n";
    __VWM_msgpump();

}
int MS_G_TimingInt = 0;

#include"ValWindowEditor.h"
void editor_thread(void* a) {
    valeditor.start_window_editor_thread();
}
void do_valwindoweditor() {
    //valeditor = new ValWindowEditor();

    //_beginthread(open_VS_hypervisor_window_, 0, neo_loginfunc);
    
    _beginthread(editor_thread, 0, NULL);
    WindowMan.wait_for_splash();
    _beginthread(MS_thread, 0, NULL);
    //WindowMan.wait_for_splash();
    //__VWM_msgpump();
}
void ms_thread_two(void* a) {
    do_valwindoweditor();
}
void vsrand() {

}
int mainhjgjg() {
    foreach(ii, 5) {
        srand(getticks() & 0x1111111111111111);
        foreach(i, 10)cout << rand() % 100 << endl;
        foreach(i, 10)cout << randstr(10) << endl;
    }
}

int mainMSWIND() {  // windowed player
    srand(getticks() & 0x1111111111111111);

    VWM_register_datan(MS_generate_new_seedbut, "RandSeedBut");
    VWM_register_datan(&MS_G_TimingInt, "MS_G_TimingInt");
    VWM_register_datan(MSGUI_resetbut, "reset_but");

    WindowMan.create_splash("MineSplash.jpg", 3000); 
    
    _beginthread(ms_thread_two, 0, NULL);
  
    Hook2 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    KEYBOARD_PROCESSING = true;
    
    __VWM_msgpump();
    MSG msg;
    while (1) {
        GetMessage(&msg, NULL, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#include"mandelbrot.h"
void mandelbrot_editor(void *a) {
    
    _beginthread(editor_thread, 0, NULL);
    WindowMan.wait_for_splash();
    _beginthread(do_mandelbrot_thread, 0, NULL);
}





void newton_derbail_itterate_numerator(double x, double y, int xf, int xe, double& rx, double& ry) {
    VS_complex_exp_dumb(x, y, xe, rx, ry);
    rx *= xf;
    rx -= 1;
}
void newton_derbail_itterate_denominator(double x, double y, int xf, int xe, double& rx, double& ry) {
    VS_complex_exp_dumb(x, y, xe - 1, rx, ry);
    rx *= (xe - 1) * xf; // might need to change that.
    ry *= (xe - 1) * xf;
}


void newton_derbail_itterate(double x, double y, int xf, int xe, double& rx, double& ry) {
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    VS_complex_exp_dumb(zx, zy, xe, zxcopy, zycopy);
    zxcopy *= xf;
    zxcopy -= 1;
    VS_complex_exp_dumb(zx, zy, xe - 1, xx, yy);
    xx *= (xe - 1) * xf; // might need to change that.
    yy *= (xe - 1) * xf;
    VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);

    rx = zx - xx;
    ry = zy - yy;

}

int Arbit_newton_roots_addtoarray_d(double x, double y,double *arr, int &len) {
    double* harr = arr;
    if (len > 1000) {
        cout << "len too long" << endl;
        pause();
    }
    foreach(i, len) {
        if (*harr == x && *(harr + 1) == y)return i;
        harr += 2;
    }
    *harr = x;
    harr++;
    *harr = y;
    len++;
    return len;
}

int Arbit_newton_roots_addtoarray(double x, double y, double* arr, int& len) {


    if (vabs(x) < .000000001)x = 0;
    if (vabs(y) < .000000001)y = 0;
    double* harr = arr;
    if (len > 1000) {
        cout << "len too long" << endl;
        pause();
    }
    foreach(i, len) {
        if (VS_complex_rangecomp(x, y, *harr, *(harr + 1), 0.00001))return i;
        if (*harr == x && *(harr + 1) == y)return i;
        harr += 2;
    }
    *harr = x;
    harr++;
    *harr = y;
    len++;
    return len;
}
newton_fractal arbitrary_newton_derbail_root_process(double x, double y, int xf, int xe, int maxits, double bail) {
    newton_fractal ret;
    int its = 1;
    double xx, yy, zxcopy, zycopy,zx=x,zy=y;
    double zxm1=0, zym1=0;
    while (its < maxits) {
        //VS_complex_exp_dumb(zx, zy, xe, zxcopy, zycopy); 
        //zxcopy *= xf;
        //zxcopy -= 1;
        //VS_complex_exp_dumb(zx, zy, xe-1, xx, yy);
        //xx *= (xe-1)*xf; // might need to change that.
        //yy *= (xe-1)*xf;
        //VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        //zxcopy = zx - xx;
        //zycopy = zy - yy;
        newton_derbail_itterate(zx, zy, xf, xe, zxcopy, zycopy);

        //if (zxcopy == zx && zycopy == zy) {
        if(VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)){
            // report as definite root;
            ret.its = its;
            ret.x = zxcopy;
            ret.y = zycopy;
            ret.cat = 1;
            if (zxcopy == zx && zycopy == zy) ret.cat = 1;
            return ret;
        }
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    ret.its = its;
    ret.x = zxcopy;
    ret.y = zycopy;
    ret.cat = 0;
    return ret;
}
int arbitrary_newton_derbail_roots( int xf, int xe, int maxits,double bail, double* arr, int arrlen) {
    newton_fractal val;
    double* pla;
    // process a sample of spaces to find roots.  
    for (double n = -3.0; n < 3.0; n += .007) {
        val=arbitrary_newton_derbail_root_process(n, n, xf, xe, maxits, bail);
        if (val.cat == 1)Arbit_newton_roots_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process(0, n, xf, xe, maxits, bail);
        if (val.cat == 1)Arbit_newton_roots_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process(n, 0, xf, xe, maxits, bail);
        if (val.cat == 1)Arbit_newton_roots_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process(n, -n, xf, xe, maxits, bail);
        if (val.cat == 1)Arbit_newton_roots_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process(n, sin(n), xf, xe, maxits, bail);
        if (val.cat == 1)Arbit_newton_roots_addtoarray(val.x, val.y, arr, arrlen);

    }
    return arrlen;
}

string arbitrary_newton_derbail_roots_output(int xf, int xe, int maxits, double bail) {
    double arr[2000];
    foreach(i, 2000)arr[i] = 0.0;
    int arrlen = 0;
    arrlen=arbitrary_newton_derbail_roots(xf, xe, maxits, bail, (double*)arr, arrlen);
    cout << arrlen << " roots detected\n";
    int a, b;
    foreach(i, arrlen) {
        a = arr[i * 2];
        b = arr[(i * 2) + 1];
        if (vabs(a) < .000000001)a = 0;
        if (vabs(b) < .000000001)b = 0;
        cout << "if(VS_complex_rangecomp(zxcopy, zycopy," << a << ", " << b << ", 0.00001))return ((its*its) % (spaces*3))+(spaces*"<< ((i+1)%5) <<"); \n";
    }

    return "done";
}



void ANDRO_feed() {
    /*int factors[300];
    int factorslen = 0;
    int i = 0;
    ANDRO_factorlist_alter(1, 4, 0, factors, factorslen);*/

    //ANDRO_factorlist_alter(1, 0, 1, factors, factorslen);
    //factors[i++] = 11;
    //factors[i++] = 13;
    //factors[i++] = 0; // z^4
    //factorslen++;

    //factors[i++] = 7;
    //factors[i++] = 11;
    //factors[i++] = 1; // z^4
    //factorslen++;

    //factors[i++] = 5;
    //factors[i++] = 7;
    //factors[i++] = 0; // z^4
    //factorslen++;
    //
    //factors[i++] = 3;
    //factors[i++] = 5;
    //factors[i++] = 1; // z^4
    //factorslen++;

    //factors[i++] = 1;
    //factors[i++] = 3;
    //factors[i++] = 0; // z^4
    //factorslen++;

    //factors[i++] = 1;
    //factors[i++] = -1;// - xe to denote trig functions?  -- maybe not, derivatives.. switch hell.. 
    //factors[i++] = 1; // instead, -xe to denote const i value
    //factorslen++;

    //factors[i++] = factorslen;
    //factors[i++] = 0;
    //factors[i++] = 1; // z^4
    //factorslen++;


   // cout << "calculating function roots for " << ANDRO_factors_str(factors, factorslen)<<"\n";
   // arbitrary_newton_derbail_roots_outputmf(factors, factorslen, 512, 50);

}
/*

3 roots detected z^3-1
x: -0.5 y: -0.866025
x: 1 y: 0
x: -0.5 y: 0.866025

5 roots detected
x: -0.809017 y: -0.587785
x: 0.309017 y: -0.951057
x: 1 y: 0
x: -0.809017 y: 0.587785
x: 0.309017 y: 0.951057

13 roots detected
x: -0.748511 y: -0.66312
x: 0.120537 y: -0.992709
x: 1 y: 0
x: -0.748511 y: 0.663123
x: 0.120537 y: 0.992709
x: -0.354605 y: -0.93501
x: 0.885456 y: 0.464723
x: 0.885456 y: -0.464723
x: -0.970942 y: -0.23931
x: 0.568065 y: -0.822984
x: -0.354605 y: 0.935016
x: -0.970942 y: 0.239316
x: 0.568065 y: 0.822984
*/


int VS_COMPLEX_SqrtSafe(long double& xr, long double& ir) {
    long double h = xr, hh = ir;
    long double xrd, ird;
    VS_COMPLEX_Sqrt(h, hh);
    long double t = h, tt = hh;
    xrd = h; ird = hh;
    VS_complex_squareLD(t, tt);
    int rt = false;
    if (t != xr || tt != ir) {
        t = h; tt = hh;
        t += .00000000000000002;
        tt -= .00000000000000002;
        xrd = t;
        ird = tt;
        VS_complex_squareLD(t, tt);
        if (t != xr || tt != ir) {
            t = h; tt = hh;
            t += .00000000000000003;
            tt += .00000000000000003;
            xrd = t;
            VS_complex_squareLD(t, tt);
            if (t != xr || tt != ir) {

            }
            else rt= 3;
        }
        else rt= 2;
    }
    else {
        rt = 1;
    }
    if (rt) {
        xr = xrd; 
        ir = ird;
        return rt;
    }
    return 0;

}
int main() {
    int faults = 0,faultsfixed=0;
    int types[40];
    foreach(i, 40)types[i] = 0;
    foreach(xx, 1000) {
        long double test1 = vs_rand_double(), test2 = vs_rand_double();
        if(!(faultsfixed=VS_COMPLEX_SqrtSafe2(test1, test2))){        
            cout << faultsfixed << "\n";
            faults++;
        }
        types[faultsfixed]++;
        cout << "checking x : " << xx << "      \rx";
    }
    cout << "\n\n";
    cout << types[0] << ":" << types[1] << ":" << types[2] <<":"<<types[3]<< "\n";
    cout << "total faults: " << faults << "....fixed: " << faultsfixed <<"\n";
    pause();
    _beginthread(calibrate_timer_thread, 0, NULL);
   // Sleep(1000);
    _beginthread(mandelbrot_editor, 0, NULL);
    __VWM_msgpump();
}

int main_testtt() {
    
    //_Complex g =  
    _Dcomplex c = _DCOMPLEX_(-0.298, 1.0);// _Complex_I;
    cout << cabs(c) << endl;
    

    _Dcomplex* d = &c;
    long double dd = *(long double*)((void*)d);
    cout << dd << endl;
    pause();

}


/*        long double test3 = test1, test4 = test2;
        long double test5, test6;
        //cout << test1 << " test " << test2 << "\n";
        VS_COMPLEX_Sqrt(test1, test2);
        test5 = test1;
        test6 = test2;
        //cout << test1 << " test " << test2 << "\n";
        VS_complex_squareLD(test1, test2);
        //cout << test1 << " test " << test2 << "\n";
        if (test1 != test3 || test2 != test4) {
            cout.precision(17);
           // cout <<  "fault found\n";
           // cout << test1 << " test " << test2 << "\n";
           //cout << test3 << " test " << test4 << "\n";
           //cout << test5 << " test " << test6 << "\n";
           test3 = test5; test4 = test6;
           test5 += .00000000000000002;
           test6 -=  .00000000000000001;
           VS_complex_squareLD(test5, test6);
           //cout << test5 << " testalt " << test6 << "\n";
           if (test5 == test1 && test2 == test6) {
               cout << "slight nudge fixed it.....\n";
               faultsfixed++;
           }
           else {
               test3 -= .00000000000000002;
               //test4 -= .00000000000000001;
               VS_complex_squareLD(test3, test4);
               //cout << test3 << " testalt " << test4 << "\n";
               if (test3 == test1 && test2 == test4) {
                   cout << "slight other nudge fixed it.....\n";
                   //pause();
                   faultsfixed++;
               }
           }*/
