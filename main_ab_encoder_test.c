/*
* main_ab_encoder_test.c
*
* Created: 28/08/2020 10:30:49
*  Author: IHA
*/

#include <stddef.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <display_7seg.h>
#include <ab_encoder.h>

int main(void) {
	display_7seg_initialise(NULL);
	display_7seg_powerUp();
	ab_encoder_init();
	sei();

	//float number = 0.0;
	int8_t percent = 0;

	while (1)
	{
		percent += ab_encoder_currentPosition(true);

		if (percent < -100)
		{
			percent = -100;
		}
		else if (100 < percent)
		{
			percent = 100;
		}

		_delay_ms(50);
		display_7seg_display((float)percent,0);
		//display_7seg_display(number++, 3);
		//if (number>100.0) number = -100.0;
	}
}