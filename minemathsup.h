#ifndef mine_math_sup
#define mine_math_sup
     
int minemath::num_flags(){
    int f = 0;
    for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
            if(GRID[i][m] == -2) f++;            
        }
    }
    return f;
}
int minemath::num_mines(){
    int f = 0;
    for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
            if(GRID[i][m] == 0) f++;            
        }
    }
    return f;
}
int minemath::process_pattern_down(int &i, int &m){
if( m+1 < grid_sizey){ //
        if(dangerp[i][m+1] == 2){
            if( m+2 < grid_sizey){
                if(dangerb[i][m+1]-dangerf[i][m+1] == 3 ){
                    // start of pattern blocks
                    
                    
                    
                    if( dangerp[i][m+2] == 1){ //X21
                        if(GRID[i+1][m] == 0){
                            GRID[i+1][m] = -2;
                            GRID[i+1][m+2] = -2;  //  this processes 121 pattern forward
                            FLAG_SET=true;
                            cout << "found pattern f121 up down x:"<<i<<" y:"<<m << "          "<<endl;
                            return 1;
                        }
                        else if(i > 0 && GRID[i-1][m] ==0){  // change order if crashes
                            GRID[i-1][m] = -2;
                            GRID[i-1][m+2] = -2;
                            FLAG_SET=true;
                            cout << "found pattern f121 down up x:"<<i<<" y:"<<m << "          "<<endl;
                            return 1;
                        }
                    }  //
                    
                    if( dangerp[i][m+2] == 2){ // x221
                        if(m+3 < grid_sizey){ //
                            if(dangerp[i][m+3] ==1){
                                if(GRID[i+1][m+1] == 0 || GRID[i+1][m+1] == -2){
                                    GRID[i+1][m+1] = -2; 
                                    GRID[i+1][m+2] = -2;  //  this processes 1221 pattern forward
                                    FLAG_SET=true;
                                    cout << "found pattern f1221 right up x:"<<i<<" y:"<<m << "          "<<endl;
                                    return 1;
                                }
                                else if(i >0 &&  (  GRID[i-1][m-1] ==-2 || GRID[i-1][m-1] ==0)){  // change order if crashes
                                    GRID[i-1][m-1] = -2;
                                    GRID[i-1][m-2] = -2;
                                    FLAG_SET=true;
                                    cout << "found pattern f1221 Right down x:"<<i<<" y:"<<m << "          "<<endl;
                                    return 1; 
                                }
                            }
                        }
                    }
                        
                                
                
    
                    if( m-1 > -1){
                    if(GRID[i][m-1] == 2){
                        if( m-2 >-1){
                            if(dangerb[i][m-1] == 3 && GRID[i][m-2] == 1){ //X21
                                if(GRID[i+1][m] == 0){
                                    GRID[i+1][m] = -2;
                                    GRID[i+1][m-2] = -2;  //  this processes 121 pattern backward
                                    FLAG_SET=true;
                                    cout << "found pattern up right X:"<<i<<" y:"<<m << "          "<<endl;
                                    return 1;
                                }
                                else if(i-1 > -1 && GRID[i-1][m] ==0){  // change order if crashes
                                    GRID[i-1][m] = -2;
                                    GRID[i-1][m-2] = -2;
                                    FLAG_SET=true;
                                    cout << "found pattern down left X:"<<i<<" y:"<<m << "          "<<endl;
                                    return 1;
                                }
                            }
                            
                            //
                            if( dangerp[i][m-2] == 2){ // 122x
                                if(m-3>0){
                                    if(dangerp[i][m-3] ==1){
                                        if(GRID[i+1][m-1] == 0 || GRID[i+1][m-1] == -2){
                                            GRID[i+1][m-1] = -2; 
                                            GRID[i+1][m-2] = -2;  //  this processes 1221 pattern forward
                                            FLAG_SET=true;
                                            cout << "found pattern f1221 left up x:"<<i<<" y:"<<m <<"          "<< endl;
                                            return 1;
                                        }
                                        else if(i-1 > -1 &&  (  GRID[i-1][m-1] ==-2 || GRID[i-1][m-1] ==0)){  // change order if crashes
                                            GRID[i-1][m-1] = -2;
                                            GRID[i-1][m-2] = -2;
                                            FLAG_SET=true;
                                            cout << "found pattern f1221 left down x:"<<i<<" y:"<<m <<"          "<< endl; 
                                            return 1;
                                        }        
                                    }
                                }
                            }
                                            
                        }
                    }
                    }
                    
                    
                }
            }
                    
        }
        
    }
    return 0;
}



