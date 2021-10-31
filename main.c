#pragma config WDTE = OFF
#pragma config LVP = 0
#pragma config FCMEN = 0
#pragma config IESO = 0
#pragma config FOSC = 101

#include "lcd.h"
#include "keypad.h"

#define STATUS_INIT 'I'
#define STATUS_OPEN 'O'
#define STATUS_CLOSED 'C'
#define STATUS_LOCKED 'L'

char status = STATUS_INIT;
char clicks = 0;
char code[4];
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
        if (clicks == 3) {
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
            lcd_move_cursor(0x40);
            lcd_write_string("Presione * para cerrar");
            while (1) {
                
            }
        }
    }
    
    
}
