#ifndef mine_window
#define mine_window

#include <iostream>
#include <windows.h>
using namespace std;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
static LPRECT MINErect;
static bool found_mine_window=false;;
static string EWPDATA_title;
HWND minewindowHWND=NULL;
bool MineWindow(string title,int &x, int &y){
     MINErect=new RECT;
    EWPDATA_title= title;
    found_mine_window=false;
    LPARAM lp;
	EnumWindows(EnumWindowsProc, lp);
	
    x = MINErect->left;
	y = MINErect->top;
	cout << "out of enums" << endl;//
//	system("Pause");
    return found_mine_window;
}

#include<winuser.h>
void ShowMineWindow(HWND mywn){
     ShowWindow(mywn, SW_RESTORE);
 LPRECT rect=new RECT;

 GetWindowRect(mywn, rect ); 
 int wi = rect->right-rect->left;
 int hi = rect->bottom-rect->top;
  rect->left = GetSystemMetrics(SM_CXSCREEN)-(wi+10);
  rect->top = GetSystemMetrics(SM_CYSCREEN)- (hi+35);
  MINErect->left=rect->left;
  MINErect->top=rect->top;
 ::SetWindowPos(mywn ,       // handle to window
                HWND_TOPMOST,  // placement-order handle
                rect->left,     // horizontal position
                rect->top,      // vertical position
                wi,  // width
                hi, // height
                SWP_SHOWWINDOW | SWP_NOMOVE |SWP_NOSIZE |SWP_ASYNCWINDOWPOS);// window-positioning options);


 

}
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    string cmp;
	char title[80];
	//GetWindowText(hwnd,title,sizeof(title));
	if(title[0] == '\0')return true;
	cmp = title;
    if(cmp == EWPDATA_title){
        ShowMineWindow(hwnd);
        found_mine_window=true;
        GetWindowRect(hwnd, MINErect);
        minewindowHWND=hwnd;
        //system("Pause");
        return false;
    }


	return TRUE;
}
#endif
