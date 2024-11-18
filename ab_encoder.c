/*
*  Author: IHA
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <ab_encoder.h>

#define AB_ENCODER_READ_AB ((PINK >> 4) & 3)

static int8_t _current_state;
static int16_t _current_position = 0;

/* ------------------------------------------------------------- */
static const uint8_t _STATE[] =
{
	0, 1, 3, 2
};

/* ------------------------------------------------------------- */
void ab_encoder_init(void)
{
	// Set PK5 & PK4 to input
	DDRK &= ~(_BV(DDK5) | _BV(DDK4));
	// Enable pull-up on PK5 & PK4
	PORTK |= _BV(PK5) | _BV(PK4);

	// Setup to Pin Change Interrupt Request 2 on PINK5 (A) and PINK4 (B)
	PCICR |= _BV(PCIE2);
	PCMSK2 |= _BV(PCINT21) | _BV(PCINT20); 

	_current_state = _STATE[ AB_ENCODER_READ_AB ];
}

/* ------------------------------------------------------------- */
int16_t ab_encoder_currentPosition(bool reset_after_read)
{
	// disable interrupt
	char cSREG = SREG;
	cli();

	int16_t ret = _current_position;
	if ( reset_after_read )
	{
		_current_position = 0;
	}

	// Restore interrupt
	SREG = cSREG;

	return ret;
}

/* ------------------------------------------------------------- */
ISR(PCINT2_vect)
{
	int8_t newState = _STATE[ AB_ENCODER_READ_AB ];
	int8_t diff = newState - _current_state;

	if ( diff == 1 || diff < -1 )
	{
		_current_position--;
	}
	else if ( diff != 0 )
	{
		_current_position++;
	}

	_current_state = newState;
}
