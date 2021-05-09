#pragma once
// global compile options
#define Y_CONSOLE_START_POS 2  // this sets where clrscr starts clearing for varout
#define Y_CONSOLE_VAROUT_POS 1
#define Y_CONSOLE_VAROUT_DEPTH 1
static int GLOBAL_SLEEP_VALUE = 0;
#define _LOST_FOLDER "lost\\" 
#define _WON_FOLDER ""
static bool DO_PAUSE, KEYBOARD_PROCESSING=false;


#define Mouse_leftclick(){mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0,0,0);}
#define Mouse_rightclick(){mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP,0,0,0,0);}
#define Title(s) SetConsoleTitle(s)
#define ctocp(ch) ((char*)ch.c_str())
#define GetPhysicalCursorPos(p) GetCursorPos(p) 
#define SetPhysicalCursorPos(x,y) SetCursorPos(x,y)
#define SHOW(a) cout << #a << ": " << (a) << "   "<<endl;
#define SHOWf(a,b) b << #a << ": "<< (a) << endl;
#define LostSleep() Sleep(50);
#define GLOBALSLEEP();// Sleep(1200);
#define ctoint(s) atoi(s.c_str())
#define csl_pop(str) tokenizecsl(str)

string ctostr(int i) {
    char a[38];
    _itoa_s(i, a, 10);
    return a;
}



WCHAR* ctolpwstr(string& s) {
    char* a = (char*)s.c_str();
    WCHAR* p;
    int len = MultiByteToWideChar(CP_ACP, 0,  a, -1, NULL, 0);
    p = new WCHAR[len];
    MultiByteToWideChar(CP_ACP, 0, a, -1, (LPWSTR)p, len);

    return p;
}

WCHAR* ctowstr(int s) {// working.
    WCHAR *m = new WCHAR[256];
    swprintf_s(m,256, L"%d", s);
    return m;
}




string creftostr(COLORREF a) {
    string ret = ctostr((unsigned int)GetRValue(a));
    ret += ",";
    ret += ctostr((unsigned int)GetGValue(a));
    ret += ",";
    ret += ctostr((unsigned int)GetBValue(a));
    return ret;
}
int milmil, milsec;

int timestamp() {
    time_t seconds;
    time(&seconds);
    return seconds;
}
int millitime()
{
    struct _timeb timebuffer;
    _ftime64_s(&timebuffer);
    return timebuffer.millitm;
}

void startmil() {
    milsec = timestamp();
    milmil = millitime();
}
int endmil() {
    int i = millitime();
    int a = (timestamp() - milsec) * 1000;
    int b = (i < milmil ? ((-1000) + (milmil - i)) : (i - milmil));
    return (a + b);
}
string str_cursor_pos() {
    POINT p;
    GetPhysicalCursorPos(&p);;
    return "*" + ctostr(p.x) + "," + ctostr(p.y) + "*";
}
static ofstream ofile;
void outcurpos() {
    if (DO_PAUSE)return;
    string com = "c," + ctostr(endmil()) + ",";
    startmil();
    POINT p;
    GetPhysicalCursorPos(&p);
    com += ctostr(p.x) + "," + ctostr(p.y);
    cout << com << endl;
    ofile << com << endl;
}
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
void random_seed() {
    time_t seconds;
    time(&seconds);
    srand((unsigned int)seconds);
}
int random(int a) {
    return rand() % a;
}

/*******************************************************************************************************************
 ************************************** console and keyboard   *****************************************************/
void pause() {

    if (KEYBOARD_PROCESSING) {
        cout << "press f10 to unpause" << endl;
        //Title("paused");
        DO_PAUSE = true;
        while (DO_PAUSE)Sleep(7);
    }
    else system("Pause");

}

HWND GetConsoleHwnd(void) {
    return GetConsoleWindow();
}
