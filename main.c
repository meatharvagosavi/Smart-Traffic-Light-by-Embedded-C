#ifndef F_CPU
#define F_CPU 16000000UL // Tell the compiler our chip is running at 16 MHz
#endif

#include <avr/io.h>      // Standard library for AVR hardware registers
#include <util/delay.h>  // Library to create precise time delays

// Define our hardware pins on Port B
#define RED_LED     PORTB0  // Pin 8 on Arduino Uno
#define YELLOW_LED  PORTB1  // Pin 9 on Arduino Uno
#define GREEN_LED   PORTB2  // Pin 10 on Arduino Uno
#define BUTTON      PINB3   // Pin 11 on Arduino Uno

int main(void) {
    // 1. SETUP PHASE (Runs once)
    
    // DDRB (Data Direction Register B) configures pins as Inputs (0) or Outputs (1).
    // Here we use bitwise operators to set the LED pins as Outputs.
    DDRB |= (1 << RED_LED) | (1 << YELLOW_LED) | (1 << GREEN_LED);
    
    // Set the Button pin as an Input.
    DDRB &= ~(1 << BUTTON);
    
    // Enable the internal "pull-up" resistor for the button. 
    // This makes the pin read HIGH normally, and LOW when pressed.
    PORTB |= (1 << BUTTON);

    // 2. MAIN EXECUTION LOOP (Runs forever)
    while (1) {
        
        // Default State: Green light is ON, others are OFF
        PORTB |= (1 << GREEN_LED);                            // Turn Green ON
        PORTB &= ~((1 << RED_LED) | (1 << YELLOW_LED));       // Turn Red & Yellow OFF

        // Check if the pedestrian button is pressed.
        // Because of the pull-up resistor, a press connects the pin to ground (LOW / 0).
        if (!(PINB & (1 << BUTTON))) {
            
            // Someone pressed the button! Start the traffic light sequence.
            
            // 1. Green off, Yellow on for 2 seconds
            PORTB &= ~(1 << GREEN_LED);
            PORTB |= (1 << YELLOW_LED);
            _delay_ms(2000); 
            
            // 2. Yellow off, Red on for 5 seconds (Pedestrians cross!)
            PORTB &= ~(1 << YELLOW_LED);
            PORTB |= (1 << RED_LED);
            _delay_ms(5000); 
            
            // 3. Sequence ends, loop restarts, turning Green back on.
        }
    }
    
    return 0; // This will never be reached, but is standard C practice.
}
