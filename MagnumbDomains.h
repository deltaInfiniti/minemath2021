/* processes deep domain pattern recognition for minesweeper
 uses process detailed at deltainfiniti.com/long_patterns.txt
 

 this whole process is a bit daunting.  I'm having trouble getting motivated to put code down.
 I think I'm focused too much on optimization and I should first get the system working.  
 I'm trying to plan ahead for a binary simulation system I'm practically 100% sure won't yeild results
 Just write the damn thing in a struct array with loops like it's 2009. make it fast later. 

 even with moderate to severe optimizations, this process will be orders of magnitude slower than the conventional heuristic solver. 
 womp womp.
 */

#pragma once
// this is a helper class for mangnumb opus minesweeper solver.  
// holds magnumb_frontier and magnumb_domain classes.  
struct magnumb_ll {
	magnumb_domain* domain;
	magnumb_ll* magnumb_next;
	magnumb_ll* magnumb_branch[5];
};
// write LL free node generation and garbage collection class and associated thread. 

class magnumb_cell {

public:

	int tval;// theoretical value of land
	int nval; // value of number in cell if cell is number.
	int domain; // domain ID it's associated with. 0 = undomained
	int rval;// real value of domain

};

#define MD_toplef 0b00000001
#define MD_topmid 0b00000010
#define MD_toprit 0b00000100
#define MD_right  0b00001000
#define MD_botrit 0b00010000
#define MD_botmid 0b00100000
#define MD_botlef 0b01000000
#define MD_left   0b10000000

class magnumb_domain {
	//magnumb_cell grid[3][3]; //holds domain values. 
	short id;  // this domain's number
	//short target; // high byte is x,  low byte is y
	byte targetx;
	byte targety;
	byte  landbits; // each bit is a land. lowbit is top left,count clockwise. top bit is middle left. 1, land is in domain, 0 ignore cell
	byte value; // number of mines in this domain
	byte weight; // highest number of bits that can be 1	
	// split values
 
	byte thresh; // considered weight threshold for simulation
	byte split_asc[8]; // id of domains this is split accross, 8 is overkill. highest number should be 3 or 4. [7] can be count
	byte split_asc_len;
	magnumb_ll* parent;// node list parent, null if this is first node. 

	void zero();
};
void magnumb_domain::zero() {
	id = 0;
	targetx = 0;
	targety = 0;
	landbits = 0;
	value = 0;
	weight = 0;
	thresh = 0;
	split_asc[0] = 0;
	split_asc[1] = 0;
	split_asc[2] = 0;
	split_asc[3] = 0;
	split_asc[4] = 0;
	split_asc[5] = 0;
	split_asc[6] = 0;
	split_asc[7] = 0;
	split_asc_len=0;
	parent = NULL;
}

#define Magnumb_Frontier_TREE_SIZE 20
class magnumb_frontier {  //
public:
	int MF_width, MF_height;
	int grid[BAD][BAD]; // const grid copy of real board gridf
	int workgrid[BAD][BAD];// copied from frgrid to make inline edits to. 

	int frgrid[BAD][BAD]; //derived representation of fronteir array for data stability
	int frworkgrid[BAD][BAD];// copied from frgrid, for live work
	
	int deadgrid[BAD][BAD]; // grid of dead cells  can be a frgrid flag maybe 8-9
	magnumb_ll *tree[Magnumb_Frontier_TREE_SIZE]; // node tree- list of roots/plants 
	magnumb_ll* parseliststart; //start of queue of nodes to parse
	magnumb_domain domains[100];
	byte domainslen;
	
	magnumb_frontier();
	magnumb_frontier(int x, int y);
	void set(int x, int y);
	~magnumb_frontier(); // will need to remove all magnumb_ll pointer locations, either return to garbage collect or de
	void make_frgrid(); //creates frgrid. from grid. lete.
	void runonce(); // run this once to setup the class variable. 

	void start_new_process(); // clear values other than dead lands, gets grid.
	void start_new_game(); // clear all values
	void frgrid_addlands(int x, int y); // adds lands around x,y to frgrid from grid
	void parse_domains();  //finds all domains - main runner

	// nessesary for first pass 
	short find_target(); // get a number not parsed from frworkgrid
	short adjust_target(); // adjusts current target by theoretical value for each domain, enum split domains, 
	void create_domain_at(short target); // generates a new magnumb_domain based on the target
	void parse_domain(short target); // check domain for safeclicks/mines and prepare domain for workgrid
	void target_to_workgrid(short target); // move all data to workgrid
	void asc_to_parselist(short target);// find numbers associated with domain not parsed yet, cat to parselist
	void clear_frgrid(short target); // removes number from frworkgrid 
	short pop_parselist(); // pop a value off of parselist.

	//first pass wants list
	void target_to_tree(short target); // move new magnumb_ll to tree
	void resolve_tree_loops();// find tree loops and separate branches -> split domains 

