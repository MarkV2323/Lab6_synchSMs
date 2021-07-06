/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #1
 *	Youtube Link: 
 *  Exercise Description:
 *
 *  Blink LEDs B0, B1, B2 in a sequence, 1 second each.
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
enum States{start, init} state;

// Globals

// Tick Function
void tick() {
    
    // READ INPUT
    tmpA = PINA & 0xFF;

    // Transitions
    switch(state) {
        case start:
            state = init;
            break;
        case init:
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
            break;
        default:
            break;
    }

}

// Main Function using timer.h header
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00; // PortB as output

    // Sets timer to 1 second, and on
    TimerSet(1000);
    TimerOn();

    unsigned char tmpB = 0x00;

    /* Insert your solution below */
    while (1) {
        // User Code
        tmpB = ~tmpB; // Toogles PortB
        PORTB = tmpB; // writes output
        
        // tick
        // wait 1 sec
        while (!TimerFlag);

        TimerFlag = 0;
        // This example doesn't use a synchSM, should use one with TickSM()
        // showcases use of ISR and flag
    }

    return 1;
}

