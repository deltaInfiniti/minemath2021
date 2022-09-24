#ifndef mine_MagNumb_Opus
#define mine_MagNumb_Opus

#define MUTATE_fast_array_alter_extra_args 

#define GAME_TYPE_INTERMEDIATE 1
#define GAME_TYPE_EASY 2
#define GAME_TYPE_EXPERT 0
#define GAME_TYPE_MAX 4
//464 mines in 49x49
#define GAME_TYPE_99 5
// 1912 mines in 99x99
#define GAME_TYPE_1080max 6// 59x99 @1204
// old max was 49x49
// new max is 99x99
#define GAME_TYPE 0
#define OUTPUT_SEEDS 0
#include"ValScreenwrapper.h"

//quick-click globals
static bool CORNER_CLICK = 1;//  clicks only corners
static bool SIDE_CLICK = 0; // clicks both corners and middle of sides
static int RANDOM_CLICK = 0;// number of random clicks
static int LOCATION_CLICKx = 0;// x coord of location click
static int LOCATION_CLICKy = 0;// x coord of location click
static bool JUST_ONE_CLICK = 1;
/*  MUTATE_fast_array_alter.h
   macro mutating, array bounds safe, 'around' targetting, function for use in
   alternative versions of  grid insert/safe clicks/add flags  */
#define MUTATE_fast_array_alter fast_array_add
#define iptf() (*ipt)+=val;
#include "mutate_fast_array_alter.h"

#define MUTATE_fast_array_alter fast_array_sub
#define iptf() (*ipt)-=val;
#include "mutate_fast_array_alter.h"

#define MUTATE_fast_array_alter fast_array_set_ifzero
#define iptf() (*ipt==0?*ipt=val:0);
#include "mutate_fast_array_alter.h"

#define MUTATE_fast_array_alter fast_array_sub_ifnum
#define iptf() ((*ipt>0 && *ipt<8) ? *ipt-=val:0);
#include "mutate_fast_array_alter.h"

#define MUTATE_fast_array_alter fast_array_set
#define iptf() (*ipt)=val;
#include "mutate_fast_array_alter.h"

#define MUTATE_fast_array_alter fast_array_inc
#define iptf() (*ipt)++;
#include "mutate_fast_array_alter.h"

#define MUTATE_fast_array_alter fast_array_dec
#define iptf() (*ipt)--;
#include "mutate_fast_array_alter.h"
   /*notes and plans
	   unroll some loops for speedup
	   change the 'around' functions to use mutation_fast_array_alter
	    7/21/22- After some thought, except the danger reduction on land change, the rest of the around functions
		           all edit multiple grids simultaneously, requiring a fundamental change in thought processes involved
				   - I started a new version called parseless_flow but soon realized that the around function's extended
				   knowledge in determining the bit-profile of the next call is only super useful in the edge case
				   and somewhat useful on lands adjacent to edge lands.  Edge lands would require a 2nd switch statement
				   inside the full 1111 state switch to determine the bitpaterns of the next set of calls.  Since most
				   lands on a mineboard would go through 2 switch statements, which is still likely faster than recalculating
				   the bitpatterns for each adjacent cell individually for non-edge cells.

	   create stripped down stormer for WR attempts -- mostly done.  .13 record .15 recorded on 8/31/20
																	 .12 recorded on 7/14/22, 111 ms recorded on 7/15/22

	   use pointer to reduce on vector access overhead  --use mutation_fast_array_alter  -- in loops
		 -- further timing research says this is basically not nessesary.  both above and below

	   when parsing (safe clicks probably) can set x/y bounds to ignore-
		 - in flags, parse y/x, if whole x row is danger0 danger=(danger||danger++)
			  then add 1 to ignorex[y].  reset loops to continue if ignorex[y]

		 - x is longer direction, but needs to be changed to inner loop on other parses
		   - in order to skip whole x loop at a given y.

		 this may drastically speed up further parsing steps.
			- 7/15/22 this is not going to give much extra speed for the cost of calculation. 
			          - as in magnumbdomains, 

		 for performance reasons, this version does not log much data about the game
		   add redundant versions of opus methods that record more info -- 80% done
		   7/21/22  - substantial logging and statistical information recording is done during all runs

	   add coastline/island simulations
	   7/21/22 -  Magmumb Domains lives. Initial domain breaking, direct colision and probative VLA reduction system in place today
	              Tested in guessless mode over 5m samples with 0 failures, win rate has recently risen from ~2.5% to 4.01% guessless. 

	   add robust heuristic guessing system
	   7/21/22  - after a few days of testing, I've reached a 20% winrate with guessing

	   EDIT: as of 7/15/22, all of these are completed.  I am nearly satisfied.
			 currently, I have only 1 system left to impliment in minemath.
			 - Theoretical domain probability guessing system
			   -not very likely to increase solve rate substantially.
			    -- 7/22/22 boy howdy was I wrong about that prediction. Lots learned thanks to BinaryChop on r/Minesweeper
				--- their simulator system is robust and quite fast for being written in JS. 
				--- their solverate seems to be ~50% with guessing and around 5% without. a yawning chasm of imperfection
				--- discovered VLA reduction partial collision cascading and it's relative, reverse propagation yesterday
				--- need to formalize the definitions and do some more sanity testing before I create a whole system for it.
				---- create TheoreticalDomain Class to handle switching between domains and theoretical domains. 
				---- Tdomains will have a minimum and maximum number of mines associated rather than a set number.
				---- tdomains can calculate real percentages based on binomial coeficient.  Write a hashtable hardcode for binco
				theory=  DDD =   landsleft :choose(highest number of mines in domains) -landsleft :choose(lowest number of mines in domains) 
				             Note- myabe reversed. put lower value on bottom...  remember which is lower to affect the parent Tdom
					     remove chance DDD/ LL:choose(highest) from higher set's contribution, opposite for lower contribution.




   */
#define CLICK_SLEEP() //Sleep(200);

   //mAGnumbOpus:
   // Full solver, Main should only need minimal lines to run this.
struct vpoint {
	int x;
	int y;
};

char crashbuffer[1000];
vpoint safe_clicks[5000]; // list of safe clicks to be made 
int safe_clicks_len = 0;
int cell_pixel_width[2] = { 0,0 }; // depreciated
int restart_x = 0; //xy location of restart button
int restart_y = 0;


ValScreen opusvs; // valscreen for screen data 
int opuscx, opuscy; // holds last click data
int opus_sidesx, opus_sidesy; // new version of sides[2];
// opus_cpw is defunct. use BIGx BIGy instead.
int opus_CPWx = 17; // Cell_pixel_width[0] clone
int opus_CPWy = 17;// Cell_pixel_width[1] clone
int opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh; // valscreen getHWNDscreen dimension vars

int opus_click_offsetx, opus_click_offsety; // quick absolute offset to middle of 0,0 land
int opus_cell_color_count = 0; // records number of loops required for cell_color to be determined.


int opus_BIGoffsetx, opus_BIGoffsety; // deprecated, used for absolute mouse move/ click functions
bool opusFound_mine_or_click = false; // flag to see if should test win/loss or continue solving
bool opus_guessed_this_game = false; // did a guess happen this game
int opus_guessed_this_game_total = 0;  // total number of games won with guesses
int opus_bombcount = 0; // number of bombs found.  if 1 that bomb is a 7
INPUT opus_input; // win8 compatible input variable for send_clicks
COLORREF opus_corner_pix; // color of top left boarder pix for testing if cell is live or space/number
int Magnum_flagged = 0, Magnum_clicked = 0; // number of each magnum processed this loop. if 0,0 no paterns found.
int opus_tbombcount = 0; // total bombcolored cells found this frame
int opus_flags_placed = 0; // number of flags found in this frame
int opus_totalflags = 0; // total number of flags on the board
bool did_this_game_magframe = 0, did_this_game_magfrontier_collision = 0, did_this_game_magfrontier_VLA = 0; //flags for what solving techniques were used this game
int opus_difficulty_savedcount[4] = { 0,0,0,0 }; // count of saved games this run of this difficulty
// 100 is required for 99x99 boards.  can be changed to 37 for expert boards but doesn't change much.
#define Board_Array_Dims 100
//#define Board_Array_Dims 50
#define BAD Board_Array_Dims
#define BAD2 10000 // bad*bad


BOOL CALLBACK opus_EWP(HWND hwnd, LPARAM lParam);
HWND opusHWND = NULL;

//int BIG_x=20, BIG_y=20;
// resetting all grids will automatically prompt a full board re-parse with next 'run'

//notes-  Blank spaces must be stored differently than in GRID.  0'd spaces due to flagging will act improperly if these are not checked to make sure 0 bombs are touching.
 // stores flag normalized data -- ONLY HOLDS NUMBERS and lands(9) normalized for flags around it. all other states -1
//opusgridf normals space,flag = -1  /  number= grid number-# of touching flags / land=9 / fully processed cell=8  // default 9
int opusgridf[BAD][BAD];
int opusgridf_reset[BAD][BAD];// stores empty board (all 9s) to copy into opusgridf on fast_reset


// opusdanger must be filled with 3 on corners, 5 on non-corner sides and 8 on any other space before each board start.
int opusdanger[BAD][BAD];// stores number of lands touching this square, -1 if is land
int opusdanger_reset[BAD][BAD];  // stores empty board (3's&5's&8's) to be memcpy into opusdanger on fast_reset


int opusflags[BAD][BAD];// number of flags touching this square, no reset, all values default to 0

// opus grid normals: 0= land square, 1-6= that number, 9= flag, 8= space
int opusgrid[BAD][BAD];


void opus_trainer_thread(void* a); // runs minemath Helper - visual trainer for minesweeperx. 
void opus_trainer_draw_flags(); // used by minemath helper 
void opus_trainer_draw_safeclicks(); // used by minemath helper

// these are the main thread runners for magnumbOpus- does everything. just get a drawing window and start these threads.
void opus_main_thread_info(void* a); // outputs extended timing info, doesn't seem to have a measurable performance hit
void opus_main_thread(void* a); // standard stormer thread. 

void opus_doclick(int x, int y, bool h); // click handler for click changing demo version
void opus_click(int x, int y, bool h); // basic xp compatible mouse clicker (avg time 100x 3000ms on win10)
void opus_click2(int x, int y, bool h); // basic win8 compatible mouse clicker(avg time 100x 1400ms on win10)
void opus_MouseLeftClick(int x, int y); // helper function for clicksqueue and click2
void opus_click3(int x, int y, bool h); // direct input mouse event into minesweeper window input queue( avg time 100x 6ms)		
void opus_clickqueue(int x, int y); // queue clicks for sending all once non-coalessed 
void opus_send_click_queue(); // sends queue'd clicks

void opus_main_thread(void* a);
// this runs MagNumbOpus completely.  No guessing currently.  threading required for keyboard processing.  keyboard processing required.
void opus_reset();
// reset opus data grids and instance variables
void opus_fast_reset();
// quick reset all opus data grids and instance variables. must call _reset at least once before calling this
void opus_restart_game();
// do restart clicks. - clicks smiley, then starts game with clicks specified at compile time


int opus_grid_insert(int x, int y, int value);
int opus_grid_insert_mutated(int x, int y, int value);
// inserts new number or space into grid
// alters grid, gridf, danger where applicable
int opus_cell_color(int x, int y);
// used by readboard to determine the type of cell via pixel data
int opus_readboard();
// uses opusvs to read the mineboard, uses color_cell and grid_insert to fill all vectors
int opus_readboard_buffered(); // much faster.
// uses opusvs to read the mineboard through DIB buffer, uses color_cell_buffered and grid_insert_mutated to fill all vectors

// this block can be optimized-  Many loops and mutliple bounds testing instances can be changed to pointer math or mutated functions
void opus_add_safe_clicks(int x, int y); // set safeclick array // do safeclicks in this block somewhere
void opus_add_flags(int x, int y);// changes all lands around x,y to flag and alters gridf danger and flags appropriately.
void opus_flag_and_safe_clicks(); // flags and safeclicks in same loop for slightly faster processing. untested.
void opus_flags();  // comutes flags and calls _add_flags
void opus_safe_clicks(); // computes safe clicks and adds to safeclick array  // switch to doing clicks here directly.
void opus_dedupe_safeclicks(); // removes duplicate entries from safe_clicks

void opus_output_info(string fnmae);// outputs as much data from last game as possible to info.txt
void opus_color_out(); // output all( or select) data structures to console with color


void MagNumb_calibrate(bool manual);// run screen calibration/ auto or manual
//void Magnumb();// advanced pattern recognition system.  detailed above.
//void Magnumb_Manager(int threads);
//void* Magnumb_Thread(void* a);


//int Opus();
// runs MagNumb Opus completely.
// parse GRID/gridf, find safe clicks/flags run and manage Magnum | Magnum threads.

int num_common_lands(int& x, int& y, int xx, int yy);
// used by Magnubm_basic
// returns number of 'common lands' between (touching both)  x,y and xx,yy. 
void get_non_common(int& x, int& y, int xx, int yy);
// used by Magnubm_basic to find land touching x,y but not touching xx,yy
// sets x and y to location of land 
void Magnumb_basic();
// basic essential patern recognition system.  Complete detection of normalized 1(2)-1(3)~2 and 2(3)-1(2)~2 style paterns
// adds flags and safe-clicks where applicable. tested safe and accurate 


int num_uncommon_lands(int x, int y, int xx, int yy); // assumes lands are adjacent, returns total uncommon lands belonging to x,y
void inline magnumb_frame_process(int gftarg, int gfref, int n, int i, int x, int y); // magnum frame helper function
void Magnumb_frame(); // advanced version of magnumb patern recognition system. detects/solves all 2 adjacent number paterns




int MagNumb_calibrate();
// calibrates Opus--
//   - finds/opens/moves/resizes drawing console and records HWND
//   - finds/opens/moves minesweeper x window and sets to always on top
//   - fills all hard-coded configuration data
//   - draws configuration to drawing console for visual integrity check
void opus_get_drawing_console();
// opens 'drawing.exe' helper program for a free, nonassociated window to draw to. 
int opus_draw_clicks();
// draws to drawing console current mineboard image with overlayed corner and middle-land positions 
// visually displays configuration check.
void opus_Show_Window(HWND mywn);
// sets HWND to TOPMOST and unhides it
void opus_ontop(HWND mywn, int x, int y, int w, int h);
// sets HWND to TOPMOST at x,y with dims width=w height=h
bool opus_MineWindow(string title, int& x, int& y, int& w, int& h);
// calls opus_EWP and gets window dimensions of window with title=title;
BOOL CALLBACK opus_EWP(HWND hwnd, LPARAM lParam);
// opus specific enum windows proc 




#define GRID_VALUE_BOMB -2  //>?  grid bomb value.  could be a 7
#define GRID_VALUE_LAND 0
#define GRID_VALUE_SPACE 8
#define GRID_VALUE_FLAG 9
#define GRID_VALUE_SAFE 10


#define GRIDF_VALUE_LAND 9
#define GRIDF_VALUE_SPACE -1
#define GRIDF_VALUE_FLAG -1

