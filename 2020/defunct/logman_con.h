#ifndef ACCOUNT_MANAGER_DEF
#define ACCOUNT_MANAGER_DEF

#include<ValCrypt.h>
#include<varlist.h>
#include<consoleutils.h>
#define stat(a) cout << a << "                                    \r";
string readpass(string s){ cout<<s<<"==>"; return gethidden();}
void nl_add_account(ValCrypt &valCr, varlist &dat, int wh){
    string n = readstr("please enter a new neopets username");
    string p = readpass("please enter a new neopets passwrod");
    dat.set(valCr.encrypt_Sk("username_"+ctostr(wh)),valCr.encrypt_Sk(n));
    dat.set(valCr.encrypt_Sk(n),valCr.encrypt_Sk(p));
    dat.save("data.di");
}

void start_nl(ValCrypt &valCr,varlist&data,string pass=""){
    cout << "\n*********No datafile found, Creating New Profile: Please proceed*****"<<endl;
    string p = (pass==""?readpassword("please enter a new master password"):pass); 
    valCr.start(p,137); 
    nl_add_account(valCr,data,0);
}
    
string accountmanager(ValCrypt &valCr,string pass=""){
    clrscr();
    cout<<"************Neopets Login**************\n\n";
    stat("loading");
    
//    ValCrypt valCr;
    varlist data;
    data.load("data.di");
    string t,n,p;
    if(data.isempty()){start_nl(valCr,data,pass); return accountmanager(valCr);}
    else {
        if(pass=="")p=readpass("Please enter your password");
        else p=pass;
        valCr.start(p,137);
    }
    int i = 0,c=97850;
    while(1){
        c=98744;
        i=0
;        clrscr();
        cout<<"************Saved Neopets Usernames**************\n";
        while(1){
            p=valCr.encrypt_Sk("username_"+ctostr(i));
            if((t=data.valueof(p))=="")break;
            cout <<"["<<i<<"]"<<valCr.decrypt_Sk(t)<<endl;
            i++;
        }
        cout <<"["<<i<<"]new account\n";
        i++; 
        while(c>i+1)c=readint("which #");
        if(c==i-1){
            nl_add_account(valCr,data,i-1);
            continue;
        }
        p=valCr.encrypt_Sk("username_"+ctostr(c));
        n=data.valueof(p);
        p=data.valueof(n);
        n=valCr.decrypt_Sk(n);
        p=valCr.decrypt_Sk(p);
        cout<< n<<":"<< p<<endl;
        //sleep(2000);
        break;
    }
    data.clear();
    return n +"="+ p;
}  
#endif