int minemath::process_pattern_accross(int &i, int &m){
    
    if( i+1 < grid_sizex){
        if(dangerp[i+1][m] == 2){
            if( i+2 < grid_sizex){
                if(dangerb[i+1][m]-dangerf[i+1][m] == 3 ){
                    // start of pattern blocks
                    
                    
                    
                    if( dangerp[i+2][m] == 1){ //X21
                        if(GRID[i][m+1] == 0){
                            GRID[i][m+1] = -2;
                            GRID[i+2][m+1] = -2;  //  this processes 121 pattern forward
                            FLAG_SET=true;
                            cout << "found pattern f121 right down x:"<<i<<" y:"<<m <<"          "<< endl;
                            return 1;
                        }
                        else if(m-1 >-1 && GRID[i][m-1] ==0){  // change order if crashes
                            GRID[i][m-1] = -2;
                            GRID[i+2][m-1] = -2;
                            FLAG_SET=true;
                            cout << "found pattern f121 left up x:"<<i<<" y:"<<m <<"          "<< endl;
                            return 1;
                        }
                    }
                    
                    if( GRID[i+2][m] == 2 ){ // x221
                        if(i+3 < grid_sizex){
                            if(GRID[i+3][m] ==1){
                                if(GRID[i+1][m+1] == 0 || GRID[i][m+1] == -2){
                                    GRID[i+1][m+1] = -2; 
                                    GRID[i+2][m+1] = -2;  //  this processes 1221 pattern forward
                                    FLAG_SET=true;
                                    cout << "found pattern f1221 right up x:"<<i<<" y:"<<m << "          "<<endl;
                                    return 1;
                                }
                                else if(m-1 >-1 &&  (  GRID[i+1][m-1] ==-2 || GRID[i+1][m-1] ==0)){  // change order if crashes
                                    GRID[i+1][m-1] = -2;
                                    GRID[i+2][m-1] = -2;
                                    FLAG_SET=true;
                                    cout << "found pattern f1221 Right down x:"<<i<<" y:"<<m <<"          "<< endl;
                                    return 1; 
                                }
                            }
                        }
                    }
                        
                                
                
    
                    if( i-1 > -1){
                    if(GRID[i-1][m] == 2){
                        if( i-2 >-1){
                            if(dangerb[i-1][m] == 3 && GRID[i-2][m] == 1){ //X21
                                if(GRID[i][m+1] == 0){
                                    GRID[i][m+1] = -2;
                                    GRID[i-2][m+1] = -2 ; //  this processes 121 pattern backward
                                    FLAG_SET=true;
                                    cout << "found pattern back up X:"<<i<<" y:"<<m <<"          "<< endl;
                                    return 1;
                                }
                                else if(m-1 >0 && GRID[i][m-1] ==0){  // change order if crashes
                                    GRID[i][m-1] = -2;
                                    GRID[i-2][m-1] = -2;
                                    cout << "found pattern back 2 X:"<<i<<" y:"<<m <<"          "<< endl;
                                    FLAG_SET=true;
                                    return 1;
                                }
                            }
                            
                            
                            if( GRID[i-2][m] == 2){ // 122x
                                if(i-3>0){
                                    if(GRID[i-3][m] ==1){
                                        if(GRID[i][m+1] == 0 || GRID[i][m+1] == -2){
                                            GRID[i-1][m+1] = -2; 
                                            GRID[i-2][m+1] = -2;  //  this processes 1221 pattern forward
                                            FLAG_SET=true;
                                            cout << "found pattern f1221 left up x:"<<i<<" y:"<<m <<"          "<< endl;
                                            return 1;
                                        }
                                        else if(m-1 >0 &&  (  GRID[i][m-1] ==-2 || GRID[i][m-1] ==0)){  // change order if crashes
                                            GRID[i-1][m-1] = -2;
                                            GRID[i-2][m-1] = -2;
                                            FLAG_SET=true;
                                            cout << "found pattern f1221 left down x:"<<i<<" y:"<<m <<"          "<< endl; 
                                            return 1;
                                        }        
                                    }
                                }
                            }
                                            
                        }
                    }
                    }
                    
                    
                }
            }
                    
        }
        
    }
    return 0;
}


