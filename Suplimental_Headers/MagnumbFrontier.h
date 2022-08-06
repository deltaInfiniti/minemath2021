/* processes deep domain pattern recognition for minesweeper
 uses process detailed at deltainfiniti.com/long_patterns.txt
 

 this whole process is a bit daunting.  I'm having trouble getting motivated to put code down.
 I think I'm focused too much on optimization and I should first get the system working.  
 I'm trying to plan ahead for a binary simulation system I'm practically 100% sure won't yeild results
 Just write the damn thing in a struct array with loops like it's 2009. make it fast later. 

 even with moderate to severe optimizations, this process will be orders of magnitude slower than the conventional heuristic solver. 
 womp womp.
 

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
	/
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


/*
Above is left over from magnumb domains prtotype from 2020.  Today is 7/6/22 and I've come up with a better way

2022 version of magnumbDomains will be called MagnumbFrontier 
Most of the same principles apply, but I've found a reasonable way to get around using theoretical values
which I've recently discovered to be flawed in situations where number fits into domain landcount more than once.
adopt V -(L-A) heuristic for theoretical calculations...  V-Domain Value, L= Lands in domain, A= lands adjacent to target number 
Target number reduction (per domain) == V- (L-A) or (A+V-L).
When you have a situation with a 2 on 4 lands for example, you need to be adjacent to 3 lands to assure 1 mine adjacency
  thus 1 total reduction from that interaction, but being adjacent to all 4 (only possible if numbers are cardinally adjacent)
  ensures that you get both values. (edit 7/8: caveat being that having those 3 lands only assures 1 mine, but doesn't rule out
  there being more than 1 mine in that set of squares, only the lowest domain value containing that set determines that. this is
  probably why I called them theoretical in the first place).


--------------------- all of this block was written 7/6 but is no longer used in practice -------------------------------
I've also decided to not design the module to be extended for simulation testing as I've become convinced
it cannot yield results if the domains system can't. 
only major decision left to make is when to reduce numbers found sufficiently adjacent to a domain...
-- when the domain is formed and before it's removed from workgrid
-- when the number is located.
----- the former would be slightly heuristically simpler but would also lead to numbers being found
----- with lands associated that represent a numerical reduction and would lead to cyclical testing
----- when associating loner lands to an adjacent number's domain when those lands exist in a contributing domain

----- if done afterwords, will have to serach for loner lands at this point instead with similar logics.

in my notes last night, I decided to add 'effectingIds' array to each domain item in order to slightly short circuit that search
when reducing a number, add contributing domains' ID to effectingIds array and increase EffectingIdsLen.
                      - search association of target number's domain for lands in contributing domain and remove
when adding a new loner land, search effectingIds for domains with lonerland(s) and skip association if found

----------------------- next few lines also written 7/6 but do still apply to current practice ----------------------------
in 2022, I've given up on the linked list trees and will now just use a global grid of domains as every other system does
I'm also changing the way the flow slightly in that the initial parsing step will move all live lands into the workgrid
  recording the lowest and highest x and y values it adds to the workgrid to make limited bounding far simpler.



7/8   After a few days of graphing and notes, I've refactored my flow for a 4th time and discovered a few important truths
      by testing domains that aren't probative. I need to ensure that all solid domains have an exact known quantity of mines
	  to ensure the math is sound.  New flow is essentially, Parse Workgrid into domains, no removals.  
	  parse out collisions and collision reductions.  Test for probative domains
	  if no probative domains, calculate out v-(l-a) heuristic for each domain pair.  If this theoretical reduction produces
	  a probative domain, that domain is solved.  if no solution is found after theoretical reductions, must guess.

7/9   Finished the system as it exists in my head. I can prove it's 100% safe probative for both direct collision and theoretical
      reduction to safe probative state.  Can use non-probative theoretical reduction to calculate guesses.  Today there is a metric butt ton of very dirty
	  nonoptimal code.  Lots of loops, lots of bounds checking, lots of quick and dirty searches and hacks.  Many improvements
	  if this system ends up leading to any results.
Glossary:
  Adjacency             -  a relationship between 2 squares, usually a land and a number.  a land is adjacent to a number if it exists in the 
                           8 squares surrounding the targetted number. Mathmatically, Target (x,y) values may have at most +- 1 compared to reference
						   aka direct adjacency
  Cardinal Adjacency    -  modified adjacency-  Only counts 4 cardinal directions- up, down, left and right.
  contributing domain   -  when targetting a new number, a contributing domain is one who's adjacency has or will reduce the target by 1 or more.
                           mathmatically, reduction value for a number vs a domain is V- (L-A)
                           aka contributory domain
  Direct collision      -  when all of a domain's lands exist in another larger domain. 
  Probative domain      -  a domain which leads to a known flag or safe click.  defined as having 0 value and assoclen>0 (safe) or value==assoclen (flag)
  solid domain          -  a domain being represented by a domain object in the current solve without theoretical adaptations.  post-processing
                           defined by value/assoclen === probabilty of being a mine. 
  theoretical reduction -  reduction made by V-L-A heuristic that may actually contain more lands than can be proven reside in that set at least
  V-(L-A)               -  Equation describing the theoretical reduction heuristic between a number and a set domain where V is the value of the set domain
                           L is the number of lands in the set domain and A is the count of those lands the target number has adjacency with.
  
*/