/******************************************ultrabeta optimization block*************************************
#define MUTATE_fast_array_alter fast_array_DecrementDangerAround
#define iptf() ((*ipt>0 && *ipt<8) ? *ipt-=val:0);
#define iptf() (--*ipt== opusgridf && *ipt<8) ? *ipt-=val:0);
#include "mutate_fast_array_alter.h"


*/
/************************************************************************************************************
****************************************   reset and restart block   ****************************************/
void opus_fast_reset() {
	did_this_game_magframe = 0;
	did_this_game_magfrontier_collision = 0;
	did_this_game_magfrontier_VLA = 0;
	opus_guessed_this_game = false;
	safe_clicks_len = 0;
	opus_bombcount = 0;
	opus_flags_placed = 0;
	memset(opusgrid, 0, BAD2 * 4);
	//memset(opusdanger,0,BAD2*4);
	memset(opusflags, 0, BAD2 * sizeof(int));
	//memset(opusgridf,9,BAD2*4);
	memcpy(opusgridf, opusgridf_reset, BAD2 * 4);
	memcpy(opusdanger, opusdanger_reset, BAD2 * 4);
}
#define Mine_Corners(var,x,y,val) var[0][0]=val; var[0][y]=val; var[x][0]=val; var[x][y]=val;
void opus_reset() {
	did_this_game_magframe = 0;
	did_this_game_magfrontier_collision = 0;
	did_this_game_magfrontier_VLA = 0;
	safe_clicks_len = 0;
	opus_bombcount = 0;
	opus_guessed_this_game = false;
	opus_flags_placed = 0;
	int holdw = opus_sidesx - 1;
	int holdh = opus_sidesy - 1;
	// reset opusgrid corner=3, side=5,middle=8;
	opusdanger[0][0] = 3;
	opusdanger[0][holdh] = 3;
	opusdanger[holdw][0] = 3;
	opusdanger[holdw][holdh] = 3;

	opusgrid[0][0] = 0;
	opusgrid[0][holdh] = 0;
	opusgrid[holdw][0] = 0;
	opusgrid[holdw][holdh] = 0;


	Mine_Corners(opusflags, holdw, holdh, 0);
	Mine_Corners(opusgridf, holdw, holdh, 9);

	for (int x = 1; x < holdw; x++) { //slightly unrolled loop for corners/sides
		opusdanger[x][0] = 5;
		opusdanger[x][holdh] = 5;

		opusgrid[x][0] = 0;
		opusgrid[x][holdh] = 0;

		opusflags[x][0] = 0;
		opusflags[x][holdh] = 0;

		opusgridf[x][0] = 9;
		opusgridf[x][holdh] = 9;
		if (x < holdh) {
			opusdanger[0][x] = 5;
			opusdanger[holdw][x] = 5;

			opusgrid[0][x] = 0;
			opusgrid[holdw][x] = 0;

			opusflags[0][x] = 0;
			opusflags[holdw][x] = 0;

			opusgridf[0][x] = 9;
			opusgridf[holdw][x] = 9;

		}
		for (int y = 1; y < holdh; y++) {
			opusdanger[x][y] = 8;
			opusgrid[x][y] = 0;
			opusflags[x][y] = 0;
			opusgridf[x][y] = 9;
		}
	}
	memcpy(opusdanger_reset, opusdanger, BAD2 * 4);
	memcpy(opusgridf_reset, opusgridf, BAD2 * 4);

}
bool opus_check_win() {
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			if (opusdanger[x][y] != 0)return 0;
		}
	}
	return 1;
}
//opus_check_pix(x,y);
bool OPUS_Testing_noscaling = true;
void opus_restart_game() {
	// inherits flags from minemath2014 
//		     SetCursorPos(restart_x,restart_y);
//		     Mouse_leftclick();
//		     Mouse_leftclick();
//		     CLICK_SLEEP();
//		     CLICK_SLEEP();
//		     CLICK_SLEEP();
//		     CLICK_SLEEP();
//	
			//startmil();
	if (OPUS_Testing_noscaling) {
		SendMessage(opusHWND, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM((opus_sidesx * 8) + 5, 20));  // this seems to work
		SendMessage(opusHWND, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM((opus_sidesx * 8) + 5, 20)); // all difficulties
	}
	else {
		SendMessage(opusHWND, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM((opus_sidesx * 10) + 5, 20));  // this seems to work
		SendMessage(opusHWND, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM((opus_sidesx * 10) + 5, 20)); // all difficulties
	}

	bool last = 0;
	if (LOCATION_CLICKx > 0 && LOCATION_CLICKy > 0) {
		opus_click3(LOCATION_CLICKx, LOCATION_CLICKy, true);
		last = true;
	}

	
	if (CORNER_CLICK) {
		last = 1;

		opus_click3(0, 0, true);
		if (JUST_ONE_CLICK)return;
		opus_click3(0, opus_sidesy - 1, true);
		opus_click3(opus_sidesx - 1, opus_sidesy - 1, true);
		opus_click3(opus_sidesx - 1, 0, true);
	}
	if (SIDE_CLICK) {
		last = 1;
		opus_click3(opus_sidesx / 2, opus_sidesy - 1, true);
		if (JUST_ONE_CLICK)return;
		opus_click3(opus_sidesx / 2, 0, true);
		opus_click3(opus_sidesx - 1, opus_sidesy / 2, true);
		opus_click3(0, opus_sidesy / 2, true);
	}
	int ran = RANDOM_CLICK;
	last = (ran > 0 ? 1 : last );
	while (ran) {
		last = 1;
		opus_click3(random(opus_sidesx), random(opus_sidesy), true);
		ran--;
	}
	if (!last) {
		//        opus_click(random(opus_sidesx),random(opus_sidesy),true);
		opus_click3(0, 0, true);
	}

}
/************************************************************************************************************
****************************************   screen reading managment block ************************************/

int opus_numfreq[10] = { 0 };

// insert value into grid.  Set danger, grid and gridf when applicable to keep lists live.
int opus_grid_insert(int x, int y, int value) {
	if (value == GRID_VALUE_BOMB) {
		if (opus_bombcount++ < 2)value = GRID_VALUE_SPACE; // probably a 7.. treat as empty 
		opus_tbombcount++;
	}
	int hold = opusgrid[x][y];
	if (hold == GRID_VALUE_FLAG) return -3;
	if (value == hold)return -1;

	// all changes should be land->space or Land->number
	opusgrid[x][y] = value;


	bool is_x_top = x < opus_sidesx - 1;
	bool is_y_top = y < opus_sidesy - 1;
	int ym = y - 1, yp = y + 1, xm = x - 1, xp = x + 1;
	// reduce danger (land) array value around target
	if (y > 0) {
		opusdanger[x][ym]--;
		if (is_x_top) {
			opusdanger[xp][ym]--;
		}
	}
	if (is_y_top)opusdanger[x][yp]--;
	if (x > 0) {
		if (y > 0) {
			opusdanger[xm][ym]--;
		}
		if (is_y_top) {
			opusdanger[xm][yp]--;
		}
		opusdanger[xm][y]--;
	}
	if (is_x_top) {
		if (is_y_top) {
			opusdanger[xp][yp]--;
		}
		opusdanger[xp][y]--;
	}

	// if empty space 
	if (value == GRID_VALUE_SPACE) {
		opusgridf[x][y] = -1;
		return -2;
	}
	else opus_numfreq[value]++;
	//if is a new number set flag normalized value in gridf

	value = value - opusflags[x][y];
	opusgridf[x][y] = value;
	//if(value==0) ; // add to 'attention' list 
	return 1;
}

int opus_CCC_arr[15] = { 0 };
int opus_cell_color(int x, int y) {
	// slowest part of calibration step. 
	// mine_color_cell clone with reasonable optimizations.
	opus_cell_color_count = 0; // to check highest loop count before finding expected color.  remove after finding highest/lowest bounds.  can make into single tree, should only need to check 2-3 pix
						// 

	int xx = x * BIG_x;
	int yy = y * BIG_y;
	if (opusvs.Get_Pixel(xx, yy) == opus_corner_pix)return GRID_VALUE_LAND;// cell is live

	COLORREF cpix;
	xx += (BIG_x / 2) - 1;//xx+=(opus_CPWx/2)+1;
	yy += (BIG_y / 2); //yy+= (opus_CPWy/2)+2;

	//for(int i = -1; i < 2; i++){
	//int i = -1;
	for (int m = -2; m < 2; m++) {
		opus_cell_color_count++;
		cpix = opusvs.Get_Pixel(xx, yy + m);

		switch ((int)cpix) {

		case 12632256:
			continue;
			break;
		case 0:
			return GRID_VALUE_BOMB;//  This could be a 7.  maybe write a check later.  
			break;                     // current behavior- all boards containing 7's considered lost.
		case 16711680:
			return 1;
			break;
		case 32768:
		case 31488:
			return 2;
			break;
		case 255:
			return 3;
			break;
		case 8388608:
			return 4;
			break;
		case 128:
			return 5;
			break;
		case 8421376:
			return 6;
			break;
		};

	}
	//no color found, this is a space. 
	 // this is a very slow way to do this
	opus_cell_color_count = 9;
	return GRID_VALUE_SPACE;

}

// after this opusgrid, opusgridf and opusdanger should be set correctly.
int opus_readboard() {
	// I'd like to reduce this loop, but I can't get sliding dynamic bounds to be faster.  too much branching, checking/redudnacies 
	//int high_c=0;
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			//opus_check_pix(x,y);
			if (opusgridf[x][y] != GRIDF_VALUE_LAND)continue;  // only need to check what used to be lands.
			opus_grid_insert(x, y, opus_cell_color(x, y));
			opus_CCC_arr[opus_cell_color_count]++;
			//if(opus_cell_color_count==9)continue;
			//if(high_c<opus_cell_color_count)high_c=opus_cell_color_count;

		}
	}
	return 0;//return high_c;
}

/************************************************************************************************************
****************************************   grid parsing and move detecting block *****************************/

void opus_safe_clicks() {
	// find obvious safe clicks and add/process them
	int hold;
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			if (opusgridf[x][y] > 6)continue;

			if (opusgrid[x][y] == opusflags[x][y]) {  //maybe use opusgridf[x][y]==0 could workfaster.
				opus_add_safe_clicks(x, y);
				opusgridf[x][y] = 8;

			}
		}
	}
}

void opus_flags() { // maybe can combine with safeclicks in same loop. 
	int hold;
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			hold = opusgridf[x][y];
			if (hold == 0 || opusgridf[x][y] == 8)continue;

			if (hold == opusdanger[x][y]) {
				opus_add_flags(x, y);
				opusgridf[x][y] = 8;

				x -= 2;  // addflags can change opusdanger so reparse from a -2-1
				y -= 2;

			}
		}
	}
}

void opus_flag_and_safe_clicks() {
	//combines safe clicks and flags in one loop.  may be incomplete. requires testing.
	int hold;
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			hold = opusgrid[x][y];
			if (hold != 0 && opusgridf[x][y] != 8 && hold == opusdanger[x][y]) {

				opus_add_flags(x, y);
				opusgridf[x][y] = 8;
				x--;  // addflags can change opusdanger so reparse from a -1-1
				y -= 2;
			}
			else if (opusgridf[x][y] < 6 && opusgrid[x][y] == opusflags[x][y]) {  //maybe use opusgridf[x][y]==0 could workfaster.

				opus_add_safe_clicks(x, y);
				opusgridf[x][y] = 8;

			}

		}
	}
}
//#define MUTATE_fast_array_alter fast_array_safeclick
//#define iptf() *ipt.x=x; *ipt.y=y; 
//#include "mutate_fast_array_alter.h"
void opus_safeclick(int x, int y) {  // maybe just do the clicks in here instead of parsing them back out later.
	if (opusgrid[x][y] == 0) {

		safe_clicks[safe_clicks_len].x = x;
		safe_clicks[safe_clicks_len].y = y;
		//opusgrid[x][y]=GRID_VALUE_SAFE;
		safe_clicks_len++;
		opusFound_mine_or_click = true;
	}
}


void opus_add_safe_clicks(int x, int y) {
	// add or process safe clicks around x y exclusive.
	bool is_x_top = x < opus_sidesx - 1;
	bool is_y_top = y < opus_sidesy - 1;
	int ym = y - 1, yp = y + 1, xm = x - 1, xp = x + 1;
	if (y > 0) {
		opus_safeclick(x, ym);
		if (is_x_top) {
			opus_safeclick(xp, ym);
		}
	}
	if (is_y_top)opus_safeclick(x, yp);
	if (x > 0) {
		if (y > 0) {
			opus_safeclick(xm, ym);




		}
		if (is_y_top) {
			opus_safeclick(xm, yp);
		}

		opus_safeclick(xm, y);
	}
	if (is_x_top) {
		if (is_y_top) {
			opus_safeclick(xp, yp);

		}
		opus_safeclick(xp, y);
	}

}


void opus_flags_grid(int x, int y) {
	// can make inline later if it works properly.
	int hold = opusgridf[x][y];
	if (hold < 7 && hold >= 0) opusgridf[x][y]--; // if index is number

}




#define OPUS_FLAGS_M(x,y) opusdanger[x][y]--; opusflags[x][y]++;
void opus_flags(int x, int y) {
	// handle inserting flags into system.  Updates all associated arrays live.
	if (opusgrid[x][y] == 0) {
		opusFound_mine_or_click = true;
		opusgrid[x][y] = GRID_VALUE_FLAG;
		opusgridf[x][y] = GRIDF_VALUE_FLAG;
		opus_flags_placed++;
		bool is_x_top = x < opus_sidesx - 1;
		bool is_y_top = y < opus_sidesy - 1;
		int ym = y - 1, yp = y + 1, xm = x - 1, xp = x + 1;
		if (y > 0) {
			opus_flags_grid(x, ym);
			OPUS_FLAGS_M(x, ym);
			if (is_x_top) {
				opus_flags_grid(xp, ym);
				OPUS_FLAGS_M(xp, ym);
			}
		}
		if (is_y_top) {
			opus_flags_grid(x, yp);
			OPUS_FLAGS_M(x, yp);
		}
		if (x > 0) {
			if (y > 0) {
				opus_flags_grid(xm, ym);
				OPUS_FLAGS_M(xm, ym);



			}
			if (is_y_top) {
				opus_flags_grid(xm, yp);
				OPUS_FLAGS_M(xm, yp);
			}

			opus_flags_grid(xm, y);
			OPUS_FLAGS_M(xm, y);
		}
		if (is_x_top) {
			if (is_y_top) {
				opus_flags_grid(xp, yp);

				OPUS_FLAGS_M(xp, yp);

			}
			opus_flags_grid(xp, y);
			OPUS_FLAGS_M(xp, y);
		}
		// set opusgridf here -- where number, subtract 1
		// set opusdanger here -- all surrounding spaces danger--
		// set opusflags here -- all surrounding spaces flags++
		//opus_color_out();  // visualizer for error checking
		//pause();
	}
}

void opus_add_flags(int x, int y) {
	// turns lands into flags around xy exclusive.

	bool is_x_top = x < opus_sidesx - 1;
	bool is_y_top = y < opus_sidesy - 1;
	int ym = y - 1, yp = y + 1, xm = x - 1, xp = x + 1;
	if (y > 0) {
		opus_flags(x, ym);
		if (is_x_top) {
			opus_flags(xp, ym);
		}
	}
	if (is_y_top) {
		opus_flags(x, yp);
	}
	if (x > 0) {
		if (y > 0) {
			opus_flags(xm, ym);
		}
		if (is_y_top) {
			opus_flags(xm, yp);
		}

		opus_flags(xm, y);
	}
	if (is_x_top) {
		if (is_y_top) {
			opus_flags(xp, yp);

		}
		opus_flags(xp, y);
	}

}

/*******************************************************************************************************************
**************************************   click and input block  **************************************************/
void opus_doclick(int x, int y, bool h) {
	switch (CLICK_TYPE) {
	case 0: opus_click3(x, y, h); break;
	case 1: opus_click(x, y, h); break;
	case 2: opus_click2(x, y, h); break;
	};
}

