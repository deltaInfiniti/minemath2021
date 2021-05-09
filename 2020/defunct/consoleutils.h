#ifndef Console_CORE
#define Console_CORE

#include<varlist.h>
//#include<color.h>
COORD getxy(){
    HANDLE hOut;
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hOut,&SBInfo);
    return SBInfo.dwCursorPosition;
}


void console_resize(int x,int y)
{	
 LPRECT rect=new RECT;
 HWND mywn = GetConsoleHwnd();
 // get the current window size and position
 GetWindowRect(mywn, rect ); 
// cout << "done"<<endl;
 //rect->left = 0;
 //rect->top = 0;
 rect->right = x;
 rect->bottom =y;
// cout << "set"<<endl;
 // now change the size, position, and Z order 
 // of the window. 
 int wi = x;//rect->right-rect->left;
 int hi = y;//rect->bottom-rect->top;

 ::SetWindowPos(mywn ,       // handle to window
                HWND_TOP,  // placement-order handle
                rect->left,     // horizontal position
                rect->top,      // vertical position
                wi,  // width
                hi, // height
                SWP_SHOWWINDOW );// window-positioning options);
}

//void console_resize(int a, int b){
//    HANDLE hOut;
//    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
//    SMALL_RECT DisplayArea = {0, 0, 0, 0};
//    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    GetConsoleScreenBufferInfo(hOut,
//                               &SBInfo);
//    DisplayArea.Bottom = b;
//    DisplayArea.Right = a;
//    SetConsoleWindowInfo(hOut,
//                             TRUE,
//                             &DisplayArea);
//
//
//}

void gotoxy(COORD wh){gotoxy(wh.X,wh.Y);}
/*
void clrscr(){
    HANDLE hOut;COORD Position;DWORD Written;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;Position.Y = 0;
    FillConsoleOutputCharacter(hOut,' ',15000,Position,&Written);
    gotoxy(0,0);
}
*/
#define clr_grey 7
#define clr_red 12
#define clr_green 6
#define clr_blue 9
#define clr_yellow 14
HANDLE hStdout, hStdin;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
WORD wOldColorAttrs;
static string COLORS[16], foreground = "white", background="black";
static int Old_Color_f = 15,Old_Color_b=0;
static int Color_f=15,Color_b=0;




void setcolors(int i, int n){
    Old_Color_f=Color_f;Old_Color_b=Color_b;Color_f=i;Color_b=n;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;
    n*=16;
    i += n;
    WORD atrs = i;
     SetConsoleTextAttribute(hStdout, atrs);
}
void setcolors(int i){
    setcolors(i,Color_b);

}
void setcolor(){
    setcolors(7);
}
void setcolors(){
    setcolors(7);
}
#define setcolor(i) setcolors(i)
#define setcolor_f(i) setcolors(i)
#define setcolor_b(i) setcolors(Color_f,i);

int color_index(string c){
    for(int i =0; i < 15; i++) if(COLORS[i]==c)return i;
}

void setcolors(string fr, string bk="black"){
	setcolors(color_index(fr),color_index(bk));
}

/* error coloring- *****************************************************
	colors functions from error levels *****************************/

#define fcase(i,n) case i: return n; break;
int error_color(int vl){
    switch(vl){
	fcase(0,15);
	fcase(1,1);
	fcase(2,9);
	fcase(3,10);
	fcase(4,6);
	fcase(5,14);
	fcase(6,12);
	fcase(7,4);
	fcase(8,13);
	fcase(9,5);
    }
    return 7;
}

void setcolorerr(int cc){ setcolor(error_color(cc)); }

/***************************** end error coloring functions **********************************************/
/***************************** Begin Rainbow Coloring functions ******************************************/
// rainbow_out cout's output random colors.  if flag is 0 just text, 1, just backround, 2 both
void rainbow_out(string output,int flag=0){
    
    int fb = Color_f, bb = Color_b;
    int i=fb,n=bb;    
    for(int i =0; i < output.length(); i++){
	if(flag == 2 || flag == 0) i = (int)rand() % 15;
	if(flag == 2 || flag == 1) n = (int)rand() % 15;
        setcolors(i,n);
        cout <<output[i];
    }

    setcolors(fb,bb);  
}
#define rainbowtext(str) rainbow_out(str)
#define rainbowback(str) rainbow_out(str,1)
#define rainbowall(str) rainbow_out(str,2)
/*****************************  End Rainbow Coloring Functions*******************************************/
/***************************** Begin Console LoadingBar Functions****************************************/
COORD bar_crd;
string bar_title;


