#include <REGX52.H>
#include "clock.h"
unsigned int u8sec=0;
unsigned int u8min=0;
unsigned int u8hour=0;

unsigned int u8countDisply=0;
/* swithes */
sbit increment=P2^6;
sbit decrement=P2^5;

//unsigned int arr[10]={0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x10};
//unsigned int arr[10]={0x67,0x7F,0x07,0x7C,0x6D,0x66,0x4F,0x5B,0x06,0x3F};
unsigned int arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67};
void clock_work(){

		if(u8countDisply <250){
			P2=0x79;
			P3=1;
			P1=arr[u8sec/10];
			delay(15);
			P3=P3<<1;
		
			P1=arr[u8sec%10];
			delay(15);
		}else if(u8countDisply <1000){
			P2=0x7A;
			P3=1;
			
			P1=arr[u8min/10];
			delay(15);
			P3=P3<<1;
		
			P1=arr[u8min%10];
			delay(15);
		}else if(u8countDisply < 1500){
			P3=1;
			P2=0x7C;
			P1=arr[u8hour/10];
			delay(15);
			P3=P3<<1;
		
			P1=arr[u8hour%10];
			delay(15);
			
		}else{
			u8countDisply=0;
		}
		u8countDisply++;
}
void second(){
	
}
void minutes(){
			P2=0xFA;
			P3=1;
			
			P1=arr[u8min/10];
			delay(15);
			P3=P3<<1;
		
			P1=arr[u8min%10];
			delay(15);
	
			if(increment == 0){
				delay(500);
				if(increment == 0){
					u8min++;}
			}else{
				/*do nothing */
			}
	
			if(decrement ==0){
				delay(500);
				if(decrement ==0){
					u8min--;
				}
			}else{
				/*do nothing */
		}
}

void hours(){
			P3=1;
	    P2=0xFC;
			P1=arr[u8hour/10];
			delay(15);
			P3=P3<<1;
		
			P1=arr[u8hour%10];
			delay(15);
			
			if(increment ==0){
				delay(500);
				if(increment ==0){
					u8hour++;
				}
			}else{
				/*do nothing */
			}
			
			if(decrement ==0){
				delay(500);
				if(decrement ==0){
					u8hour--;
				}	
			}else{
				/*do nothing */
			}
			u8countDisply=0;
}
void delay(unsigned int u8delay){
unsigned int j,k;
for (j=0;j<=u8delay;j++)
for (k=0;k<=120;k++);
}
void timer_init(){
	
	  TMOD = 0x01;       //Timer0 mode 1 
    TH0 = 0XC3;        //Load the timer value
    TL0 = 0X50;
    TR0 = 1;           //turn ON Timer zero
    ET0 = 1;           //Enable TImer0 Interrupt
    EA = 1;            //Enable Global Interrupt 

	
}
unsigned char counter=0;
void timer0_isr() interrupt 1
{
	counter++;
	TH0 = 0XC3;        //RELoad the timer value
  TL0 = 0X50;
	if(counter >= 20){
		 counter=0;
		if(u8sec <60){
			u8sec++;
		}else if(u8min <60){
			u8sec=0;
			u8min++;
		}else if(u8hour <60){
			u8min=0;
			u8hour++;	
		}
		
	}else{
     TR0 = 1;
	}		
}