void opus_click(int x, int y, bool h) {
	if (x<0 || y<0 || x > opus_sidesx || y > opus_sidesy) return;
	int xx = x * BIG_x + _MWOx + (BIG_x / 2);//(opus_CPWx/2)+ _MWOx;
	int yy = y * BIG_y + _MWOy + (BIG_y / 2);//(opus_CPWy/2)+ _MWOy;

	//Sleep(500);
	if (DO_PAUSE)pause();
	SetCursorPos(xx, yy);
	Mouse_leftclick();
	CLICK_SLEEP();
}

void opus_MouseLeftClick(int x, int y) {
	opus_input.mi.dx = (x * 17) + 140;
	opus_input.mi.dy = y * 30 + 30;
	opus_input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &opus_input, sizeof(INPUT));
}

void opus_click3(int x, int y, bool h) {
	int xx = (x * BIG_x) + 20;
	int yy = (y * BIG_y) + 72;
	if (OPUS_Testing_noscaling) {
		xx -= 6;
		yy -= 14;
	}
	SendMessage(opusHWND, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(xx, yy));

	SendMessage(opusHWND, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(xx, yy));
	
//	Sleep(0);

}

void opus_click4(int x, int y, bool h) {
	int xx = (x * 20) + 20;
	int yy = (y * 20) + 72;
	//	SendMessage(opusHWND, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(xx, yy));
	PostMessage(opusHWND, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(xx, yy));
	//	SendMessage(opusHWND, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(xx, yy));
	PostMessage(opusHWND, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(xx, yy));
	//	Sleep(0);

}
void opus_click2(int x, int y, bool h) {
	//if(x<0 || y<0 ||x > opus_sidesx || y > opus_sidesy) return;
	if (DO_PAUSE)pause();
	int xx = x * BIG_x + opus_BIGoffsetx;//(opus_CPWx/2)+ _MWOx;
	int yy = y * BIG_y + opus_BIGoffsety;//(opus_CPWy/2)+ _MWOy;
	opus_MouseLeftClick(xx, yy);
}
INPUT opus_input_queue[50];
int opus_inputq_count = 0;

void opus_clickqueue(int x, int y) {
	opus_input.mi.dx = (x * 17) + 140;
	opus_input.mi.dy = y * 30 + 30;

	opus_input_queue[opus_inputq_count] = opus_input;
	opus_inputq_count++;
}
void opus_send_click_queue() {
	LPINPUT s = opus_input_queue;
	SendInput(opus_inputq_count, s, sizeof(INPUT));
	opus_inputq_count = 0;
}

void opus_dedupe_safeclicks() {
	if (safe_clicks_len == 0)return;
	//vpoint hold[500];
	int plc = 1, n;
	//hold[0]=safe_clicks[0];
	for (int i = 1; i < safe_clicks_len; i++) {
		for (n = 0; n < plc; n++) {
			if (safe_clicks[n].x == safe_clicks[i].x && safe_clicks[n].y == safe_clicks[i].y)break;
		}
		if (n == plc) {
			safe_clicks[plc] = safe_clicks[i];
			plc++;
		}
	}
	safe_clicks_len = plc;
}


/*******************************************************************************************************************
**************************************       console output block  ***********************************************/

int opus_danger_color[10] = { 3,11,9,1,10,6,2,12,4,13 };
void opus_color_out() {

	opusvs.get_buffer();
	opusvs.bufwin_draw();
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD atrs[8] = { 7,1,10,12,4,5,13,11 };
	int numcolor = 0;
	int hold;
	string holds;
	SHOW(opus_sidesx);
	SHOW(opus_sidesy);
	SHOW(opus_flags_placed);
	SHOW(opus_bombcount);
	cout << "grid: \n";
	for (int n = 0; n < opus_sidesy; n++) {
		for (int i = 0; i < opus_sidesx; i++) {
			numcolor = 0;
			hold = opusgrid[i][n];
			if (hold == -1) holds = " ";
			if (hold == GRID_VALUE_BOMB) {
				holds = char(226);//"@";
				numcolor = 3;
			}
			if (hold == GRID_VALUE_SAFE) {
				numcolor = 6;
				holds = "$";

			}
			if (hold == GRID_VALUE_LAND) {
				holds = char(240);//"=";//(char)176;
				//numcolor=-1;
				//SetConsoleTextAttribute(hStdout, 231);
				//cout << "[]";
				 //cout << char(192) << char(217);   
			}
			if (hold == GRID_VALUE_FLAG) {
				holds = char(159);//"+";
				numcolor = 7;
			}
			if (hold == GRID_VALUE_SPACE) holds = " ";
			if (hold > 0 && hold < 7) {
				holds = ctostr(hold);
				numcolor = hold;
			}
			if (numcolor != -1) {
				SetConsoleTextAttribute(hStdout, atrs[numcolor]);
				cout << " " << holds;
				SetConsoleTextAttribute(hStdout, atrs[0]);
			}
		}
		cout << "\n";
	}
	cout << "danger: \n";
	for (int n = 0; n < opus_sidesy; n++) {
		for (int i = 0; i < opus_sidesx; i++) {
			hold = opusdanger[i][n];
			SetConsoleTextAttribute(hStdout, opus_danger_color[9 - hold]);
			cout << " " << hold;
			SetConsoleTextAttribute(hStdout, atrs[0]);

		}
		cout << endl;
	}
	cout << "gridf: \n";
	for (int n = 0; n < opus_sidesy; n++) {
		for (int i = 0; i < opus_sidesx; i++) {
			hold = opusgridf[i][n];
			holds = ctostr(hold);
			if (hold == GRIDF_VALUE_SPACE) holds = " ";
			if (hold == -2)holds = "@";
			if (hold == GRIDF_VALUE_LAND)holds = "-";
			cout << " " << holds;
		}
		cout << endl;
	}
	cout << "\n";
	cout << "flags: \n";
	for (int n = 0; n < opus_sidesy; n++) {
		for (int i = 0; i < opus_sidesx; i++) {
			hold = opusflags[i][n];;
			holds = ctostr(hold);
			if (hold == 0) holds = "-";
			if (hold != 0) SetConsoleTextAttribute(hStdout, opus_danger_color[hold]);

			cout << " " << holds;
			SetConsoleTextAttribute(hStdout, atrs[0]);
		}
		cout << endl;
	}
	cout << endl;
	gotoxy(0, Y_CONSOLE_START_POS);
}





void opus_output_info(string fname) {

	ofstream ifile(ctocp(fname));

	if (!ifile) {
		cout << "could not open file for writing" << endl;
	}
	string out[5];
	string hold;
	for (int n = 0; n < opus_sidesy; n++) {
		for (int i = 0; i < opus_sidesx; i++) {

			hold = ctostr(opusgrid[i][n]);
			if (hold == "-1") hold = " ";
			if (hold == "-2") hold = "@";
			if (hold == "0") hold = "=";//(char)176;
			if (hold == "9") hold = "+";


			out[0] += " " + hold;
			out[1] += ctostr(opusdanger[i][n]);
			out[2] += ctostr(opusgridf[i][n]);
			out[3] += ctostr(opusflags[i][n]);

		}
		out[0] += "\n";
		out[1] += "\n";
		out[2] += "\n";
		out[3] += "\n";
	}
	//cout << out[0];
	SHOWf(opus_sidesx, ifile);
	SHOWf(opus_sidesy, ifile);
	SHOWf(restart_x, ifile);
	SHOWf(restart_y, ifile);



	SHOWf(_MWOx, ifile);
	SHOWf(_MWOy, ifile);
	SHOWf(_MWw, ifile);
	SHOWf(_MWh, ifile);



	SHOWf(opus_GHSx, ifile);
	SHOWf(opus_GHSy, ifile);
	SHOWf(opus_GHSw, ifile);
	SHOWf(opus_GHSh, ifile);


	SHOWf(opus_CPWx, ifile);
	SHOWf(opus_CPWy, ifile);
	SHOWf(BIG_x, ifile);
	SHOWf(BIG_y, ifile);
	SHOWf(opus_click_offsetx, ifile);
	SHOWf(opus_click_offsety, ifile);

	SHOWf(opus_corner_pix, ifile);

	SHOWf(opus_BIGoffsetx, ifile);
	SHOWf(opus_BIGoffsety, ifile);
	ifile << " ************* opusgrid **************" << endl;
	ifile << out[0];
	ifile << " ************* opusdanger **************" << endl;
	ifile << out[1];
	ifile << " ************* opusgridf **************" << endl;
	ifile << out[2];
	ifile << " ************* opusflags **************" << endl;
	ifile << out[3];
	ifile << " ************* crashbuffer **************" << endl;
	for (int i = 0; i < 1000; i++) {
		ifile << crashbuffer[i];
	}
	ifile.close();


}

/*******************************************************************************************************************
 **************************************     pattern recognition block     ****************************************************/

int num_common_lands(int& x, int& y, int xx, int yy) { // assumes lands are direct adjacent
	int ret = 0;
	if (x != xx) {
		if (y - 1 > -1) {
			if (opusgridf[x][y - 1] == 9) ret++;
			if (opusgridf[xx][y - 1] == 9) ret++;
		}
		if (y + 1 < opus_sidesy) {
			if (opusgridf[x][y + 1] == 9) ret++;
			if (opusgridf[xx][y + 1] == 9) ret++;
		}
	}
	else if (y != yy) {
		if (x - 1 > -1) {
			if (opusgridf[x - 1][y] == 9) ret++;
			if (opusgridf[x - 1][yy] == 9) ret++;
		}
		if (x + 1 < opus_sidesx) {
			if (opusgridf[x + 1][y] == 9) ret++;
			if (opusgridf[x + 1][yy] == 9) ret++;
		}
	}
	return ret;
}






int opus_unc_lands_x[3] = { 0 };
int opus_unc_lands_y[3] = { 0 };
// returns number of lands adjacent to x,y that aren't adjacent to xx,yy
// sets opus_unc_landsx|y array to xy coords of x,y's uncommon lands
int num_uncommon_lands(int x, int y, int xx, int yy) { // assumes lands are orthogonally adjacent
	if (abs(x - xx) + abs(y - yy) != 1) {
		cout << "num_uncommon_lands failed- target and reference are the same\n";
		return 0;
	}
	opus_unc_lands_x[0] = -1;
	opus_unc_lands_x[1] = -1;
	opus_unc_lands_x[2] = -1;

	//ZeroMemory(opus_unc_lands_x, sizeof(int) * 3);
	ZeroMemory(opus_unc_lands_y, sizeof(int) * 3);
	int ret = 0;
	int dir = 0;
	if (x != xx) {
		dir = (x > xx ? 1 : -1);
		if (x + dir >= 0 && x + dir < opus_sidesx) {
			if (y > 0 && opusgridf[x + dir][y - 1] == 9) {
				ret++;
				opus_unc_lands_x[0] = x + dir;
				opus_unc_lands_y[0] = y - 1;
			}
			if (opusgridf[x + dir][y] == 9) {
				ret++;
				opus_unc_lands_x[1] = x + dir;
				opus_unc_lands_y[1] = y;
			}
			if (y < opus_sidesy - 1 && opusgridf[x + dir][y + 1] == 9) {
				ret++;
				opus_unc_lands_x[2] = x + dir;
				opus_unc_lands_y[2] = y + 1;
			}
		}
		return ret;
	}
	if (y != yy) {
		dir = (y > yy ? 1 : -1);
		if (y + dir >= 0 && y + dir < opus_sidesy) {
			if (x > 0 && opusgridf[x - 1][y + dir] == 9) {
				ret++;
				opus_unc_lands_x[0] = x - 1;
				opus_unc_lands_y[0] = y + dir;
			}
			if (opusgridf[x][y + dir] == 9) {
				ret++;
				opus_unc_lands_x[1] = x;
				opus_unc_lands_y[1] = y + dir;
			}
			if (x < opus_sidesx - 1 && opusgridf[x + 1][y + dir] == 9) {
				ret++;
				opus_unc_lands_x[2] = x + 1;
				opus_unc_lands_y[2] = y + dir;
			}
		}

	}


	return ret;
}

void inline magnumb_frame_process(int gftarg, int gfref, int n, int i, int x, int y) {
	if (gfref > 0 && gfref < 7 && gftarg <= gfref) { // check if reference is number, if >= target#
		if (num_uncommon_lands(x, y, n, i) <= gfref - gftarg && num_common_lands(x, y, n, i) >= gftarg) {   // added num_common_lands for safety...?
			//cout << "detected pattern at " << n << " " << i << " " << x << " " << y << "\n\n";
			if (opus_unc_lands_x[0] != -1) {
				Magnum_flagged = 1; opus_flags(opus_unc_lands_x[0], opus_unc_lands_y[0]);
			}
			if (opus_unc_lands_x[1] != -1) {
				Magnum_flagged = 1; opus_flags(opus_unc_lands_x[1], opus_unc_lands_y[1]);
			}
			if (opus_unc_lands_x[2] != -1) {
				Magnum_flagged = 1; opus_flags(opus_unc_lands_x[2], opus_unc_lands_y[2]);
			}

			num_uncommon_lands(n, i, x, y);
			if (opus_unc_lands_x[0] != -1) opus_safeclick(opus_unc_lands_x[0], opus_unc_lands_y[0]);
			if (opus_unc_lands_x[1] != -1) opus_safeclick(opus_unc_lands_x[1], opus_unc_lands_y[1]);
			if (opus_unc_lands_x[2] != -1) opus_safeclick(opus_unc_lands_x[2], opus_unc_lands_y[2]);

		}
	}
}

//magnumb frame-  depth patern finding  this should be the longest current pattern finder.
// if number is next to another number. (targ/ref)  9/4 avg .006ms per call
// uncommon land example= land adjacent to ref but not adjacent to targ
// targ value <= ref value
//- if ref uncommon lands <= ref value-targ value
//    &&  number of common lands >= target value
// target's uncommon lands are safe.
// ref's uncommon lands are flag 
// can detect 1-1 paterns by definition
// can detect 1-2 patterns
// can detect 1-4 style patterns.....  
// can obviously detect 1-1-1 holes. or Larger-smaller-smaller holes
// maybe this is the only iteration needed
// 3 number patterns can use similar ideas
void Magnumb_frame() {
	int xm, ym, xp, yp, x, y, hold;
	//Magnum_flagged = 0; Magnum_clicked = 0;
	int gftarget, gfsecn;
	for (int n = 0; n < opus_sidesx; n++) {
		for (int i = 0; i < opus_sidesy; i++) {  // parse list
			xm = n - 1; ym = i - 1; xp = n + 1; yp = i + 1; x = n; y = i;
			gftarget = opusgridf[n][i];
			if (gftarget > 0 && gftarget < 5) { // target a number
				if (x > 0) {
					gfsecn = opusgridf[xm][y]; // reference a number
					magnumb_frame_process(gftarget, gfsecn, n, i, xm, i);
				}
				xm = xp;
				if (x < opus_sidesx - 1) {
					gfsecn = opusgridf[xm][y];
					magnumb_frame_process(gftarget, gfsecn, n, i, xm, i);
				}
				if (y > 0) {
					gfsecn = opusgridf[x][ym];
					magnumb_frame_process(gftarget, gfsecn, n, i, n, ym);
				}
				ym = yp;
				if (y < opus_sidesy - 1) {
					gfsecn = opusgridf[x][ym];
					magnumb_frame_process(gftarget, gfsecn, n, i, n, ym);
				}

			}


		}
	}


}