/*  MagnumbFrontier.h        Revamped in 2022*/

bool MAGNUMB_VLA_RUTHLESS_SHORTCIRCUIT = false;  // fast return on VLA reductions when safe clicks found
class magnumb_domain {
public:
	short id;  // this domain's number
	
	short x;
	short y;
	char value; // number of mines in this domain
	
	
	short Assocx[8]; // list of lands x values this domain contains
	short Assocy[8]; // list of lands x values this domain contains
	char Assoclen;

//	short EffectedIds[8]; // list of domains reducing this domain's value
//	char Effectedlen;

	magnumb_domain() { zero(); }
	void zero();
};
void magnumb_domain::zero() {
	id = 0;
	x = 0;
	y = 0;
	value = 0;
	Assoclen = 0;
}

//magnumb_domain *Domgrid[BAD][BAD]; // make all NULL when resetting. Might need to call delete or free() here.
#define Magnumb_DOMLISTLEN 500
magnumb_domain Domlist[Magnumb_DOMLISTLEN]; // also initialize id, len to 0.
short Domlistlen = 0;  
int Magnumb_Workgrid[BAD][BAD];
short Magnumb_workbounds[4] = { 500,500,0,0 }; // contains xmin,ymin,xmax,ymax  bounds for data in workgrid
static int Magnumb_Probecount = 0; // number of probative domains/lands found this run
static int Magnumb_Minecount = 0; // number of mines found this run
void Magnumb_resetFrontiersArrays() {
	//loop and clear domlist
	Domlistlen = 0;
	for (int i = 0; i < Magnumb_DOMLISTLEN; i++)Domlist[i].zero();

	//loop and clear workgrid
	for (int i = 0; i < BAD; i++)
		for (int n = 0; n < BAD; n++)
			Magnumb_Workgrid[i][n] = 0;
	//reset lens 

	Magnumb_workbounds[0] = 500;
	Magnumb_workbounds[1] = 500;
	Magnumb_workbounds[2] = 0;
	Magnumb_workbounds[3] = 0;

}
#define Magnumb_is_grid_number(gridspace) (gridspace>0 && gridspace<7)

void Magnumb_Copy_Adjacent_Lands_To_Work(int x,int y) { // ,short id
	//slow and dirty but i'm just trying to make it work. 
	// later move making the domains in here. 
	
	for (int n = -1; n < 2; n++) {
		if (x + n < 0 || x + n> opus_sidesx)continue;
		for (int i = -1; i < 2; i++) {
			if (y + i < 0  || y + i > opus_sidesy)continue;
			if (opusgridf[x][y] == GRIDF_VALUE_LAND) Magnumb_Workgrid[x][y] = GRIDF_VALUE_LAND;
		}
	}

}
void Magnumb_FillWorkgrid() {
	// loop through gridf, copy numbers and adj lands into workgrid
	// assign a domain ID to all numbers.  Value can be reduced to 0, landcount can be reduced to 0.
	// record xmin,ymin,xmax,ymax and record into workbounds
	for (int x = 0; x < opus_sidesx; x++) {
		for (int y = 0; y < opus_sidesy; y++) {
			if (Magnumb_is_grid_number(opusgridf[x][y])) {
				Domlist[Domlistlen].x = x;
				Domlist[Domlistlen].y = y;
				Domlist[Domlistlen].value = opusgridf[x][y];
				Domlist[Domlistlen].id = Domlistlen;
				Domlist[Domlistlen].Assoclen=0 ;
				//Domlist[Domlistlen].Effectedlen = 0;
				Domlistlen++;
				Magnumb_Workgrid[x][y] = opusgridf[x][y];
				Magnumb_Copy_Adjacent_Lands_To_Work(x, y); // ,Domlistlen-1;
				if (x < Magnumb_workbounds[0])Magnumb_workbounds[0] = x-1;
				if (y < Magnumb_workbounds[1])Magnumb_workbounds[1] = y-1;
				if (x > Magnumb_workbounds[2])Magnumb_workbounds[2] = x+1;
				if (y > Magnumb_workbounds[3])Magnumb_workbounds[3] = y+1;
			}
		}
	}
	if (Magnumb_workbounds[0] < 0)Magnumb_workbounds[0] = 0;
	if (Magnumb_workbounds[1] < 0)Magnumb_workbounds[1] = 0;
	if (Magnumb_workbounds[2] >= opus_sidesx)Magnumb_workbounds[2] = opus_sidesx;
	if (Magnumb_workbounds[3] >= opus_sidesy)Magnumb_workbounds[3] = opus_sidesy;
}
void Magnumb_Associate_Adjacent_Lands_to_domain(short id) {
	// search around domain x,y for lands, count and associate them to domain
	// remove all associations from the workgrid
	 
		//slow and dirty but i'm just trying to make it work. 
	int x =Domlist[id].x, y = Domlist[id].y;
	for (int n = -1; n < 2; n++) {
		if (x + n < 0 || x + n>= opus_sidesx)continue;
		for (int i = -1; i < 2; i++) {
			if (y + i < 0 || y + i >= opus_sidesy)continue;
			if (opusgridf[x + n][y + i] == GRIDF_VALUE_LAND) {
				Domlist[id].Assocx[Domlist[id].Assoclen] = x + n;
				Domlist[id].Assocy[Domlist[id].Assoclen] = y + i;
				Domlist[id].Assoclen++;
				//Magnumb_Workgrid[x + n][y + i] = 8;
			}
		}
	}
}
short Magnumb_finddomain(int x, int y) {

	for (int i = 0; i < Domlistlen; i++) {
		if (Domlist[i].x == x && Domlist[i].y == y) return i;

	}
	return -1;

}