COORD init_loadingbar(string title){
	cout << "\r";
	bar_crd=getxy();
	bar_title=title;
	return bar_crd;
}

string makebar(int perc){
	string ret = "";
	perc = (((perc/3)*2) + perc/7);
	for(int i = 0; i < perc; i++){
		ret += "||";
	}
	return ret;
}

static char lb_last='|';
static int col_lb=12; // 6
void nextchar_lb(){
  if(col_lb==12)col_lb=6;
  if(lb_last=='|') lb_last='/';
  else if(lb_last=='/') lb_last='-';
  else if(lb_last=='-') lb_last='\\';
  else if(lb_last=='\\') lb_last='/';
  setcolor(col_lb);
  cout << lb_last;
  setcolor();
}

void spaceout(string title,int perc){
	if(title.length()>10) title = title.substr(0,10);
	COORD cr = getxy();
	for(int i = 0; i < title.length(); i++){
		cr.Y+=2;
		gotoxy(cr.X,cr.Y);
		cout << title[i];
	}
	cr.Y=35;
	gotoxy(cr.X,cr.Y);
	setcolorerr(perc/10);
	cout << perc;
	setcolor();
}

void loadingbar(int perc, COORD crd= bar_crd,string title=bar_title){
// 75 chars length
	COORD cr = getxy(),crt=crd;
	crt.Y=78;
	gotoxy(crd);
	
	cout << makebar(perc);
	gotoxy(crd);
	
	spaceout(title,perc);
	gotoxy(crt);
	nextchar_lb();
	gotoxy(cr);
}
	
void slowwait(int w){
    w = w/67;
    COORD hold=getxy();
    while(w>0){
        cout << w*67 << "      ";
        gotoxy(hold.X,hold.Y);
        Sleep(63);
        w--;
    }
    gotoxy(hold.X,hold.Y);
    cout << "       ";
    gotoxy(hold.X,hold.Y);
}

/****************************** out function, Formatted output wrapper ********************************************
out(string(,bool,int))
out("this is some <c12>red<c> text"); will output "this is some" in grey, "red" in red, and "text" in grey
out("<v> sometechnicaldata");  will only output that if VERBOSELOG is set to true, default value is false
out("blahblah<v> techdata"); will output blahblah always, and techdata only if VERBOSELOG
out("<e>red text <e0>no error<e1> cool color <e5> medium Color <e9> Hot colors ");  produce a different color.
   ranging from white(0), blue(2), green(4), red(6), purple(9) making statebased color changes easy

each of the above will be preceeded by the line number if USELINENUMS;
each of the above will output a newline by defaule (see macro out(what) below)

*/


#define out(what) outt(what,true,__LINE__);
static bool VERBOSELOG = false,USELINENUMS=true,OUTTLOG=true;
#define PAUSEEACHLOG false

void outt(string what,bool newline=true,double line=0){
    if(OUTTLOG){
        ofstream ofile("log.txt",ios::app);
        string tt = (newline ? "\n":"");
        ofile << what << ":"<<line<<tt;
        ofile.close();
    }
    if(VERBOSELOG||USELINENUMS)cout << "LINE "<<line<<": ";
    bool wout=false;
    string tag = "";
    int num,b;
    bool verbose=false,rainbow=false;

    if(!instr(what,"<")){ // if no tagging is present, just output the string
        cout << what;
        wout=true;
    }
    else
    for(int i=0;i<what.length();i++){
        if(what[i]=='<'){
            tag= getbetween(what,"<",">",i-1);
            b=findnext(what,">",i);
            if(b>1)i=b;
            if(tag == "v"){
                verbose = !verbose;
            }
            if(tag[0]=='c'){
                if(tag[1]=='r'){ rainbow=!rainbow; continue;}
                if(tag[1]=='='){ tag=tag.substr(2);}// grab arg                
                tag[0]='0';
                num = ctoint(tag);
                if(num<0)setcolor(tag); 
                else setcolor(num);
            }
            if(tag[0]=='e'){
                tag[0]='0';
                num = ctoint(tag);
                if(num != -1)setcolorerr(num);
                else setcolor(4);
            }
            continue;
        }
        if(rainbow) setcolor(rand(15));
        if(verbose){
            if(VERBOSELOG){ 
                cout << what[i];
                wout=true;
                continue;
            }
        }
        else{ cout << what[i];
            wout=true;
        }
    }
    
    setcolor(7);

    if(wout&&newline){
        cout << endl;
    }
    if(PAUSEEACHLOG){pause();}

}

