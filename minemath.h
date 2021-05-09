#ifndef mine_mathh
#define mine_mathh


#define GUESS_THRESHOLD 30
#define USE_OLD_SAFE_METHOD true
//#define DO_OUTPUT
/*   Minemath.h
	a class and controller AI for playing minesweeper with a relatively high success rate
	originally created as an AI to play neggsweeper, a distraction/diversion game on NeoPets.com
	adapted for use in arbitrary minesweeper style games
	Main file in minemath project contains functions required to use this as a minesweeperx autoplayer.
	current world record fastest expert solve is .26 seconds as recorded by minesweeperx.   
	documented .94 second expert run at  https://www.youtube.com/watch?v=DUbsbpimbas

	includes an extremely robust solver which can determine any mathmatically provable safe click
	and a relatively fast guess definer.  Mathmatically worst possible odds for guess are 50/50
	
	List of functions to come:
	
	colorize console output (with consoleutils.h out function for ease but not speed)
	live helper display- draw circles/rectangles on mineboard after each click to show safe spaces or good guesses
	
	**migrate screengrab functionality to minemath to reduce on GDI memory related issues
	  -- valscreenwrapper.h created for this purpose
	  
	Weighted targetting to make hard guesses near  50/50 chances in an attempt to improve guess odds.
	 *  mostly done -----multiple clicks system to forward list of safe clicks to avoid intermediate parsing
	 
	sliding buffer to determine changes between clicks // done in opus
		- carry over mine and flag data
		- carry over number and danger data
		- overwrite danger data within 2 blocks of changed block
		- mutlithreading capabilities for parsing danger grid as blocks are updated via event ( very low priority)
			- addflags in opus can be threaded 
		
	automatic callibration 
	Heavy Solver-guess revamped- MagnumOpus
		-  Uses simulated frames to determine patern behavior when no safe click is found.
		-  pattern behavior can be determined by layering 'possible frames' on top of eachother 
		  - any block that must exist in any single state in all 'possible frames' must be that type of block.
		  - process every non 1 number.  generate each possible stack that number can create
		        -order list of simulations to parse, lower numbers should go first for faster parsing/higher success rate 
		        
		           -create structure array to hold grid coords for each affected block for each target number
		           -add bombs left to right per number.
		     	     	- test each surrounding LOWER number against new bomb grid (equal and higher numbers all stack frames affecting these will be possible)
		     	 	    - if any number is touching more than iteself in bombs in this theoretical frame, that frame is not possible
		     	 	    - if any number is not touching exactly itself in bombs this frame is impossible..
		     	 	    - if all numbers are parsed and no number is impossible, the frame is determined to be possible 
		     	   	    	-add 1 to field of structure representing land or bomb. 
		     	   	-binary move bombs untill all theoretical frames are 'generated'
		     - count each " possible stack frame". nodes containing the stack count in land with 0 in bomb, or stack count in bomb 0 in land must be that type.
		     - if node is 'empty' click that space and run
		     - if node is 'bomb', set that bomb and reparse for safe clicks/new patterns
		     - if no node is determinable, default to hard_guess 
		     - alternatively, could determine lowest danger space by finding highest node value in empty node from stack frame testing step.
		-threaded mode for faster simulations.  Can segment grid- Segments must overlap by 2 blocks at least for full parsing.
		//only have to add one to stack frame count for theoretical index when theoretical bomb/land is touching that square.
		


*/
class minemath{

    public:
        minemath(){minemath(0,0);};
        minemath(int x, int y);
        // call this before each game, x+y are dimensions of minefield
        void Start_game(int x, int y);
        // call this to set cells 0 is land, -1 is flag, positive number is number
        bool Set_grid(int x, int y, int value);
        // call this to get click coords
        bool run(int &x, int &y);
        // call this to output current board to console
        void output();
        // outputs information about game to file.
        void output_info(string fname);

        
       // new:
       void find_guess_hard(int &x, int &y);
       void Find_flags_new(int x, int y,int rig, int bott);
       bool add_flags_around_new(int x, int y,int &top,int &left, int &right, int &bottom);
       int low_num_around(int x, int y);
       int play_new();
       bool run_new(int &x, int &y);
       int find_guess_new(int &x, int &y);
       int danger_of_new(int x, int y, int &grp);
       int process_pattern_down(int &i, int &m);
       int process_pattern_accross(int &i, int &m);
       int find_pattern();
       int safeclick_loop(int &miplace);
       int num_flags();
       int num_mines();
        int xarray[50];
        int yarray[50];
        int miplace;
        int runtimes; // calls to run this game
        int truntimes; // calls to run total
        int gguesses;
        int tguesses;
        int thguesses;
        int hguesses;