/*******************************************************************************************************************
**************************************  initialization block   ****************************************************/
static LPRECT MINErect;
static bool found_mine_window = false;;
static string EWPDATA_title;
HWND minewindowHWND = NULL;
#undef RECT
bool opus_MineWindow(string title, int& x, int& y, int& w, int& h) {
	MINErect = new RECT;
	EWPDATA_title = title;
	found_mine_window = false;
	LPARAM lp = NULL;
	EnumWindows(opus_EWP, lp);
	GetWindowRect(opusHWND, MINErect);
	x = MINErect->left;
	y = MINErect->top;
	w = MINErect->right - x;
	h = MINErect->bottom - y;
	return found_mine_window;
}


BOOL CALLBACK opus_EWP(HWND hwnd, LPARAM lParam)
{
	string cmp;
	char title[80];
	GetWindowTextA(hwnd, title, sizeof(title));
	if (title[0] == '\0')return true;
	cmp = title;
	if (cmp == EWPDATA_title) {
		opus_Show_Window(hwnd);
		found_mine_window = true;

		opusHWND = hwnd;
		//system("Pause");
		return false;
	}


	return TRUE;
}
void opus_HWND_move_resize(HWND mywn, int x, int y, int right, int bottom) {
	::SetWindowPos(mywn, HWND_TOPMOST, x, y, right, bottom, SWP_SHOWWINDOW);
}
void opus_Show_Window(HWND mywn) {
	ShowWindow(mywn, SW_RESTORE);
	::SetWindowPos(mywn, HWND_TOPMOST, 0, 0, 0, 0,
		SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_ASYNCWINDOWPOS);// window-positioning options);

}
void opus_ontop(HWND mywn, int x, int y, int w, int h) {

	::SetWindowPos(mywn,       // handle to window
		HWND_TOPMOST,  // placement-order handle
		x,     // horizontal position
		y,      // vertical position
		w,  // width
		h, // height
		SWP_SHOWWINDOW);// window-positioning options);
}

int opus_draw_clicks() {
	cout << endl;
	int fails = 0;
	COLORREF corner_pix = opusvs.Get_Pixel(0, 0);
	cout << endl << creftostr(corner_pix) << endl;
	corner_pix = opusvs.Get_Pixel(BIG_x, BIG_y);
	cout << endl << creftostr(opus_corner_pix) << endl;
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			//cout << x << ":" << y << "    \r";
			int xx = x * BIG_x;//+cell_pixel_width[0];//+ _MWOx;
			int yy = y * BIG_y;//+cell_pixel_width[1];//+ _MWOy;
			//cout << x << ":" << y <<"    :    " << xx << ":" << yy <<"    \r";
			if (opusvs.Get_Pixel(xx, yy) != opus_corner_pix) {
				//cout << "\n wrong color: " << creftostr(opusvs.Get_Pixel(xx,yy))<<endl;
				fails++;
			}
			opusvs.buf_drawbox(xx, yy, 3, 3);
			//opusvs.buf_drawbox(xx+(opus_CPWx /2),yy+(opus_CPWy /2),3,3);
			opusvs.buf_drawbox(xx + (BIG_x / 2), yy + (BIG_y / 2), 3, 3);

		}
	}
	if (fails > 0) {
		cout << "board autocalibration detected failure.  Game may be in session\n";
		cout << "if game is in session, and calibration is correct, continue. else, restart minemath\n";
	}
	else {
		cout << "no calibration failures detected" << endl;
	}
	opusvs.bufwin_draw();
	return fails;

}

void opus_get_drawing_console(int xx = 820, int yy = 50, int ww = 800, int hh = 500) {
	int x, y, w, h;
	cout << "getting drawing window" << endl;
	if (!opus_MineWindow("drawing", x, y, w, h)) {
		system("start drawing.exe");
		cout << "opening drawing.exe" << endl;
		Sleep(500);
	}

	opus_MineWindow("drawing", x, y, w, h);
	opus_ontop(opusHWND, xx, yy, ww, hh);

	opusvs.condc = GetDC(opusHWND);
	cout << "found and set drawing window\n";
}
POINT opus_mouse_define_point(string where = "the point") {
	bool kp = KEYBOARD_PROCESSING;
	POINT ret;
	string tt[2] = { "f10","any key" };
	cout << "hover mouse cursor over " << where << " and press " << (kp ? tt[0] : tt[1]);
	DO_PAUSE = true;
	if (kp)while (DO_PAUSE) Sleep(100);
	else
		_getch();

	GetCursorPos(&ret);;
	DO_PAUSE = false;

	return ret;
}

int MagNumb_calibrate() {
	// all of this is calibrated to my computer with 125% screen scaling
	// almost every value in this calibrator is hard-coded
	// manual calibrator will also produce the same values 
	int x, y, w, h;
	if (GAME_TYPE == GAME_TYPE_EXPERT) {
		opus_sidesx = 30;//30
		opus_sidesy = 16;
		opus_totalflags = 99;
	}
	if (GAME_TYPE == GAME_TYPE_INTERMEDIATE) { opus_sidesx = 16; opus_sidesy = 16; opus_totalflags = 40; }


	if (GAME_TYPE == GAME_TYPE_EASY) { opus_sidesx = 8; opus_sidesy = 8; opus_totalflags = 10; }
	if (GAME_TYPE == GAME_TYPE_MAX) { opus_sidesx = 49; opus_sidesy = 49; opus_totalflags = 464; }
	if (GAME_TYPE == GAME_TYPE_99) { opus_sidesx = 99; opus_sidesy = 99; opus_totalflags = 1912; }
	if (GAME_TYPE == GAME_TYPE_1080max) { opus_sidesx = 99; opus_sidesy = 59; opus_totalflags = 1204; }
	cout << "started MagNumb_calibrate" << endl;
	//opus_get_drawing_console(820,50,800,500);

	//cout <<"created transparent window"<<endl;
	cout << "starting minesweeper x search" << endl;

	if (opus_MineWindow("Minesweeper X", _MWOx, _MWOy, _MWw, _MWh)) {
		_MWOx = 940;
		_MWOy = 550;
		opus_ontop(opusHWND, _MWOx, _MWOy, _MWw, _MWh);

		cout << "found mine window at x,y,w,h: " << _MWOx << ":" << _MWOy << ":" << _MWw << ":" << _MWh << endl;
	}
	else {
		cout << "no mine window found" << endl;
		pause();
		return false;
	}
	restart_x = _MWOx + 320;
	if (GAME_TYPE == GAME_TYPE_INTERMEDIATE)restart_x = _MWOx + 160;
	if (GAME_TYPE == GAME_TYPE_EASY)restart_x = _MWOx + 90;
	restart_y = _MWOy + 90;



	_MWOx += 20;
	_MWOy += 128;
	if (OPUS_Testing_noscaling) {
		_MWw -= 31; //16.35
		_MWh -= 118;
	}
	else {
		_MWw -= 39; //16.35
		_MWh -= 147;
	}
	opusvs.Set(_MWOx, _MWOy, _MWw, _MWh);
	cout << "fixed mine window at x,y,w,h: " << _MWOx << ":" << _MWOy << ":" << _MWw << ":" << _MWh << endl;

	opus_GHSx = 12;
	opus_GHSy = 55;
	opus_GHSw = 480;
	opus_GHSh = 255;
	if (GAME_TYPE == GAME_TYPE_INTERMEDIATE)opus_GHSw = 255;
	if (GAME_TYPE == GAME_TYPE_EASY) { opus_GHSw = 127; opus_GHSh = 127; }
	if (GAME_TYPE == GAME_TYPE_MAX) { opus_GHSw = 784; opus_GHSh = 784; }
	if (GAME_TYPE == GAME_TYPE_99) { opus_GHSw = 1584; opus_GHSh = 1584; }
	if (GAME_TYPE == GAME_TYPE_1080max) { opus_GHSw = 1584; opus_GHSh = 943; }
	//opus_GHSh=256;
	cout << "HWND vars: x,y,w,h: " << opus_GHSx << ":" << opus_GHSy << ":" << opus_GHSw << ":" << opus_GHSh << "\n";
	// cpw will be defunct, change all to bigx/y
	cell_pixel_width[0] = 17;
	cell_pixel_width[1] = 17;
	opus_CPWx = 17;
	opus_CPWy = 17;
	BIG_x = 20;
	BIG_y = 20;
	if (OPUS_Testing_noscaling) {
		BIG_x = 16;
		BIG_y = 16;
		opus_CPWx = 11;
		opus_CPWy = 11;
		cell_pixel_width[0] = 11;
		cell_pixel_width[1] = 11;
	}
	opus_click_offsetx = _MWOx + (opus_CPWx / 2);
	opus_click_offsety = _MWOy + (opus_CPWy / 2);

	opus_corner_pix = RGB(255, 255, 255);

	opus_BIGoffsetx = (opus_CPWx / 2) + _MWOx;
	opus_BIGoffsety = (opus_CPWy / 2) + _MWOy;

	opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);
	opusvs.get_buffer();
	opus_draw_clicks();




	opus_input.type = INPUT_MOUSE;
	opus_input.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP | MOUSEEVENTF_MOVE);
	opus_input.mi.mouseData = 0;
	opus_input.mi.dwExtraInfo = 0;
	opus_input.mi.time = 0;


	/*if(KEYBOARD_PROCESSING){
		cout <<" press f8 to accept this calibration, press f9 to manually calibrate"<<endl;
		bool f8state = F8FLAG,f9state = F9FLAG;
		while(f8state == F8FLAG&&f9state == F9FLAG)Sleep(300);
		if(f9state != F9FLAG){
			cout << "manual calibration not implimented yet"<<endl;
			pause();
			exit(1);
		}

		return f8state != F8FLAG;
	}
	*/


	return true;

}

int Opus() {
	// this will be the final iteration of opus_mainthread once testing is done.
	opusFound_mine_or_click = false;
	opus_readboard(); // remove buff if global VS is fine
	opus_flag_and_safe_clicks();
	if (opusFound_mine_or_click) return 1;
	//Magnumb();
	return 0;
}




// opus_main_thread does full run.  only 1 thread is supported at the moment.
// simplify this by taking initialize out 
// remove safeclick loops and put safe-clicks directly in add_safeclick
int opus_frames = 0, opus_tframes = 0, opus_tgames = 0, opus_twins = 1, opus_t_time = 0, opus_ttime = 0, opus_lowtime = 1000000;
int opus_games_lost_to_guess = 0, opus_games_lost_to_bomb = 0, opus_games_lost_to_pattern = 0, opus_games_lost_to_first_click = 0;
bool OPUS_last_click_guess = false;
int OPUS_total_guesses = 0, opus_games_lost_to_guessing = 0, opus_failed_frames = 0;
static int MagnumbFrontiers_Cumulative_guess_assessment = 0;
ValStopwatch imgboard, procboard, flags, safeclicks, dedupe, magnumb, clicks, magnumbfrontier, fullframe, winoutt, restarttimer;

void opus_main_thread(void* a) {



	while (!MagNumb_calibrate()) {
		system("start minesweeperx.exe");
		Sleep(300);
	}
	opus_reset();
	opus_output_info("opusinfo.txt");
	pause();
	int h;
	clrscr();

	//startmil();
	short timer = get_new_timer_frame();
	int fasttime = 156;

	while (1) {

		while (1) {
			if (GLOBAL_SLEEP_VALUE)Sleep(GLOBAL_SLEEP_VALUE);

			//Magnum_flagged = 0;
			opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);
			opus_frames++;
			opus_tframes++;

			h = opus_readboard();
			if (opus_bombcount > 2) {
				if (opus_check_win()) {
					//cout << "game won" << 

					//t_time=endmil();
					//t_time=vs_timer_readms(timer);
					opus_ttime += opus_t_time;

					cout << "game appears to be won\n" << opus_frames << " : total frames this game.   " << opus_tframes << " : total frames this run\n"; ;
					cout << "game took " << opus_t_time << "ms" << "    average win time: " << opus_ttime / opus_twins << endl;
					cout << "total wins this run: " << opus_twins++ << ".   total games this run: " << opus_tgames << endl << endl;
					if (opus_t_time < fasttime)pause();
					//pause(); 
				}
				if (DO_PAUSE)pause();
				opus_fast_reset();
				opus_frames = 0;
				opus_restart_game();
				opus_tgames++;
				reset_timer_frame(timer);//startmil();
				continue;
			}
			opus_flags();

			opus_safe_clicks();
			opus_dedupe_safeclicks();
			if (safe_clicks_len == 0) {
				//Magnumb_basic(); 
				Magnumb_frame();
				opus_flags();
				opus_safe_clicks();
				opus_dedupe_safeclicks();

				if (safe_clicks_len == 0 && Magnum_flagged == 0) {

				}
				else {
					while (safe_clicks_len != 0) {
						safe_clicks_len--;
						opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
					}
					opus_t_time = vs_timer_readms(timer);
					continue;
				}
				break;
			}

			while (safe_clicks_len != 0) {
				safe_clicks_len--;
				opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
			}
			opus_t_time = vs_timer_readms(timer);
		}
		if (opus_check_win()) {
			//t_time=vs_timer_readms(timer);//t_time=endmil();
			opus_ttime += opus_t_time;

			cout << "game appears to be won\n" << opus_frames << " : total frames this game.   " << opus_tframes << " : total frames this run\n"; ;
			cout << "game took " << opus_t_time << "ms" << "    average win time: " << opus_ttime / opus_twins << endl;
			cout << "total wins this run: " << ++opus_twins << ".   total games this run: " << opus_tgames << ".   games per win avg: " << opus_tgames / opus_twins << endl << endl;
			if (opus_t_time < fasttime)pause();
		}
		if (DO_PAUSE)pause();
		opus_fast_reset();
		opus_restart_game();
		reset_timer_frame(timer);//startmil();
		opus_tgames++;
		opus_frames = 0;

		//Sleep(1500);   

	}
	pause();


}
BYTE magnumb_guesses[BAD][BAD][2]; //  [x][y][0] is highest possible chance, [1] is lowest possible chance.
// new guesses function based on adjacency values.  somewhat faster than old guesses method, but no optimizations yet
int magnumb_guess_fill() {  // not currently functional. 
	int magtarget = 0, vhold = 0;
	int nnn, iii;
	ZeroMemory(magnumb_guesses, BAD * BAD * 2);
	for (int n = 0; n < opus_sidesx; n++) {
		for (int i = 0; i < opus_sidesy; i++) {
			magtarget = opusgridf[n][i];
			if (magtarget > 0 && magtarget < 7) {
				vhold = (magtarget * 100) / opusdanger[n][i];   // Normalized number/ number of lands touching. *100 for int
				// for each adjacent land, set magnumb_guesses 
				for (int nn = -1; nn < 2; nn++) {  // write fast array alter for this. 
					for (int ii = -1; ii < 2; ii++) {
						if (ii == 0 && nn == 0)continue;
						nnn = n + nn;
						iii = i + ii;
						if (nnn < 0 || nnn >= opus_sidesx || iii < 0 || iii >= opus_sidesx)continue;
						if (opusgrid[nnn][iii] != 9)continue;
						if (magnumb_guesses[nnn][iii][0] < vhold) magnumb_guesses[nnn][iii][0] = vhold;
						if (magnumb_guesses[nnn][iii][1] > vhold || magnumb_guesses[nnn][iii][1] == 0)magnumb_guesses[nnn][iii][1] = vhold;
					}
				}

			}
		}
	}
	return 0;
}
int magnumb_guess_parse(int& x, int& y, int type = 0) { // type 0=low, 1=hi, 2=avg
	int lo = 10000, hi = 0, avg = 10000;
	int lox = 0, loy = 0, hix = 0, hiy = 0, avgx = 0, avgy = 0;
	int hold = 0;
	for (int n = 0; n < opus_sidesx; n++) {
		for (int i = 0; i < opus_sidesy; i++) {
			if (opusgridf[n][i] != GRIDF_VALUE_LAND)continue;
			if (magnumb_guesses[n][i][0] > hi) {
				hi = magnumb_guesses[n][i][0];
				hix = n; hiy = i;
			}
			if (magnumb_guesses[n][i][1] < lo) {
				lo = magnumb_guesses[n][i][1];
				lox = n; loy = i;
			}
			hold = (magnumb_guesses[n][i][1] + magnumb_guesses[n][i][0]) / 2;
			if (hold < avg) {
				avg = magnumb_guesses[n][i][1];
				avgx = n; avgy = i;
			}
		}
	}
	if (type == 0) {
		x = lox; y = loy; return lo;
	}
	if (type == 1) {
		x = hix; y = hiy; return hi;
	}
	x = avgx; y = avgy; return avg;
}







