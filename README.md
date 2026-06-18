# 🚦 Smart Traffic Light Controller (Embedded C)

A bare-metal Embedded C project for the ATmega328P microcontroller (Arduino Uno) that simulates a traffic light system with an interactive pedestrian crossing button.

This project bypasses the standard Arduino libraries to demonstrate core embedded systems concepts, including direct hardware register manipulation, GPIO configuration, bitwise operations, and pull-up resistors.

## ✨ Features
* **Bare-Metal C:** Written entirely using AVR hardware registers (`DDRB`, `PORTB`, `PINB`).
* **Interactive Control:** Includes a pedestrian push-button that interrupts the standard traffic flow.
* **Internal Pull-Up Resistors:** Utilizes the microcontroller's internal pull-up resistor for cleaner hardware design (no external resistor needed for the button).
* **Hardware Debounce (Simulated):** Provides realistic delay states for traffic transitions.

## 🛠️ Hardware Requirements
If you are building this physically, you will need:
* 1x Arduino Uno (or standalone ATmega328P)
* 1x Red LED
* 1x Yellow LED
* 1x Green LED
* 3x 220Ω Resistors (for LEDs)
* 1x Pushbutton
* Breadboard and Jumper Wires

### Pin Mapping (ATmega328P Port B)
| Component    | Arduino Pin | AVR Register Bit | Direction |
|--------------|-------------|------------------|-----------|
| Red LED      | Pin 8       | `PORTB0`         | Output    |
| Yellow LED   | Pin 9       | `PORTB1`         | Output    |
| Green LED    | Pin 10      | `PORTB2`         | Output    |
| Pushbutton   | Pin 11      | `PINB3`          | Input     |

## 💻 Circuit Wiring
1. Connect the **anodes (long legs)** of the Red, Yellow, and Green LEDs to Pins 8, 9, and 10 respectively.
2. Connect the **cathodes (short legs)** of the LEDs to Ground (GND) via 220Ω resistors.
3. Connect one side of the **Pushbutton** to Pin 11.
4. Connect the other side of the **Pushbutton** directly to Ground (GND). *(Note: No external resistor is required because the code enables the internal pull-up resistor on Pin 11).*

## 🚀 How to Run

### Option 1: Browser Simulation (Recommended for Beginners)
You can run this code without any physical hardware using Wokwi.
1. Go to [Wokwi.com](https://wokwi.com) and create a new Arduino Uno project.
2. Build the circuit matching the Pin Mapping above.
3. Replace the default `.ino` file with the `main.c` file from this repository.
4. Click **Play** to start the simulation.

### Option 2: Physical Hardware (AVR-GCC Toolchain)
To flash this to a physical Arduino Uno using the command line:

1. **Compile the code:**
   ```bash
   avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
   avr-gcc -mmcu=atmega328p main.o -o main
   avr-objcopy -O ihex -R .eeprom main main.hex