		//mAGnumbOpus:
		// Full solver, Main should only need minimal lines to run this.
		/*
		notes-  Blank spaces must be stored differently than in GRID.  0'd spaces due to flagging will act improperly if these are not checked to make sure 0 bombs are touching.
		
		
		int opusgrid[BAD][BAD];// need a struct for this. Include x,y,lastparsedframe, bombcount, emptycount (maybe these are arrays), int IS_TRUE(0 if not true, 1 if true bomb, 2 if true safe click), lastchangedframe, needsupdate
        int opusarray[9]; // current 'affected frame' blocks for quick access 
        POINT opus_parse_list[1000];
        
        void MagNumb_calibrate(bool manual);// run screen calibration/ auto or manual
        void Magnum();// parse GRID, find safe clicks, determine changed spaces for first attention, run and manage Opus or Opus threads.
		
		void Opus();
		void Opus_Manager(int threads);
		void* Opus_Thread(void* a);
		
		//bool opus_getScreen();  // store and manipulate all HDC here, in class, to avoid GDI errors.  Maybe write it's own wrapper class.  Mouse_follow seems to work without errors and many screen grabs.
		//bool opus_getPixel();   // valscreen makes this redundant
		
		
		bool opus_is_adjacent(index, x,y) ;// opusarray index and x,y grid coords to test adjacency (ix==x+-1, iy==y+-1);
		// maybe make into macro.  maybe 
		void opus_generate_parse_list();
		bool opus_simulation(int x, int y); // parse full simulation for number at this location.  return true if some block type was determined
		bool opus_next_frame(); // returns true if the frame was successfuly advanced, false if last frame in simulation.  binary moves simulated bombs.
		bool opus_check_frame(); // checks this specific frame for possibility. returns true if possible.
		
		void opus_grid_insert(int x, int y, int value); // only fills opus_grid, for use by grid_fill();
		void opus_grid_manual_insert(int x, int y, int value); //fills grid and opus_grid at the same time.  
		void opus_grid_fill(); //fills opus_grid with data from GRID and dangerb/f/p
		void opus_reset(); // reset opus vars
		void opus_newgame();
		 
		
		
		
		
		
		  
		  
		*/  

    private:
  
       bool play(int &x, int &y);
       int danger_of(int x, int y);
       void find_click();
       void add_clicks_around(int x, int y);
       void find_guess(int &x, int &y);
       void find_safe_click(int &x,int &y);
       void find_safe_click_old(int &x,int &y);
       
       void Find_flags();
       void add_flags_around(int x, int y);
       void reset_grid();

       //  meat of the action
       // parses dangerb and dangerf out of GRID
       void danger_Grid(int x, int y, int &bomb, int &flag);

       void parse_danger_grid();

            #define Board_Array_Dims 50
            #define BAD Board_Array_Dims
            #define BAD2 2500 // bad*2
            
            int GRID[BAD][BAD]; //grid  -2=flag -1=space 0=live >0 that number
            int dangerb[BAD][BAD];//live cells around a number
            int dangerf[BAD][BAD]; // flags around a number
            int dangerp[BAD][BAD]; // GRID-dangerf for speed
            bool Clicks[BAD][BAD]; //holds click data for fast access
                                  // ammend to csl later

            bool GRID_PARSED;//=false;
            int grid_sizex;
            int grid_sizey;
            bool FLAG_SET;//=false;
            bool SAFE_CLICKS;//=false;
            int num_safe_clicks;//0
            int last_clickx;//=-1;
            int last_clicky;//=-1;




};

#include "minemathsup.h"  // supliment file includes 'new' functions for versioning reasons. can probably add here now.

