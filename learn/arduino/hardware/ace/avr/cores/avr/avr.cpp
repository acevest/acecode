#include <AceAvr.h>

// On the board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATMEGA328P
//
//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5) (D 19)
//      (D 0) PD0  2|    |27  PC4 (AI 4) (D 18)
//      (D 1) PD1  3|    |26  PC3 (AI 3) (D 17)
//      (D 2) PD2  4|    |25  PC2 (AI 2) (D 16)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1) (D 15)
//      (D 4) PD4  6|    |23  PC0 (AI 0) (D 14)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13)
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
//      (D 7) PD7 13|    |16  PB2 (D 10) PWM
//      (D 8) PB0 14|    |15  PB1 (D 9)  PWM
//                  +----+
//
// (PWM+ indicates the additional PWM pins on the ATmega168.)

uint8_t get_digital_pin_port(uint8_t pin) {
    if(pin < 8) {
        return PD;
    }

    if(pin < 14) {
        return PB;
    }

    return PC;
}

uint8_t get_digital_pin_bit_mask(uint8_t pin) {
    uint8_t seg = 0;

    switch(get_digital_pin_port(pin)) {
    case PB:
        seg = 8;
        break;
    case PC:
        seg = 14;
        break;
    case PD:
        seg = 0;
        break;
    }

    return (1 << (pin - seg));
}

volatile uint8_t* get_digital_pin_port_mode_register(uint8_t pin) {
    switch(get_digital_pin_port(pin)) {
    case PB:
        return &DDRB;
    case PC:
        return &DDRC;
    case PD:
        return &DDRD;
    }

    return 0;
}


volatile uint8_t* get_digital_pin_port_output_register(uint8_t pin) {
    switch(get_digital_pin_port(pin)) {
    case PB:
        return &PORTB;
    case PC:
        return &PORTC;
    case PD:
        return &PORTC;
    }

    return 0;
}