short Magnumb_GetDomain(int x, int y) {
	// search list for existing x,y
	short id = Magnumb_finddomain(x, y);
	// if existing x,y is found, check that all values in assoc aren't in effectid.assoc lists
	// ^^^ this might be it's own method.. fixdomain.  Might want to call this on all domains every time a new one is made
	// if not existing, fill next item in domlist with workgridxy's data 
	// associate all existing adjacent land values in workgrid 
	Magnumb_Associate_Adjacent_Lands_to_domain(id);  // after moving this to copay_adjacent_lands_to_work, comment this out
	// remove x,y from the workgrid
	//Magnumb_Workgrid[x][y] = 8;
	return id;
}
void Magnumb_Remove_Land_From_Domain(short id, short x, short y) {
	short place = -1;
	for (int i = 0; i < Domlist[id].Assoclen; i++) {
		/*if (latch) {
			Domlist[id].Assocx[i - 1] = Domlist[id].Assocx[i];
			Domlist[id].Assocy[i - 1] = Domlist[id].Assocy[i];
			continue;
		}*/
		if (Domlist[id].Assocx[i] == x && Domlist[id].Assocy[i] == y) {
			place = i;
			break;
		}
	}
	if (place > -1) {
		Domlist[id].Assoclen--;
		Domlist[id].Assocx[place] = Domlist[id].Assocx[Domlist[id].Assoclen];
		Domlist[id].Assocy[place] = Domlist[id].Assocy[Domlist[id].Assoclen];
	}
}
bool Magnumb_find_probative_domains_process(int i) {
	//  edit this to make it remove solved domains from domain list. 
	if (Domlist[i].value == Domlist[i].Assoclen && Domlist[i].value == 0) return false;
		
	if (Domlist[i].value == 0 && Domlist[i].Assoclen > 0) {
		for (int n = 0; n < Domlist[i].Assoclen; n++) {
			Magnumb_Probecount++;
			//cout << "Find_probative_Domains called safeclicks for x,y: " + ctostr(Domlist[i].Assocx[n]) << "," << ctostr(Domlist[i].Assocy[n]) << "            \r";
			opus_safeclick(Domlist[i].Assocx[n], Domlist[i].Assocy[n]);
		}
		// set all lands in this domain as safe.
		//opus_safeclick(x,y);
		// set LASTCLICK or whatever to magnumb_fronteirs
		return true;
	}
	if (Domlist[i].value == Domlist[i].Assoclen) {
		for (int n = 0; n < Domlist[i].Assoclen; n++) {
			//Magnumb_Probecount++;
			Magnumb_Minecount++;
			//cout << "Find_probative_Domains called opusflags for x,y: " + ctostr(Domlist[i].Assocx[n]) << "," << ctostr(Domlist[i].Assocy[n]) << "            \r";
			opus_flags(Domlist[i].Assocx[n], Domlist[i].Assocy[n]);
		}
		//set all lands in this domain as flags.
		//opus_flags(x,y);
		return true;
	}
	return false;
}
bool Magnumb_find_probative_domains() {
	bool hold;
	//bool test = false;
	for (int i = 0; i < Domlistlen; i++) {
		hold = Magnumb_find_probative_domains_process(i);
		if (hold == true && MAGNUMB_VLA_RUTHLESS_SHORTCIRCUIT) return true;
		//if(!test)test=hold;

	}
	//return test;
	return false;
}
void Magnumb_Check_Domain_Collision_process(short id, short id2) {
	if (abs(Domlist[id].x - Domlist[id2].x) > 2 || abs(Domlist[id].y - Domlist[id2].y) > 2) return;
	if (Domlist[id].Assoclen < 2 || Domlist[id2].Assoclen < 2
		|| Domlist[id].value < 1 || Domlist[id2].value < 1) return;  // edited value from 2 to 1 because....
	short tx[4] = { 0,0,0,0 };
	short ty[4] = { 0,0,0,0 };
	short ttot = 0;

	for (int i = 0; i < Domlist[id].Assoclen; i++) {
		for (int n = 0; n < Domlist[id2].Assoclen; n++) {
			if (Domlist[id].Assocx[i] == Domlist[id2].Assocx[n] &&
				Domlist[id].Assocy[i] == Domlist[id2].Assocy[n]) {
				tx[ttot] = Domlist[id].Assocx[i];
				ty[ttot] = Domlist[id].Assocy[i];
				ttot++;
			}
		}
	}
	// changed below from value to assoclen...  because... 
	if (ttot == Domlist[id].Assoclen) {// if all of ID's assoc lands are in id2
		//remove tx,ty list from id2, reduce id2 by ttot;
		for (int i = 0; i < ttot; i++) {
			Magnumb_Remove_Land_From_Domain(id2,tx[i],ty[i]);
		}
		Domlist[id2].value -= Domlist[id].value;//changed from ttot;
		// if new value == 0 
		//         and .assoclen ==0, delete, remove or push back domain
		//         Magnumb_find_probative_domains_process
		return;
	}
	else if (ttot == Domlist[id2].Assoclen) {// if all of ID2's assoc lands are in id
		//remove tx,ty list from id, reduce id2 by ttot;
		for (int i = 0; i < ttot; i++) {
			Magnumb_Remove_Land_From_Domain(id, tx[i], ty[i]);
		}
		Domlist[id].value -= Domlist[id2].value;//changed from ttot;
	}
}