minemath::minemath(int x, int y){
//    grid_sizex=x;
//    grid_sizey=y;
    FLAG_SET=false;
    SAFE_CLICKS=false;
    last_clickx=-1;
    last_clicky=-1;
    num_safe_clicks=0;
 //   reset_grid();
    truntimes=0;
    runtimes=0;
    tguesses =0;
    gguesses =0;
    thguesses =0;
    hguesses=0;

}
/*
void minemath::outputb(){
	gotoxy(0,40);
    for(int i = 0; i < grid_sizex; i++){
		cout << endl;
        for(int m = 0; m < grid_sizey; m++){
            cout << dangerb[i][m] << endl;
        }
    }
}

void minemath::outputf(){
	gotoxy(0,40);
    for(int i = 0; i < grid_sizex; i++){
		cout << endl;
        for(int m = 0; m < grid_sizey; m++){
            cout << dangerf[i][m] << endl;
        }
    }
}
*/
void minemath::output(){
	gotoxy(0,0);
    for(int i = 0; i < grid_sizex; i++){
		cout << endl;
        for(int m = 0; m < grid_sizey; m++){

			if(GRID[i][m]== 0)cout << "X";
			else if(GRID[i][m]== -2)cout<<"F";
			else if(GRID[i][m]== -1)cout<<" ";
			else if(GRID[i][m]> 0)cout <<GRID[i][m];
		}
	}
}
void minemath::output_info(string fname){
	//gotoxy(0,0);
	ofstream ofile("minemath_board_info.txt");
	ofile << "total calls to run: " << truntimes << endl;
	ofile << "guesses total: " << tguesses << endl;
	ofile << "guesses last game: " << gguesses << endl;
	ofile << "hard guesses total: " << hguesses << endl;
    ofile << "hard guesses last game: " << hguesses << endl;
	
	//mnmnm,nm,n
	ofstream ifile(fname.c_str());
	ifile << "calls to run:" << runtimes << endl;
	ifile << "GRID:\n";
    for(int i = 0; i < grid_sizex; i++){
		ifile << endl;
        for(int m = 0; m < grid_sizey; m++){

			if(GRID[i][m]== 0)ifile << "X";
			else if(GRID[i][m]== -2)ifile<<"F";
			else if(GRID[i][m]== -1)ifile<<" ";
			else if(GRID[i][m]> 0)ifile <<GRID[i][m];
			ifile << " ";
		}
	}
	ifile << "\n\ndangerb:\n";
    int hold = 0;
    for(int i = 0; i < grid_sizex; i++){
		ifile << endl;
        for(int m = 0; m < grid_sizey; m++){
            hold =dangerb[i][m];
            if(hold <0) ifile << "  ";
            else ifile << hold << " ";        }
    }
	ifile << "\n\ndangerf:\n";
    for(int i = 0; i < grid_sizex; i++){
		ifile << endl;
        for(int m = 0; m < grid_sizey; m++){
            hold = dangerf[i][m];
            if(hold <0) ifile << "  ";
            else ifile << hold << " ";
        }
    }
    ifile.close();

}
void minemath::Start_game(int x, int y){
    grid_sizex=x;
    grid_sizey=y;
    FLAG_SET=false;
    SAFE_CLICKS=false;
    last_clickx=-1;
    last_clicky=-1;
    num_safe_clicks=0;
    reset_grid();
    truntimes+=runtimes;
    runtimes=0;
    tguesses += gguesses;
    gguesses =0;
    thguesses += hguesses;
    hguesses=0;
}

bool minemath::Set_grid(int x, int y, int value){

    if(GRID[x][y]==-2) return false;

    GRID[x][y]=value;
    GRID_PARSED=false;
    return true;
} 

void minemath::reset_grid(){

	for(int i = 0; i < BAD; i++)
		for(int m = 0; m < BAD; m++){
			GRID[i][m] = 0;
			dangerb[i][m] = 0;
			dangerf[i][m] = 0;
		    dangerp[i][m] = 0;
            Clicks[i][m]=0;
        }

}

