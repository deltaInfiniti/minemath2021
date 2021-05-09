// THIS FILE IS TO BE INCLUDED INLINE WITH VARLIST AND SHOULD NOT BE USED SEPERATLY.
// CSLs.h has all of the Comma Seperated List manipulation functions and depends on 
// some functions found in varlist.h.


//#include <varlist.h>  // include only for testing purposes



//when adding items to a csl, call cslformat to remove ,s
string& cslformat(string& str) {
    str_replace_all(str, "`", "`1");
    str_replace_all(str, ",", "`0");
    return str;
}
//when reading data from a csl call cslunformat to convert back
string& cslunformat(string& str) {
    str_replace_all(str, "`0", ",");
    str_replace_all(str, "`1", "`");
    return str;
}

#define csl_pop(str) tokenizecsl(str)
string tokenizecsl(string& str, bool format = true) {
    int i = findnext(str, ",", 0);
    string ret = "";
    if (i == -1) {
        ret = str;
        str = "";
        return ret;
    }
    ret = getbetween(str, 0, i);
    if (format)cslunformat(ret);
    str = getbetween(str, i + 1);
    return ret;
}
#define csl_add(csl,wh) addtocsl(csl,wh);
void addtocsl(string& str, string wh) {
    cslformat(wh);
    str += "," + wh;
}
bool csl_isin(string csl, string what) {
    string tmp;
    while (csl != "") {
        tmp = csl_pop(csl);
        if (tmp == what)return true;
    }
    return false;
}
//  Strlist and csl convertion functions.  Strlist already has a built in tocsl Member function.
#include<strlist.h>
#ifdef StrList_CORE

int csltoslist(string csl,strlist &lst){
    string tmp;
    int ret = 0;
    while(csl!=""){
        ret++;
        tmp = csl_pop(csl);
        lst.set(tmp);
    }
    return 0;
}

#endif
