/*          Mutate_fast_array_alter.h
  	mutating function for altering 2d array around target tx,ty
  	add and change the below defines, change to suit your needs.  
  	first changes the function name, iptf changes what is done to affected squares (and ternary checks)
  	*/

// #define MUTATE_fast_array_alter your_func_name
//#define iptf() *ipt+=val;  // (*ipt==0?*ipt=val:0);
//#define MUTATE_fast_array_alter_extra_args 
//#define iptinc() ipt++
//#define iptjmp(n) ipt+= n

void MUTATE_fast_array_alter(int * ipt, int xmax, int ymax, int tx, int ty, int val MUTATE_fast_array_alter_extra_args){  //  working. make mutable
	// ipt is pointer to 2d array cast.   xmax is dim of array[x][],  ymax is dim of array[][y], tx:ty is target to alter around, val is value to alter 
	BYTE bt = ((((((tx>0) << 1 )| (ty>0)) << 1)| (tx<xmax-1)) << 1)| (ty<ymax-1);
	//if(!addsub)val=val*-1;
	//ipt=(int*)arr;
	switch(bt){ 
		case 15:
			// 1111 all ok
			//ipt=&arr[tx-1][ty-1];//left
			iptjmp(((tx-1)*(ymax))+ty-1);
			iptf();iptinc();
			iptf();iptinc();
			iptf();
			iptjmp(ymax-2);//ipt=&arr[tx][ty-1]; //top/bottom
			iptf();iptjmp(2); 
			iptf();
			iptjmp(ymax-2);//ipt=&arr[tx+1][ty-1];//right
			iptf();iptinc();
			iptf();iptinc();
			iptf();
		break;
		case 3: // 0011  this is 0,0
			iptinc();
			iptf();
			iptjmp( ymax-1);
			iptf();
			iptinc();
			iptf();
			
		break;
		case 12: // max max
			iptjmp( (ymax*xmax)-(ymax+2));
			iptf();
			iptinc();
			iptf();
			iptjmp(ymax-1);
			iptf(); 
		break;
		case 6: // 0, max
			iptjmp(ymax-2);
			iptf();
			iptjmp(ymax);
			iptf();
			iptinc();
			iptf();
		break;
		case 9:// max 0
			iptjmp(ymax*(xmax-2));
			iptf();
			iptinc();
			iptf();
			iptjmp(ymax);
			iptf();
		break;
		case 11:// ok, 0
			iptjmp((tx-1) * ymax);
			iptf();
			iptinc();
			iptf();
			iptjmp(ymax);
			iptf(); 
			iptjmp(ymax-1);
			iptf();
			iptinc();
			iptf();
		break;
		case 14: // ok max
			iptjmp( ((tx-1) * ymax)+(ymax-2));
			iptf();
			iptinc();
			iptf();
			iptjmp(ymax-1);
			iptf(); 
			iptjmp( ymax);
			iptf();
			iptinc();
			iptf();
		break;
		case 13: 			// max ok
			iptjmp( (xmax-2)*ymax + (ty-1));
			iptf();
			iptinc();
			iptf();
			iptinc();
			iptf();
			iptinc();
			iptjmp(ymax-3) ;
			iptf();
			iptjmp(2);
			iptf();

		break;
		case 7: // 0 ok
			iptjmp( ty-1);
			iptf();
			iptjmp(2);
			iptf();
			
			iptjmp(ymax-2);
			iptf();
			iptinc();
			iptf();	
			iptinc();
			iptf();	
			
		break;
	};
	
}
#undef iptf
//#undef MUTATE_fast_array_alter_extra_args
#undef MUTATE_fast_array_alter 
