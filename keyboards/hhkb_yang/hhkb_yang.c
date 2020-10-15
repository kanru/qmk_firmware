#include "hhkb_yang.h"

extern uint8_t power_save_level;

void keyboard_pre_init_kb(void) {
    // BT power up
    setPinOutput(D5);
    writePinLow(D5);

    // Row selectors
    setPinOutput(B0);
    setPinOutput(B1);
    setPinOutput(B2);

    // Col selectors
    setPinOutput(B3);
    setPinOutput(B4);
    setPinOutput(B5);

    // Key strobe
    setPinOutput(B6);
    writePinHigh(B6);

    // Key: input with pull-up
    setPinInputHigh(D7);

    // Unused pins on Pro2 ANSI
    // Input with pull up to save power
    setPinInputHigh(C6);
    setPinInputHigh(C7);

    // Turn on switch PCB
    setPinOutput(D6);
    writePinLow(D6);
}

void suspend_power_down_kb(void) {
    if (power_save_level > 2) {
        // Disable UART TX to avoid current leakage
        UCSR1B &= ~_BV(TXEN1);
        // Set TX pin to input high
        //setPinInputHigh(D3);
        // Power down BLE module
        writePinHigh(D5);
    }
}

void suspend_wakeup_init_kb(void) {
    // Power up BLE module
    writePinLow(D5);
    // Enable UART TX
    UCSR1B |= _BV(TXEN1);
}
