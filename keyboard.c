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
 * Modified by Przemyslaw Slusarczyk, pslusarczyk [at] ujk [dot] edu [dot] pl 
 * Institute of Physics, Jan Kochanowski University, Kielce, Poland
 */

/* ----------------------------------------------------------------------- */

#include <xc.h>
#include "keyboard.h"
//#include "board4_xtal.h"
#define _XTAL_FREQ      1000000UL 

// Outputs RB2:RB0
const unsigned char columns[]= {COL_1, COL_2, COL_3};

// Inputs RD3:RD0

unsigned char GetKey(void) {
    unsigned char i;
    unsigned char key = 0;
    unsigned char tmp = PORTB;  // store Port B state

    PORTB = 0xFF;
    while(key == 0) {
        for(i=0; i<3; i++) {    // switch columns
            PORTB |= (unsigned char)~columns[i];  // select column
      
            if(ROW_1 == BT_PRESS){              // button pressed
                __delay_ms(KEY_DELAY);          // debouncing
                if(ROW_1 == BT_PRESS){          // still pressed
                    while(ROW_1 == BT_PRESS);   // wait for release
                    key = (unsigned char)(1+i);
                    break;
                }
            }
            
            if(ROW_2 == BT_PRESS){              // button pressed
                __delay_ms(KEY_DELAY);          // debouncing
                if(ROW_2 == BT_PRESS){          // still pressed
                    while(ROW_2 == BT_PRESS);   // wait for release
                    key = (unsigned char)(4+i);
                    break;
                }
            } 
            
            if(ROW_3 == BT_PRESS){              // button pressed
                __delay_ms(KEY_DELAY);          // debouncing
                if(ROW_3 == BT_PRESS){          // still pressed
                    while(ROW_3 == BT_PRESS);   // wait for release
                    key = (unsigned char)(7+i);
                    break;
                }
            }
            
            if(ROW_4 == BT_PRESS){              // button pressed
                __delay_ms(KEY_DELAY);          // debouncing
                if(ROW_4 == BT_PRESS){          // still pressed
                    while(ROW_4 == BT_PRESS);   // wait for release
                    key = (unsigned char)(10+i);
                    break;
                }
            }
            
            PORTB &= (unsigned char)columns[i];
        }
        __delay_ms(5);
    }
    
    PORTB = tmp;                // restore Port B state
    return key;
} 


unsigned char GetKeyTimeout(unsigned int timeout) {
    unsigned int  time_ms = 0;
    unsigned char i;
    unsigned char key = 0;
    unsigned char tmp = PORTB;  // store Port B state

    PORTB = 0xFF;
    while(((time_ms < timeout) || (timeout == 0)) && (key == 0)) {
        for(i=0; i<3; i++) {    // switch columns
            PORTB |= (unsigned char)~columns[i];  // select column
      
            if(ROW_1 == BT_PRESS){              // button pressed
                __delay_ms(KEY_DELAY);          // debouncing
                if(ROW_1 == BT_PRESS){          // still pressed
                    while(ROW_1 == BT_PRESS);   // wait for release
                    key = (unsigned char)(1+i);
                    break;
                }
            }
            
            if(ROW_2 == BT_PRESS){              // button pressed
                __delay_ms(KEY_DELAY);          // debouncing
                if(ROW_2 == BT_PRESS){          // still pressed
                    while(ROW_2 == BT_PRESS);   // wait for release
                    key = (unsigned char)(4+i);
                    break;
                }
            } 
            
            if(ROW_3 == BT_PRESS){              // button pressed
                __delay_ms(KEY_DELAY);          // debouncing
                if(ROW_3 == BT_PRESS){          // still pressed
                    while(ROW_3 == BT_PRESS);   // wait for release
                    key = (unsigned char)(7+i);
                    break;
                }
            }
            
            if(ROW_4 == BT_PRESS){              // button pressed
                __delay_ms(KEY_DELAY);          // debouncing
                if(ROW_4 == BT_PRESS){          // still pressed
                    while(ROW_4 == BT_PRESS);   // wait for release
                    key = (unsigned char)(10+i);
                    break;
                }
            }
            
            PORTB &= (unsigned char)columns[i];
        }
        __delay_ms(5);
        time_ms += 5;
    }
    
    if(key == 0) key = 255;     // timeout
    PORTB = tmp;                // restore Port B state
    return key;
} 




