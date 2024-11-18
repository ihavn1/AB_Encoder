/**
\file
\brief Driver to AB-Incremental Encoder

\author Ib Havn
\version 1.0.0

\defgroup AB-Incremental Encoder driver
\{
\brief Driver to an AB-Encoder that can be connected to the <I>VIA ARDUINO MEGA2560 Shield rev. 2.0</I>.

The AB-signals from the encoder must be connected to J103 (PORTK) pin 5 and 6 on the <I>VIA ARDUINO MEGA2560 Shield rev. 2.0</I>.

<b>J103 to AB-Encoder</b>
| J103 pin | Encoder Signal | MCU Signal |
| :----:| :------------------------------: | :------------------------------: |
| 6 | A | PK5 |
| 5 | B | PK4 |
| 9 | GND | GND |

\defgroup ab_driver_creation Functions to create and initialize the driver.
\brief How to create the driver.

\defgroup ab_driver_basic_function Basic driver functions
\brief Commonly used functions.
Here you you will find the functions you normally will need.

\defgroup ab_driver_implementation Driver Implementation Details
\brief How the AB-Signals are detected by the driver
\}
*/

#ifndef AB_ENCODER_H_
#define AB_ENCODER_H_
#include <stdint.h>
#include <stdbool.h>

/* ======================================================================================================================= */
/**
\ingroup ab_driver_creation
\brief Initialise the AB-Encoder driver.

Initialise the driver.
The position of the encoder is reset to 0.

\note A call to this function enables the Pin Change Interrupt Request 2 on pin PK4 & PK5.

\note This should only be called ONCE during initialisation of the application.

\note Remember to enable the general interrupt (sei()).
*/
void ab_encoder_init();

/* ======================================================================================================================= */
/**
\ingroup ab_driver_basic_function
\brief Get the position of AB-Encoder.

 Returns the current position of the incremental Encoder
 \param[in] reset_after_read if true will the current position be reset after it is read.
 \return current position of encoder
*/
int16_t ab_encoder_currentPosition(bool reset_after_read);

/**
\addtogroup ab_driver_implementation 
\brief How the AB-Signals are detected by the driver

This driver is using two pin change interrupts to detect when the A & B signals from the AB-Encoder change state.

The AB-Signals can be seen here when the encoder is turned both CW and CCW.

\htmlonly
<script type="WaveDrom">
{signal:
	[
	['CW',
	{name: 'A', wave: '0.H.L.H.L.' },
	{name: 'B', wave: '0H.L.H.L.H' },
	],
	{},	
	['CCW',
	{name: 'A', wave: '0H.L.H.L.H'},
	{name: 'B', wave: 'L.H.L.H.L.'},
	],
	],
	head:{text: 'AB-Encoder - CW/CountUP and CCW/CountDown Scenarios', tick: 0},
}
</script>
\endhtmlonly

In both scenarios the counter in the driver is counted up (CW) or counted down (CCW) on each change of state of the AB-signals.

The driver is implemented as a state machine following this diagram
\htmlonly <img width="75%" src="AB_Encoder_State_machine.svg"> \endhtmlonly
*/
#endif /* AB-ENCODER_H_ */