/******************************end historical section*********************************************************/
/******************************begin 2022 optimizations********************************************************/

int opus_grid_insert_mutated(int x, int y, int value) {
	if (value == GRID_VALUE_BOMB) {
		if (opus_bombcount++ < 2)value = GRID_VALUE_SPACE; // probably a 7.. treat as empty 
		opus_tbombcount++;
	}
	int hold = opusgrid[x][y];
	if (hold == GRID_VALUE_FLAG) return -3;
	if (value == hold)return -1;

	// all changes should be land->space or Land->number
	opusgrid[x][y] = value;


	fast_array_dec((int*)opusdanger, BAD, BAD, x, y, 1);

	// if empty space 
	if (value == GRID_VALUE_SPACE) {
		opusgridf[x][y] = -1;
		return -2;
	}
	else opus_numfreq[value]++;
	//if is a new number set flag normalized value in gridf

	value = value - opusflags[x][y];
	opusgridf[x][y] = value;
	//if(value==0) ; // add to 'attention' list 
	return 1;
}


bool opus_exhaustive_wincheck() {
	int ls = 0;
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			if (opusvs.buf_Get_Pixel(x * BIG_x, y * BIG_y) == opus_corner_pix) ls++;
		}
	}
	return ls == opus_totalflags;
}

int opus_cell_color_buffered(int x, int y) {
	// used to be slowest part of calibration step. --2nd slowest currently behind screen scrape 9/5 
	// mine_color_cell clone with extensive optimizations.
	// change this to work directly with vs.bits buffer clone for much faster parsing. --check
	opus_cell_color_count = 0; // to check highest loop count before finding expected color. 
	//remove after finding highest/lowest bounds.  can make into single tree, should only need to check 2-3 pix


	int xx = x * BIG_x;
	int yy = y * BIG_y;
	if (opusvs.buf_Get_Pixel(xx, yy) == opus_corner_pix)return GRID_VALUE_LAND;// cell is live

	COLORREF cpix;
	//xx += (opus_CPWx / 2)-1 ;
	//yy += (opus_CPWy / 2) ;
	//xx += (BIG_x / 2)-1 ;
	//yy += (BIG_y / 2) ;
	xx += (BIG_x / 2);
	yy += (BIG_y / 2) - 1;

	// xx-1  m from-3 to 0  gets in 2 100%
	//for (int i = -3; i < -1; i++) {
		//int i = -1;
	//for (int m = 0; m < 3; m += 2) {
	for (int m = 0; m < 7; m += 2) {
		opus_cell_color_count++;
		cpix = opusvs.buf_Get_Pixel(xx, yy + m);
		//opusvs.buf_drawbox(xx + i, yy + m, 3, 3);
		switch ((int)cpix) {

		case 12632256:
			continue;
			break;
		case 0:
			return GRID_VALUE_BOMB;//  This could be a 7.  maybe write a check later.  
			break;                     // current behavior- all boards containing 2+ 7's considered lost.
									   //7s considered flags without associated gridf alters
									   // solve around them 
		case 16711680:
			return 1;
			break;
		case 32768:
			return 2;
			break;
		case 255:
			return 3;
			break;
		case 8388608:
			return 4;
			break;
		case 128:
			return 5;
			break;
		case 8421376:
			return 6;
			break;
			/*
			case 31488:
				return 2;
				break;
			case 8060928:
				return 4;
				break;
			case 123:
				return 5;
				break;
			case 8092416:
				return 6;
				break;
			*/
		};

	}
	//}
	//no color found, this is a space. 
	 // this is a slow way to do this
	//opus_cell_color_count = 9;
	opus_cell_color_count++;

	return GRID_VALUE_SPACE;

}

// after this opusgrid, opusgridf and opusdanger should be set correctly.
int opus_readboard_buffered() {
	// readboard version with all beta speed upgrades.
	// swith gridf access to pointer increment

	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			
			if (opusgridf[x][y] != GRIDF_VALUE_LAND)continue;  // only need to check what used to be lands.
			opus_grid_insert_mutated(x, y, opus_cell_color_buffered(x, y));  //****changed this line to mutated function
			opus_CCC_arr[opus_cell_color_count]++;
		}
	}
	
	return 0;
}




//outputs stats and win data.. call after win detected.
void opus_global_winout() {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (opus_t_time < opus_lowtime)opus_lowtime = opus_t_time;
	if (opus_guessed_this_game) {
		opus_guessed_this_game_total++;
	}
	opus_twins++;
	opus_ttime += opus_t_time;
	clrscr();

	cout << "total frames this game:" << opus_frames << "   total frames this run:" << opus_tframes << "   Runtime:"<< ms_to_timestr(GLOBAL_RUNTIMER.read_ms_nolap()) <<  "\n";
	cout << "last won game took    :" << opus_t_time << "ms    average win time: " << opus_ttime / opus_twins << "ms\n";
	cout << "games won w/out guess : " << opus_twins - opus_guessed_this_game_total << "    games won with guess   : " << opus_guessed_this_game_total << "    % of won games with no guesses: " << ((float)((opus_twins - opus_guessed_this_game_total) * 100) / (float)opus_twins) << "%\n";
	cout << "total wins this run   : " << opus_twins << "    total games this run: " << opus_tgames << "       Success rate:  "; //  "   average games per win: " << (float)opus_tgames / (float)opus_twins << "\n";
	SetConsoleTextAttribute(hStdout, 3); cout << 100.0/( (float)opus_tgames / (float)opus_twins); SetConsoleTextAttribute(hStdout, 7);
	cout << "%\nfastest win this run  :";
	SetConsoleTextAttribute(hStdout, 10); cout << opus_lowtime; SetConsoleTextAttribute(hStdout, 7);
	cout << "   Win rate adjusted for early losses:" << 100.0/ ((float)(opus_tgames - opus_games_lost_to_first_click) / (float)opus_twins) << "%\n\n\n";
	cout << "games with no moves after first click(s)(guessless)/2nd move was failed guess:" << opus_games_lost_to_first_click << "\n";
	cout << "games lost due to no safe clicks:" << opus_games_lost_to_guess << "\n";
	cout << "failed pattern recognition: " << opus_games_lost_to_pattern << "\n\n";
	cout << "games lost to bombs(guessing): " << opus_games_lost_to_bomb << "\n\n";;
	cout << "total number of resets due to solver failure: " << opus_failed_frames << "\n\n";
	cout << "total number of guesses this run: " << OPUS_total_guesses;
	cout << "    guessing failure rate  1: ";
	if (opus_games_lost_to_guessing > 0) {
		cout << ((float)OPUS_total_guesses / (float)opus_games_lost_to_guessing) << "\n\n";
		cout << "calculated guess percentage: " << (float)MagnumbFrontiers_Cumulative_guess_assessment / (float)OPUS_total_guesses << "\n\n";
	}
	else cout << "1 \n\n";

	cout << "total bombcolored cells found this run " << opus_tbombcount << "\n\n";
	cout << "extended timing information: \n";
	cout << "color_count-number of pixels checked per square : \n1:" << opus_CCC_arr[1] << " 2:" << opus_CCC_arr[2] << " 3:"
		<< opus_CCC_arr[3] << " 4:" << opus_CCC_arr[4] << " 5:" << opus_CCC_arr[5] << "\n\n";
	//	<< opus_CCC_arr[6] << " " << opus_CCC_arr[7] << " "
	//	<< opus_CCC_arr[8] << " " << opus_CCC_arr[9] << " " << opus_CCC_arr[10] <<"\n\n"
	//	<< opus_CCC_arr[11] << " " << opus_CCC_arr[12] << " "
	//	<< opus_CCC_arr[13] << " " << opus_CCC_arr[14] << " " << opus_CCC_arr[15] << "\n\n ";
	//cout << "flags this frame: " << opus_flags_placed << "\n";  // should always be 99 on winout
	cout << "number frequencies- how many of each number seen:\n1:" << opus_numfreq[1] << " 2:" << opus_numfreq[2] << " 3:"
		<< opus_numfreq[3] << " 4:" << opus_numfreq[4] << " 5:" << opus_numfreq[5] << " 6:" << opus_numfreq[6] << "\n\n";
	cout << "saved games of difficulty type:\n1:" << opus_difficulty_savedcount[0] << "  2:" << opus_difficulty_savedcount[1]
		<< "  3:" << opus_difficulty_savedcount[2] << "  4:" << opus_difficulty_savedcount[3] << "\n\n\n\n";


	clicks.output("sending click data to sweeper window");
	imgboard.output("getting board image from screen");
	procboard.output("reading board and updating dangergrid");
	magnumbfrontier.output("Magnumb frontiers long pattern recognition");
	flags.output("finding flags");
	safeclicks.output("finding safeclicks");
	magnumb.output("running simple heuristic pattern recognition");
	dedupe.output("removing duplicates from click list");
	winoutt.output("checking for win state and outputing win statistics");
	restarttimer.output("restarting the game when lost");
	fullframe.output("Full Frame");
}


#include "MagnumbFrontier.h"
void opus_reset_opusvs() {
	ValScreen vshwndsearch;
	int x, y, w, h;
	cout << "opusvs reset: before reset iswindow:" << (IsWindow(opusHWND) ? "true" : "false");
	cout << "opusvs reset: before reset findwindow==opusHWND:" << (FindWindow(NULL, TEXT("Minesweeper X")) ? "true" : "false");
	opusHWND = vshwndsearch.find_Window("Minesweeper X", x, y, w, h);
	opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);
	opusvs.get_buffer();
	opus_reset();
}

void opus_output_vs() {
	string temp = "f5outboard.bmp";
	opusvs.write_file(temp);
	cout << "wrote f5outboard.bmp";
}
void opus_saveboard_analyzer_format(int num, string prefix="frame") {
	ofstream ifile(prefix + ctostr(num) + "guessless.mine");
	ifile << opus_sidesx << "x" << opus_sidesy << "x" << opus_totalflags << "\n";
	for (int y = 0; y < opus_sidesy; y++) {
		for (int x = 0; x < opus_sidesx; x++) {
			if (opusgrid[x][y] == GRID_VALUE_FLAG) ifile << "F";
			else if (opusgrid[x][y] == GRIDF_VALUE_LAND) ifile << "H";
			else if (opusgrid[x][y] == GRID_VALUE_SPACE) ifile << "0";
			else if (opusgrid[x][y] == GRID_VALUE_BOMB) ifile << "7";
			
			else if (opusgrid[x][y] == 0) ifile << "H";
			else ifile << opusgrid[x][y];
		}
		ifile << "\n";
	}
	ifile.close();

}
void opusStayOnTop(HWND mywn, bool reverse = false) {
	LPRECT rect = new RECT;
	GetWindowRect(mywn, rect);
	int wi = rect->right - rect->left;
	int hi = rect->bottom - rect->top;

	::SetWindowPos(mywn,       // handle to window
		(reverse ? HWND_NOTOPMOST : HWND_TOPMOST),  // placement-order handle
		rect->left,     // horizontal position
		rect->top,      // vertical position
		wi,  // width
		hi, // height
		SWP_SHOWWINDOW);// window-positioning options);
	delete rect;
}
short opus_get_maxd(short x, short y, short width, short height) {
	if (x == 0) {
		if (y == 0 || y == height - 1)return 3;
		return 5;
	}
	if (x == width - 1) {
		if (y == height - 1 || y == 0)return 3;
		return 5;
	}
	if (y == 0)return 5;
	if (y == height - 1)return 5;
	return 8;
}

#define check_tempmines(x,y) if(tempmines[x][y])count++; 
void opus_bs_loss_searchforsurrounded() {
	bool tempmines[BAD][BAD];
	bool tempmines2[BAD][BAD];
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			tempmines[x][y] = 0;
			tempmines[x][y] = ( opusvs.buf_Get_Pixel((x * BIG_x) + (BIG_x / 2), (y * BIG_y) + (BIG_y / 2)  )) == 0;
			tempmines2[x][y] = 0;
			tempmines2[x][y] = (opusvs.buf_Get_Pixel((x * BIG_x) + (BIG_x / 2), (y * BIG_y) + (BIG_y / 4))) == 255;

		}
	}
	short count = 0;
	short fcount = 0;
	for (int x = 0; x < opus_sidesx; x++) {
		count = 0;
		for (int y = 0; y < opus_sidesy; y++) {
			if (tempmines2[x][y] && opusgrid[x][y] != 3) fcount++;
			bool is_x_top = x < opus_sidesx - 1;
			bool is_y_top = y < opus_sidesy - 1;
			int ym = y - 1, yp = y + 1, xm = x - 1, xp = x + 1;
			//cascade open cells
			if (y > 0) {
				check_tempmines(x, ym);
				if (is_x_top) {
					check_tempmines(xp, ym);
				}
			}
			if (is_y_top)check_tempmines(x, yp);
			if (x > 0) {
				if (y > 0) {
					check_tempmines(xm, ym);
				}
				if (is_y_top) {
					check_tempmines(xm, yp);
				}
				check_tempmines(xm, y);
			}
			if (is_x_top) {
				if (is_y_top) {
					check_tempmines(xp, yp);
				}
				check_tempmines(xp, y);
			}
			if (tempmines[x][y] && count == opus_get_maxd(x, y, opus_sidesx, opus_sidesy)) {
				//cout << "surrounded state found at "<<x<<":"<<y<<".  \n";
				//opus_saveboard_analyzer_format(123, "surrounded");
				//pause();
			}
			count = 0;
		}
		
	}
	if (fcount == opus_totalflags) {
		cout << "probably won this game but solver thinks it lost\n" << endl;
		pause();
	}

}

//this function needs to be refactored in such a bad way......  it's become a bit.. unweildy.

int opus_sclick_tot = 0; // total safeclicks this frame
int opus_sclick_totc = 0;// total safeclicks this run