//parse danger grid for numbers
void minemath::danger_Grid(int x, int y, int &bomb, int &flag){
	int ret = 0,xi,ym;
    if(GRID[x][y] < 0){bomb=-1;flag=-1;return ;}
    bomb = 0; flag=0;
	for(int i = -1; i < 2; i++){
        xi=x+i;
        if(xi > -1 && xi < grid_sizex){
    		for(int m = -1; m < 2; m++){
                
    			if(i == 0 && m == 0) continue;
    			ym=m+y;
    			if(ym > -1 && ym < grid_sizey){

                    if(GRID[xi][ym] == 0) bomb++;
    				if(GRID[xi][ym] == -2){flag++; bomb++;}

    			}
    		}
        }
    }
    #ifdef _DO_PATTERN
    dangerp[x][y] = GRID[x][y]-dangerf[x][y];
    #endif
//    if(bomb==0) flag=1;
//    if(flag==0);
}

// for each square, run danger_grid with it's correspoding parralell arrays
void minemath::parse_danger_grid(){
	for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
            dangerb[i][m]=0; dangerf[i][m]=0;
			danger_Grid(i,m,dangerb[i][m],dangerf[i][m]);
		}
	}
}



void minemath::add_flags_around(int x, int y){
	for(int i = -1; i < 2; i++){
		if(x+i > -1 && x+i < grid_sizex){
            for(int m = -1; m < 2; m++){
    			if(i == 0 && m == 0) continue;
				if(y+m > -1 && y+m < grid_sizey){

                    if(GRID[x+i][y+m] == 0){// if square is still live add to flags
                        GRID[x+i][y+m] = -2;
                        FLAG_SET=true;
                    }

                }
    		}
        }
	}
}

void minemath::Find_flags(){
	for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
			if(GRID[i][m] > 0 && dangerb[i][m] == GRID[i][m]-dangerf[i][m]){ //  if the number of bombs surrounding == Nnumber
				add_flags_around(i,m );
            }
        }
	}
}



#define SFC_check(xx,yy) if(Clicks[xx][yy] ==1){x=xx; y=yy;  SAFE_CLICKS=true; return;}
#define check(x,y) SFC_check(x,y)
void minemath::find_safe_click(int &x,int &y){
    if(USE_OLD_SAFE_METHOD) return find_safe_click_old(x,y);
    if(y ==-1 ||x==-1){
        x=last_clickx;
        last_clickx=-1;
        y=last_clicky;
        find_safe_click(x,y);
        return;
    }
    check(x,y);
    int cx, cy,ctch=0;;
    int xp,xm,yp,ym;
    for(int i = 1; true ;i++){
        xp = x+i; xm = x-i; yp = y+i; ym =y-i;
        if(  (xp > grid_sizex  && yp > grid_sizey ) && (xm < 0  &&  ym < 0))   return;
        if(xp < grid_sizex  && yp < grid_sizey) check(xp,yp);
        if(xm > 0  &&  ym > 0)    check(xm,ym);
        
        for(int m = 1; m <= i+1;m++ ){
            ctch=(yp-m);
            if(!( ctch > grid_sizey  || ctch <0))  check(xp, ctch);
            
            ctch=(xp-m);
            if(!( ctch > grid_sizey  || ctch <0)) check(ctch, yp);

            ctch=(ym+m);
            if(!( ctch > grid_sizey  || ctch <0))check(xm, ctch);

            ctch=(xm+m);
            if(!( ctch > grid_sizey  || ctch <0))check(ctch, ym);
        }
                
    }
}


void minemath::find_safe_click_old(int &x,int &y){
    for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
            if(Clicks[i][m]==1){
                Clicks[i][m]=0;
                x=i;
                y=m;
                SAFE_CLICKS=true;
                return;
            }

        }
    }
    x=-1; y=-1;
    SAFE_CLICKS=false;
}

