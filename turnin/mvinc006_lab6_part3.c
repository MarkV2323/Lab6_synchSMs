/*	Author: Mark Vincent
 *  Partner(s) Name: NA
 *	Lab Section: A01
 *	Assignment: Lab #6  Exercise #3
 *	Youtube Link: https://youtu.be/MxQY58C0p2s
 *  Exercise Description:
 *
 *  Take an old lab an add a timer to it.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

// States ie, {Start, Init, ... etc}
enum States{start, init, off, on} state;

// Globals
unsigned int tmpA = 0x00;
unsigned int tmpC = 0x00;
unsigned int b1count = 0x00;
unsigned int b2count = 0x00;
enum Flags{button1, button2, both, stillOn1, stillOn2, stillOn3, none} flag;

// tick function
void tick() {
    
    // READ INPUT
    tmpA = ~PINA & 0xFF;

    // Transitions
    switch(state) {
        case start:
            state = init;
            break;
        case init:
            // Check where to go next
            if (tmpA == 0x00) {
                // goes to OFF, with flag set to none
                flag = none;
                state = off;

            } else if (tmpA == 0x01) {
                // goes to ON, with flag set to button1
                flag = button1;
                state = on;
                // inits b1counter to 0
                b1count = 0;

            } else if (tmpA == 0x02) {
                // goes to ON, with flag set to button2
                flag = button2;
                state = on;
                // inits b2counter to 0
                b2count = 0;

            } else if (tmpA == 0x03) {
                // goes to ON, with flag set to both.
                flag = both;
                state = on;
            }
            break;
        case off:
            // Check where to go next
            if (tmpA == 0x00) {
                // goes to OFF, with flag set to none
                flag = none;
                state = off;

            } else if (tmpA == 0x01) {
                // goes to ON, with flag set to button1
                flag = button1;
                state = on;
                b1count = 0;
            } else if (tmpA == 0x02) {
                // goes to ON, with flag set to button2
                flag = button2;
                state = on;
                b2count = 0;
            } else if (tmpA == 0x03) {
                // goes to ON, with flag set to both.
                flag = both;
                state = on;
            }
  
            break;
        case on:
            // Check where to go next
            if (tmpA == 0x00) {
                // goes to OFF, with flag set to none
                flag = none;
                state = off;
                // resets both counts
                b1count = 0;
                b2count = 0;
            } else if (tmpA == 0x01) {
                // goes to ON, with flag set to button1
                if (flag == stillOn1) {
                    // increment b1count
                    b1count = b1count + 1;
                } else {
                    flag = button1;
                    state = on;
                }

            } else if (tmpA == 0x02) {
                // goes to ON, with flag set to button2
                if (flag == stillOn2) {
                    // nothing
                    b2count = b2count + 1;
                } else {
                    flag = button2;
                    state = on;
                }

            } else if (tmpA == 0x03) {
                // goes to ON, with flag set to both.
                if (flag == stillOn3) {
                    // nothing
                } else {
                    flag = both;
                    state = on;
                }
            }
             break;
        default:
            state = start;
            break;
    }

    // Actions
    switch(state) {
        case start:
            break;
        case init:
            // Sets output to 7 and writes.
            tmpC = 0x07;
            PORTC = tmpC;
            break;
        case off:
            // Decides whether to increment, decrement or nothing
            if (flag == none) {
                // Does nothing.
            } else {
                // shouldn't be able to get here.
            }
            break;
        case on:
            // increments or decrements if counts are right values
            if ((b1count == 10) && (tmpC < 9)) {
                b1count = 0;
                tmpC = tmpC + 1;
                flag = stillOn1;
            } else if ((b2count == 10) && (tmpC > 0)) {
                b2count = 0;
                tmpC = tmpC - 1;
                flag = stillOn2;
            } else {
                // does nothing
            }

            // Decides whether to increment, decrement or nothing
            if (flag == button1) {
                // Does a increment on PORTC by 1 if PORTC < 9.
                if (tmpC < 9) {
                    // Does increment
                    tmpC = tmpC + 1;
                    flag = stillOn1;
                } else {
                    // Does nothing
                }
            } else if (flag == button2) {
                // Does a decrement on PORTC by 1 if PORTC > 0.
                if (tmpC > 0) {
                    // Does decrement
                    tmpC = tmpC - 1;
                    flag = stillOn2;
                } else {
                    // Does nothing
                }
            } else if (flag == both) {
                // Resets tmpC to 0x00
                tmpC = 0x00;
                flag = stillOn3;
            } else {
                // does nothing
            }
            // writes output
            PORTC = tmpC;
            break;
        default:
            break;
    }

}

// Main Function using timer.h header
int main(void) {  
    
    // PORTS
    DDRA = 0x00; PORTA = 0xFF; // Configure PORTA as input
    DDRC = 0xFF; PORTC = 0x00; // Configure PORTC as output
    
    // Sets timer to 100ms, and on
    TimerSet(100);
    TimerOn();
    
    // init state and output
    state = start;
    PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
        
        // tick
        tick();

        // wait 1 sec
        while (!TimerFlag);

        TimerFlag = 0;
    }

    return 1;
}

