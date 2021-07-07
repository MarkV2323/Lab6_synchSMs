/*	Author: Mark Vincent II
 *  Partner(s) Name: NA
 *	Lab Section: A01
 *	Assignment: Lab #6  Exercise #2
 *	Youtube Link: https://youtu.be/xp0h6Eushsk
 *  Exercise Description:
 *
 *  Create a simple light game.
 *  
 *  Button on press on A0 to "stop" the LED flashing sequence, keep LED stopped
 *  on lit. Press button again to restart game.
 *  
 *  Should light B0, B1, B2 in sequence, at 300 ms
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
enum States{start, init, game, result} state;

// Globals
unsigned int tmpA = 0x00;
unsigned int tmpB = 0x00;

// flags for button pressed
enum Flags{gameP, gameR, resultP, resultR} flag;

// Tick Function
void tick() {
    
    // READ INPUT (from button, hence inverse)
    tmpA = ~PINA & 0xFF;

    // Transitions
    switch(state) {
        case start:
            state = init;
            break;
        case init:
            flag = resultR;
            state = game;
            break;
        case game:
            // Button has been pressed, stop at LED
            if ((tmpA == 0x01) && flag == resultR) {
                // button has been pressed.
                flag = gameP;
                // Swaps to result state.
                state = result;
            } else if ((tmpA == 0x00) && flag == resultP) {
                // button has been released
                flag = resultR;
                // stay in game state.
                state = game;
            } else {
                // Stay in game state.
                state = game;
            }
            break;
        case result:
            if ((tmpA == 0x01) && flag == gameR) {
                // resets tmpB to 0x01
                tmpB = 0x01;
                PORTB = tmpB;
                // button has been pressed.
                flag = resultP;
                // Swaps to game state.
                state = game;
            } else if ((tmpA == 0x00) && flag == gameP) {
                // button has been released
                flag = gameR;
                // stay in result state.
                state = result;
            } else {
                // Stay in result state.
                state = result;
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
            // init tmpB to 0x01
            tmpB = 0x01;
            PORTB = tmpB;
            break;
        case game:
            // flashes LEDs in a sequence
            if (tmpB == 0x01) {
                // write new LED to PORTB
                tmpB = 0x02;
                PORTB = tmpB;
            } else if (tmpB == 0x02) {
                // write new LED to PORTB
                tmpB = 0x04;
                PORTB = tmpB;
            } else if (tmpB == 0x04) {
                // write new LED to PORTB
                tmpB = 0x01;
                PORTB = tmpB;
            }
            break;
        case result:
            // write stopped LED to PORTB
            PORTB = tmpB;
            break;
        default:
            break;
    }

}

// Main Function using timer.h header
int main(void) {
    
    // PORTS
    DDRA = 0x00; PORTA = 0xFF; // PortA as input
    DDRB = 0xFF; PORTB = 0x00; // PortB as output

    // Sets timer to .3 second, and on
    TimerSet(300);
    TimerOn();
    
    // init state and output
    state = start;
    PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
        
        // tick
        tick();

        // wait .3 sec
        while (!TimerFlag);

        TimerFlag = 0;
    }

    return 1;
}