#endif
#ifndef COLORINIT_DEF
#define COLORINIT_DEF

class colorinitializer{
    public:
        colorinitializer();
};

#define SCE_C(n,c) case n: setcolor(c); break;
void setcolorex(int ev){
    setcolors(15,0);
    switch(ev){
        SCE_C(0,15);
        SCE_C(1,1);
        SCE_C(2,9);
        SCE_C(3,10);
        SCE_C(4,6);
        SCE_C(5,14);
        SCE_C(6,12);
        SCE_C(7,14);
        SCE_C(8,13);
        SCE_C(9,15);
        default:
            setcolor(7);
        break;
    }
    
}
int initializecolor(){
    //add a second set with the abbreviations.
//    cout << "initializing color protocol: " << endl;
    COLORS[0] = "black";  // ba
    COLORS[1] = "dark blue"; //db
    COLORS[2] = "dark green"; //dg
    COLORS[3] = "light blue"; //lb
    COLORS[4] = "dark red"; //dr
    COLORS[5] = "purple"; //p
    COLORS[6] = "green"; //g
    COLORS[7] = "grey";  //gr
    COLORS[8] = "dark grey"; //dgr
    COLORS[9] = "blue"; //b
    COLORS[10] = "light green"; //lg
    COLORS[11] = "cyan"; //c
    COLORS[12] = "red"; //r
    COLORS[13] = "pink"; //pi
    COLORS[14] = "yellow"; //y
    COLORS[15] = "white"; //w
   // Get handles to STDIN and STDOUT.
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    return 0;
}
int timestamp();
static unsigned int GL_UPTIME_START=0;
string getdate(){   
   short month,day;
   struct tm *ptr;     
   time_t sec;         
   time(&sec);         
   ptr = localtime(&sec); 

   month = (short) ptr->tm_mon + 1;
   day   = (short) ptr->tm_mday;
   return ctostr(month)+"/"+ctostr(day);
}

int get_uptime(){ return timestamp() - GL_UPTIME_START;}    

colorinitializer::colorinitializer(){
    initializecolor();
    GL_UPTIME_START = timestamp();
    srand(GL_UPTIME_START);
    
}

static colorinitializer *COLORINIT = new colorinitializer();

#define msgbox(str1,str2) MessageBox(NULL, str2, str1, MB_OK);
#define title(str) SetConsoleTitle(str);
#define array(array,setto,len,var) var = 0; while(var < len) { array[var] = setto; var++;}

string readhtmlnotagtext(string htmltext){
    string ret = "";
    int i = 0;
    while(htmltext[i] != '>' && i < htmltext.length())i++; 
    while(i < htmltext.length()) {
        i++;
        while(htmltext[i] != '<' && i < htmltext.length()){
            ret += htmltext[i];
            i++;
        }
        i++;
        while(htmltext[i] != '>' && i < htmltext.length())i++;
    }
    return ret;
    
}
string readhtmlnotagtext(string from, int s, int e){ // from from[s]-from[e] inclusive
    string temp ="";
    for( int i = s; i <= e; i++)
        temp += from[i];
    return readhtmlnotagtext(temp);
}

string readhtmlnotagtext(string from, int s){
    string temp = "";
    for(int i = s; i < from.length(); i++)
        temp += from[i];
    return readhtmlnotagtext(temp);
}
string compilestr(char vals[], int size, char delim){
    int n = 0;
    string ret = "";
    while(vals[n] != delim && n < size){
        ret+= vals[n];
        n++;
    }
    return ret;
}

string gethidden(){
    char last=' ', NEWLINE = '\r', BACKSPACE = '\b';
    int n = 0;
    char ret[255];
    array(ret, '\0', 25, n);
    n = 0;
    while (last != NEWLINE && n < 255) {
        last = _getch();
        if (last != BACKSPACE && last != NEWLINE)
            ret[n] = last;

        if (last != BACKSPACE && last != NEWLINE)
            cout << "*";
        if (last == BACKSPACE) {
            cout << "\b \b";
            ret[n - 1] = '\0';
            n -= 2;
        }
        n++;
    }
cout << endl;
return compilestr(ret, 255, '\0');
}
string readpassword(string prompt){
    outt(prompt+"==>",false);
    return gethidden();
} 
#endif

	
	

