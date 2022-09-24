
#define MINEMATH_USE_EMU
#ifdef MINEMATH_USE_EMU

#define MM_emu_MINEBOARD_VALUE_MINE 9
#define MM_emu_MINEBOARD_VALUE_EMPTY 0
#define MM_emu_MINEBOARD_ISNUMBER(x,y)  (this.mineboard[x][y] >0 && this.mineboard[x][y] <9)
#include "valtimer.h"
#define MM_emu_BAD 99


#define MM_emu_ACTIVEBOARD_VALUE_OPEN 1
#define MM_emu_ACTIVEBOARD_VALUE_CLOSED 0
#define MM_emu_ACTIVEBOARD_VALUE_FLAGGED 2


#define MUTATE_fast_array_alter_extra_args 
#define MUTATE_fast_array_alter MME_fast_array_inc
#define iptf() (*ipt)++;
#include "mutate_fast_array_alter.h"

#define MUTATE_fast_array_alter MME_fast_array_dec
#define iptf() (*ipt)--;
#include "mutate_fast_array_alter.h"

int emu_danger_color[10] = { 3,11,9,1,10,6,2,12,4,13 };
string readstr(string q);
bool readbool(string q);
int readint(string q);


class MineMath_emulator {

public:
	unsigned char mineboard[MM_emu_BAD][MM_emu_BAD];
	unsigned int dangerboard[MM_emu_BAD][MM_emu_BAD];
	unsigned int stats_minetotals[MM_emu_BAD][MM_emu_BAD];
	unsigned char activeboard[MM_emu_BAD][MM_emu_BAD];
	unsigned short width = 0, height = 0;
	unsigned short total_mines = 0;
	unsigned int total_lands = 0;
	unsigned int lands_cleared = 0;
	int total_validate_changes = 0;
	int stats_totaldangerundermines = 0;

	MineMath_emulator(short w, short h,short count) {
		width = w; height = h;
		total_lands = h * w;
		total_mines = count;
		lands_cleared = 0;
		for (int i = 0; i < MM_emu_BAD; i++) {
			for (int n = 0; n < MM_emu_BAD; n++) {
				mineboard[i][n] = 0;
				dangerboard[i][n] = 0;
				stats_minetotals[i][n] = 0;
				activeboard[i][n] = 0;
			}
		}
	}