int minemath::find_pattern(){
	for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
            if(GRID[i][m]-dangerf[i][m]== 1){
                process_pattern_accross(i,m);
                process_pattern_down(i,m);
                if(FLAG_SET) return 1;
            }
        }
    }
    return 0;
}   

int minemath::find_guess_new(int &x, int &y){
    // for live cell x,y ret is the relative danger
    // add in incrimental search near sent x and y
    
    int lowest = 10000,ltmp=0,lx=-1,ly=-1,reps=0,grp=0;
	for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
			if(GRID[i][m] == 0 ){ // if grid pos is a bomb
			    grp=0;
				ltmp = danger_of_new(i,m,grp);
				if(ltmp==-1)continue;
				if(ltmp==-2){x=i;y=m;return 0;}
				if(ltmp <lowest){
					lowest=ltmp;
					lx=i;
					ly=m;
					reps=0;
				}
				if(ltmp==lowest)reps++;
			}
		}
	}

    int rguess=0;
	if(lx==-1){// if for some reason no click is found
	   
		int rand_space = 2;
        do{
            if(++rguess == GUESS_THRESHOLD){
                x=-1;
                y=-1;
                return 9999;
            }
            // calculate random space
			lx = rand()%(grid_sizex);
			ly = rand()%(grid_sizey);
		}while(GRID[lx][ly] != 0 ); // find live space;
    	cout << "calculated random space  lx: "<<lx << "   ly: "<<ly <<"\n";
    }
	
	x=lx;
	y=ly;
	return lowest;
}
#define _DANGER_MACRO 8  // lower number will exempt wild guesses
                         // 6 exempts clicking mostly surrounded squares 
                         // to avoid guessing corners of lone numbers
int minemath::danger_of_new(int x, int y, int &grp){
  if(GRID[x][y]!=0)return -1;
  if(dangerb[x][y]>_DANGER_MACRO)return -1;// cell is surrounded.
  
    int ret = 0,tot = 0,min = 0,hld = 0;
    int ii=(x+1==grid_sizex?1:2);
    int mm;
    for(int i = (x==0?0:-1) ; i < ii; i++){
        mm = (y+1==grid_sizey?1:2);
        for(int m = (y==0?0:-1) ; m < mm; m++){
             if(GRID[x+i][y+m] >0  ){ 
                //hld = (1000*dangerb[x+i][y+m]-dangerf[x+i][y+m]) /(GRID[x+i][y+m] - dangerf[x+i][y+m]) ;
                //hld = 10000 - ( (100*(GRID[x+i][y+m] - dangerf[x+i][y+m])) / (dangerb[x+i][y+m]-dangerf[x+i][y+m]));
                hld = (100* (GRID[x+i][y+m] - dangerf[x+i][y+m])  )  / (dangerb[x+i][y+m]-dangerf[x+i][y+m]);
                hld -= (GRID[x+i][y+m] - dangerf[x+i][y+m]);
                if(hld>min){
                    grp += min;
                    min=hld;
                }else grp+=hld;
                
                tot++;
            }
         }
    }
    if(tot==0)return -1; //cell is surrounded.
 //   if(ret==0)return -2; // if cell has no danger, probably
//                         // surrounded, no math possible

   grp = grp/tot;
   return min;
}

