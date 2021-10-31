#ifndef __LCD_GUARD__
#define __LCD_GUARD__

#define DATA PORTD
#define RS PORTDbits.RD4
#define EN PORTDbits.RD5
#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdbool.h>

void lcd_send(char data);
void lcd_init(bool display, bool cursor, bool blink);
void lcd_display(bool display, bool cursor, bool blink);
void lcd_write_string(char *string);
void lcd_move_cursor(char address);

#endif