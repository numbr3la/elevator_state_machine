/* ########################################################################

   PICsim - PIC simulator http://sourceforge.net/projects/picsim/

   ########################################################################

   Copyright (c) : 2015  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#include <xc.h>
#include "lcd.h"

void LCD_Init(void) {
	L_ENABLE = 0;
	L_RS = 0; __delay_ms(20);
	L_ENABLE = 1;
	
	LCD_Cmd(L_CFG); __delay_ms(5);
	LCD_Cmd(L_CFG); __delay_ms(1);
	LCD_Cmd(L_CFG); 
    
	LCD_Cmd(L_OFF);
	LCD_Cmd(L_ON); 
	LCD_Cmd(L_CLEAR);
	LCD_Cmd(L_CFG);
    LCD_Cmd(L_LINE_1);
}


void WriteLCDPort(unsigned char value) {  // write to LCD port
    L_PORT = value;
}


void LCD_Cmd(unsigned char value) {
	L_ENABLE = 1;
    WriteLCDPort(value);
    L_RS = 0; __delay_ms(3);
    L_ENABLE = 0; __delay_ms(3);
	L_ENABLE=1;
}
 
void LCD_Data(unsigned char value) {
	L_ENABLE = 1;
    WriteLCDPort(value);
    L_RS = 1; __delay_ms(3);
    L_ENABLE = 0; __delay_ms(3);
	L_ENABLE = 1;
}

void LCD_String(const char* str) {
 unsigned char i=0;
  
 while(str[i] != '\0' ) {
   LCD_Data(str[i]);
   i++;
 }  
}






 