int minemath::safeclick_loop(int &miplace){
    do{
        FLAG_SET=false;
        parse_danger_grid();
        Find_flags_new(0,0,-1,-1);
    }while(FLAG_SET);
    parse_danger_grid();
    find_click();

    do{
        miplace++;
        find_safe_click_old(xarray[miplace],yarray[miplace]);
    }while(xarray[miplace]!=-1 && yarray[miplace]!=-1);
    
}
int minemath::play_new(){
    xarray[0]=-1; yarray[0]=-1;

    miplace=-1;
    safeclick_loop(miplace);    
    if(miplace >0) return miplace;

    #ifdef _DO_PATTERN 
    find_pattern();

    safeclick_loop(miplace);    
    if(miplace >0) return miplace;
    #endif
    
    find_guess_new(xarray[0],yarray[0]);
    if(xarray[0]!=-1 && yarray[0]!=-1)gguesses++;
    return 0;   
}

int minemath:: low_num_around(int x, int y){
	int find = 9;
    for(int i = -1; i < 2; i++){
    	if(x+i > -1 && x+i < grid_sizex){
	   	   for(int m = -1; m < 2; m++){
                if(i == 0 && m == 0) continue;
                if(y+m > -1 && y+m < grid_sizey){
                 if(GRID[x+i][y+m] > 0 && GRID[x+i][y+m] <find) find=GRID[x+i][y+m];
                }
            }
        }
    }
    return find;
}        

void minemath::find_guess_hard(int &x, int &y){
    hguesses++;
    int hold=9, num;
    x=-1;
    for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
			if(GRID[i][m] == 0){
			     if(x==-1){x=i;y=m;}
                 num =low_num_around(i,m);
			     if ( num <=hold){
                        x=i;
                        y=m;
                        if((i==0 || i==grid_sizex-1 || m==0 || m==grid_sizey-1) && num==1) return;
                        hold=num;
                 }  
            }
        }
        
    }
}
    
bool minemath::run_new(int &x, int &y){
    runtimes++;
    if(miplace >0){
        //cout << miplace << ' ';
        x= xarray[miplace-1];
        y = yarray[miplace-1];
        miplace--;
        return (miplace >0);
    }
    play_new();
    //output();
    if(miplace>0)miplace--;
    x=xarray[miplace];
    y=yarray[miplace];
    if(x<0 || y < 0){
        cout << "h ";
        find_guess_hard(x,y);
        miplace=-1;
        return false;
    }
    miplace--;
    return (miplace >0);
}

bool minemath::add_flags_around_new(int x, int y,int &top,int &left, int &right, int &bottom){

	for(int i = -1; i < 2; i++){
		if(x+i > -1 && x+i < grid_sizex){
            for(int m = -1; m < 2; m++){
    			if(i == 0 && m == 0) continue;
				if(y+m > -1 && y+m < grid_sizey){

                    if(GRID[x+i][y+m] == 0){// if square is still live add to flags
                        GRID[x+i][y+m] = -2;
                        if(x+i<left) left=x+i;
                        if(y+m<top) top=y+m;
                        if(x+i>right) right=x+i;
                        if(y+m>bottom) bottom=y+m;
                        dangerf[x][y]++;
                        FLAG_SET=true;
                    }

                }
    		}
        }
	}


}
void minemath::Find_flags_new(int x=0, int y=0,int rig=-1, int bott=-1){
    if(rig == -1 || bott == -1){rig=grid_sizex; bott=grid_sizey;}
	int top=199,bottom=-1,left=199,right=-1;
    for(int i = x; i < rig; i++){
		for(int m = y; m < bott; m++){
			if(GRID[i][m] > 0 && dangerb[i][m]-dangerf[i][m] == GRID[i][m]-dangerf[i][m]){ //  if the number of bombs surrounding == Nnumber
				add_flags_around_new(i,m,top,left,right,bottom );    
            }	
				
        }
	}
		
	if(top!=199){
        for(int i = left; i <=right; i++){
            for( int m = top; m <=bottom; m++){
                danger_Grid(i,m,dangerb[i][m],dangerf[i][m]);
            }
        }
        Find_flags_new(left,top,right,bottom);
    }

}
#endif
