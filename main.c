/*
 * File:   Code.c
 * Author: dhruvmanish
 * This file combines two melodies, upon the press of a button and plays it using the buzzer at the same time. 
 * Created on October 5, 2021, 4:27 PM
 */


#define F_CPU 1000000UL
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

// Format: note name_ which bit timer _ number of octave

// Fourth octave 8 bit timer frequencies
#define C_8_4 238
#define Db_8_4 224
#define D_8_4 211
#define Eb_8_4 200
#define E_8_4 188
#define F_8_4 178
#define Gb_8_4 168
#define G_8_4 158
#define Ab_8_4 149
#define A_8_4 141
#define Bb_8_4 133
#define B_8_4 125

// Fifth octave 8 bit timer frequencies
#define C_8_5 118
#define Db_8_5 112
#define D_8_5 105
#define Eb_8_5 99
#define E_8_5 94
#define F_8_5 88
#define Gb_8_5 83
#define G_8_5 79
#define Ab_8_5 74
#define A_8_5 70
#define Bb_8_5 66
#define B_8_5 62

// Third octave 16 bit timer frequencies
#define C_16_3 3821
#define Db_16_3 3607
#define D_16_3 3404
#define Eb_16_3 3213
#define E_16_3 3033
#define F_16_3 2863
#define Gb_16_3 2702
#define G_16_3 2550
#define Ab_16_3 2407
#define A_16_3 2271
#define Bb_16_3 2144
#define B_16_3 2024

// Fourth octave 16 bits frequencies
#define C_16_4 1910
#define Db_16_4 1802
#define D_16_4 1701
#define Eb_16_4 1606
#define E_16_4 1515
#define F_16_4 1430
#define Gb_16_4 1350
#define G_16_4 1275
#define Ab_16_4 1202
#define A_16_4 1135
#define Bb_16_4 1072
#define B_16_4 1011

/*
 *
 */

//Declaration of functions
void IO_in(void);
void clock_on(void);
void clock_off(void);

int main(int argc, char** argv) {

    IO_in();

    while (1) {
        if (PIND & (1 << PIND6)) {

        } else {

            // Two arrays for the two melodies, one melody is with a higher octave
            uint8_t music1[36] = {Db_8_4, D_8_4, Eb_8_4, E_8_4, E_8_4, E_8_4, Db_8_4, D_8_4, Db_8_4, C_8_4, C_8_4, C_8_4, 0, Db_8_4, D_8_4, Eb_8_4, E_8_4, E_8_4, E_8_4, 0, Gb_8_4, G_8_4, 0, C_8_5, B_8_5, 0, E_8_4, G_8_4, B_8_5, Bb_8_5, Bb_8_5, Bb_8_5};
            //   Db D Eb E (long) Db ||| D Eb E (long) Eb D Db C (long) Db D Eb E (long) F# G  Eb E F# G C B E G B Bb
            uint16_t music2[36] = {Db_16_3, D_16_3, Eb_16_3, E_16_3, E_16_3, E_16_3, Db_16_3, D_16_3, Db_16_3, C_16_3, C_16_3, C_16_3, 0, Db_16_3, D_16_3, Eb_16_3, E_16_3, E_16_3, E_16_3, 0, Gb_16_3, G_16_3, 0, C_16_4, B_16_4, 0, E_16_3, G_16_3, B_16_4, Bb_16_4, Bb_16_4, Bb_16_4};

            clock_on();

            // For loop function to play all the frequencies of the arrray
            for (int i = 0; i < 36; i++) {
                OCR0A = music1[i];
                OCR1A = music2[i];
                _delay_ms(500);
            }

            clock_off();
        }

    }

    return (EXIT_SUCCESS);
}

void IO_in(void) {
    // Make PB2 (OC0A) an output, starting low)
    PORTB &= (1 << PORTB2);
    DDRB |= (1 << DDB2);

    // Make PB1 (OC1A) an output, starting low)
    PORTB &= (1 << PORTB3);
    DDRB |= (1 << DDB3);

    // Declare Switch an input
    DDRD &= ~(1 << DDD6);
    // Turn on pull ups for
    PORTD |= (1 << PORTD6);

    // Register bits set up for the the 8 bit timer
    TCCR0A = 0x42;
    TCCR0B = 0x02;

    // Register bits set up for the 16 bit timer
    TCCR1A = 0x40;
    TCCR1B = 0x09;
}

void clock_on(void) {

    // Set the bits to turn the clock on
    TCCR1B = 0x09;
    TCCR0B = 0x02;
}

void clock_off(void) {

    // Set the bits to turn the clock off
    TCCR0B = 0x00;
    TCCR1B = 0x00;
}

