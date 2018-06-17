/*
 * ------------------------------------------------------------------------
 *   File Name: lib.cpp
 *      Author: Zhao Yanbai
 *              2018-06-17 15:27:28 Sunday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
#include <AceAvr.h>

void set_digital_pin_mode(uint8_t pin, uint8_t mode) {
    uint8_t bit_mask = get_digital_pin_bit_mask(pin);
    volatile uint8_t *mod_reg = get_digital_pin_port_mode_register(pin);
    volatile uint8_t *out_reg = get_digital_pin_port_output_register(pin);

    if(0 == mod_reg || 0 == out_reg) return;

    uint8_t oldSREG = SREG;
    cli();

    switch(mode) {
    case INPUT:
        *mod_reg &= ~bit_mask;
        *out_reg &= ~bit_mask;
        break;
    case INPUT_PULLUP:
        *mod_reg &= ~bit_mask;
        *out_reg |= ~bit_mask;
        break;
    case OUTPUT:
        *mod_reg |= bit_mask;
        break;
    }

    SREG = oldSREG;
}

void digital_write(uint8_t pin, uint8_t val) {
    uint8_t bit_mask = get_digital_pin_bit_mask(pin);
    volatile uint8_t *out_reg = get_digital_pin_port_output_register(pin);

    uint8_t oldSREG = SREG;
    cli();
    val == LOW ? *out_reg &= ~bit_mask : *out_reg |= bit_mask;
    SREG = oldSREG;
}