void Magnumb_Check_Domain_Collision() {
// check to see if my domain is totally inside another domain and separate them if nessessary.
// if a larger domain is reduced by a domain that's entirely inside it
//     (reduce the value of the larger domain by the value of the smaller domain
//		remove the lands from the smaller domain from the larger domain )
//      if after this, the value of the domain is 0 all lands in domain are safe
//                   ,  the value of the domain == the number of lands in it, all are flags
	
	for (int i = 0; i < Domlistlen; i++) {
		for (int n = i + 1; n < Domlistlen; n++) {
			Magnumb_Check_Domain_Collision_process(i,n);
		}
		if (OPUS_DOGUESSES) {

		}
	}
	for (int i = 0; i < Domlistlen; i++) {// remove dead domains
		if (Domlist[i].Assoclen == Domlist[i].value && Domlist[i].value == 0) {
			auto temp = Domlist[i];
			Domlist[i] = Domlist[Domlistlen - 1];
			Domlist[Domlistlen - 1]=temp;
			Domlistlen--;
			i--;
		}
	}
}


bool Magnumb_do_VLA_reduce_process(int id,int id2) {
	if (abs(Domlist[id].x - Domlist[id2].x) > 2 || abs(Domlist[id].y - Domlist[id2].y) > 2) return false;
	if (Domlist[id].Assoclen < 2 || Domlist[id2].Assoclen < 2
		|| Domlist[id].value < 1 || Domlist[id2].value < 1) return false;

	short tx[4] = { 0,0,0,0 };
	short ty[4] = { 0,0,0,0 };
	short ttot = 0;

	for (int i = 0; i < Domlist[id].Assoclen; i++) {
		for (int n = 0; n < Domlist[id2].Assoclen; n++) {
			if (Domlist[id].Assocx[i] == Domlist[id2].Assocx[n] &&
				Domlist[id].Assocy[i] == Domlist[id2].Assocy[n]) {
				tx[ttot] = Domlist[id].Assocx[i];
				ty[ttot] = Domlist[id].Assocy[i];
				ttot++;
			}
		}
	}
	short vla1 = (ttot + Domlist[id2].value) - Domlist[id2].Assoclen;
	short vla2 = (ttot + Domlist[id].value) - Domlist[id].Assoclen;
	bool latch = false;
	short tid = -1;
	short ret = 0;
	if (vla1 == Domlist[id].value && Domlist[id].Assoclen > ttot) {  // if value is reduced to 0 and contains non-contributary lands
		// search id1 for lands not in tx,ty  ||  safeclick these 
		for (int i = 0; i < Domlist[id].Assoclen; i++) {
			latch = true;
			for (int n = 0; n < ttot; n++) {
				//if (Domlist[id].Assocx[i] != tx[n] || Domlist[id].Assocy[i] != ty[n]) {
				if (Domlist[id].Assocx[i] == tx[n] && Domlist[id].Assocy[i] == ty[n]) {
					latch = false;
					break;
				}
			}
			if (latch) {
				Magnumb_Probecount++;
				//cout << "Magnumb_VLA_reduce called safeclicks for x,y: " + ctostr(Domlist[id].Assocx[i]) << "," << ctostr(Domlist[id].Assocy[i]) << "            \r";
				opus_safeclick(Domlist[id].Assocx[i], Domlist[id].Assocy[i]);
				ret++;
			}
		}

	}
	if (vla2 == Domlist[id2].value && Domlist[id2].Assoclen > ttot) {
		// search id1 for lands not in tx,ty  ||  safeclick these 
		for (int i = 0; i < Domlist[id2].Assoclen; i++) {
			latch = true;
			for (int n = 0; n < ttot; n++) {
				//if (Domlist[id].Assocx[i] != tx[n] || Domlist[id].Assocy[i] != ty[n]) {
				if (Domlist[id2].Assocx[i] == tx[n] && Domlist[id2].Assocy[i] == ty[n]) {
					latch = false;
					break;
				}
			}
			if (latch) {
				ret++;
				Magnumb_Probecount++;
				//cout << "Magnumb_VLA_reduce called safeclicks for x,y: " + ctostr(Domlist[id2].Assocx[i]) << "," << ctostr(Domlist[id2].Assocy[i]) << "            \r";
				opus_safeclick(Domlist[id2].Assocx[i], Domlist[id2].Assocy[i]);
			}
		}

	}
	//  calculate guess potential Theoretical VLA domains here.  
	//  if there is a VLA reduction to a target domain
	//  remove target domains non-adj lands into Tdom1
	//  remove target domains' adj lands into Tdom2
	//  remove reference domains' non-adj lands into Tdom3
	//    -- note-- don't actually remove the lands from parent domain. theoretical domains are treated separately
	//  non probative vla reductions in post-conventional solve, post-domain collision state must be split
	//  split reductions contain n or n+1 mines in domain, making them theoretical. 
	//  chance calculation-  (100*(Tdom min + Tdom max)) /  Landcount*2
	

	/*  can't actually guarantee flags here.  OK as a theoretical guess but is always n/n+1 odds which isn't good.
	if (vla1 >0  && Domlist[id].value - vla1 == Domlist[id].Assoclen-ttot) {
		// if reduction make theoretical value == to the number of lands 
		for (int i = 0; i < Domlist[id].Assoclen; i++) {
			for (int n = 0; n < ttot; n++) {
				if (Domlist[id].Assocx[i] != tx[n] || Domlist[id].Assocy[i] != ty[n]) {
					opus_flags(Domlist[id].Assocx[i], Domlist[id].Assocy[i]);
				}
			}
		}

	}
	if (vla2 == Domlist[id2].value) {
		for (int i = 0; i < Domlist[id2].Assoclen; i++) {
			for (int n = 0; n < ttot; n++) {
				if (Domlist[id2].Assocx[i] != tx[n] || Domlist[id2].Assocy[i] != ty[n]) {
					opus_flags(Domlist[id2].Assocx[i], Domlist[id2].Assocy[i]);
				}
			}
		}
	}
	*/
	return ret>0;

}
 
