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

// Outputs RB2:RB0
#define COL_1 0x01
#define COL_2 0x02
#define COL_3 0x04

// Inputs RD3:RD0
#define ROW_1     PORTDbits.RD3
#define ROW_2     PORTDbits.RD2
#define ROW_3     PORTDbits.RD1
#define ROW_4     PORTDbits.RD0

#define BT_PRESS    0       // state of the pressed button
#define BT_RELEASE  1       // state of the released button

#define KEY_DELAY     10

unsigned char GetKey(void); 
unsigned char GetKeyTimeout(unsigned int timeout); /*timeout=0 no time out*/ 
