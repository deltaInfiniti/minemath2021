/*          Mutate_fast_array_alter.h
  	mutating function for altering 2d array around target tx,ty
  	add and change the below defines, change to suit your needs.  
  	first changes the function name, iptf changes what is done to affected squares (and ternary checks)
  	*/

// #define OPUS_MUTATE_ParselessFlow   your_func_name
// #define OM_PF_operate(bitpattern,tx,ty)  // your action per adj node
// #define OM_PF_walk(distance)  // change the walk semantics, why... who knows but it's here.
//#define OPUS_MUTATE_ParselessFlow_extra_args // don't think this is nessesary for minesweeper parseless either.

/*              format for 15:switch cases
                ipt += ((tx - 1) * (ymax)) + ty - 1;
				OM_PF_operate(bitpattern, tx-1, ty-1); ipt++;
				OM_PF_operate(bitpattern, tx, ty-1); ipt++;
				OM_PF_operate(bitpattern, tx+1, ty-1);
				ipt += ymax - 2;//ipt=&arr[tx][ty-1]; //top/bottom
				OM_PF_operate(bitpattern, tx-1, ty); ipt += 2;
				OM_PF_operate(bitpattern, tx+1, ty);
				ipt += ymax - 2;//ipt=&arr[tx+1][ty-1];//right
				OM_PF_operate(bitpattern, tx-1, ty+1); ipt++;
				OM_PF_operate(bitpattern, tx, ty+1); ipt++;
				OM_PF_operate(bitpattern, tx+1, ty+1);
*/

void OPUS_MUTATE_ParselessFlow(int * ipt, int *basept, int xmax, int ymax, int tx, int ty, char bitpattern  OPUS_MUTATE_ParselessFlow_extra_args){  
//	BYTE bt = ((((((tx>0) << 1 )| (ty>0)) << 1)| (tx<xmax-1)) << 1)| (ty<ymax-1);

	switch(bitpattern){ 
		case 15:// 1111 all ok, target is not an edge, 
			
			BYTE bt = ((((((tx>1) << 1 )| (ty>1)) << 1)| (tx<xmax-2)) << 1)| (ty<ymax-2);
			switch (bt) {

			case 15:
				
				ipt += ((tx - 1) * (ymax)) + ty - 1;
				OM_PF_operate(15, tx, ty); ipt++;
				OM_PF_operate(15, tx, ty); ipt++;
				OM_PF_operate(15, tx, ty);
				ipt += ymax - 2;//ipt=&arr[tx][ty-1]; //top/bottom
				OM_PF_operate(15, tx, ty); ipt += 2;
				OM_PF_operate(15, tx, ty);
				ipt += ymax - 2;//ipt=&arr[tx+1][ty-1];//right
				OM_PF_operate(15, tx, ty); ipt++;
				OM_PF_operate(15, tx, ty); ipt++;
				OM_PF_operate(15, tx, ty);
			break;
			}

		break;


		case 3: // 0011  this is 0,0
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt+= ymax-1;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
			
		break;
		case 12: // max max
			ipt+= (ymax*xmax)-(ymax+2);
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt+=ymax-1;
			 OM_PF_operate(bitpattern,tx,ty); 
		break;
		case 6: // 0, max
			ipt += ymax-2;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt += ymax;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
		break;
		case 9:// max 0
			ipt += ymax*(xmax-2);
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt+=ymax;
			 OM_PF_operate(bitpattern,tx,ty);
		break;
		case 11:// ok, 0
			ipt+= (tx-1) * ymax;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt += ymax;
			 OM_PF_operate(bitpattern,tx,ty); 
			ipt+= ymax-1;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
		break;
		case 14: // ok max
			ipt+= ((tx-1) * ymax)+(ymax-2);
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt += ymax-1;
			 OM_PF_operate(bitpattern,tx,ty); 
			ipt+= ymax;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
		break;
		case 13: 			// max ok
			ipt += (xmax-2)*ymax + (ty-1);
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			ipt+=ymax-3 ;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt+=2;
			 OM_PF_operate(bitpattern,tx,ty);

		break;
		case 7: // 0 ok
			ipt += ty-1;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt+=2;
			 OM_PF_operate(bitpattern,tx,ty);
			
			ipt += ymax-2;
			 OM_PF_operate(bitpattern,tx,ty);
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);	
			ipt++;
			 OM_PF_operate(bitpattern,tx,ty);	
			
		break;
	};
	
}
#undef iptf
//#undef MUTATE_fast_array_alter_extra_args
#undef MUTATE_fast_array_alter 
