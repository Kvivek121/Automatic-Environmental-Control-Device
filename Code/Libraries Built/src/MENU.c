/*
 * MENU.c
 *
 *  Created on: Feb 21, 2023
 *      Author: acer
 */

#include "liquidcrystal_i2c.h"
#include "stdio.h"

int temp_threshold=30,humi_threshold=50,press_threshold=2000;
int count=0;
int time_elapsed=0;
volatile int pos_button =0;
volatile int neg_button=0;
volatile int menu_button=0;
int Welcom_count=0;
int view_count=0;

/****************************************************************************************************************/
/************************************************Interrupt Button Code ******************************************/
void Menu()
{
	char buf1[10];
	while(menu_button>0)
	{
		if (Welcom_count==0)
		{
			HD44780_Clear();
			HD44780_SetCursor(1,0);
			HD44780_PrintStr("THRESHOLD MENU");
			HAL_Delay(1000);
			Welcom_count++;
		}

		if (count==1)
		{
			if (view_count==0)
			{
				HD44780_Clear();
				HD44780_SetCursor(2,0);
				HD44780_PrintStr("Temperature");
				view_count++;
			}

			if (pos_button==1 )
			{
				time_elapsed=0;
				temp_threshold++;
				pos_button=0;
				// to print updated Threshold Value
				sprintf(buf1, "%d", temp_threshold);
				HD44780_SetCursor(5,1);
				HD44780_PrintStr(buf1);
			}

			if (neg_button==1)
			{
				time_elapsed=0;
				temp_threshold--;
				neg_button=0;
				// to print updated Threshold Value
				sprintf(buf1, "%d", temp_threshold);
				HD44780_SetCursor(5,1);
				HD44780_PrintStr(buf1);
			}
		}

		if (count==2)
		{
			if (view_count==0)
			{
				HD44780_Clear();
				HD44780_SetCursor(2,0);
				HD44780_PrintStr("Humidity");
				view_count++;
			}

			if (pos_button==1)
			{
				time_elapsed=0;
				humi_threshold++;
				pos_button=0;
				// to print updated Threshold Value
				sprintf(buf1, "%d", humi_threshold);
				HD44780_SetCursor(5,1);
				HD44780_PrintStr(buf1);
			}

			if (neg_button==1)
			{
				time_elapsed=0;
				humi_threshold--;
				neg_button=0;
				// to print updated Threshold Value
				sprintf(buf1, "%d", humi_threshold);
				HD44780_SetCursor(5,1);
				HD44780_PrintStr(buf1);
			}
		}

		if (count==3)
		{
			if (view_count==0)
			{
				HD44780_Clear();
				HD44780_SetCursor(2,0);
				HD44780_PrintStr("Pressure");
				view_count++;
			}

			if (pos_button==1)
			{
				time_elapsed=0;
				press_threshold++;
				pos_button=0;
				// to print updated Threshold Value
				sprintf(buf1, "%d", press_threshold);
				HD44780_SetCursor(5,1);
				HD44780_PrintStr(buf1);
			}

			if (neg_button==1)
			{
				time_elapsed=0;
				press_threshold--;
				neg_button=0;
				// to print updated Threshold Value
				sprintf(buf1, "%d", press_threshold);
				HD44780_SetCursor(5,1);
				HD44780_PrintStr(buf1);
			}
		}

		if (count>=5)
		{
			count=0;
			menu_button=0;
			Welcom_count=0;
			view_count=0;
		}
		/*if (time_elapsed > 10)
	{
		count=0;
		menu_button=0;
	}*/
	}
}
