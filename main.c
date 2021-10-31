#pragma config WDTE = OFF
#pragma config LVP = 0
#pragma config FCMEN = 0
#pragma config IESO = 0
#pragma config FOSC = 101

#include "lcd.h"
#include "keypad.h"

void main(void) {
    OSCCON = 0x79;
    
    keypad_init();
    
    __delay_ms(32);
    lcd_init(true, false, false);
    lcd_move_cursor(0x03);
    lcd_write_string("Bienvenido");
    lcd_move_cursor(0x40);
    lcd_write_string("Establezca clave");
    
    while(1);
}
