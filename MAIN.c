#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "time0init.h"

unsigned char keynum=0,mode=0,selete=0,timeflash=0;

void showtime()
{
    if(mode==1 && selete==0 && timeflash==1){LCD_ShowString(1,1,"    ");}
    else {LCD_ShowNum(1,1,20,2);LCD_ShowNum(1,3,DS1302_TIME[0],2);}
    if(mode==1 && selete==1 && timeflash==1){LCD_ShowString(1,6,"  ");}
    else {LCD_ShowNum(1,6,DS1302_TIME[1],2);}
    if(mode==1 && selete==2 && timeflash==1){LCD_ShowString(1,9,"  ");}
    else {LCD_ShowNum(1,9,DS1302_TIME[2],2);}
    if(mode==1 && selete==3 && timeflash==1){LCD_ShowString(2,1,"  ");}
    else {LCD_ShowNum(2,1,DS1302_TIME[3],2);}
    if(mode==1 && selete==4 && timeflash==1){LCD_ShowString(2,4,"  ");}
    else {LCD_ShowNum(2,4,DS1302_TIME[4],2);}
    if(mode==1 && selete==5 && timeflash==1){LCD_ShowString(2,7,"  ");}
    else {LCD_ShowNum(2,7,DS1302_TIME[5],2);}
    if(mode==1 && selete==6 && timeflash==1){LCD_ShowString(1,11," ");}
    else {LCD_ShowNum(2,11,DS1302_TIME[6],1);}
}


void settime()
{
    if (keynum==2) {selete++;if(selete>6)selete=0;}


    if(keynum==3)
    {
        DS1302_TIME[selete]++;
        if (DS1302_TIME[0]>99)DS1302_TIME[0]=0;
        if (DS1302_TIME[1]>12)DS1302_TIME[1]=1;
        if (DS1302_TIME[1]==1 || DS1302_TIME[1]==3 || DS1302_TIME[1]==5 || DS1302_TIME[1]==7 || DS1302_TIME[1]==8 || DS1302_TIME[1]==10 || DS1302_TIME[1]==12)
        {
            if (DS1302_TIME[2]>31)DS1302_TIME[2]=1;
        }
        if (DS1302_TIME[1]==2)
        {
            if(DS1302_TIME[0]%4==0){if (DS1302_TIME[2]>29)DS1302_TIME[2]=1;}
            else if (DS1302_TIME[0]%4!=0){if (DS1302_TIME[2]>28)DS1302_TIME[2]=1;}
        }

        if (DS1302_TIME[3]>23)DS1302_TIME[3]=0;
        if (DS1302_TIME[4]>59)DS1302_TIME[4]=0;
        if (DS1302_TIME[5]>59)DS1302_TIME[5]=0;
        if (DS1302_TIME[6]>7)DS1302_TIME[6]=1;
    }

    if (keynum==4)
    {
        DS1302_TIME[selete]--;
        if (DS1302_TIME[0]>99)DS1302_TIME[0]=99;
        if (DS1302_TIME[1]<1)DS1302_TIME[1]=12;
        if (DS1302_TIME[1]==1 || DS1302_TIME[1]==3 || DS1302_TIME[1]==5 || DS1302_TIME[1]==7 || DS1302_TIME[1]==8 || DS1302_TIME[1]==10 || DS1302_TIME[1]==12)
        {
            if (DS1302_TIME[2]<1)DS1302_TIME[2]=31;
        }
        if (DS1302_TIME[1]==2)
        {
            if(DS1302_TIME[0]%4==0){if (DS1302_TIME[2]<1)DS1302_TIME[2]=29;}
            else if (DS1302_TIME[0]%4!=0){if (DS1302_TIME[2]<1)DS1302_TIME[2]=28;}
        }

        if (DS1302_TIME[3]>23)DS1302_TIME[3]=23;
        if (DS1302_TIME[4]>59)DS1302_TIME[4]=59;
        if (DS1302_TIME[5]>59)DS1302_TIME[5]=59;
        if (DS1302_TIME[6]<1)DS1302_TIME[6]=7;
    }
    showtime();
}


void main ()
{
    DS1302_init();
    LCD_Init();
    Timer0Init();
    DS1302_SetTime();
    LCD_ShowString(1,1,"    -  -  ");
    LCD_ShowString(2,1,"  :  :  ");

	while(1)
    {
    keynum=Key();
    if (keynum==1) {mode++;if (mode>2) mode=0;}

    switch (mode)
    {
    case 0:DS1302_ReadTime();showtime();break;
    case 1:settime();break;
    case 2:DS1302_SetTime();selete=0;mode=0;break;
    }

    LCD_ShowNum(1,13,selete,1);

    }
}


void shinging () interrupt 1
{
    static unsigned int time;
	TL0 = 0x66;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值    
    time++;
    if (time>500)
    {
        timeflash=!timeflash;
        time=0;
    }
}
