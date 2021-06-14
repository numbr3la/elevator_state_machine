#pragma config FOSC = HS    // (HS oscillator)
#pragma config WDTE = OFF   // (WDT disabled)
#pragma config PWRTE = OFF  // (PWRT disabled)
#pragma config BOREN = OFF  // (BOR disabled)
#pragma config LVP = ON     // (PGM function; low-volt. prog. enabled)
#pragma config CPD = OFF    // (Data EEPROM code protection off)
#pragma config WRT = OFF    // (Write protection off;)
#pragma config CP = OFF     // (Code protection off)

#include <xc.h>
#include <stdlib.h>

#include "lcd.h"
#include "keyboard.h"


#define BT_PRESS    0       // state of the pressed button
#define BT_RELEASE  1       // state of the released button

#define _XTAL_FREQ      1000000UL 
#define BLINK_TIME_MS   1000


static const char *floor[] = {" --  PARTER  -- ", 
                              "   --  1  --", 
                              "   --  2  --",
                              "   --  3  --",
                              "   --  4  --",
                              "   --  5  --"};

int floor_location;
int button_location;
unsigned char key;

typedef enum {
            STATE_IDLE,
            STATE_GOINGUP,
            STATE_GOINGDOWN,
            STATE_DOOROPEN,
            STATE_DOORCLOSED,
            STATE_ATTOP,
            STATE_ATBOTTOM
                    
}STATE_t;
STATE_t mystate = STATE_IDLE;

void mydelay(int milisec){
    int periods = milisec / 10;
    int i = 0;
    
    ADCON1 = 0x06;
    TRISA |= 0x20;
    
    do
    {
        if(PORTAbits.RA5 == BT_PRESS){
            while(PORTAbits.RA5 == BT_PRESS);
            PORTCbits.RC2 ^= 1;
        }
        
    __delay_ms(10);
    i++;
    }while(i < periods);
}

void buzzer(void) {
    PORTCbits.RC1=1;        // buzzer on
    __delay_ms(1000);
    PORTCbits.RC1=0;        // buzzer off    
}

void idle(char floor[]){
    TRISB  = 0x3F;                  // Enable button RB5 - RB0;
    LCD_Cmd(L_CLEAR);
    LCD_Cmd(L_LINE_1); LCD_String(floor);
    LCD_Cmd(L_LINE_4); LCD_String("  Press Button  ");
    
    while(1){
        if(PORTBbits.RB0 == BT_PRESS){
            button_location = 0;
            break;
        }
        if(PORTBbits.RB1 == BT_PRESS){
            button_location = 1;
            break;
        }
        if(PORTBbits.RB2 == BT_PRESS){
            button_location = 2;
            break;
        }
        if(PORTBbits.RB3 == BT_PRESS){
            button_location = 3;
            break;
        }
        if(PORTBbits.RB4 == BT_PRESS){
            button_location = 4;
            break;
        }
        if(PORTBbits.RB5 == BT_PRESS){
            button_location = 5;
            break;
        }
    }
    LCD_Cmd(L_CLEAR);
}

void door_open(char floor[]){
    LCD_Cmd(L_CLEAR);
    LCD_Cmd(L_LINE_1); LCD_String(floor);
    LCD_Cmd(L_LINE_2); LCD_String("  Door opening  ");
    buzzer();
    LCD_Cmd(L_LINE_2); LCD_String("   Door open  ");
    __delay_ms(1000);
}

void door_closed(char floor[]){
    LCD_Cmd(L_CLEAR);
    LCD_Cmd(L_LINE_1); LCD_String(floor);
    LCD_Cmd(L_LINE_2); LCD_String("  Door closing  ");
    buzzer();
    LCD_Cmd(L_LINE_2); LCD_String("   Door closed  ");
    __delay_ms(1000);
}

void move_down(int position){
    for(int i = floor_location; i >= position; i--){
        LCD_Cmd(L_LINE_1); LCD_String(floor[i]);
        LCD_Cmd(L_LINE_4); LCD_String("   Going down  ");
        mydelay(200);
        LCD_Cmd(L_LINE_4); LCD_String("                ");
        mydelay(100);
        LCD_Cmd(L_LINE_4); LCD_String("   Going down  ");
        mydelay(200);
        LCD_Cmd(L_LINE_4); LCD_String("                ");
        __delay_ms(100);
        mydelay(L_CLEAR);  
        floor_location = i;
    }
}

void move_up(int position){
    for(int i = floor_location; i <= position; i++){
        LCD_Cmd(L_LINE_1); LCD_String(floor[i]);
        LCD_Cmd(L_LINE_4); LCD_String("    Going up  ");
        mydelay(200);
        LCD_Cmd(L_LINE_4); LCD_String("               ");
        mydelay(100);
        LCD_Cmd(L_LINE_4); LCD_String("    Going up   ");
        mydelay(200);
        LCD_Cmd(L_LINE_4); LCD_String("               ");
        mydelay(100);
        LCD_Cmd(L_CLEAR);  
        floor_location = i;
    }
}

unsigned char select_floor() {
    unsigned char tmp;
    
    LCD_Cmd(L_CLEAR); 
    LCD_Cmd(L_LINE_1); LCD_String(floor[floor_location]);
    LCD_Cmd(L_LINE_3); LCD_String("- Select floor -");
    LCD_Cmd(L_LINE_4); LCD_String("       ");
    
    TRISB = 0x00; 
    TRISD = 0x0F;
    
    tmp = GetKeyTimeout(5000);
    if(tmp > 0 && tmp < 10) tmp += (unsigned char)0x30;
    else if(tmp == 11) tmp = 0x30;
    
    TRISD = 0x00;
    LCD_Data(tmp);
    
    __delay_ms(1000);
    
    LCD_Cmd(L_CLEAR);
    return tmp;
}

void main(void) {
    TRISA = 0xC3;   // b10100011 
    TRISB = 0x01;   // b00000001   
    TRISC = 0x01;   // b00000001
    TRISD = 0x00;   // b00000000
    TRISE = 0x00;   // b00000000
    
    LCD_Init();
    floor_location = 0;

    while(1){
        switch(mystate){
            case STATE_IDLE:
                idle(floor[floor_location]);
                if(floor_location == button_location) {
                    mystate = STATE_DOOROPEN;
                    break;
                }
                if(button_location > floor_location) mystate = STATE_GOINGUP;
                else mystate = STATE_GOINGDOWN;
            break;
            
            case STATE_DOOROPEN:
                door_open(floor[floor_location]);
                key  = select_floor();
                mystate = STATE_DOORCLOSED;
                break;
                
            case STATE_DOORCLOSED:
                door_closed(floor[floor_location]);
                button_location = (int) key - 48;
                
                if(key == 255){ mystate = STATE_IDLE; break ;}
                if(button_location > 5) {mystate = STATE_IDLE; break;}
                if(button_location > floor_location) {
                    mystate = STATE_GOINGUP;
                    break;
                } 
                if(button_location < floor_location){
                    mystate = STATE_GOINGDOWN;
                }
                break;
                
            case STATE_GOINGUP:
                move_up(button_location);
                mystate = STATE_DOOROPEN;
                break;
                
            case STATE_GOINGDOWN:
                move_down(button_location);
                mystate = STATE_DOOROPEN;
                break;
        }
    }
}