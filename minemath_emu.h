
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


int emu_danger_color[10] = { 3,11,9,1,10,6,2,12,4,13 };
string readstr(string q) {
	cout << q << "==>";
	string var;
	getline(cin, var);
	return var;
}
bool readbool(string q) {
	string r = "";
	while (r != "y" && r != "n") {
		cout << q << "(y/n)==>";
		getline(cin, r);
	}
	return (r == "y");
}
int readint(string q) {
	string s = readstr(q);
	return ctoint(s);
}

class MineMath_emulator {

	unsigned char activeboard[MM_emu_BAD][MM_emu_BAD];
	unsigned char mineboard[MM_emu_BAD][MM_emu_BAD];
	unsigned int dangerboard[MM_emu_BAD][MM_emu_BAD];
	unsigned int stats_minetotals[MM_emu_BAD][MM_emu_BAD];
public:
	unsigned short width = 0, height = 0;
	unsigned short total_mines = 0;
	unsigned int total_lands = 0;
	unsigned int lands_cleared = 0;

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
		ofile << width << "x" << height << "x" << total_mines<<"\n";
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

	bool doClick(short x, short y,bool flag=false) {
		if (activeboard[x][y]==MM_emu_ACTIVEBOARD_VALUE_CLOSED ) {//&& 
			return opencell(x, y);
		}
		else if (activeboard[x][y] == MM_emu_ACTIVEBOARD_VALUE_FLAGGED) {
			cout << "can't open a flagged cell \n";
			return true;
		}
		return true;
	}



	
	bool setMine(short x, short y) {
	//	cout << "setMine x,y : " << x << ":" << y << "\n";
		if (mineboard[x][y] != MM_emu_MINEBOARD_VALUE_MINE && x < width && y < height) {
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
		x = tx;
		y = ty;
	}
	int total_validate_changes = 0;
	bool validate() {
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
					total += (mineboard[i][x] == MM_emu_MINEBOARD_VALUE_MINE ? 1 : 0);
					stats_minetotals[i][x] += (mineboard[i][x] == MM_emu_MINEBOARD_VALUE_MINE ? 1 : 0);
				}
			}
		}
	//	cout << "total mines found : " << total << "\n";
		return total == total_mines;
	}

#define absindex_toxy(ind,x,y) x=ind%width; y=ind/width; 
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
		for (int i = 0; i < height; i++) {
			for (int n = 0; n < width; n++) {
				
					cout << " " << dangerboard[n][i] << " ";
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
	*/