void opus_main_thread_info(void* a) {

	bool lastclick_pattern = 0;
	while (!MagNumb_calibrate()) {
		system("start minesweeperx.exe");
		Sleep(300);
	}
	GLOBAL_RUNTIMER.LapUnPause();
	opus_reset();
	opus_output_info("opusinfo.txt");
	pause();
	int h;
	clrscr();


	//startmil();
	short timer = get_new_timer_frame();
	int fasttime = 20;// 143;
	bool winlatch = false;

	ValScreen vshwndsearch;


	int x, y, w, hh;
	int xxx = 0, yyy = 0;
	while (1) {

		while (1) {
			fullframe.Lap_ex();
			if (DO_PAUSE)pause();
			if (GLOBAL_SLEEP_VALUE)Sleep(GLOBAL_SLEEP_VALUE);
			fullframe.LapUnPause();
			//Sleep(0);  // comment this out if not using Postmessage in Click
			imgboard.LapUnPause();
			opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);
			opusvs.get_buffer();
			//opusvs.get_buffer(opusvs.bmp,opus_GHSw,opus_GHSh);
			imgboard.Lap();

			Magnum_flagged = 0;
			opus_frames++;
			opus_tframes++;
			procboard.LapUnPause();
			//h = opus_readboard();
			h = opus_readboard_buffered();
			procboard.Lap();
			//opusvs.bufwin_draw();
			//Sleep(1000);
			if (opus_bombcount > 2) {
				Sleep(1);
				opusHWND = vshwndsearch.find_Window("Minesweeper X", x, y, w, hh);
				if (opus_check_win()) {  // this should practically never happen.

					opus_global_winout();
					if (opus_t_time < fasttime)pause();
					cout << "won after finding bombcount... fix me\n";
					pause();

				}
				if (DO_PAUSE)pause();
				//cout << "game lost to bombs" << endl;
				opus_games_lost_to_bomb++;
				if (lastclick_pattern) {
					cout << "last click was pattern loss\n";
					//pause();
					opus_games_lost_to_pattern++;
				}
				if (OPUS_last_click_guess) {
					//cout << "last click was guess loss\n";
					opus_games_lost_to_guessing++;
				}

				opus_bombcount = 0;
				//goto dorestart;
				opus_fast_reset();
				opus_frames = 0;
				opus_restart_game();
				opus_restart_game();
				opus_tgames++;
				reset_timer_frame(timer);//startmil();

				continue;
			
			}
			lastclick_pattern = 0;
		reparse:
			
			flags.LapUnPause();
			opus_flags();
			flags.Lap();

			safeclicks.LapUnPause();
			opus_safe_clicks();
			safeclicks.Lap();
			flags.LapUnPause();
			opus_flags();
			flags.Lap();

			safeclicks.LapUnPause();
			opus_safe_clicks();
			safeclicks.Lap();
			dedupe.LapUnPause();
			opus_dedupe_safeclicks();
			dedupe.Lap();

			if (safe_clicks_len == 0) {
				if (opus_frames > 1000) {
					opus_failed_frames++;
					opus_reset();
				}
				magnumb.LapUnPause();
				//Magnumb_basic();
				Magnumb_frame();
				//opus_flags();
				//opus_safe_clicks();
				magnumb.Lap();

				dedupe.LapUnPause();
				opus_dedupe_safeclicks();
				dedupe.Lap();

				if (safe_clicks_len != 0 || Magnum_flagged != 0) {
					lastclick_pattern = 1;
					did_this_game_magframe = 1;
					OPUS_last_click_guess = false;
					opus_sclick_tot += safe_clicks_len;
					opus_sclick_totc++;
					clicks.LapUnPause();
					while (safe_clicks_len != 0) {
						safe_clicks_len--;
						opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
					}
					opus_t_time = vs_timer_readms(timer);
					clicks.Lap();
					continue;
				}
				magnumbfrontier.LapUnPause();
				MagnumbFrontiers();
				magnumbfrontier.Lap();

				//pause();
				if (Magnumb_Probecount > 0) {
					//pause();
					lastclick_pattern = 1;
					
					opus_sclick_tot += safe_clicks_len;
					opus_sclick_totc++;
					clicks.LapUnPause();
					OPUS_last_click_guess = false;
					while (safe_clicks_len != 0) {
						safe_clicks_len--;
						opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
					}
					clicks.Lap();
					continue;
				}
				else if (Magnumb_Minecount > 0) {
					goto reparse;  // could get rid of this with a while(1) loop, break statement right at the end, continue here.......
					//continue; // found a mine, reparse from the start
				}
				else {
					//  no moves/mines left to find.   guesses go here.
					if (opus_check_win() && opus_exhaustive_wincheck()) {
						//goto winout;  //could replace this with a latch and a break;
						winlatch = true;
						break;
					}
					if (OPUS_DOGUESSES == 1) {

						magnumb_guess_fill();
						magnumb_guess_parse(xxx, yyy, 0);
						//cout << "Heuristic found a guess at x y:" << xxx << " " << yyy << "\n";
						Sleep(500);
						opus_doclick(xxx, yyy, 0);
						Sleep(500);
						OPUS_last_click_guess = true;
						OPUS_total_guesses++;
						//continue;// goto reparse;
					}
					else if (OPUS_DOGUESSES == 2) {

						xxx = MagnumbFrontiers_guess[0];
						yyy = MagnumbFrontiers_guess[1];
						if (MagnumbFrontiers_lastguess[0] == xxx && MagnumbFrontiers_lastguess[1] == yyy) {  //&& MagnumbFrontiers_callcount - MagnumbFrontiers_lastcallcount < 4
							//cout << "breaking out, same guess twice\n";
							break; // need more attuned guessing if board isn't solved.
							// surrounded squares currently unsolved
						}
						MagnumbFrontiers_lastguess[0] = xxx;
						MagnumbFrontiers_lastguess[1] = yyy;
						opus_guessed_this_game = true;
						cout << "Magnumb FRontiers found a guess at x y:" << xxx << " " << yyy << "                  \r";
						//cout << "Magnumb Frontiers callcount: " << MagnumbFrontiers_callcount << "\n";
						//Sleep(200);
						opus_doclick(xxx, yyy, 0);
						//Sleep(200);
						OPUS_last_click_guess = true;
						MagnumbFrontiers_Cumulative_guess_assessment += MagnumbFrontiers_guess_probability;
						OPUS_total_guesses++;
						//continue;
					}
					else {
						//if(opus_frames>10) opus_saveboard_analyzer_format(opus_tgames);
						break; // not guessing, restart.
					}
				}// else- magnumFrontiers failed

			}
			else {// if safeclicklen!=0;  these clicks are generated by simple finder formula
				opus_sclick_tot += safe_clicks_len;
				opus_sclick_totc++;
				clicks.LapUnPause();

				while (safe_clicks_len != 0) {

					safe_clicks_len--;
					opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
				}
				clicks.Lap();

				opus_t_time = vs_timer_readms(timer);
			}
		} // break inside MagnumbFruntiers failed else block ends up here.. switch up winout goto for a break.
		winoutt.LapUnPause();
		if (opus_bombcount > 0) {
			//cout << "writing bombboard.bmp";
			//string temp = "bombboard" + ctostr(opus_tframes) + ".bmp";
			//opusvs.write_file(temp);//ctostr(opus_tframes) + 
		}

		if (winlatch || (opus_check_win() && opus_exhaustive_wincheck())) {
			//t_time=vs_timer_readms(timer);//t_time=endmil();
		winout:
			winlatch = false;
			fullframe.Lap_ex();
			fullframe.skip_next_lap = true;
			opus_global_winout();
			if (!opus_exhaustive_wincheck()) {
				cout << "\n\nexhaustive win check failed" << endl;
				pause();
			}
			if (OPUS_DOGUESSES == 0 || !opus_guessed_this_game && GAME_TYPE==0) {

				int type = 1;
				/*type += did_this_game_magframe;
				type += did_this_game_magfrontier_collision*10;
				type += did_this_game_magfrontier_VLA * 100;*/
				if (did_this_game_magframe)type = 2;
				if (did_this_game_magfrontier_collision)type = 3;
				if (did_this_game_magfrontier_VLA)type = 4;
				if (type != 2) {
					string fname = ctostr(type) + "type_";
					opus_saveboard_analyzer_format(opus_tgames, fname);
					opus_difficulty_savedcount[type - 1]++;
				}
			}
			Sleep(50);
			HWND hw = vshwndsearch.find_Window("Congratulations", x, y, w, hh);
			// detection works... showing/clicking the toolwindow doesn't  
			if (hw) {
				Sleep(500);
				ShowWindow(hw, SW_SHOW);
				ShowWindow(hw, SW_HIDE);
				SetWindowPos(hw, nullptr, 100, 100, 0, 0, SWP_NOSIZE);
				opusStayOnTop(hw);
				cout << "fastest time window detected\n";
				pause();
				SendMessage(hw, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(220, 150));
				SendMessage(hw, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(220, 150));
				//click at 220,150
				Sleep(200);
				//"Best Times" window at 350/200
				hw = vshwndsearch.find_Window("Best Times", x, y, w, hh);
				opusStayOnTop(hw);
				Sleep(200);
				SendMessage(hw, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(350, 200));  // this seems to work
				SendMessage(hw, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(350, 200)); // all difficulties
				
				pause();
			}
			//pause();
			if (opus_t_time < fasttime) {
				cout << "fastest time detected\n";
				
				pause();
			}
		}
		else {
			//string st = ctostr(opus_tframes) + ".bmp";
			//if(opus_frames>10)opusvs.write_file(st);
			if (opus_frames > 2) {
				opus_games_lost_to_guess++;  //change this up a bit.
				//cout << "writing board.bmp";
				//string temp = ctostr(opus_tframes) + "board.bmp";
				//opusvs.write_file(temp);//ctostr(opus_tframes) + 
			}
			else opus_games_lost_to_first_click++;
			opus_bs_loss_searchforsurrounded();

		}
		winoutt.Lap();
		//game is over, refresh grids, reset variables, click restart on game, do first click(s).
	dorestart:
		restarttimer.LapUnPause();
		if (DO_PAUSE)pause();
		opus_fast_reset();
		reset_timer_frame(timer);
		opus_restart_game();
		opus_tgames++;
		opus_frames = 0;
		restarttimer.Lap();
		//Sleep(1500);   

	}
	pause();

}

void opus_readboard_emu(MineMath_emulator* MSemu) {
	short temp;
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {

			if (opusgridf[x][y] != GRIDF_VALUE_LAND)continue;  // only need to check what used to be lands.
			temp = MSemu->getCellValue(x, y);
			if (temp == 9)continue;
			temp = (temp == 0 ? -1 : temp);
			opus_grid_insert_mutated(x, y, temp );
		}
	}
}

void opus_process_clicks() {
	opus_sclick_tot += safe_clicks_len;
	opus_sclick_totc++;
	clicks.LapUnPause();
	while (safe_clicks_len != 0) {
		safe_clicks_len--;
		opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
	}
	clicks.Lap();
}
bool opus_process_clicks_emu(MineMath_emulator* MSemu) {
	opus_sclick_tot += safe_clicks_len;
	opus_sclick_totc++;
	clicks.LapUnPause();
	bool ret = true;
	while (safe_clicks_len != 0) {
		safe_clicks_len--;
		if (!MSemu->doClick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0)) { 
			ret = false; break; 
		}
	}
	clicks.Lap();
	return ret;
}
bool opus_Process_magnumb_guesses() {
	int xxx = MagnumbFrontiers_guess[0];
	int yyy = MagnumbFrontiers_guess[1];
	if (MagnumbFrontiers_lastguess[0] == xxx && MagnumbFrontiers_lastguess[1] == yyy) {  //&& MagnumbFrontiers_callcount - MagnumbFrontiers_lastcallcount < 4
		//cout << "breaking out, same guess twice\n";
		return false;// break; // need more attuned guessing if board isn't solved.
		// surrounded squares currently unsolved
	}
	MagnumbFrontiers_lastguess[0] = xxx;
	MagnumbFrontiers_lastguess[1] = yyy;
	opus_guessed_this_game = true;
	//cout << "Magnumb FRontiers found a guess at x y:" << xxx << " " << yyy << "                  \r";
	//cout << "Magnumb Frontiers callcount: " << MagnumbFrontiers_callcount << "\n";
	//Sleep(200);
	opus_doclick(xxx, yyy, 0);
	//Sleep(200);
	OPUS_last_click_guess = true;
	MagnumbFrontiers_Cumulative_guess_assessment += MagnumbFrontiers_guess_probability;
	OPUS_total_guesses++;
	return true;
}
bool opus_Process_magnumb_guesses_emu(MineMath_emulator* MSemu) {
	int xxx = MagnumbFrontiers_guess[0];
	int yyy = MagnumbFrontiers_guess[1];
	if (MagnumbFrontiers_lastguess[0] == xxx && MagnumbFrontiers_lastguess[1] == yyy) {  //&& MagnumbFrontiers_callcount - MagnumbFrontiers_lastcallcount < 4
		//cout << "breaking out, same guess twice\n";
		return false;// break; // need more attuned guessing if board isn't solved.
		// surrounded squares currently unsolved
	}
	MagnumbFrontiers_lastguess[0] = xxx;
	MagnumbFrontiers_lastguess[1] = yyy;
	opus_guessed_this_game = true;
	//cout << "Magnumb FRontiers found a guess at x y:" << xxx << " " << yyy << "                  \r";
	//cout << "Magnumb Frontiers callcount: " << MagnumbFrontiers_callcount << "\n";
	//Sleep(200);
	MSemu->doClick(xxx, yyy);//opus_doclick(xxx, yyy, 0);
	//Sleep(200);
	OPUS_last_click_guess = true;
	MagnumbFrontiers_Cumulative_guess_assessment += MagnumbFrontiers_guess_probability;
	OPUS_total_guesses++;
	return true;
}

