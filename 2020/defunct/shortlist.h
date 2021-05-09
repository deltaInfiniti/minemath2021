#ifndef Short_list_def
#define Short_list_def
#define shortlist cookiehandler
#define slnp cookienode*

struct cookienode{
    string name;
    string value;
    cookienode *next;
};
#define cnptr cookienode*

cnptr newcook(){
    cnptr ret=new cookienode;
    ret->name="";
    ret->value="";
    ret->next=NULL;
    return ret;
}

class cookiehandler{
    private:
        void removenextnode(cnptr vv);  

    public:
        cookiehandler();
        cnptr start;
        void set(string name,string val);
        string cookieval();
        string valueof(string name);
        string nameof(string val);
        bool isset(string name){ return (valueof(name)!="");};
        void clear();
};  
void cookiehandler::clear(){
    while(start!=NULL){
        slnp tmp = start;
        start = start->next;
        delete (tmp);
    }
} 
      
string cookiehandler::valueof(string name){
    if(start == NULL) return "";
    cnptr nc = start;
    while(nc != NULL){
        if(nc->name == name ) return nc->value;
        nc = nc->next;
    }
    return "";
}
string cookiehandler::nameof(string val){
    if(start == NULL) return "";
    cnptr nc = start;
    while(nc != NULL){
        if(nc->value == val ) return nc->name;
        nc = nc->next;
    }
    return "";
}        
cookiehandler::cookiehandler(){
    start = NULL;
}
void cookiehandler::removenextnode(cnptr vv){
    cnptr del = vv->next;
    if(del != NULL){
        vv->next=del->next;
        delete(del);
    }
}

string cookiehandler::cookieval(){
    cnptr cn = start;
    string ret="";
    while(cn!=NULL){
        ret+= cn->name+"="+cn->value;
        if(cn->next != NULL) ret += "; ";
        cn=cn->next;
    }
    if(ret != "");
    ret = "\r\nCookie: "+ret;
    return ret;
}

void cookiehandler::set(string name,string val){
    if(start==NULL){
        cnptr nc = newcook();   
        nc->name=name;
        nc->value=val;
        start = nc;
        return;
    }
    cnptr nc = start,*last=NULL;
    while(nc!=NULL){
        if(nc->name == name){
            if(nc->value==""){
                removenextnode(last);
                return;
            }
            nc->value = val;
            return;
        }
        last=nc;
        nc=nc->next;
    }
    // if u got here, last is last pointer in list. add new here
    nc = newcook();
    nc->name=name;
    nc->value=val;
    last->next=nc;   
}

//int main_test_ch(){
//    
//    cookiehandler ch;
//    ch.set("abc","cde");
//    ch.set("djs","skj");
//    ch.set("abd","cge");
//    ch.set("djd","sfj");
//    ch.set("abad","dde");
//    ch.set("djs","ssj");
//    ch.set("abc","somethingnew");
//    cout << "\n\n were done here"<<endl;
//    
//    cout << ch.cookieval() << endl;
//    pause();
//    return 0;
//}
#endif
