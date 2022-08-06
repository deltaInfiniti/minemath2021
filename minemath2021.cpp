

//#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE ((DPI_AWARENESS_CONTEXT)-2)

//test 
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
bool OPUS_trainer_Normalized = true;
bool OPUS_trainer_safeclicks = true;
bool OPUS_trainer_flags = true;
bool OPUS_trainer_guesses = true;
bool OPUS_MAGNUMB_drawdomains = false;
#include "minemath_emu.h"
#include "ValScreenwrapper.h" 
#include "opus.h"
#include <Windows.h>
#include <WinUser.h>

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
int main_tes() { // emu_tester
    G_VS_RANDSEED(getticks());
    _beginthread(calibrate_timer_thread, 0, NULL);
    //while (1) {
    //    binout(G_VS_Rand3(G_VS_randMAX));
    //    pause();
    //}
    MineMath_emulator testemu(30, 16, 99);
    //cout << testemu.get_maxd(0, 0) << "  " << testemu.get_maxd(0, 1) << "  " << testemu.get_maxd(30, 16) << "  \n";
    //pause();

    
    Sleep(3300); 
    testemu.play();


    ValStopwatch stop,watch;
    watch.LapUnPause();
    for (int x = 0; x < 10000; x++) {
        stop.LapUnPause();
        testemu.fill_mineboard5();
        stop.Lap();
        testemu.reset();
    }
    watch.Lap();
    watch.output("watch");
    stop.output("filling board");
    testemu.reset();
   
    for (int x = 0; x < 100000; x++) {
        testemu.fill_mineboard5();
        testemu.validate();
        testemu.reset();
    }
    cout << "total validate changes: " << testemu.total_validate_changes << "\n";
    testemu.console_output_stats();
    pause();
    
    while (1) {
        stop.LapUnPause();
        testemu.fill_mineboard5();
        stop.Lap();
        testemu.console_output();
        if(!testemu.validate())cout << "validate failed\n";
        stop.output("filling board");
        testemu.reset();
        pause();
    }
    pause();

}

int main_r() {// minemath2021 WR bot runner 

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

int main() {// emulator runner


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
int main_mdtrainer() {// minemath2021 trainer main

    _beginthread(calibrate_timer_thread, 0, NULL);
    opusvs.Set(300, 300, 1800, 1800);
    MSG msg;

    setFontSize(11);


    gotoxy(0, 3);
    StayOnTop(800, 1800);
    opus_HWND_move_resize(GetConsoleHwnd(), 60, 50, 800, 1000);
    opus_trainer_hwnd = trainer.create_transparent_window(865, 585, 800, 500);//(300,300,800,800);  
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
int main_windows() {
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



