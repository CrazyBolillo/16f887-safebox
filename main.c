#pragma config DEBUG = 1
#pragma config LVP = 0
#pragma config FCMEN = 0
#pragma config IESO = 0
#pragma config BOREN = 00
#pragma config CPD = 0
#pragma config CP = 0
#pragma config MCLRE = 0
#pragma config PWRTE = 1
#pragma config WDTE = 0
#pragma config FOSC = 101

#include "lcd.h"
#include "keypad.h"
#include <stdint.h>

#define CODE_LEN 4
#define ATTEMPT_LIMIT 3

#define STATUS_INIT 'I'
#define STATUS_OPEN 'O'
#define STATUS_CLOSED 'C'
#define STATUS_LOCKED 'L'

char status = STATUS_INIT;
uint8_t clicks = 0;
uint8_t attempt_count = 0;
char code[CODE_LEN];
char attempt[CODE_LEN];
char key = 0;

char convert_key(char key) {
    switch (key) {
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return 'A';
        case 5: return '4';
        case 6: return '5';
        case 7: return '6';
        case 8: return 'B';
        case 9: return '7';
        case 10: return '8';
        case 11: return '9';
        case 12: return 'C';
        case 13: return '*';
        case 14: return '0';
        case 15: return '#';
        case 16: return 'D';
        default: return 0;
    }
}

bool verify_code() {
    for (uint8_t index = 0; index != CODE_LEN; index++) {
        if (code[index] != attempt[index]) {
            return false;
        }
    }
   
    return true;
}

void main(void) {
    OSCCON = 0x79;
    
    keypad_init();
    __delay_ms(32);
    lcd_init(true, false, false);
    lcd_move_cursor(0x03);
    lcd_write_string("Bienvenido");
    lcd_move_cursor(0x40);
    lcd_write_string("Establezca clave");
    
    // Initialize before going into main loop.
    while (status == STATUS_INIT) {
        if (clicks == CODE_LEN) {
            status = STATUS_OPEN;
            clicks = 0;
            break;
        }
        
        key = convert_key(keypad_read());
        if ((key >= '0') && (key <= '9')) {
            code[clicks] = key;
            clicks++;
        }
    }
    
    // Initilization  complete. Main program loop starts.
    while (1) {
        while (status == STATUS_OPEN) {
            lcd_clear_display();
            lcd_move_cursor(0x04);
            lcd_write_string("ABIERTO");
            lcd_move_cursor(0x43);
            lcd_write_string("Cerrar con *");
            while (status == STATUS_OPEN) {
                key = keypad_read();
                if (key == 13) {
                    status = STATUS_CLOSED;
                    break;
                }
            }
        }
        while (status == STATUS_CLOSED) {
            lcd_clear_display();
            lcd_move_cursor(0x04);
            lcd_write_string("CERRADO");
            lcd_move_cursor(0x46);
            clicks = 0;
            while (status == STATUS_CLOSED) {
                if (clicks == CODE_LEN) {
                    clicks = 0;
                    if (verify_code()) {
                        status = STATUS_OPEN;
                        break;
                    }
                    else {
                        lcd_move_cursor(0x46);
                        lcd_write_string("    ");
                        lcd_move_cursor(0x46);
                        attempt_count++;
                    }
                }
                key = convert_key(keypad_read());
                if ((key >= '0') && (key <= '9')) {
                    lcd_write_char(key);
                    attempt[clicks] = key;
                    clicks++;
                }
            }
        }
    }
    
    
}
