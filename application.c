/*
 * application.c
 *
 *  Created on: Mar 4, 2022
 *      Author: HAZEM-PC
 */

#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h>
#include "util/delay.h"

int main()
{
	uint16 value=0;
	/* Enable Global Interrupt I-Bit */
		SREG |= (1<<7);
	/* Initialize both the LCD and ultrasonic driver */
		LCD_init();
		Ultrasonic_init();
		LCD_displayString("Distance = ");
		while(1)
		{
			value=Ultrasonic_readDistance();
			LCD_moveCursor(0,10);
			LCD_intgerToString(value);
			LCD_displayString(" CM");
			_delay_ms(50);
		}
}

