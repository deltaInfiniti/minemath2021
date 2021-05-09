


#ifndef COLOR_CORE
#define COLOR_CORE
#include <varlist.h>

HANDLE hStdout, hStdin;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
WORD wOldColorAttrs;
static string COLORS[16], foreground = "white", background="black";
static int Old_Color_f = 15,Old_Color_b=0;
static int Color_f=15,Color_b=0;


string error_color(int vl){
    switch(vl){
        case 0:
            return "white";
        break;
        case 1:
            return "dark blue";
        break;
        case 2:
            return "blue";
        break;
        case 3:
            return "light green";
        break;
        case 4:
            return "green";
        break;
        case 5:
            return "yellow";
        break;
        case 6:
            return "light red";
        break;
        case 7:
            return "red";
        break;
        case 8:
            return "dark red";
        break;
        case 9:
            return "pink";
        break;
        case 10:
            return "purple";
        break;
    }
    return "white";
}

string allowerc(string low){
    string work="";
    int n = 0;
    while(n < low.length()){
        work += tolower(low[n]);
        n++;
    }
    return work;
}


string colorat(int i){
    return COLORS[i];
}

int colorindex(string look){
    look = allowerc(look);
    for(int i = 0; i < 16; i++){
        if(look == COLORS[i])
            return i;
    }
    return -1;
}


/*
bool setcolors(string fr, string back){
    int frnd=colorindex(fr), bkrnd = colorindex(back);
    if(frnd == -1){
        string msg = "cannot find specified color: " + fr;
//        msgbox("error",msg.c_str());
        return false;
    }
    if(bkrnd == -1){
        string msg = "cannot find specified color: " + fr;
//        msgbox("error",msg.c_str());
        return false;
    }
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;
    foreground = fr;
    background = back;
    bkrnd *= 16;
    int total = frnd +bkrnd;
    WORD atrs = total;
    SetConsoleTextAttribute(hStdout, atrs);
    return true;
}

void setcolors(string fr){
    if(ctoint(fr) != -1) fr = colorat(ctoint(fr));
    setcolors(fr,background);
}
void setcolorerr(int err){
    setcolors(error_color(err));
}
void setcolor(int i){
    setcolors(colorat(i),background);
}
*/

void rainbowtext(string output){
    string frt=foreground, bakt=background;
    WORD old = wOldColorAttrs;
    for(int i =0; i < output.length(); i++){
        setcolors(colorat((int)rand() % 15),background);
        cout << output[i];
    }
    setcolors(frt,bakt);
    wOldColorAttrs = old;
  
}

void rainbowback(string output){
    string frt=foreground, bakt=background;
    WORD old = wOldColorAttrs;
    for(int i =0; i < output.length(); i++){
        setcolors(foreground,colorat((int)rand() % 15));
        cout << output[i];
    }
    setcolors(frt,bakt);
    wOldColorAttrs = old;
  
}

void rainbowall(string output){
    string frt=foreground, bakt=background;
    WORD old = wOldColorAttrs;
    for(int i =0; i < output.length(); i++){
        setcolors(colorat((int)rand() % 15),colorat((int)rand() % 15));
        cout <<output[i];
    }
    setcolors(frt,bakt);
    wOldColorAttrs = old;
  
}


void invertcolor(){
    setcolors(background,foreground);
}

void resetcolor(){
    setcolors("grey","black");
}

void colorformat(string text){
    string color = "grey",setcolor;
    for(int i = 0; i < text.length(); i++){
        if(text.substr(i,8) == "<format:"){
            int ind = findnextl(text,"<format:",i);
            setcolor = getbetween(text,ind,">");
            color = setcolor;
            i +=8+color.length()+1;
        }
        if(setcolor == "rainbow" || setcolor == "random")
        color = colorat((int)rand() % 15);
        setcolors(color);
        cout << text[i];
    }
    setcolors("grey");
}