	//  not yet implimented/ wanted list
	void second_pass_parse_domains();// must reset process before running this after parse_domains


};
magnumb_frontier::magnumb_frontier() {
	for (int i = 0; i < Magnumb_Frontier_TREE_SIZE; i++) {
		tree[i] = NULL;
	}
	parseliststart = NULL;
	domainscount=0;
}
magnumb_frontier::magnumb_frontier(int x, int y) {
	MF_width = x; 
	MF_height = y;
	magnumb_frontier();
}
void magnumb_frontier::set(int x, int y) {
	MF_width = x;
	MF_height = y;
}
magnumb_frontier::~magnumb_frontier() {
	// delete or send nodes from tree to garbage collection
	// delete or send nodes from parselist to garbage collection
}
void magnumb_frontier::runonce() {
	//zerofill all grids here

}
void magnumb_frontier::start_new_game() {
	// start new game, get ready for new parse process. 
}
void magnumb_frontier::start_new_process() {
	// clear everything except dead cells 
	memcpy(grid, opusgridf, BAD * BAD * sizeof(int));
}
void magnumb_frontier::frgrid_addlands(int x, int y) {
	// adds lands around x,y to frgrid from grid

}

#define FRGRID_dead 9
#define FRGRID_land 8
#define FRGRID_space 0
void magnumb_frontier::make_frgrid() {
	int htarg;
	for (int x = 0; x < MF_width; x++) {
		for (int y = 0; y < MF_height; y++) {
			frgrid[x][y] = FRGRID_space;
			if (deadgrid[x][y])continue;
			htarg = grid[x][y];
			if (htarg > 0 && htarg < 7) { // target square is number. 
			  //add lands around this number. to frgrid
				frgrid_addlands(x, y);
			  //add this number to frgrid
				frgrid[x][y] = htarg;
			}
			  
		}
	}
} 
void magnumb_frontier::parse_domains() {  //finds all domains - main runner
	// uses all the rest of the functions in this class to derive domains and find mines/safeclicks 
	// assumes either startnew and make_frgrid called before this.
	// sets safeclick and mine locations to return to calling process. 
	// redo all prototypes to move away from short target.  just pass 2 bytes or keep targets as a member array.
	int x, y, parent=-1;

	if (find_target(x, y)) {
		domains[domains_len].zero();
		domains[domains_len].targetx = x;
		domains[domains_len].targety = y;

		adjust_target(x, y, domains_len);
		//if domains value == 0 and domains_asc_count ==0, all undomained associated lands are safe
		// if domains value == undomained surrounding lands, and domains_asc_count==0, all undomained associated lands are mines
		// if clicks/mines are found here, set clicks as empty cell, set flags and reduce frgrid values around that number
		// by definition, no domained number left in frgrid will be touching any of those lands 
		// if clicks/mines are found, can return for quick replay or continue parsing

		
		//create_domain_at(int domain_num); // fills magnumb_domain based on the target, add lands to landbyte,  set value,weight,thresh,parent

	 }

	
	/* 
	   parse_domain(short target); // check domain for safeclicks/mines and prepare domain for workgrid
	   target_to_workgrid(short target); // move all data to workgrid
	
	// target_to_tree(short target); // move new magnumb_ll to tree             // do this later
	//void resolve_tree_loops();// find tree loops and separate branches -> split domains   //do this later

	void asc_to_parselist(short target);// find numbers associated with domain not parsed yet, cat to parselist
	void clear_frgrid(short target); // removes number from frworkgrid 
	short pop_parselist(); // pop a value off of parselist.
	*/
}
BOOL magnumb_frontier::find_target(int& xx, int& yy) { // fast version of find target.  maybe write better later.

	for (int x = 0; x < MF_width; x++) {
		for (int y = 0; y < MF_height; y++) {
			if (frgrid[x][y] > 0 && frgrid[x][y] < 7) {
				xx = x; yy = y;
				return true;
			}
		}
	}
	return false;
}
bool magnumb_frontier::adjust_target(int x, int y, int domain_index ) {
	// adjust target number from frgrid by the theretical value of lands touching per domain
	// if a domain's theoretical reduction ends up being fractional, include those lands in domain asc 
	int ascs[8] = { 0 }; //theoretical value of ascociated domains
	int ascsids[8] = { 0 }; //domain id of ascs theoretical value
	int ascslen = 0;
	// parse all surrounding lands. 
	// func here probably
	// if target land is in a domain, get that domain ID,
	//check ascsids for that value
	// if ascsids[index]==ID   set ascs[index] += theoretical_value of target land

	
	// after all lands are parsed, parse through ascs. 
	if (ascslen == 0)return false;
	// for each ascs,
	// if there's a fractional component, add that/those land(s) to domain_index 's lands byte, add domain ID to domains_asc, increment landcount
	// round fractional component down
	  /////  there is a a way to remove lands from fractional component if PART of tthe overlapping domain has a theoretical value over 1 and another has less.
	  //// you can remove the group with Tvalue>1 furthest away from new domain component. by definition, at this point, this will be at least 2 lands.
	  //// 
	//reduce target number's value (domain value) by integer Tvalue of that ascs

	//after this loop, domains_index should have asc_domains filled, value adjusted, associated domained lands added to landbyte


}
/*
grab copy of gridf  offset by 2,2 so no bounds checking needs to be done. 
translate to fr 
grab corner number when possible
otherwise choose a target to start with
move values to workgrid as they are placed into domain.
find all associated nodes(numbers touching this domain)
cat nodes to trace linked list queue  
parse untill nodes list is empty
file this as a frontier
parse frwork into workgrid untill all numbers are covered.
for intra-game saving keep 'dead' domains (confirmed hard guesses with no touching lands) to avoid reparsing the same domains.

// when cutting down overlapping arrays, make sure to update ALL associated domains. 

*/