	char getCellValue(short x, short y) {
		if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_OPEN) {
			return dangerboard[x][y];
		}
		if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_FLAGGED)return 10;
		return 9;
	}

	bool checkWin() {
		return lands_cleared == total_lands - total_mines;
	}

	void reset() {
		for (int i = 0; i < width+3; i++) {
			for (int n = 0; n < height+3; n++) {
				mineboard[i][n] = 0;
				dangerboard[i][n] = 0;
				activeboard[i][n] = 0;
			}
		}
		lands_cleared = 0;
	}




	void play() {
		int x, y;
		reset();
		fill_mineboard5();
		while (1) {
			clrscr();
			output_active();
			x = readint("x");
			y = readint("y");
			x--;
			y--;
			if (x < 0 || x >= width) {
				cout << "valid x between 1 and " << width - 1 << "\n"; continue;
			}
			if (y < 0 || y >= height) {
				cout << "valid y between 1 and " << height - 1 << "\n"; continue;
			}
			if (!doClick(x, y)) {
				cout << "you lost\n";
				console_output();
				pause();
				reset();
				fill_mineboard5();
			}
			if (checkWin()) {
				cout << "you won\n";
				console_output();
				pause();
				reset();
				fill_mineboard5();
			}

		}

	}
	bool opencell(short x, short y) {
		if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_OPEN)return true;
		if (mineboard[x][y] == MM_emu_MINEBOARD_VALUE_MINE) return false;
		activeboard[x][y] = MM_emu_ACTIVEBOARD_VALUE_OPEN;
		lands_cleared++;
		if (dangerboard[x][y] == 0) {
			bool is_x_top = x < width - 1;
			bool is_y_top = y < height - 1;
			int ym = y - 1, yp = y + 1, xm = x - 1, xp = x + 1;
			//cascade open cells
			if (y > 0) {
			    opencell(x, ym);
				if (is_x_top) {
					opencell(xp, ym); 
				}
			}
			if (is_y_top)opencell(x, yp);
			if (x > 0) {
				if (y > 0) {
					opencell(xm, ym);
				}
				if (is_y_top) {
					opencell(xm, yp);
				}
				opencell(xm, y);
			}
			if (is_x_top) {
				if (is_y_top) {
					opencell(xp, yp);
				}
				opencell(xp, y);
			}

		}

		return true;
		

	}
	bool flagcell(short x, short y) {
		if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_OPEN)return false;
		if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_FLAGGED)
			activeboard[x][y] = MM_emu_ACTIVEBOARD_VALUE_CLOSED;
		else 	
			activeboard[x][y] = MM_emu_ACTIVEBOARD_VALUE_FLAGGED;
		return true;
	}

	bool doClick(short x, short y,bool flag=false) {
		if (activeboard[x][y]==MM_emu_ACTIVEBOARD_VALUE_CLOSED ) {//&& 
			if (flag) return flagcell(x, y);
			return opencell(x, y);
		}
		else if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_FLAGGED) {
			if (flag) activeboard[x][y] = MM_emu_ACTIVEBOARD_VALUE_CLOSED;
			else 
				cout << "can't open a flagged cell \n";
			return true;
		}
		return true;
	}

	

	
	bool setMine(short x, short y) {
	//	cout << "setMine x,y : " << x << ":" << y << "\n";
		if (mineboard[x][y] != MM_emu_MINEBOARD_VALUE_MINE && x < width && y < height && x >= 0 && y >= 0) {
			//increment dangerboard around here. 
			MME_fast_array_inc((int*)dangerboard, MM_emu_BAD, MM_emu_BAD, x, y, 1);
			mineboard[x][y] = MM_emu_MINEBOARD_VALUE_MINE;
			return true;
		}
		return false;
	}

	short get_maxd(short x, short y) {
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

	bool isDanger_max(short x, short y) {
		if (mineboard[x][y] == MM_emu_MINEBOARD_VALUE_MINE
			&& get_maxd(x, y) == dangerboard[x][y])    return true;
			
		return false;
	}

	void moveMine(short &x, short &y) {
		unsigned long long int randval;
		bool latch = true;
		short tx, ty;
		while (latch) {
			randval = G_VS_Rand3(G_VS_randMAX);
			for (int i = 0; i < 50; i++) {
				tx = randval % width;
				ty = (randval >> 4) % height;
				if (setMine(tx, ty)) {
					latch = false;
					break;
				}
			}
		}
		mineboard[x][y] = MM_emu_MINEBOARD_VALUE_EMPTY;
		MME_fast_array_dec((int*)dangerboard, MM_emu_BAD, MM_emu_BAD, x, y, 1);
		x = tx;
		y = ty;
	}

	bool validate2() {
		short total = 0;
		for (int i = 0; i < width; i++) {
			for (int x = 0; x < height; x++) {
				if (isDanger_max(i, x)) {
					total_validate_changes++;
					short xx = i, yy = x;
					moveMine(xx, yy);
					if (xx <= i && yy <= x) {
						total++;
						stats_minetotals[xx][yy]++;
					}
				}
				else {
					if (mineboard[i][x] == MM_emu_MINEBOARD_VALUE_MINE) {
						total++;
						stats_totaldangerundermines += dangerboard[i][x];
					}
					//total += (mineboard[i][x] == MM_emu_MINEBOARD_VALUE_MINE ? 1 : 0);

					stats_minetotals[i][x] += (mineboard[i][x] == MM_emu_MINEBOARD_VALUE_MINE ? 1 : 0);
				}
			}
		}
	//	cout << "total mines found : " << total << "\n";
		return total == total_mines;
	}
	bool validate() {
		short total = 0;
		for (int i = 0; i < width; i++) {
			for (int x = 0; x < height; x++) {

				if (mineboard[i][x] == MM_emu_MINEBOARD_VALUE_MINE) {
					total++;
					stats_totaldangerundermines += dangerboard[i][x];
					stats_minetotals[i][x]++;
					if (isDanger_max(i, x)) {
						// this is a surrounded mine. some systems move this.
						//use validate2 to move mines like this
						total_validate_changes++;
					}
				}
				//total += (mineboard[i][x] == MM_emu_MINEBOARD_VALUE_MINE ? 1 : 0);
			}
		}
		//	cout << "total mines found : " << total << "\n";
		return total == total_mines;
	}



	valVeryRandom VVRand;
#define absindex_toxy(ind,x,y) x=ind%width; y=ind/width; 
	void fill_mineboard_seeded(string seed) {
		VVRand.build(seed);
	}
	void fill_mineboard_seeded1() {

		short x = 0, y = 0;
		unsigned long long int randval;
		short minesset = 0;

		randval = VVRand.next();
		x = randval % width;
		y = (randval >> 4) % height;
		while (minesset < total_mines) {
			randval = VVRand.next();
			for (int n = 0; n < 15 && minesset < total_mines; n++) {
				x += randval & (0x1111111111111111);

				y += x / width;
				x = x % width;
				y = y % height;

				randval = randval >> 3;//16
				if (setMine(x, y))minesset++;
			}
		}
	}
	void fill_mineboard_seeded1_2() {

		unsigned short x = 0, y = 0;
		unsigned long long int randval;
		short minesset = 0;

		//randval = VVRand.next();
		//x = randval % width;
		//y = (randval >> 4) % height;
		while (minesset < total_mines) {
			randval = VVRand.next();

			x += randval & (0x1111111111111111);

			y += x / width;
			x = x % width;
			y = y % height;


			if (setMine(x, y))minesset++;

		}
	}

	void fill_mineboard_seeded1_1() {

		short x = 0, y = 0;
		unsigned long long int randval;
		short minesset = 0;
		short ind = 0;
		randval = VVRand.next();
		x = randval % width;
		y = (randval >> 4) % height;
		while (minesset < total_mines) {
			randval = VVRand.next();
			for (int n = 0; n < 6 && minesset < total_mines; n++) {
				ind = randval % total_lands;
				absindex_toxy(ind, x, y);
				randval = randval >> 8;//16
				if (setMine(x, y))minesset++;
			}
		}
	}

	void fill_mineboard_seeded2() {

		short x = 0, y = 0;
		unsigned long long int randval=0;
		short minesset = 0;
		while (minesset < total_mines) {
			randval = VVRand.next();
			//x = (randval & (4194304)) % width;
			x = randval % width;
			//randval = randval >> 8;
			//y = (randval & (4194304)) % height;
			randval = VVRand.next();
			y = (randval) % height;
			if (setMine(x, y))minesset++;

		}
	}
	void fill_mineboard5() {

		short x = 0, y = 0;
		unsigned long long int randval;
		short minesset = 0;

		randval = G_VS_Rand3(G_VS_randMAX);
		x = randval % width;
		y = (randval >> 4) % height;
		while (minesset < total_mines) {
			randval = G_VS_Rand3(G_VS_randMAX);
			for (int n = 0; n < 24 && minesset < total_mines; n++) {
				x += randval & (0x1111);
				if (x >= width) {
					y += x / width;
					x = x % width;
					if (y >= height)y = y % height;
				}
				randval = randval >> 2;
				if (setMine(x, y))minesset++;
			}
		}
	}
	void fill_mineboard8() {

		short x = 0, y = 0;
		unsigned long long int randval;
		short minesset = 0;

		randval = G_VS_Rand3(G_VS_randMAX);
		x = randval % width;
		y = (randval >> 5) % height;
		while (minesset < total_mines) {
			randval = G_VS_Rand3(G_VS_randMAX);
			for (int n = 0; n < 18 && minesset < total_mines; n++) {
				x += randval & (0x11111111);
				if (x >= width) {
					y += x / width;
					x = x % width;
					if (y >= height)y = y % height;
				}
				randval = randval >> 3;
				if (setMine(x, y))minesset++;
			}
		}
	}

	void fill_mineboard_spaced2() {
		unsigned short spaces[2000];
		short val = total_lands / total_mines;
		short mval = (total_lands % total_mines )+val;
		if (mval < 5) {
			val--;
			mval += total_mines;
		}
		//val*=7;
		val += width;
		unsigned long long int randval;
		for (int i = 0; i < (total_lands *3); i++) {
			spaces[i] = val;
		}
		short x=0, y=0;
		short spacex = 0;
		//mval *= 7;
		mval = total_lands * 2;
		while (mval > 0) {
			randval = G_VS_Rand3(G_VS_randMAX);
			//spacex = randval % total_mines;
			for (int n = 0; n < 24 && mval>0; n++) {
				spacex += randval & 63;
				if (spacex >= (total_lands * 2))spacex %= total_lands * 2;
				randval = randval >> 2;
				spaces[spacex]++;
				mval--;

			}
			 
		}	
		spacex = spacex >> 1;
		absindex_toxy(spacex, x, y);
		short minesset = 0;
		short i = 0;
		while(minesset != total_mines && i < total_mines*2){
			x += spaces[i++];
			if (x >= width) {
				y += x / width;
				x = x % width;
				if (y >= height)y = y % height;
			}
			if (setMine(x, y))minesset++;
		}


	}
	void fill_mineboard_spaced() {
		unsigned short spaces[2000];
		short val = 13;
		short mval = total_mines*3;
		unsigned long long int randval;
		for (int i = 0; i < (total_lands * 2); i++) {
			spaces[i] = val;
		}

		short x = 0, y = 0;
		short spacex = 0;
		while (mval > 0) {
			randval = G_VS_Rand3(G_VS_randMAX);
			//spacex = randval % total_mines;
			for (int n = 0; n < 24 && mval>0; n++) {
				spacex += randval & 31;  //64
				if (spacex >= (total_lands))spacex %= total_lands;
				randval = randval >> 2;
				spaces[spacex] += (randval & 1 ? 1 : -2);
				spacex += spaces[spacex];
				mval--;

			}

		}
		
		absindex_toxy(spacex, x, y);
		short minesset = 0;
		short i = 0;
		while (minesset != total_mines ) {
			x += spaces[i++];
			if (x >= width) {
				y += x / width;
				x = x % width;
				if (y >= height)y = y % height;
			}
			if (setMine(x, y))minesset++;
			if (i >= total_mines * 2) i = 0;
		}
	}
	void rotate_Mineboard_Right(short num) {
		num %= total_lands;
		int tempboard[MM_emu_BAD][MM_emu_BAD];
		CopyMemory( (((int*)tempboard)) +(sizeof(int)*num) , mineboard, sizeof(int) * (MM_emu_BAD * MM_emu_BAD));
		short x = 0, y = 0;
		for (int i = 0; i < num; i++) {
			absindex_toxy(i, x, y);
			tempboard[x][y] = mineboard[width - x][height - y];
		}
		CopyMemory(tempboard, mineboard, sizeof(int) * (MM_emu_BAD * MM_emu_BAD));
	}

	void slide_mineboard_right() {
		short temp;
		for (int i = 0; i < height; i++) {
			temp = mineboard[0][i];
			for (int n = 0; n < width-1; n++) {
				mineboard[n][i] = mineboard[n + 1][i];
			}
			mineboard[width - 1][i] = temp;
		}

	}
	void slide_mineboard_down() {
		short temp;
		for (int i = 0; i < width; i++) {
			temp = mineboard[i][0];
			for (int n = 0; n < height - 1; n++) {
				mineboard[i][n] = mineboard[i][n+1];
			}
			mineboard[i][height-1] = temp;
		}

	}
	void slide_mineboard_up() {
		short temp;
		for (int i = 0; i < width; i++) {
			temp = mineboard[i][height-1];
			for (int n = height-1; n >0; n--) {
				mineboard[i][n] = mineboard[i][n - 1];
			}
			mineboard[i][0] = temp;
		}

	}
	void slide_mineboard_left() {
		int temp=0;
		for (int i = 0; i < height; i++) {
			temp = mineboard[width-1][i];
			for (int n = width-1; n >0; n--) {
				mineboard[n][i] = mineboard[n - 1][i];
			}
			mineboard[0][i] = temp;
		}

	}
	void fix_danger() {
		for (int i = 0; i < width ; i++) {
			for (int n = 0; n < height ; n++) {
				dangerboard[i][n] = 0;
			}
		}
		for (int i = 0; i < width; i++) {
			for (int n = 0; n < height; n++) {
				if (mineboard[i][n] == MM_emu_MINEBOARD_VALUE_MINE) {
					//increment dangerboard around here. 
					MME_fast_array_inc((int*)dangerboard, MM_emu_BAD, MM_emu_BAD, i, n, 1);
				}
			}
		}


	}
	void fill_mineboard_bunched() {
		unsigned short spaces[2000];
		short val = 67;//9 //14
		short mval = total_mines * 2;
		unsigned long long int randval;
		for (int i = 0; i < (total_lands * 2); i++) {
			spaces[i] = val;
		}

		short x = 0, y = 0;
		short spacex = 0;
		while (mval > 0) {
			randval = G_VS_Rand3(G_VS_randMAX);
			//spacex = randval % total_mines;
			for (int n = 0; n < 40 && mval>0; n++) {
				spacex += randval & 255;// 1,2 
				if (spacex >= (total_lands))spacex %= total_lands;
				randval = randval >> 1;
				spaces[spacex] += (randval & 1 ? 1 : -3);
				spaces[spacex] = (spaces[spacex] < 0 ? 0 : spaces[spacex]);
				//spacex += spaces[spacex];
				mval--;

			}
			spacex = spacex << 1;

		}
		spacex += randval & 127;
		absindex_toxy(spacex, x, y);
		short minesset = 0;
		short i = 0;
		short xmod, ymod;
		short stopvalinc = total_mines / 6;
		short stopval = stopvalinc;
		do {
			while (minesset != stopval) {
				if (randval < 100000000) randval = G_VS_Rand3(G_VS_randMAX);
				x += spaces[i++];
			
				if (x >= width) {
					y += x / width;
					x = x % width;
					if (y >= height)y = y % height;
				}
				xmod = (randval & 3) - 2; ymod = ((randval >> 2) & 3) - 2;
				randval = randval >> 4;
				if (setMine(x, y))minesset++;
				if ((minesset == stopval))break;

				xmod = (randval & 3) - 2; ymod = ((randval >> 2) & 3) - 2;
				randval = randval >> 2;
				if (setMine(x + xmod, y + ymod))minesset++;
				if (i >= total_mines * 2) i = 0;
			}
			stopval += stopvalinc;
			if(stopval > total_mines) stopval = total_mines;
			for (int b = 0; b < ((randval & 7) % 4)+1; b++) {
				slide_mineboard_left();
				slide_mineboard_up();
			}
			
		} while (minesset != total_mines);
		fix_danger();
	}


	void fill_mineboard_reallife() {
		unsigned short spaces[2000];
		short val = 6; //14
		short mval = total_mines * 2;
		unsigned long long int randval;
		for (int i = 0; i < (total_lands * 2); i++) {
			spaces[i] = val;
		}

		short x = 0, y = 0;
		short spacex = 0;
		while (mval > 0) {
			randval = G_VS_Rand3(G_VS_randMAX);
			//spacex = randval % total_mines;
			for (int n = 0; n < 40 && mval>0; n++) {
				spacex += randval & 127;// 1,2 
				if (spacex >= (total_lands))spacex %= total_lands;
				randval = randval >> 1;
				spaces[spacex] += (randval & 1 ? 1 : -3);
				spaces[spacex] = (spaces[spacex] < 0 ? 0 : spaces[spacex]);
				//spacex += spaces[spacex];
				mval--;
			}
			spacex = spacex << 1;
		}
		absindex_toxy(spacex, x, y);
		short minesset = 0;
		short i = 0;
		short xmod, ymod;
		while (minesset != total_mines) {
			if (randval < 100000000) randval = G_VS_Rand3(G_VS_randMAX);
			x += spaces[i++];
			if (x >= width) {
				y += x / width;
				x = x % width;
				if (y >= height)y = y % height;
			}
			
			if (setMine(x, y))minesset++;
			if ((minesset == total_mines))break;

			xmod = (randval & 3) - 2; ymod = ((randval >> 2) & 3);
			randval = randval >> 2;
			//if (xmod == 0)continue;
			if (setMine(x + xmod, y + ymod))minesset++;
			if ((minesset == total_mines) || randval & 8)continue;

			/*xmod = (randval & 3); ymod = ((randval >> 2) & 3) - 1;
			randval = randval >> 2;
			if (setMine(x + xmod, y + ymod))minesset++;
			if ((minesset == total_mines) || randval & 8)continue;*/

			if (i >= total_mines * 2) i = 0;
		}
	}

	void console_output() {

		for (int i = 0; i < height; i++) {
			for (int n = 0; n < width; n++) {
				if (mineboard[n][i] == MM_emu_MINEBOARD_VALUE_EMPTY) {
					cout << "   ";
				}else if (mineboard[n][i] == MM_emu_MINEBOARD_VALUE_MINE) {
					cout << " * ";
				}
				else
				cout << " " << mineboard[n][i] << " ";
			}
			cout << "\n";
		}
		cout << "\n\n\n\n\nDanger\n";
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < height; i++) {
			for (int n = 0; n < width; n++) {
					SetConsoleTextAttribute(hStdout, emu_danger_color[dangerboard[n][i]]);
					cout << " " << dangerboard[n][i] << " ";
					SetConsoleTextAttribute(hStdout, 7);
			}
			cout << "\n";
		}
	}
	void console_output_stats() {
		for (int i = 0; i < height; i++) {
			for (int n = 0; n < width; n++) {

				cout << " " << stats_minetotals[n][i] << " ";
			}
			cout << "\n";
		}

	}
	void output_active() {
		WORD atrs[8] = { 7,1,10,12,4,5,13,11 };
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "    1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30  \n";
		for (int y = 0; y < height; y++) {
			cout << y + 1 << " ";
			if (y < 9)cout << " ";

			for (int x = 0; x < width; x++) {
				if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_OPEN) {
					if (dangerboard[x][y] > 0) {
						SetConsoleTextAttribute(hStdout, atrs[dangerboard[x][y]]);
						cout << " " << dangerboard[x][y] << " ";
						SetConsoleTextAttribute(hStdout, atrs[0]);
					}
					else cout << "   ";
				}
				else {
					cout << " # ";
				}
			}
			cout << "\n\n";
		}


	}
	void output_validate_stats() {
		int lowminetot = stats_minetotals[0][0], himinetot = stats_minetotals[0][0];
		long int runningtotal = 0;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (stats_minetotals[x][y] > himinetot)himinetot = stats_minetotals[x][y];
				if (stats_minetotals[x][y] < lowminetot) lowminetot = stats_minetotals[x][y];
				runningtotal += stats_minetotals[x][y];
			}
		}
		int tavg = runningtotal / (height * width), ttot = 0;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				ttot += abs((int)(tavg - stats_minetotals[x][y]));
			}
		}

		cout << "lowest freq: " << lowminetot << "\n highest freq: " << himinetot << "\naverage: " << tavg << "\n";
		cout << "avg deviation from mean: " << ttot / (height * width) << "\n";
	}
	void tofile_mbf(string fname) {
		ofstream ofile(fname.c_str(), ios::binary);
		char temp;
		temp = width;
		ofile << temp;
		temp = height;
		ofile << temp;
		temp = total_mines / 256;
		ofile << temp;
		temp = total_mines % 256;
		ofile << temp;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (mineboard[x][y] == MM_emu_MINEBOARD_VALUE_MINE) {
					temp = x;
					ofile << temp;
					temp = y;
					ofile << temp;
				}
			}
		}
		ofile.close();

	}

	void tofile_dotmine(string fname) {
		ofstream ofile(fname.c_str());
		ofile << width << "x" << height << "x" << total_mines << "\n";
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_FLAGGED)ofile << "F";
				else if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_OPEN) {
					ofile << dangerboard[x][y];
				}
				else ofile << "H";
			}
			ofile << "\n";
		}
		ofile.close();
	}

};