void Magnumb_do_VLA_reduce() {
	for (int i = 0; i < Domlistlen; i++) {
		for (int n = i + 1; n < Domlistlen; n++) {
			if ( Magnumb_do_VLA_reduce_process(i, n) && MAGNUMB_VLA_RUTHLESS_SHORTCIRCUIT) return;
		}
	}
}

void MagnumbFrontiers_output(string fname) {
	ofstream ifile(ctocp(fname));

	if (!ifile) {
		cout << "could not open file for writing" << endl;
	}
	string hold, temp;
	char outgrid[BAD*2][BAD*2];
	for (int i = 0; i < BAD; i++)
		for (int n = 0; n < BAD; n++) outgrid[i][n] = ' ';

	SHOWb(opus_sidesx, ifile);
	SHOWb(opus_sidesy, ifile);


	SHOWb( Domlistlen,ifile);
	SHOWb(Magnumb_workbounds[0], ifile);
	SHOWb(Magnumb_workbounds[1], ifile);
	SHOWb(Magnumb_workbounds[2], ifile);
	SHOWb(Magnumb_workbounds[3], ifile);
	char landval = (char)254;// '=';
	for (int i = 0; i < Domlistlen; i++) {
		hold = "id:"+ctostr(i)+"  Value:" + ctostr(Domlist[i].value) + "  x,y:" + ctostr(Domlist[i].x) + ","+ ctostr(Domlist[i].y)+"\nLands:\n";
		temp = ctostr(Domlist[i].value);
		outgrid[(Domlist[i].x*2)+1][(Domlist[i].y*2)+1] = temp[0];
		// straight up fuck it. I don't have time to do this smart..
		for (int n = 0; n < Domlist[i].Assoclen; n++) {
			hold += ctostr(i) + ":" + ctostr(Domlist[i].Assocx[n]) + "," + ctostr(Domlist[i].Assocy[n]) + "   ";
			if (Domlist[i].Assocx[n] == Domlist[i].x - 1 && Domlist[i].Assocy[n] == Domlist[i].y - 1) {
				// up left corner land
				if (outgrid[(Domlist[i].x * 2)][(Domlist[i].y * 2)] != ' ')outgrid[(Domlist[i].x * 2)][(Domlist[i].y * 2)] = 'x';
				else outgrid[(Domlist[i].x * 2)][(Domlist[i].y * 2)] = '\\' ;
				outgrid[(Domlist[i].x * 2) - 1][(Domlist[i].y * 2) - 1] = landval; // '\';
				//outgrid[(Domlist[i].x * 3) - 2][(Domlist[i].y * 3) - 2] = '=';
			}
			if (Domlist[i].Assocx[n] == Domlist[i].x + 1 && Domlist[i].Assocy[n] == Domlist[i].y + 1) {
				// bottom right corner land
				if (outgrid[(Domlist[i].x * 2) + 2][(Domlist[i].y * 2) + 2] != ' ')outgrid[(Domlist[i].x * 2) + 2][(Domlist[i].y * 2) + 2] = 'x';
				else outgrid[(Domlist[i].x * 2)+2][(Domlist[i].y * 2)+2] = '\\';
				outgrid[(Domlist[i].x * 2) + 3][(Domlist[i].y * 2) + 3] = landval; // '\';
					//outgrid[(Domlist[i].x * 3) - 2][(Domlist[i].y * 3) - 2] = '=';
			}
			if (Domlist[i].Assocx[n] == Domlist[i].x + 1 && Domlist[i].Assocy[n] == Domlist[i].y - 1) {
				// top right corner land
				if (outgrid[(Domlist[i].x * 2) + 2][(Domlist[i].y * 2)] != ' ')outgrid[(Domlist[i].x * 2) + 2][(Domlist[i].y * 2)] = 'x';
				else outgrid[(Domlist[i].x * 2) + 2][(Domlist[i].y * 2) ] = '/';
				outgrid[(Domlist[i].x * 2) + 3][(Domlist[i].y * 2) -1] = landval; // '\';
					//outgrid[(Domlist[i].x * 3) - 2][(Domlist[i].y * 3) - 2] = '=';
			}
			if (Domlist[i].Assocx[n] == Domlist[i].x - 1 && Domlist[i].Assocy[n] == Domlist[i].y + 1) {
				// top right corner land
				if (outgrid[(Domlist[i].x * 2)][(Domlist[i].y * 2) + 2] != ' ') outgrid[(Domlist[i].x * 2)][(Domlist[i].y * 2) + 2] = 'x';
				else outgrid[(Domlist[i].x * 2) ][(Domlist[i].y * 2)+2] = '/';
				outgrid[(Domlist[i].x * 2) -1][(Domlist[i].y * 2) +3] = landval; // '\';
					//outgrid[(Domlist[i].x * 3) - 2][(Domlist[i].y * 3) - 2] = '=';
			}
			if (Domlist[i].Assocx[n] == Domlist[i].x + 1 && Domlist[i].Assocy[n] == Domlist[i].y ) {// seems to work.
				// to the right
				outgrid[(Domlist[i].x * 2) + 2][(Domlist[i].y * 2) + 1] = '-';
				outgrid[(Domlist[i].x * 2) + 3][(Domlist[i].y * 2) + 1] = landval; // '\';
					//outgrid[(Domlist[i].x * 3) - 2][(Domlist[i].y * 3) - 2] = '=';
			}
			if (Domlist[i].Assocx[n] == Domlist[i].x - 1 && Domlist[i].Assocy[n] == Domlist[i].y) {
				// to the left
				outgrid[(Domlist[i].x * 2) ][(Domlist[i].y * 2) + 1] = '-';
				outgrid[(Domlist[i].x * 2) -1][(Domlist[i].y * 2) + 1] = landval; // '\';
					//outgrid[(Domlist[i].x * 3) - 2][(Domlist[i].y * 3) - 2] = '=';
			}
			if (Domlist[i].Assocx[n] == Domlist[i].x  && Domlist[i].Assocy[n] == Domlist[i].y+1) {
				// down
				outgrid[(Domlist[i].x * 2) + 1][(Domlist[i].y * 2) + 2] = '|';
				outgrid[(Domlist[i].x * 2) + 1][(Domlist[i].y * 2) + 3] = landval; // '\';
					//outgrid[(Domlist[i].x * 3) - 2][(Domlist[i].y * 3) - 2] = '=';
			}
			if (Domlist[i].Assocx[n] == Domlist[i].x && Domlist[i].Assocy[n] == Domlist[i].y - 1) {
				// up
				outgrid[(Domlist[i].x * 2)+1 ][(Domlist[i].y * 2) ] = '|';
				outgrid[(Domlist[i].x * 2)+1 ][(Domlist[i].y * 2) -1] = landval; // '\';
					//outgrid[(Domlist[i].x * 3) - 2][(Domlist[i].y * 3) - 2] = '=';
			}

		}

		hold += "\n\n";
		SHOWf(hold,ifile);
	}
	string workout = "", gridout = "", secline = "", wgridout = "";
	for (int i = 0; i < opus_sidesy; i++) {
		secline = "";
		for (int n = 0; n < opus_sidesx; n++) {
			workout += outgrid[n * 2][i*2];
			workout += outgrid[(n * 2)+1][(i*2)];
			secline += outgrid[(n * 2)][(i*2) + 1];
			secline += outgrid[(n * 2) + 1][(i*2) + 1];
			if (opusgridf[n][i] == GRIDF_VALUE_SPACE)gridout += " ";
			else if (opusgridf[n][i] == GRIDF_VALUE_LAND)gridout += "-";
			else if (opusgridf[n][i] == 8)gridout += " ";
			else gridout += ctostr(opusgridf[n][i]);
			if (Magnumb_Workgrid[n][i] == 0)wgridout += ' ';
			else wgridout += ctostr(Magnumb_Workgrid[n][i]);
			gridout += " ";
		} 
		workout += "\n" + secline + "\n";
		gridout += "\n\n"; wgridout += "\n";
	}
	ifile << "\n***********  gridf  ***********\n";
	cout << "\n***********  gridf  ***********\n";
	
	ifile << gridout << endl;
	cout << gridout << endl;
	//SHOWb(gridout,ifile);
	ifile << " \n***********  workgrid  ***********\n";
	ifile << wgridout << endl;
	cout << " \n***********  workgrid  ***********\n";
	cout << wgridout << endl;
	//SHOWb(wgridout, ifile);
	ifile << " \n***********  Domains  ***********\n";
	ifile << workout << endl; 
	cout << " \n***********  Domains  ***********\n";
	cout << workout << endl;

	//SHOWb(workout, ifile);


}

