#include <REGX52.H>
#include "clock.h"

sbit parameters=P2^3;

unsigned char op_flag=0;
void main(void){

	timer_init();
	while(1){
	if(parameters==0){	
			delay(600);
		if(parameters==0){
			op_flag++;
		}
		if(op_flag > 2){
			op_flag=0;
		}
	}
	if(op_flag==0){
		clock_work();
	}else if(op_flag==1){
		 minutes();
	}else if(op_flag==2){
			hours();
	}
		
	}

}