void opus_process_guessless_fileout() {
	if (OPUS_DOGUESSES == 0 || !opus_guessed_this_game && GAME_TYPE == 0) {

		int type = 1;
		/*type += did_this_game_magframe;
		type += did_this_game_magfrontier_collision*10;
		type += did_this_game_magfrontier_VLA * 100;*/
		if (did_this_game_magframe)type = 2;
		if (did_this_game_magfrontier_collision)type = 3;
		if (did_this_game_magfrontier_VLA)type = 4;
		if (type != 2) {
			string fname = ctostr(type) + "type_";
			opus_saveboard_analyzer_format(opus_tgames, fname);
			opus_difficulty_savedcount[type - 1]++;
		}
	}
}
void opus_process_guessless_fileout_emu(MineMath_emulator* MSemu) {
	if (!OUTPUT_SEEDS)return;
	if (OPUS_DOGUESSES == 0 || !opus_guessed_this_game && GAME_TYPE == 0) {

		int type = 1;
		/*type += did_this_game_magframe;
		type += did_this_game_magfrontier_collision*10;
		type += did_this_game_magfrontier_VLA * 100;*/
		if (did_this_game_magframe)type = 2;
		if (did_this_game_magfrontier_collision)type = 3;
		if (did_this_game_magfrontier_VLA)type = 4;
		if (type != 2) {
			string fname = ctostr(type) + "type_"+ctostr(opus_tframes)+".mbf";
			MSemu->tofile_mbf(fname);
			//opus_saveboard_analyzer_format(opus_tgames, fname);
			opus_difficulty_savedcount[type - 1]++;
		}
	}
}
#define timer_function(timer,funct) timer.LapUnPause(); funct; timer.Lap(); 
void opus_main_thread_emulator(void* emu) {

	MineMath_emulator* MSemu = (MineMath_emulator*)emu;
	opus_sidesx = MSemu->width;
	opus_sidesy = MSemu->height;
	opus_bombcount = MSemu->total_mines;

	opus_reset();
	opus_output_info("opusinfo.txt");
	pause();
	int h;
	clrscr();
	MSemu->reset();
	MSemu->fill_mineboard_bunched();//MSemu->fill_mineboard5();
	MSemu->doClick(0, 0);
	int x, y, w, hh;
	int xxx = 0, yyy = 0;
	int temp = 0;
	short timer = get_new_timer_frame();
	bool winlatch = false;

	while (1) {
		while (1) {
			winlatch = false;
			fullframe.Lap_ex();
			if (DO_PAUSE)pause();
			if (GLOBAL_SLEEP_VALUE)Sleep(GLOBAL_SLEEP_VALUE);
			fullframe.LapUnPause();
			//clrscr();
			//if(opus_tframs%100==0)
			//MSemu->output_active();
			//Sleep(100);

			Magnum_flagged = 0;
			opus_frames++;
			opus_tframes++;
			timer_function(procboard, opus_readboard_emu(MSemu));			
			

			do {
				temp = safe_clicks_len;
				timer_function(flags, opus_flags());
				timer_function(safeclicks, opus_safe_clicks());
				timer_function(dedupe, opus_dedupe_safeclicks());
			} while (temp != safe_clicks_len);

			

			if (safe_clicks_len == 0) {
				if (opus_frames > 1000) {
					opus_failed_frames++;
					opus_reset();
				}
				timer_function(magnumb, Magnumb_frame());
				timer_function(dedupe, opus_dedupe_safeclicks());

				if (safe_clicks_len != 0 || Magnum_flagged != 0) {					
					did_this_game_magframe = 1;
					OPUS_last_click_guess = false;
					opus_process_clicks_emu(MSemu);//opus_process_clicks();
					opus_t_time = vs_timer_readms(timer);
					continue;
				}
				timer_function(magnumbfrontier, MagnumbFrontiers());

				if (Magnumb_Probecount > 0) {
					OPUS_last_click_guess = false;
					opus_process_clicks_emu(MSemu);//opus_process_clicks();
					
				}
				else if (Magnumb_Minecount > 0) {
					//goto reparse;  // could get rid of this with a while(1) loop, break statement right at the end, continue here.......
					continue; // found a mine, reparse from the start
				}
				else {
					//  no moves/mines left to find.   guesses go here.
					if(MSemu->checkWin()){//if (opus_check_win() && opus_exhaustive_wincheck()) {
						//goto winout;  //could replace this with a latch and a break;
						winlatch = true;
						break;
					}
					if (OPUS_DOGUESSES == 1) {
						//not implemented here
					}
					else if (OPUS_DOGUESSES == 2) {
						if (!opus_Process_magnumb_guesses())break;
					}
					else {
						//if(opus_frames>10) opus_saveboard_analyzer_format(opus_tgames);
						break; // not guessing, restart.
					}
				}// else- magnumFrontiers failed

			}
			else {// if safeclicklen!=0;  these clicks are generated by simple finder formula
				opus_process_clicks_emu(MSemu);//opus_process_clicks();

				opus_t_time = vs_timer_readms(timer);
			}
		} // break inside MagnumbFruntiers failed else block ends up here.. switch up winout goto for a break.

		winoutt.LapUnPause();
		if (MSemu->checkWin()) {//if (winlatch || (opus_check_win() && opus_exhaustive_wincheck())) {
			//t_time=vs_timer_readms(timer);//t_time=endmil();
			winlatch = false;
			fullframe.Lap_ex();
			fullframe.skip_next_lap = true;
			opus_global_winout();
			opus_process_guessless_fileout_emu(MSemu);
			//MSemu->tofile_mbf("test.mbf");
			//pause();
		}
		else {
			//string st = ctostr(opus_tframes) + ".bmp";
			//if(opus_frames>10)opusvs.write_file(st);
			if (opus_frames > 2) {
				opus_games_lost_to_guess++;  //change this up a bit.
				//cout << "writing board.bmp";
				//string temp = ctostr(opus_tframes) + "board.bmp";
				//opusvs.write_file(temp);//ctostr(opus_tframes) + 
			}
			else opus_games_lost_to_first_click++;
		}
		winoutt.Lap();
		//game is over, refresh grids, reset variables, click restart on game, do first click(s).
	dorestart:
		
		if (DO_PAUSE)pause();

		restarttimer.LapUnPause();
		reset_timer_frame(timer);
		opus_fast_reset();
		MSemu->reset();
		MSemu->fill_mineboard8();//MSemu->fill_mineboard5();
		//MSemu->validate();
		MSemu->doClick(0, 0);
		opus_tgames++;
		opus_frames = 0;
		restarttimer.Lap();
		//Sleep(1500);   

	}
	pause();






}


/******************************************Begin Opus Trainer section ****************************/
HWND opus_trainer_hwnd;
int opus_trainerx, opus_trainery, opus_trainerw, opus_trainerh;
ValScreen trainer;

void opus_trainer_draw_safeclicks() {
	int x, y;
	while (safe_clicks_len != 0) {
		safe_clicks_len--;
		x = safe_clicks[safe_clicks_len].x * BIG_x;
		x += BIG_x / 4;
		y = safe_clicks[safe_clicks_len].y * BIG_y;
		y += BIG_y / 4;
		//trainer.buf_drawbox2(x, y, 5, 5, 0, 200, 0);
		trainer.buf_drawbox2(x, y, BIG_x / 2, BIG_y / 2, 0, 200, 0);
	}
	//opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y,0);
}
void opus_trainer_draw_flags() {

	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			//if (opusgrid[x][y] == GRID_VALUE_FLAG) trainer.buf_drawbox2(x * BIG_x, y * BIG_y, 5, 5, 200, 0, 0);
			if (opusgrid[x][y] == GRID_VALUE_FLAG) trainer.buf_drawbox2((x * BIG_x)+BIG_x/3, (y * BIG_y)+ BIG_y / 3, BIG_x / 3, BIG_y / 3, 200, 0, 0);
		}
	}
}
#include"valtextcontrol.h"  // used to draw fonted text to HDC/HBMP 
void opus_trainer_drawtextD(string text,int x, int y) {  //deprecated
	trainer.buf_drawtext(x * BIG_x, y * BIG_y, 20, 20, text);
}

/*
transparent window Live By-Hand Helper bot.   Fully functional. Extremely fast. tested accurate.
--draw green square over safe clicks
-- draw red square over dead spaces
-- add helper mode to alter all numbers to gridf normalized numbers
-- add helper mode to clear all spaces already parsed(0 in danger)
--minesweeperx will record the window without edits, so will obs
--    use this to beat the current minesweeper world recordand show everyone how you did it. :P
*/
void opus_trainer_thread(void* a) {
	// need transparent window for this. 	
	while (!MagNumb_calibrate()) {
		system("start minesweeperx.exe");
		Sleep(300);
	}
	cout << "out of calibrate" << endl;
	opus_reset();

	//trainer.Set(opus_trainerx,opus_trainery,opus_trainerw,opus_trainerh);
	trainer.Set(_MWOx, _MWOy, _MWw, _MWh);
	trainer.get_screen();
	trainer.get_buffer();
	trainer.condc = GetDC(opus_trainer_hwnd);
	cout << "before loop " << endl;
	SetWindowLong(opus_trainer_hwnd, GWL_STYLE, 0);
	::SetWindowPos(opusHWND, HWND_NOTOPMOST, 0, 0, 0, 0,
		SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_ASYNCWINDOWPOS);
	Sleep(10);
	::SetWindowPos(opus_trainer_hwnd, HWND_TOPMOST, 0, 0, 0, 0,
		SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_ASYNCWINDOWPOS);
	pause();
	while (1) {
		Sleep(30);
		opus_fast_reset();
		opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);

		opus_readboard();
		//opus_flags();
		//opus_safe_clicks();
		//Magnumb_basic(); 
		//opus_flags();
		//opus_safe_clicks();
		//Magnumb_basic(); 
		Magnumb_frame();
		//opus_flags();
		//opus_safe_clicks();

		opus_dedupe_safeclicks();
		trainer.white_buffer();
		trainer.buf_draw_boarder(1);
		opus_trainer_draw_safeclicks();
		opus_trainer_draw_flags();
		trainer.bufwin_draw(100, 100);
	}

}
ValTextControl Opus_vtc("Impact", 100, 100, 20, 20, "t");

void opus_vtc_runonce() {
	Opus_vtc.fontdat.lfWeight = 800;
	Opus_vtc.fontdat.lfHeight = 18;
}

void opus_trainer_drawtext(string str, int x, int y) {
	Opus_vtc.content = str;
	Opus_vtc.x = (BIG_x * x )+ ((BIG_x-Opus_vtc.getrealtwidth()) /2);
	Opus_vtc.y = (BIG_y * y)+2;
	Opus_vtc.DIBdraw(trainer.condc, trainer.newbitmap);
}
#ifndef VRGB 
#define VRGB COLORREF
#define VRGB_BLUE 16711680
#define VRGB_RED  255
#define VRGB_GREEN 64000
#define VRGB_WHITE 16777215
#define VRGB_BLACK 0

#define VRGB_PINK 13120200 //200,50,200
#define VRGB_PURPLE 16728192//128, 64, 255
#define VRGB_CYAN 16776960  //0,255,255
#define VRGB_YELLOW 65535  //255,255,0
#define VRGB_BROWN 15440  //80,60,0
#define VRGB_ORANGE 348341  //181,80,5
#define VRGB_GREEN_DARK 146456  //24,60,2
#define VRGB_GREEN_LIGHT 7405454  //142,255,112
#define VRGB_RED_DARK 2626  //66,10,0
#define VRGB_RED_LIGHT 1447616  //192,22,22
#define VRGB_BLUE_DARK 4259840  //0,0,65
#define VRGB_BLUE_LIGHT 11555116  //44,81,176
#define VRGB_GREY_DARK 2105376  //32,32,32
#define VRGB_GREY_LIGHT 6316128  //96,96,96
#define VRGB_GREY_VLIGHT 8421504 // 128,128,128
#define VRGB_GREY_VVLIGHT 12632256 //192...
#define VRGB_GREY 4210752  //64,64,64
#define RECT val_rect
#endif 
void opus_trainer_drawnum(int n, int x, int y) {
	switch (n) {
	case 0: Opus_vtc.SetColor(VRGB_ORANGE); break;
	case 1: Opus_vtc.SetColor(VRGB_BLUE); break;
	case 2: Opus_vtc.SetColor(VRGB_GREEN_LIGHT&VRGB_GREY_LIGHT); break;
	case 3: Opus_vtc.SetColor(VRGB_RED_LIGHT); break;
	case 4: Opus_vtc.SetColor(VRGB_BLUE); break;
	case 5: Opus_vtc.SetColor(VRGB_RED_DARK); break;
	case 6: Opus_vtc.SetColor(VRGB_PINK); break;
	case 7: Opus_vtc.SetColor(VRGB_PURPLE); break;
	case 8: Opus_vtc.SetColor(VRGB_BLUE_DARK); break;
	case 9: Opus_vtc.SetColor(VRGB_BLUE_DARK); break;
	};

	opus_trainer_drawtext(ctostr(n), x, y);
}
void opus_trainer_greysqaure(int x, int y) {
	int xx = (x * BIG_x)+2, yy = (y * BIG_y)+2;
	trainer.buf_drawbox2(xx, yy, BIG_x - 4, BIG_y - 4, 192, 192, 192);
}

void opus_trainer_drawNormalized() {


	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			if (opusgrid[x][y] == GRID_VALUE_FLAG)continue;
			if (opusdanger[x][y] == 8 || opusgridf[x][y] == GRIDF_VALUE_LAND)continue;
			if (opusdanger[x][y] == 0) {
				opus_trainer_greysqaure(x, y);
				continue;
			}
			
			
			if (opusgrid[x][y] != opusgridf[x][y]) {
				opus_trainer_greysqaure(x, y);
				if(opusgridf[x][y]<8)opus_trainer_drawnum(opusgridf[x][y], x, y);
			}

		}
	}
}
void opus_trainer_drawDomains() {
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			if (opusgrid[x][y] == GRID_VALUE_FLAG)continue;
			if (opusdanger[x][y] == 8 || opusgridf[x][y] == GRIDF_VALUE_LAND)continue;
			if (opusdanger[x][y] == 0 || (opusgrid[x][y]>0 && opusgrid[x][y]<8)) {
				opus_trainer_greysqaure(x, y);
				continue;
			}
		}
	}
	int dx, dy,dxx,dyy;
	for (int i = 0; i < Domlistlen; i++) {
		opus_trainer_greysqaure(Domlist[i].x, Domlist[i].y);
		if (Domlist[i].Assoclen == 0)continue;
		dx = BIG_x * Domlist[i].x + (BIG_x / 2);
		dy = BIG_y * Domlist[i].y + (BIG_y / 2);
		for (int n = 0; n < Domlist[i].Assoclen; n++) {
			dxx = (Domlist[i].Assocx[n] * BIG_x) + (BIG_x / 2);
			dyy = (Domlist[i].Assocy[n] * BIG_y) + (BIG_y / 2);
			trainer.buf_drawlinefrom_slope(dx, dy, dxx, dyy, 5);
		}
		//trainer.buf_drawbox2((BIG_x * Domlist[i].x)+4, (BIG_y * Domlist[i].y)+4, BIG_x - 6, BIG_y - 6, 192, 192, 192);
		//Opus_vtc.BK_Color;
		Opus_vtc.IS_BKR = true;
		Opus_vtc.IS_TRANSP = false;
		opus_trainer_drawnum(Domlist[i].value, Domlist[i].x, Domlist[i].y);
		
	}
	Opus_vtc.IS_TRANSP = true;

}

void MagnumbFrontiers_trainer_thread(void* a) {
	// need transparent window for this. 	
	while (!MagNumb_calibrate()) {
		system("start minesweeperx.exe");
		Sleep(300);
	}
	opus_vtc_runonce();
	cout << "out of calibrate" << endl;
	opus_reset();

	//trainer.Set(opus_trainerx,opus_trainery,opus_trainerw,opus_trainerh);
	trainer.Set(_MWOx, _MWOy, _MWw, _MWh);
	trainer.get_screen();
	trainer.get_buffer();
	trainer.condc = GetDC(opus_trainer_hwnd);
	cout << "before loop " << endl;
	SetWindowLong(opus_trainer_hwnd, GWL_STYLE, 0);
	::SetWindowPos(opusHWND, HWND_NOTOPMOST, 0, 0, 0, 0,
		SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_ASYNCWINDOWPOS);
	Sleep(10);
	::SetWindowPos(opus_trainer_hwnd, HWND_TOPMOST, 0, 0, 0, 0,
		SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_ASYNCWINDOWPOS);
	trainer.white_buffer();
	trainer.bufwin_draw(0, 0);
	trainer.bufwin_draw(_MWw, 0);
	trainer.bufwin_draw(_MWw + _MWw, 0); // erases the pregenerated titlebar
	pause();
	trainer.bufwin_draw(0, 0);



	bool latch;
	while (1) {
		if (DO_PAUSE)pause();
		Sleep(100);
		opus_fast_reset();
		opusHWND=(FindWindow(NULL, TEXT("Minesweeper X")));
		opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);
		opusvs.get_buffer();

		opus_readboard_buffered();
		if (opus_bombcount > 4) {
			Sleep(1000); continue;
		}
		opus_flags();
		opus_safe_clicks();
		//Magnumb_basic(); 
		//opus_flags();
		//opus_safe_clicks();
		//Magnumb_basic(); 
//		for (int i = 0; i < safe_clicks_len; i++) {
//			opusgridf[safe_clicks[i].x][safe_clicks[i].y] = GRIDF_VALUE_SPACE;
//		}
		Magnumb_frame();
		//opus_flags();
		//opus_safe_clicks();

		//opus_dedupe_safeclicks();
		for (int i = 0; i < safe_clicks_len; i++) {
			opusgridf[safe_clicks[i].x][safe_clicks[i].y] = GRIDF_VALUE_SPACE;
		}
		MagnumbFrontiers();
		for (int i = 0; i < safe_clicks_len; i++) {
			opusgridf[safe_clicks[i].x][safe_clicks[i].y] = GRIDF_VALUE_LAND;
		}
		opus_flags();
		opus_safe_clicks();
//		for (int i = 0; i < safe_clicks_len; i++) {
//			opusgridf[safe_clicks[i].x][safe_clicks[i].y] = GRIDF_VALUE_LAND;
//		}
		latch = false;
		
		 if ( safe_clicks_len == 0) {
			if (MagnumbFrontiers_guess[0] != -1)latch = true;
			else if(opus_flags_placed == 0 ) {
				Sleep(200);
				continue;
			}
		}
		trainer.white_buffer();
		trainer.buf_draw_boarder(1);
		if (latch) {
			if (OPUS_MAGNUMB_drawdomains)opus_trainer_drawDomains();
			else if (OPUS_trainer_Normalized)opus_trainer_drawNormalized();
			
			if (OPUS_DOGUESSES == 0) trainer.buf_drawbox2(MagnumbFrontiers_guess[0] * BIG_x, MagnumbFrontiers_guess[1] * BIG_y, 5, 5, 100, 0, 100);
			if(OPUS_trainer_flags)opus_trainer_draw_flags();
		}
		else {
			if (OPUS_MAGNUMB_drawdomains)opus_trainer_drawDomains();
			else if (OPUS_trainer_Normalized)opus_trainer_drawNormalized();
			if (OPUS_trainer_flags)opus_trainer_draw_flags();
			if (OPUS_trainer_safeclicks)opus_trainer_draw_safeclicks();
			
		}
		trainer.bufwin_draw(94, 92);
	}

}