static int MagnumbFrontiers_callcount = 0;
static int MagnumbFrontiers_guess[2] = { 0,0 };
static int MagnumbFrontiers_lastguess[2] = { 0,0 };
static int MagnumbFrontiers_lastcallcount = 0;
static int MagnumbFrontiers_guess_probability = 0;

void Magnumb_parse_guess() {
	//opus_flags_placed will need to be used here.  need to check that it's being tracked properly also.
	// this whole damn function should be calculated in other loops that already visit these places
	// probably in vla_reduce because the domains will be solidified by then
	//  this whole function is written just to get it to work and needs to be heavily optimized. 
	short lowprob = 100, hold;
	short tx, ty, tid=0;
	for (int i = 0; i < Domlistlen; i++) {
		if (Domlist[i].Assoclen == 0)continue;
		hold = (Domlist[i].value * 100) / Domlist[i].Assoclen;
		if (hold < lowprob) {
			lowprob = hold;
			tid = i;
		}
	
	}

	// try to remove lands split among other domains
	short t[8] = { 0,0,0,0,0,0,0,0 };
	short tindexmax = -1;
	for (int i = 0; i < Domlist[tid].Assoclen; i++) {
		for (int n = 0; n < Domlistlen; n++) {
			for (int ii = 0; ii < Domlist[n].Assoclen; ii++) {
				if (Domlist[n].Assocx[ii] == Domlist[tid].Assocx[ii]
					&& Domlist[n].Assocy[ii] == Domlist[tid].Assocy[ii]) {
					t[i]++;
					tindexmax = i;
				}
			}
		}
	}
	short lowtwo = 100, plc = -1;
	// find the associated land in the fewest domains. 
	if (tindexmax > -1) {
		for (int i = 0; i <= tindexmax; i++) {
			if (t[i] < lowtwo) {
				lowtwo = t[i];
				plc = i;
			}
		}
	}

	MagnumbFrontiers_guess[0] = Domlist[tid].Assocx[plc];
	MagnumbFrontiers_guess[1] = Domlist[tid].Assocy[plc];
	//MagnumbFrontiers_Cumulative_guess_assessment += lowprob;
	MagnumbFrontiers_guess_probability = lowprob;

}

