// tsheahan@comcast.com

string getbetween(string,int,int);
string getbetween(string,int);
int findnext(string,string,int);
string& cslformat(string&);
string& cslunformat(string&);
void breakarg(string,string&,string&,char);
int findfirstof(string,string,char&);
string tokenize(string &,string delim,char &);
void str_replace_all(string&,string,string,int);
string tokenizecsl(string &str,bool );
void addtocsl(string &,string );
//int ctoint(string );
string ctostr(int );
#define booltostr(bol) (bol?"true":"false")
bool isin(string , string );
int findnext(string, string , int);
int findnextl(string , string , int);
string getbetween(string,string,string,int);
string getbetween(string,int,string);
string getbetween(string,int,int);
#define ctoint(s) atoi(s.c_str())
string readstr(string);
int readint(string);

#define llower(o,t) (o<t ? o:t)
#define hhigher(o,t) !llower(o,t)
//(!o<t ? o:t)
#define pause() cout << "Press Enter to Continue...\r";while(_getch()!='\r'); cout << "                           \r"; 
#define higher(n1,n2) (n1 > n2 ? n1:n2)
#define lower(i,x) (i<x?i:x)

void outt(string,bool,double);
int rand(int i){return (rand() %(i==0?1:i) )+1;}
#define sleep(a) Sleep(a);
#define abso(a) (a>0?a:a*-1)
#define cisnum(ch) (ch>='0' &&ch<='9')
#define ctocp(c) ((char*)c.c_str())
#define msgbox(str) MessageBox(NULL, str, NULL, NULL);
#define foreach(a,b) for(int a=0; a < b; a++)
/*class varlist{
     vlip start;
    private:
     vlip end;
     int size;
      // 0= insert 1= reset  2 = start is null 3 =unused 4=endisnull
     int ptrto(string item, vlip &ret);
     bool isstack,isqueue,jump;
     string isset(vlip v, string n, string val);
    
    
    public: 
    
     varlist();
     string set(string name,string value);
     string valueof(string name);
     void output();
     
     //to test:
     void ini(vlip &vv){vv=start;};
     void i_i(vlip &vv){vv=start;};
     vlip getnext(vlip vv,string &n, string &v);
     string todsl(string delim);
     string tocsl(){todsl(",");};
     int SaveFile(string filename);
     int LoadFile(string filename);
     int load(string f){return LoadFile(f);};
     int save(string f){ return SaveFile(f);};
     bool isset(string name);
     string nameof(string value);   
     
     void queue(string n, string v);
     void stack(string n, string v);
     void pop(string &n, string &v);
     void lift(string &n, string &v);
     string gettype();
     void setjumps();
     int getlength();
     void resett();
     string csl_value(string val);
};

*/