void minemath::find_guess(int &x, int &y){
    // for live cell x,y ret is the relative danger

    int highest = -1,ltmp=0,lx=-1,ly=-1,reps=0;
	for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
			if(GRID[i][m] == 0 ){ // if grid pos is a negg
				ltmp = danger_of(i,m);
				if(ltmp==-2){x=i;y=m;return;}
				
				if(ltmp==-1)continue;
				if(ltmp >highest){
					highest=ltmp;
					lx=i;
					ly=m;
					reps=0;
				}
				if(ltmp==highest)reps++;
			}
		}
	}

    int rguess=0;
	if(lx==-1){// if for some reason the board is full...
		int rand_space = 2;
        do{
            if(++rguess == GUESS_THRESHOLD){
                x=-1;
                y=-1;
                return;
            }
            // calculate random space
			lx = rand()%(grid_sizex);
			ly = rand()%(grid_sizey);
		}while(GRID[lx][ly] != 0 ); // find live space;
	}
	x=lx;
	y=ly;
}





void minemath::add_clicks_around(int x, int y){
	for(int i = -1; i < 2; i++){
    	if(x+i > -1 && x+i < grid_sizex){
	   	   for(int m = -1; m < 2; m++){
                if(i == 0 && m == 0) continue;
                if(y+m > -1 && y+m < grid_sizey){
                	if(GRID[x+i][y+m] == 0){
                        Clicks[x+i][y+m]=1;
                        SAFE_CLICKS=true;
                    }
                }
            }
		}
	}
}

void minemath::find_click(){
	for(int i = 0; i < grid_sizex; i++){
		for(int m = 0; m < grid_sizey; m++){
			if(GRID[i][m] > 0 && dangerf[i][m] == GRID[i][m]) //  if the number flags surrounding == check
				add_clicks_around(i,m);

		}
	}
}

int minemath::danger_of(int x, int y){
  if(GRID[x][y]!=0)return -1;
  //redundant : if(GRID[x][y]>7)return -1;// cell is surrounded.
  
    int ret = 0;
    int tot = 0;
    int min = -1;
    int hld = 0;
    int grp = 0;
    int imax = ( x == grid_sizex-1 ? 1:2);
    int mmax;
    int xi=0, ym=0, g=0,f=0,b=0;
    for(int i = (x==0?0:-1); i < imax; i++){
        xi = x+i;
        //if(x+i > -1 && x+i < grid_sizex){
		      mmax = ( y == grid_sizey-1 ? 1:2);
              for(int m = -1; m < mmax; m++){
                    ym = y+m;
                    //if(ym >-1 && ym < grid_sizey){
    				
    				     if(GRID[xi][ym] >0  ){ 
                            //hld = (1000*dangerb[x+i][y+m]-dangerf[x+i][y+m]) /(GRID[x+i][y+m] - dangerf[x+i][y+m]) ;
                            /* THIS BLOCK WORKING FOR RECORD SETTER VERSION
                            //hld = 10000 - ( (100*(GRID[x+i][y+m] - dangerf[x+i][y+m])) / (dangerb[x+i][y+m]-dangerf[x+i][y+m]));
                            //if(hld>min){
//                                grp += min;
//                                min=hld;
//                            }else grp+=hld;
//                            
                            */
                            
                            g += GRID[xi][ym];
                            f +=dangerf[xi][ym];
                            b += dangerb[xi][ym];
                            tot++;
                        }
                    //}
              }
         //}
    }
    if(tot==0)return -1; //cell is surrounded.
 //   if(ret==0)return -2; // if cell has no danger, probably
//                         // surrounded, no math possible
    min = (  (1000*(g - f)) / (b-f)  );
   
   //return min+ tot;
}





/* find all flags and parse whole grid.*/
bool minemath::play(int &x, int &y){
    x=-1;y=-1;
    find_safe_click(x,y);
    if(x!=-1 && y!=-1){
        //SAFE_CLICKS=false;
        return true;
    }

    parse_danger_grid();
    Find_flags();
    #ifdef DO_OUTPUT 
        output(); 
        //pause();
    #endif
//
//    do{
//        parse_danger_grid();
//        FLAG_SET=false;
//        Find_flags();
//    }while(FLAG_SET);

    find_click();
    find_safe_click(x,y);
    if((x!=-1 && y!=-1))return SAFE_CLICKS; //true

    find_guess(x,y);
    return true;

}

bool minemath::run(int &x, int &y){
    bool r= play(x,y);
    last_clickx=(x==-2?-1:x);
    last_clicky=(y==-2?-1:y);
    return r;

}


/*Main process-

    fill board array
    call run
    check xy
    click xy

*/


#endif