#include "opus_screen.h"  // Screenwise calibration for websites with std minesweeper layout
#endif

/************************************************* Deprecated section **************************************/
/************************************************* Deprecated section **************************************/
/************************************************* Deprecated section **************************************/
/************************************************* Deprecated section **************************************/

/*
3 number patterns notes:
this will be very long to parse, and will go very very deep with each step before short circuiting.
maybe not worth the hassle unless it detects a required 50/50 guess.

can use similar idea to frames to detect 3 number patterns by letting through ones that don't meet the 2nd check
if the number of uncommon lands isn't less than ref-targ, then you can parse the numbers touching those uncommon
lands and if that makes up the deficit, you know
-- both targets uncommon lands are safe
-- ref's lands uncommon to both targets are mines.
deficit meaning ref-targ = number unaccounted.
i
if another number touching ref, make new target.
if new target has common lands with old target (needs new corner common function) skip.
if that ref-targ doesn't check normally, for verification
 take the original deficit, subtract new target, subtract ref's lands uncommon to both,
 if that ==0 you get your pattern.


*/
/*		magnum template
*
*
* if (gfsecn > 0 && gfsecn < 7 && gftarget <= gfsecn) {
						if (num_uncommon_lands(n, i, xm, i) <= gfsecn - gftarget) {
							if (opus_unc_lands_x[0] != -1) opus_safeclick(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_safeclick(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_safeclick(opus_unc_lands_x[2], opus_unc_lands_y[2]);
							num_uncommon_lands(xm, i, n, i);
							if (opus_unc_lands_x[0] != -1) opus_flags(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_flags(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_flags(opus_unc_lands_x[2], opus_unc_lands_y[2]);
						}
					}

void Magnumb() {
	int xm, ym, xp, yp, x, y, hold;
	//Magnum_flagged = 0; Magnum_clicked = 0;
	int gftarget, gfsecn;
	for (int n = 0; n < opus_sidesx; n++) {
		for (int i = 0; i < opus_sidesy; i++) {
			xm = n - 1; ym = i - 1; xp = n + 1; yp = i + 1; x = n; y = i;
			gftarget = opusgridf[n][i];
			if (gftarget > 0 && gftarget < 7) {
				if(x>0){
					gfsecn = opusgridf[xm][y];
					if (gfsecn > 0 && gfsecn < 7)
				}
				xm = xp;
				if(x<opus_sidesx-1){
					gfsecn = opusgridf[xm][y];
					if (gfsecn > 0 && gfsecn < 7)
				}
				if (y > 0){
					gfsecn = opusgridf[x][ym];
					if (gfsecn > 0 && gfsecn < 7)
				}
				ym = yp;
				if (y < opus_sidesy - 1){
					gfsecn = opusgridf[x][ym];
					if (gfsecn > 0 && gfsecn < 7)
				}

			}


		}
	}


}
*/
// set x,y as uncommon land between x,y - xx,yy
// this can be sped up with bool switch pointers.  probably can't use mutate_alter
void get_non_common(int& x, int& y, int xx, int yy) {
	int xxx = x - xx;
	int yyy = y - yy;
	if (xxx != 0) {  // if x != xx, set x to target direction and find land on y
		int xxxx = x + xxx;
		if (y - 1 > -1) {
			if (opusgridf[xxxx][y - 1] == 9) {
				x = xxxx; y--;
				return;
			}
		}
		if (y + 1 < opus_sidesy) {
			if (opusgridf[xxxx][y + 1] == 9) {
				x = xxxx; y++;
				return;
			}
		}
		if (opusgridf[xxxx][y] == 9) {
			x = xxxx;
			return;
		}

	}

	if (yyy != 0) {
		int xxxx = y + yyy;
		if (x - 1 > -1) {
			if (opusgridf[x - 1][xxxx] == 9) {
				y = xxxx; x--;
				return;
			}
		}
		if (x + 1 < opus_sidesx) {
			if (opusgridf[x + 1][xxxx] == 9) {
				y = xxxx; x++;
				return;
			}
		}
		if (opusgridf[x][xxxx] == 9) {
			y = xxxx;
			return;
		}

	}



}


void Magnumb_test_1t3(int tx, int ty, int x, int y) {
	if (opusgridf[tx][ty] == 1 && opusdanger[tx][ty] == 3) {
		// set uncommon land to safeclick	
		if (num_common_lands(tx, ty, x, y) == 2) {
			get_non_common(tx, ty, x, y);
			opus_safeclick(tx, ty);
			Magnum_clicked++;
		}
	}
}

//  4-1 is, if larger number is next to smaller number, 
//  larger-smaller == larger's uncommon land count  // generally short circuits here.. 
//  larger's uncommon lands are flags
//  smaller's uncommon lands are open
//  https://sites.google.com/site/challengesy/minesweeper/math/1-4-pattern
void Magnumb_adv() { // computes "4-1" style patterns 
	int xm, ym, xp, yp, x, y, hold;
	//Magnum_flagged = 0; Magnum_clicked = 0;
	int gftarget, gfsecn;
	for (int n = 0; n < opus_sidesx; n++) {
		for (int i = 0; i < opus_sidesy; i++) {
			xm = n - 1; ym = i - 1; xp = n + 1; yp = i + 1; x = n; y = i;
			gftarget = opusgridf[n][i];
			if (gftarget > 1 && gftarget < 7) {
				if (xm > -1) {
					gfsecn = opusgridf[xm][y];
					if (gfsecn > 0 && gfsecn<7 && gftarget > gfsecn) {

						if (gftarget - gfsecn == num_uncommon_lands(n, i, xm, y)) {
							if (opus_unc_lands_x[0] != -1) opus_flags(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_flags(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_flags(opus_unc_lands_x[2], opus_unc_lands_y[2]);
							num_uncommon_lands(xm, i, n, i);
							if (opus_unc_lands_x[0] != -1) opus_safeclick(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_safeclick(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_safeclick(opus_unc_lands_x[2], opus_unc_lands_y[2]);

						}
					}
				}
				xm = xp;
				if (x < opus_sidesx - 1) {
					gfsecn = opusgridf[xm][y];
					if (gfsecn > 0 && gfsecn<7 && gftarget > gfsecn) {
						if (gftarget - gfsecn == num_uncommon_lands(n, i, xm, y)) {
							if (opus_unc_lands_x[0] != -1) opus_flags(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_flags(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_flags(opus_unc_lands_x[2], opus_unc_lands_y[2]);
							num_uncommon_lands(xm, i, n, i);
							if (opus_unc_lands_x[0] != -1) opus_safeclick(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_safeclick(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_safeclick(opus_unc_lands_x[2], opus_unc_lands_y[2]);

						}
					}
				}
				if (y > 0) {
					gfsecn = opusgridf[x][ym];
					if (gfsecn > 0 && gfsecn<7 && gftarget > gfsecn) {

						gfsecn = opusgridf[x][ym];
						if (gftarget - gfsecn == num_uncommon_lands(n, i, n, ym)) {
							if (opus_unc_lands_x[0] != -1) opus_flags(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_flags(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_flags(opus_unc_lands_x[2], opus_unc_lands_y[2]);
							num_uncommon_lands(n, ym, n, i);
							if (opus_unc_lands_x[0] != -1) opus_safeclick(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_safeclick(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_safeclick(opus_unc_lands_x[2], opus_unc_lands_y[2]);

						}
					}
				}
				ym = yp;
				if (y < opus_sidesy - 1) {
					gfsecn = opusgridf[x][ym];
					if (gfsecn > 0 && gfsecn<7 && gftarget > gfsecn) {

						if (gftarget - gfsecn == num_uncommon_lands(n, i, n, ym)) {
							if (opus_unc_lands_x[0] != -1) opus_flags(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_flags(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_flags(opus_unc_lands_x[2], opus_unc_lands_y[2]);
							num_uncommon_lands(n, ym, n, i);
							if (opus_unc_lands_x[0] != -1) opus_safeclick(opus_unc_lands_x[0], opus_unc_lands_y[0]);
							if (opus_unc_lands_x[1] != -1) opus_safeclick(opus_unc_lands_x[1], opus_unc_lands_y[1]);
							if (opus_unc_lands_x[2] != -1) opus_safeclick(opus_unc_lands_x[2], opus_unc_lands_y[2]);

						}
					}
				}
			}
		}
	}

}


void Magnumb_basic() {  //  find 1-1 and 1-2  patterns and process them.
	int xm, ym, xp, yp, x, y, hold;
	Magnum_flagged = 0; Magnum_clicked = 0;
	for (int n = 0; n < opus_sidesx; n++) {
		for (int i = 0; i < opus_sidesy; i++) {
			xm = n - 1; ym = i - 1; xp = n + 1; yp = i + 1; x = n; y = i;

			if (opusgridf[n][i] == 1) {  // if space is normalized 1
				if (opusdanger[n][i] == 2) { // touching 2 lands
					//cout << "found 1t2 at: "<<n<<":"<<i<<endl;
					// checking for adjacent 1 touching 3 lands 
					if (xm > -1) {// make sure test is within array bounds
						//Magnumb_test_1t3(xm,y,x,y);
						if (opusgridf[xm][y] == 1 && opusdanger[xm][y] == 3) {
							// set uncommon land to safeclick	
							if (num_common_lands(xm, y, x, y) == 2) {
								get_non_common(xm, y, x, y);
								opus_safeclick(xm, y);
								Magnum_clicked++;
							}
						}
					}
					x = n; y = i;
					if (ym > -1) {
						//	Magnumb_test_1t3(x,ym,x,y);
						if (opusgridf[x][ym] == 1 && opusdanger[x][ym] == 3) {
							if (num_common_lands(x, ym, x, y) == 2) {
								get_non_common(x, ym, x, y);
								opus_safeclick(x, ym);
								Magnum_clicked++;
							}
						}
					}
					x = n; y = i;
					if (xp < opus_sidesx) {
						//Magnumb_test_1t3(xp,y,x,y);
						if (opusgridf[xp][y] == 1 && opusdanger[xp][y] == 3) {
							if (num_common_lands(xp, y, x, y) == 2) {
								get_non_common(xp, y, x, y);
								opus_safeclick(xp, y);
								Magnum_clicked++;
							}
						}
					}
					x = n; y = i;
					if (yp < opus_sidesy) {// make sure test is within array bounds
						//Magnumb_test_1t3(x,yp,x,y);	
						if (opusgridf[x][yp] == 1 && opusdanger[x][yp] == 3) {
							if (num_common_lands(x, yp, x, y) == 2) {
								get_non_common(x, yp, x, y);
								opus_safeclick(x, yp);
								Magnum_clicked++;
							}
						}
					}

				}
			}
			x = n; y = i;
			if (opusgridf[n][i] == 2) {
				if (opusdanger[n][i] == 3) { // find 2 touching 3 lands
					//cout << "found 2t3 at: "<<n<<":"<<i<<endl;

					// checking for normalized 1 on sides
					if (xm > -1) {// make sure test is within array bounds								
						if (opusgridf[xm][y] == 1) {
							//cout << "1found 2t3-1 at: "<<n<<":"<<i<<endl;
							hold = num_common_lands(xm, y, x, y);
							//cout << "numcommonlands: "<<hold<<endl;
							// set uncommon land to flag
							if (hold == 2) {
								get_non_common(x, y, xm, y);
								opus_flags(x, y);
								Magnum_flagged++;
								//cout << "1flag at: " << x << ":"<<y<<endl;
							}
						}
					}
					x = n; y = i;
					if (ym > -1) {
						if (opusgridf[x][ym] == 1) {
							//cout << "2found 2t3-1 at: "<<x<<":"<<ym<<endl;
							hold = num_common_lands(x, y, x, ym);
							//cout << "numcommonlands: "<<hold<<endl;
							// set uncommon land to flag
							if (hold == 2) {
								get_non_common(x, y, x, ym);
								opus_flags(x, y);
								Magnum_flagged++;
								//cout << "2flag at: " << x << ":"<<y<<endl;
							}
						}
					}
					x = n; y = i;
					if (xp < opus_sidesx) {
						if (opusgridf[xp][y] == 1) {
							//cout << "3found 2t3-1 at: "<<n<<":"<<i<<endl;
							if (num_common_lands(x, y, xp, y) == 2) {
								get_non_common(x, y, xp, y);
								opus_flags(x, y);
								Magnum_flagged++;
								//cout << "3flag at: " << x << ":"<<y<<endl;
							}
						}
					}
					x = n; y = i;
					if (yp < opus_sidesy) {
						if (opusgridf[x][yp] == 1) {
							//cout << "4found 2t3-1 at: "<<n<<":"<<i<<endl;
							if (num_common_lands(x, yp, x, y) == 2) {
								get_non_common(x, y, x, yp);
								opus_flags(x, y);
								Magnum_flagged++;
								//cout << "4flag at: " << x << ":"<<y<<endl;
							}
						}
					}
				}
			}

		}
	}
}






//  after exhaustive checking. 1-2 and 1-1 patterns are the only basic ones needed to be detected
// and only require 4x4 grid.  
//  this should make the simulation stage very short. 
// 1 touching 2 lands next to 1 touching 3 lands,  with 2 common lands, uncommon land is clear

// 2 touching 3 lands next to 1 touching 2+ lands, wiht 2 common lands, uncommon land is bomb
	// 1 will always be touching 2+ lands after safeclicks/flags
	// 2 will always be touching 3+ lands after safeclicks/flags

// can still use pattern recognition for hard guesses- such as
//	
//		 - - - -    x can be 1 or 2.  simulating this square can determine it's state.
//		|x = 1     normalized:  x l 1
//		|= = 2 1                l l 1
//		|1 2 f 1                1 1 
//		|  1 1 1

	// this state will be surrounded by 0's | 8's |9s in gridf.  
	//  ^^ not quite complete.  islands can also have numbers touching but can't have contiguous lands
	// will require a 5x5 square to check these types of patterns. 
	// maybe write 'find_island' function that finds bounding 0's and simulates the contents.
	// maybe write hash for island function to store solved islands.
//coastlines need to be detected also.



//int restart_x = 0, restart_y = 0;