bool MagnumbFrontiers(int callcount= MagnumbFrontiers_callcount) {
	MagnumbFrontiers_callcount++;
	Magnumb_Probecount = 0;
	Magnumb_Minecount = 0;
	// reset magnumbFrontiers grids and lists
	Magnumb_resetFrontiersArrays();

	// fill Workgrid using gridf from opus.h 
	Magnumb_FillWorkgrid();

	//MagnumbFrontiers_output(ctostr(callcount) + "_1afterworkgrid.txt");
	short id = 0;
	bool flag = false;
	//-------------- move this whole block into fill_workgrid because it's already visiting all these data points.
	for (int x = Magnumb_workbounds[0]; x <= Magnumb_workbounds[2]; x++) {
		for (int y = Magnumb_workbounds[1]; y <= Magnumb_workbounds[3]; y++) {// calculated workbounds for slightly faster parsing.
			//if (Magnumb_Workgrid[x][y] > 0 && Magnumb_Workgrid[x][y] < 7) {
			if(Magnumb_is_grid_number(Magnumb_Workgrid[x][y])){ 
				id = Magnumb_GetDomain(x, y); // create domain here and store ID
				
				
			}
		}
	}
	
	//MagnumbFrontiers_output(ctostr(callcount) + "_2afterdomains.txt");
	//flag =Magnumb_Reduce_Adj_numbers(id);
	//if (flag) return; // found a click.
	Magnumb_Check_Domain_Collision();
	//MagnumbFrontiers_output(ctostr(callcount) + "_3aftercollision.txt");
	Magnumb_find_probative_domains(); 
	//cout << "ProbeCount = " << Magnumb_Probecount << "\n";
	if (Magnumb_Probecount > 0) {
		did_this_game_magfrontier_collision = 1;
		return false;
	}
	//if (Magnumb_find_probative_domains())return true;
	Magnumb_do_VLA_reduce();
	if (Magnumb_Probecount>0) {
		did_this_game_magfrontier_VLA = 1;
		return false;
		//MagnumbFrontiers_output(ctostr(callcount) + "_4afterVLA.txt");
		//cout << "ProbeCount = " << Magnumb_Probecount << "\n";
	}
	else if(Magnumb_Minecount>0 ){

	}
	else {
		if (Domlistlen == 0) {
			//if flags_placed == all flags...?
			short t = 0;
			MagnumbFrontiers_guess[0] = -1;
			MagnumbFrontiers_guess[1] = -1;
			for (int i = 0; i < opus_sidesx; i++) {
				for (int n = 0; n < opus_sidesy; n++) {
					if (opusgridf[i][n] == GRIDF_VALUE_LAND) {
						MagnumbFrontiers_guess[0] = i;
						MagnumbFrontiers_guess[1] = n;
						t++;
					}
				}
			}
			if (MagnumbFrontiers_guess[0] == -1) {
				//cout << t<<":t   magnumb guess process didn't find any lands in gridf                       \r";
				MagnumbFrontiers_guess[0] = 1;  //uncommment for runner, comment for trainer.
				MagnumbFrontiers_guess[1] = 1;
				return false;
			}
			else {
				MagnumbFrontiers_guess_probability = opus_totalflags - opus_flags_placed / t;
			}
			//cout << "No domains, Guess going to random land left in gridf                \r";
			return false;
			//pause();
			// there are no domains, but there are lands left.  means all frontier lands are solved 
			// and only active lands left are totally surrounded by flags.  these are almost always edge lands
			// or 8s. 
			//select a random land from gridf.  
			// reported guess probability should be totalmines-opus_flags_placed / total lands in gridf.
			// do a study of random clicks in land masses and how often that leads to probative states
			// if only 1:3 random clicks give you more than a single number
			// or if 2 adjacent/semiadjacent clicks lead to probative states relatively often
			// use this data to weight the value of clicking a random square not in a domain.
		}
		//if VLA reduce ended with no probative values, board is in a state of required guess
		// parse through domains and Tdomains to find domain with lowest average chance
		// check each land and give a score-
		//   NL = number of lands adjacent
		//   NN = number of numbers adjacent on workgrid
		//   b  = Bool, true if land is split among multiple domains
		//   q  = bool, true if land is split among multiple Tdomains  ----this is a weird thing I'd like to record if it happens
		Magnumb_parse_guess();

	}
	return false;
}