#endif

/*  first attempts at generators

	//void *alloca(size_t size); look into
	void fill_mineboard4() {
		unsigned short spaces[2000];//total_mines + 1  fuck not having VLAs. 
		//ZeroMemory(spaces, sizeof(unsigned short) * (total_mines + 1));
		for (int i = 0; i < 2000; i++)spaces[i] = 0;
		short total_cells = (width * height);
		short total_lands = total_cells - total_mines;
		short x, y=0;
		unsigned long long int randval;
		unsigned short ind;
		short spacesplaces = 0;
		int indspace = 0;
		for (int i = 0; i < total_mines ; i++) {
			randval = G_VS_Rand3(G_VS_randMAX);
			for (int n = 0; n < 11 && i < total_mines; n++) {
				spaces[i] = randval & 3;
				spacesplaces += spaces[i];
				randval = randval >> 2;
				indspace = (indspace | (randval & 1)) << 1;
				i++;
			}
		}
		short tval;
		while (spacesplaces != total_lands) {
			//cout << "looping spacesplaces 1\n";
			while (spacesplaces > total_lands) {
				randval = G_VS_Rand3(G_VS_randMAX);
				//cout << "looping spacesplaces 2\n";
				for (int n = 0; n < 3 && spacesplaces > total_lands; n++) {
					ind = randval % (total_mines);
					randval=randval >> 8;
					//tval = (randval & 1 ? 2 : 1);
					tval = 1;
					spaces[ind] -= tval;
					spacesplaces -= tval;
					randval = randval >> 1;
					
				}
			}
			while (spacesplaces < total_lands) {
				randval = G_VS_Rand3(G_VS_randMAX);
				//cout << "looping spacesplaces 3\n";
				for (int n = 0; n < 3 && spacesplaces < total_lands; n++) {
					ind = randval % (total_mines);
					randval = randval >> 8;
					//tval = (total_lands - spacesplaces > 1 ? (randval & 1 ? 2 : 1) : 1);
					tval = 1;
					spaces[ind] +=  tval;
					spacesplaces += tval;
					//cout << "looping spacesplaces 3.1 "<<tval<<"\n";
					randval = randval >> 1;
				}
			}
		}
		randval = G_VS_Rand3(G_VS_randMAX);
		indspace = randval % total_mines;
		y = randval % height;
		//indspace %= total_mines;
		ind = spaces[indspace];
		short minesset = 0;
	//	cout << "going into setloop ind=" << ind << "indspace: "<<indspace<<" \n";
		for (int i = indspace+1; i < total_mines +1; i++) {
			if (ind >= width) {
				y += ind / width;
				ind = ind % width;
				y = (y >= height ? 0 : y);
			}
			setMine(ind, y);
			minesset++;
			ind += spaces[i]+1;
		//	cout << "looping setloop1 ind=" << ind << "\n";
			
		}
		for (int i = 0; i < indspace ; i++) {
			if (ind >= width) {
				y += ind / width;
				ind = ind % width;
				y = (y >= height ? 0 : y);
			}
			setMine(ind, y);
			minesset++;
			ind += spaces[i]+1;
			//cout << "looping setloop2 ind=" << ind << "\n";
		}

		//if (y != height && ind != width) {
		//	cout << "some failure, x,y != width,height : "<<ind << ":" <<y << "\n";
		//	pause();
		//}
if (minesset != total_mines) {
	cout << "some failure, mineset != total_mines : " << minesset << " : " << total_mines << "\n";
	pause();
}

	}

	void fill_mineboard3() {
		short x, y;
		unsigned long long int randval;
		short ind;
		short total_lands = width * height;
		short count = 0;
		while (count < total_mines) {
			randval = G_VS_Rand3(G_VS_randMAX);
			for (int i = 0; i < 3; i++) {
				ind = randval & 65535;
				ind %= total_lands;
				absindex_toxy(ind, x, y);
				randval = randval >> 16;
				if (setMine(x, y))count++;

			}
		}

	}

	void fill_mineboard2() {
		short bitlen = 1;
		short bitswing = 1;
		short temp = (width > height ? width : height), count = 0;
		unsigned long long int randval;
		short x, y;
		while (bitlen < temp) {
			bitlen *= 2;
			bitswing++;
		}
		unsigned short reps = 64 / bitswing;
		short xmodi = (bitlen - width);// / 2;
		short ymodi = (bitlen - height);// / 2;
		while (count < total_mines) {
			randval = G_VS_Rand3(G_VS_randMAX);
			for (int i = 0; i < reps; i++) {
				temp = randval & bitlen;
				x = (temp - xmodi) % width;
				randval = randval >> bitswing;
				y = (temp - ymodi) % height;
				randval = randval >> bitswing;
				if (mineboard[x][y] != MM_emu_MINEBOARD_VALUE_MINE) {
					mineboard[x][y] = MM_emu_MINEBOARD_VALUE_MINE;
					count++;
				}
			}
		}
	}


	void fill_mineboard1() {
		//	unsigned BYTE bitmask = 15; //00001111
		unsigned long long randval = 0;
		unsigned short x = 0, y = 0;
		int spaces = width * height;
		int count = 0;
		for (int i = 0; i < spaces; i++) {
			randval = G_VS_Rand3(G_VS_randMAX);
			randval = ((randval << 4) >> 8);
			for (int n = 0; n < 58 && i < spaces; n++) {
				mineboard[x][y] = ((randval & 1) * MM_emu_MINEBOARD_VALUE_MINE);
				if (mineboard[x][y])count++;

				randval = randval >> 1;
				if (++x == width) {
					y++;
					x = 0;
				}
				i++;
			}
		}
		unsigned char temp = 0;
		while (count > total_mines) {
			randval = G_VS_Rand3(G_VS_randMAX);
			for (int i = 0; i < 4; i++) {
				temp = randval & 255;
				x = temp % width;
				randval = randval >> 8;
				y = temp % height;
				randval = randval >> 8;
				if (mineboard[x][y] == MM_emu_MINEBOARD_VALUE_MINE) {
					mineboard[x][y] = MM_emu_MINEBOARD_VALUE_EMPTY;
					count--;
				}
			}
		}
		while (count < total_mines) {
			randval = G_VS_Rand3(G_VS_randMAX);
			for (int i = 0; i < 4; i++) {
				temp = randval & 255;
				x = temp % width;
				randval = randval >> 8;
				y = temp % height;
				randval = randval >> 8;
				if (mineboard[x][y] != MM_emu_MINEBOARD_VALUE_MINE) {
					mineboard[x][y] = MM_emu_MINEBOARD_VALUE_MINE;
					count++;
				}
			}
		}
	}
		void fill_mineboard_spaced_b() {
		unsigned short spaces[2000];
		short val = total_lands / total_mines;
		short mval = (total_lands % total_mines);
		if (mval < 5) {
			val--;
			mval += total_mines;
		}
		val++;
		mval *= 2;
		mval += (total_mines / 2);
		val = 13;
		unsigned long long int randval;
		for (int i = 0; i < (total_lands * 3); i++) {
			spaces[i] = val;
		}
		short x = 0, y = 0;
		short spacex = 0;
		//mval *= 7;
		//mval = total_lands * 2;
		while (mval > 0) {
			randval = G_VS_Rand3(G_VS_randMAX);
			//spacex = randval % total_mines;
			for (int n = 0; n < 24 && mval>0; n++) {
				spacex += randval & 31;  //64
				if (spacex >= (total_lands ))spacex %= total_lands ;
				randval = randval >> 2;
				spaces[spacex]++;
				spaces[spacex] += (randval & 1 ? 0 : -2);
				mval--;

			}

		}
		//spacex = spacex >> 1;
		absindex_toxy(spacex, x, y);
		short minesset = 0;
		short i = 0;
		while (minesset != total_mines && i < total_mines * 2) {
			x += spaces[i++];
			if (x >= width) {
				y += x / width;
				x = x % width;
				if (y >= height)y = y % height;
			}
			if (setMine(x, y))minesset++;
		}
	}
	*/