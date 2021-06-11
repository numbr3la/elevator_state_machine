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

/*
 * The HD44780U has two 8-bit registers, 
 * an instruction register (IR) and a data register (DR).
 * The IR stores instruction codes, such as display clear and cursor shift, 
 * and address information for display data RAM (DDRAM) 
 * and character generator RAM (CGRAM). 
 * 
 * 
*/ 

//#include "board4_xtal.h"
#define _XTAL_FREQ      1000000UL 

// Hitachi HD44780 LCD display driver chip protocol

// Pin definitions
#define L_ENABLE    PORTEbits.RE1   // LCD enable signal
#define L_RS        PORTEbits.RE2   // LCD register select (RS) signal
                                    // RS=0: Command, RS=1: Data
#define L_PORT      PORTD           // LCD data 8-bit port

// HD44780 Protocol Commands

#define L_ON            0x0F        // LCD on (with blinking cursor)
#define L_OFF           0x08        // LCD off

#define L_CLEAR         0x01        // LCD clear and return cursor to the home position

#define L_LINE_1        0x80        // Set address to the head of 1st line 
#define L_LINE_2        0xC0        // Set address to the head of 2st line 

#define L_CURSOR_L      0x10        // Cursor move left
#define L_CURSOR_R      0x14        // Cursor move right
#define L_DISPLAY_L     0x18        // Display shift left
#define L_DISPLAY_R     0x1C        // Display shift right

#define L_CGRAM         0x40		// Select Character Generator RAM 
#define L_DDRAM         0x80		// Select Display Data RAM 

#define CR              0x0F		// Cursor return
#define NL              0x0C        // New line

#define L_CFG           0x38

void LCD_Init(void);
void LCD_Cmd(unsigned char value); 
void LCD_Data(unsigned char value);
void LCD_String(const char* str);

