int opus_grid_insert_fast(int x, int y, int value){
	if(value==GRID_VALUE_BOMB){
		opus_bombcount++;
	}
	int hold = opusgrid[x][y];
	if(hold==GRID_VALUE_FLAG) return -3;
	if(value==hold)return -1;
	
	// all changes should be land->space or Land->number
	opusgrid[x][y] = value;
	fast_array_dec((int*)opusdanger,BAD,BAD,x,y,1);
	// if empty space 
	if(value==GRID_VALUE_SPACE){
	   opusgridf[x][y]=-1;
	   return -2;
	}
	//if is a new number set flag normalized value in gridf

 	
 	opusgridf[x][y] = value-opusflags[x][y];;
 	//if(value==0) ; // add to 'attention' list 
 	return 1;
}

		// adds danger and flags pointers
#define MUTATE_fast_array_alter_extra_args ,int * dan, int* fla
#define MUTATE_fast_array_alter opus_flags_fast_m
#define iptf()  ((*ipt>0 && *ipt<8) ? *ipt-- : 0); (*dan--); (*fla++);
#define iptinc() ipt++; dan++; fla++;
#define iptjmp(n) ipt+= n; dan+=n; fla+=n
#include "mutate_fast_array_alter2.h"
		void opus_flags_fast(int x, int y){
			if(opusgrid[x][y]==0){
				opusFound_mine_or_click=true;
				opusgrid[x][y] = GRID_VALUE_FLAG;
				opusgridf[x][y] = GRIDF_VALUE_FLAG;
				opus_flags_fast_m((int*)opusgridf,BAD,BAD,x,y,1,(int*)opusdanger,(int*)opusflags);
			}
		}
		
		void opus_add_flags_fast(int x, int y){
			// turns lands into flags around xy exclusive.
			
			bool is_x_top = x<opus_sidesx-1;
			bool is_y_top = y<opus_sidesy-1;
			int ym=y-1, yp=y+1,xm=x-1,xp=x+1;
				if(y>0){
					opus_flags_fast(x,ym);
					if(is_x_top){
						opus_flags_fast(xp,ym);
					}
				}
				if(is_y_top){
					opus_flags_fast(x,yp);
				}	
			if(x>0){
			    if(y > 0){
					opus_flags_fast(xm,ym);
				}
				if(is_y_top){
					opus_flags_fast(xm,yp);
				}
				
				opus_flags_fast(xm,y);
			}
			if(is_x_top){
				if(is_y_top){
				 	opus_flags_fast(xp,yp);
				 	
				}
				opus_flags_fast(xp,y);
			}
				
		}