/**********************************depreciated from linear solver. maybe useful later**************************
*
bool Magnumb_Reduce_Adj_numbers(short id) {
	//  search workgrid for numbers adj to lands in domain[id]
	int x = Domlist[id].x, y = Domlist[id].y;
	short hold = 0;
	for (int n = -1; n < 2; n++) {
		if (x + n < 0 || x + n >= opus_sidesx)continue;
		for (int i = -1; i < 2; i++) {
			if (y + i < 0 || y + i >= opus_sidesy)continue;
			if (!Magnumb_is_grid_number(Magnumb_Workgrid[x + n][y + i])) continue;
			for (int i = 0; i < Domlist[id].Assoclen; i++) {
				if (abs(Domlist[id].Assocx[i] - (x + n)) < 2 && abs(Domlist[id].Assocy[i] - (y + i)) < 2) {
					hold = (Magnumb_Workgrid[x + n][y + i]);//  calculate V-(l-a) for these numbers.
					if (hold < 1) {
						//  if <1, maybe associate adj land(s) to a domain at target number, or
					}
					else {//  if >0 reduce that number in work_grid
						short mid = Magnumb_finddomain(x + n, y + i);
						Domlist[mid].value -= hold;
						Magnumb_Workgrid[x + n][y + i] -= hold;
						//remove values in id.assoc from mid.assoc
						// //  if a number is reduced in this way, remove all lands in this domain[id] from that domain[n].
						// add my id to mid.effectedids
						//maybe recalculte reduction here

						return false;
					}

				}
			}
		}
	}
//  if number in workgrid after reduction is 0, all adj lands left in workgrid are safe return true;

	return false;
}
bool Magnumb_Recalculate_Reduction(short id,int & recurcount) {
	if (recurcount++ > 1000) {
		cout << "Mag_Recalculate_reduction: infinite recursion detected at id " << id << "\n";
		//output some more specialized info, maybe create a fileoutput method like opus has
		//I'm legitimately not sure if this is a thing I should be worried about.
		// I can therize a situation in which a loop of reduce,increase,reduce,increase would result in an infinite loop
		// but I can't figure out a single possible mineboard which would result in this situation
		// I suspect this would have to happen in an island that's all requisite guesses and 4 way symetry.
		//

	}
/*  parse through domain at ID, make sure all effecting domains still have sufficient V-(L-A) value
	if any effecting domain is found to have insufficient value to reduce, or less reduction than previously
		fix my effected array, reducing value or removing the node as nessessary
		fix my value as nessesary

	parse through IDs and find any IDs that reduce my value that aren't in effects list yet
	if any are found, add to effected list and reduce my value.

	if my value has changed from the start of the function
	  if value == number of lands, all flags?
	  if value == 0, all safe?

	  else find all IDs effected by me and reparse them

return false;
}
*/

