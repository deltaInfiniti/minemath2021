

//#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE ((DPI_AWARENESS_CONTEXT)-2)


#include <windows.h>
#include <iostream>   
#include <iomanip> 
#include <fstream>
#include <conio.h>
#include <string.h> 
#include<stdio.h>  
using namespace std;
#include "valtimer.h"

int BIG_x = -1, BIG_y = -1;// cell offsets to boarder pixels for easy access

int	Mine_window_offset_x, Mine_window_offset_y, Mine_window_width, Mine_window_height;
HHOOK Hook, Hook2;
static bool DO_PAUSE = false, SHIFT_DOWN = false, CONTROL_DOWN = false, KEYBOARD_PROCESSING = false;
static bool F9FLAG = false, F8FLAG = false, F7FLAG = false, F6FLAG = false, F5FLAG = false, F3FLAG = false;
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
#define Mouse_leftclick(){mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0,0,0);}
#define Title(s) SetConsoleTitleA(s)

#define ctocp(ch) ((char*)ch.c_str())
#define GetPhysicalCursorPos(p) GetCursorPos(p) 
#define SetPhysicalCursorPos(x,y) SetCursorPos(x,y)
#define SHOW(a) cout << #a << ": " << (a) << "   "<<endl;
#define SHOWf(a,b) b << #a << ": "<< (a) << endl;

#define GLOBALSLEEP();// Sleep(1200);
#define ctoint(s) atoi(s.c_str())

#define ShowConsole() ShowWindow(GetConsoleWindow(),SW_SHOW);
#define HideConsole() ShowWindow(GetConsoleWindow(),SW_HIDE);



// global compile options
#define Y_CONSOLE_START_POS 2  // this sets where clrscr starts clearing for varout
#define Y_CONSOLE_VAROUT_POS 1
#define Y_CONSOLE_VAROUT_DEPTH 1


static int CLICK_TYPE = 0;

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

    FillConsoleOutputCharacter(hOut, ' ', 9000, Position, &Written);
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
void pause() {

    if (KEYBOARD_PROCESSING) {
        cout << "press f10 to unpause" << endl;
        //Title("paused");
        DO_PAUSE = true;
        while (DO_PAUSE)Sleep(7);
    }
    else system("Pause");

}
string ctostr(int i) {
    char a[38];
    _itoa_s(i, a, 10);
    return a;
}

string creftostr(COLORREF a) {
    string ret = ctostr((unsigned int)GetRValue(a));
    ret += ",";
    ret += ctostr((unsigned int)GetGValue(a));
    ret += ",";
    ret += ctostr((unsigned int)GetBValue(a));
    return ret;
}
#include "ValScreenwrapper.h" 
#include "opus.h"


void opus_output_info(string fname);
bool TOGGLE_OPUS_KBD = true;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
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
                break;
            case VK_F4:
                (CLICK_TYPE > 1 ? CLICK_TYPE = 0 : CLICK_TYPE++);
                getxy(x, y);
                gotoxy(15, Y_CONSOLE_VAROUT_POS); SHOW(CLICK_TYPE);
                gotoxy(x, y);
                break;
            case VK_F5:
                clrscr();
                if (TOGGLE_OPUS_KBD) { opus_color_out(); opus_output_info("opusinfo.txt"); }
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
                gotoxy(30, Y_CONSOLE_VAROUT_POS); SHOW(GLOBAL_SLEEP_VALUE);
                gotoxy(x, y);

                break;
            case VK_F8:
                F8FLAG = !F8FLAG;
                GLOBAL_SLEEP_VALUE += 10;
                getxy(x, y);
                gotoxy(30, Y_CONSOLE_VAROUT_POS); SHOW(GLOBAL_SLEEP_VALUE);
                gotoxy(x, y);
                break;
            case VK_F9:
                F9FLAG = !F9FLAG;
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
int main() {// minemath2021 WR bot runner 
    _beginthread(calibrate_timer_thread, 0, NULL);
    MSG msg;
    cout << "f4-click type f5-output f6-grid_reset f7&f8-sleep:v^ f10-pause  f11-clrscr f12-quit\n\n";
    setFontSize(11);

    gotoxy(0, 3);
    cout << "starting Minemath process" << endl;

    StayOnTop(800, 1800);
    opus_HWND_move_resize(GetConsoleHwnd(), 60, 50, 800, 1000);
    opusvs.create_transparent_window2(840, 60, 730, 590);
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




