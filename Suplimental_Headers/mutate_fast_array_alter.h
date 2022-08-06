/*          Mutate_fast_array_alter.h
  	mutating function for altering 2d array around target tx,ty
  	add and change the below defines, change to suit your needs.  
  	first changes the function name, iptf changes what is done to affected squares (and ternary checks)
  	*/

// #define MUTATE_fast_array_alter your_func_name
//#define iptf() *ipt+=val;  // (*ipt==0?*ipt=val:0);
//#define MUTATE_fast_array_alter_extra_args 


void MUTATE_fast_array_alter(int * ipt, int xmax, int ymax, int tx, int ty, int val MUTATE_fast_array_alter_extra_args){  //  working. make mutable
	BYTE bt = ((((((tx>0) << 1 )| (ty>0)) << 1)| (tx<xmax-1)) << 1)| (ty<ymax-1);
	//if(!addsub)val=val*-1;
	//ipt=(int*)arr;
	switch(bt){ 
		case 15:
			// 1111 all ok
			//ipt=&arr[tx-1][ty-1];//left
			ipt+= ((tx-1)*(ymax))+ty-1;
			iptf();ipt++;
			iptf();ipt++;
			iptf();
			ipt+=ymax-2;//ipt=&arr[tx][ty-1]; //top/bottom
			iptf();ipt+=2; 
			iptf();
			ipt+=ymax-2;//ipt=&arr[tx+1][ty-1];//right
			iptf();ipt++; 
			iptf();ipt++;
			iptf();
		break;
		case 3: // 0011  this is 0,0
			ipt++;
			iptf();
			ipt+= ymax-1;
			iptf();
			ipt++;
			iptf();
			
		break;
		case 12: // max max
			ipt+= (ymax*xmax)-(ymax+2);
			iptf();
			ipt++;
			iptf();
			ipt+=ymax-1;
			iptf(); 
		break;
		case 6: // 0, max
			ipt += ymax-2;
			iptf();
			ipt += ymax;
			iptf();
			ipt++;
			iptf();
		break;
		case 9:// max 0
			ipt += ymax*(xmax-2);
			iptf();
			ipt++;
			iptf();
			ipt+=ymax;
			iptf();
		break;
		case 11:// ok, 0
			ipt+= (tx-1) * ymax;
			iptf();
			ipt++;
			iptf();
			ipt += ymax;
			iptf(); 
			ipt+= ymax-1;
			iptf();
			ipt++;
			iptf();
		break;
		case 14: // ok max
			ipt+= ((tx-1) * ymax)+(ymax-2);
			iptf();
			ipt++;
			iptf();
			ipt += ymax-1;
			iptf(); 
			ipt+= ymax;
			iptf();
			ipt++;
			iptf();
		break;
		case 13: 			// max ok
			ipt += (xmax-2)*ymax + (ty-1);
			iptf();
			ipt++;
			iptf();
			ipt++;
			iptf();
			ipt++;
			ipt+=ymax-3 ;
			iptf();
			ipt+=2;
			iptf();

		break;
		case 7: // 0 ok
			ipt += ty-1;
			iptf();
			ipt+=2;
			iptf();
			
			ipt += ymax-2;
			iptf();
			ipt++;
			iptf();	
			ipt++;
			iptf();	
			
		break;
	};
	
}
#undef iptf
//#undef MUTATE_fast_array_alter_extra_args
#undef MUTATE_fast_array_alter 
