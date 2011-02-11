
/***************************************************************************\
*                                                                           *
* 4. TEMPERATURE SENSORS                                                    *
*                                                                           *
\***************************************************************************/

/*
	TEMP_HYSTERESIS: actual temperature must be target +/- hysteresis before target temperature can be achieved.
	  NOTE: format is 30.2 fixed point, so value of 20 actually means +/- 5 degrees

	TEMP_RESIDENCY_TIME: actual temperature must be close to target for this long before target is achieved

	temperature is "achieved" for purposes of M109 and friends when actual temperature is within [hysteresis] of target for [residency] seconds
*/
#define	TEMP_HYSTERESIS				20
#define	TEMP_RESIDENCY_TIME		60

// which temperature sensors are you using? (intercom is the gen3-style separate extruder board)
// #define	TEMP_MAX6675
#define	TEMP_THERMISTOR
// #define	TEMP_AD595
// #define	TEMP_PT100
// #define	TEMP_INTERCOM

// ANALOG_MASK is a bitmask of all analog channels used- bitwise-or them all together
#define	ANALOG_MASK				6

/***************************************************************************\
*                                                                           *
* Define your temperature sensors here                                      *
*                                                                           *
* for GEN3 set temp_type to TT_INTERCOM and temp_pin to 0                   *
*                                                                           *
* Types are same as TEMP_ list above- TT_MAX6675, TT_THERMISTOR, TT_AD595,  *
*   TT_PT100, TT_INTERCOM. See list in temp.c.                              *
*                                                                           *
\***************************************************************************/

#ifndef DEFINE_TEMP_SENSOR
	#define DEFINE_TEMP_SENSOR(...)
#endif

//                 name       type          pin
DEFINE_TEMP_SENSOR(extruder,	TT_THERMISTOR,		2)
DEFINE_TEMP_SENSOR(noheater,	TT_THERMISTOR,		1)
// DEFINE_TEMP_SENSOR(bed,				TT_THERMISTOR,	1)

/***************************************************************************\
*                                                                           *
* 5. HEATERS                                                                *
*                                                                           *
\***************************************************************************/

// check if heater responds to changes in target temperature, disable and spit errors if not
// largely untested, please comment in forum if this works, or doesn't work for you!
// #define	HEATER_SANITY_CHECK

/***************************************************************************\
*                                                                           *
* Define your heaters here                                                  *
*                                                                           *
* If your heater isn't on a PWM-able pin, set heater_pwm to zero and we'll  *
*   use bang-bang output. Note that PID will still be used                  *
*                                                                           *
* See Appendix 8 at the end of this file for PWMable pin mappings           *
*                                                                           *
* If a heater isn't attached to a temperature sensor above, it can still be *
*   controlled by host but otherwise is ignored by firmware                 *
*                                                                           *
* To attach a heater to a temp sensor above, simply use exactly the same    *
*   name - copy+paste is your friend                                        *
*                                                                           *
* Some common names are 'extruder', 'bed', 'fan', 'motor'                   *
*                                                                           *
\***************************************************************************/

#ifndef DEFINE_HEATER
	#define DEFINE_HEATER(...)
#endif

//               name      port   pin    pwm
DEFINE_HEATER(extruder,	PORTD, PINB3, OCR0A)
//DEFINE_HEATER(bed,			PORTD, PINB4, OCR0B)
// DEFINE_HEATER(fan,			PORTD, PINB4, OCR0B)
// DEFINE_HEATER(chamber,	PORTD, PIND7, OCR2A)
// DEFINE_HEATER(motor,		PORTD, PIND6, OCR2B)

// and now because the c preprocessor isn't as smart as it could be,
// uncomment the ones you've listed above and comment the rest.
// NOTE: these are used to enable various capability-specific chunks of code, you do NOT need to create new entries unless you are adding new capabilities elsewhere in the code!
// so if you list a bed above, uncomment HEATER_BED, but if you list a chamber you do NOT need to create HEATED_CHAMBER
// I have searched high and low for a way to make the preprocessor do this for us, but so far I have not found a way.

#define	HEATER_EXTRUDER HEATER_extruder
// #define HEATER_BED HEATER_bed
// #define HEATER_FAN HEATER_fan

// --------------------------------------------------------------------------
// values reflecting the gearing of your machine

// calculate these values appropriate for your machine
#define	STEPS_PER_MM_X		157.480
#define	STEPS_PER_MM_Y		157.480
#define	STEPS_PER_MM_Z		157.480
//Actually, .4803, everything will be off by .0001%

// http://blog.arcol.hu/?p=157 may help with this next one
#define	STEPS_PER_MM_E		40

// --------------------------------------------------------------------------
// values depending on the capabilities of your stepper motors and other mechanics
// again, all numbers are integers specified in mm/minute

// used for G0 rapid moves and as a cap for all other feedrates
#define	MAXIMUM_FEEDRATE_X	400	
#define	MAXIMUM_FEEDRATE_Y  400
#define	MAXIMUM_FEEDRATE_Z	400
#define	MAXIMUM_FEEDRATE_E	650

// used when searching endstops and similar
#define	SEARCH_FEEDRATE_X	50
#define	SEARCH_FEEDRATE_Y	50
#define	SEARCH_FEEDRATE_Z	50
#define	SEARCH_FEEDRATE_E	50


/*
	acceleration, reprap style.
		Each movement starts at the speed of the previous command and accelerates or decelerates linearly to reach target speed at the end of the movement.
		Can also be set in Makefile
*/
//#define ACCELERATION_REPRAP

/*
	acceleration and deceleration ramping.
		Each movement starts at (almost) no speed, linearly accelerates to target speed and decelerates just in time to smoothly stop at the target. alternative to ACCELERATION_REPRAP
		Can also be set in Makefile
*/
//#define ACCELERATION_RAMPING

// how fast to accelerate when using ACCELERATION_RAMPING
// smaller values give quicker acceleration
// valid range = 1 to 8,000,000; 500,000 is a good starting point
#define ACCELERATION_STEEPNESS	500000

#ifdef ACCELERATION_REPRAP
	#ifdef ACCELERATION_RAMPING
		#error Cant use ACCELERATION_REPRAP and ACCELERATION_RAMPING together.
	#endif
#endif

/*
firmware build options
*/

// this option makes the step interrupt interruptible.
// this should help immensely with dropped serial characters, but may also make debugging infuriating due to the complexities arising from nested interrupts
#define		STEP_INTERRUPT_INTERRUPTIBLE	1

/*
	Xon/Xoff flow control.
		Redundant when using RepRap Host for sending GCode, but mandatory when sending GCode files with a plain terminal emulator, like GtkTerm (Linux), CoolTerm (Mac) or HyperTerminal (Windows).
		Can also be set in Makefile
*/
#define	XONXOFF
// #define DEBUG


/*
	how often we overflow and update our clock; with F_CPU=16MHz, max is < 4.096ms (TICK_TIME = 65535)
*/
#define		TICK_TIME			2 MS
#define		TICK_TIME_MS	(TICK_TIME / (F_CPU / 1000))

#define TH_COUNT 8

/*
	move buffer size, in number of moves
		note that each move takes a fair chunk of ram (69 bytes as of this writing) so don't make the buffer too big - a bigger serial readbuffer may help more than increasing this unless your gcodes are more than 70 characters long on average.
		however, a larger movebuffer will probably help with lots of short consecutive moves, as each move takes a bunch of math (hence time) to set up so a longer buffer allows more of the math to be done during preceding longer moves
*/
#define	MOVEBUFFER_SIZE	8

/*
	FiveD on Arduino implements a watchdog, which has to be reset every 250ms or it will reboot the controller. As rebooting (and letting the GCode sending application trying to continue the build with a then different Home point) is probably even worse than just hanging, and there is no better restore code in place, this is disabled for now.
*/
// #define USE_WATCHDOG

/*
	analog subsystem stuff
	REFERENCE - which analog reference to use. see analog.h for choices
	ANALOG_MASK - which analog inputs we will be using, bitmask. eg; #define ANALOG_MASK	MASK(AIO0_PIN) | MASK(3) for AIN0 and AIN3
*/
#define	REFERENCE			REFERENCE_AVCC

#ifndef	ANALOG_MASK
#define	ANALOG_MASK		0
#endif

/*
	Machine Pin Definitions
*/

#include	"arduino.h"

/*
	RESERVED pins
	we NEED these for communication
*/

#define	RESERVED_RXD					DIO0
#define	RESERVED_TXD					DIO1

/*
	these pins are used for the MAX6675
*/
#ifdef TEMP_MAX6675
#define	RESERVED_SCK					DIO13
#define	RESERVED_MISO					DIO12
#define	RESERVED_MOSI					DIO11
#define	RESERVED_SS						DIO10
#endif

/*
	Size of the largest dimension of the bed
*/
#define MAX_BED_SIZE	180

/*
	user defined pins
	adjust to suit your electronics,
	or adjust your electronics to suit this
	Arudino A0=D14 A1=D15 A2=D16 A3=D17 A4=D18 A5=D19
*/

#define	X_STEP_PIN					DIO2
#define	X_DIR_PIN					DIO3
#define	X_MIN_PIN					DIO4

#define	Y_STEP_PIN					DIO10
#define	Y_DIR_PIN					DIO7
#define	Y_MIN_PIN					DIO8

#define	Z_STEP_PIN					AIO5
#define	Z_DIR_PIN					AIO4
#define	Z_MIN_PIN					AIO3

#define	E_STEP_PIN					DIO11
#define	E_DIR_PIN					DIO13
//D13=Y_MAX?
//A2=Z_MAX
//D9=X_MAX
//A1 = free
//A2 = free

#define	STEPPER_ENABLE_PIN		AIO1

// list of PWM-able pins and corresponding timers
// timer1 is used for step timing so don't use OC1A/OC1B (DIO9/DIO10)
// OC0A												DIO6
// OC0B												DIO5
// OC1A												DIO9
// OC1B												DIO10
// OC2A												DIO11
// OC2B												DIO3

#define	HEATER_PIN						DIO5
//#define	HEATER_PWM						OCR0A
//#define BANG_BANG
// With 24V heater on resistor speced for 12V, ne3ver give more than half.
#define BANG_BANG_ON 128
#define BANG_BANG_OFF 20

#define	FAN_PIN								DIO6
#define	FAN_PWM								OCR0B

/* If your endstops are inverted, set this to 1 instead of 0 */
#define ENDSTOPS_OK_VALUE    1
/* Number of consecutive readings on all endstops which must match before assuming we're there. */
#define DEBOUNCE_ENDSTOPS    5000

// --------------------------------------------------------------------------
// you shouldn't need to edit anything below this line

// same as above with 25.4 scale factor
#define	STEPS_PER_IN_X		((uint32_t) ((25.4 * STEPS_PER_MM_X) + 0.5))
#define	STEPS_PER_IN_Y		((uint32_t) ((25.4 * STEPS_PER_MM_Y) + 0.5))
#define	STEPS_PER_IN_Z		((uint32_t) ((25.4 * STEPS_PER_MM_Z) + 0.5))
#define	STEPS_PER_IN_E		((uint32_t) ((25.4 * STEPS_PER_MM_E) + 0.5))



/*
	fan
*/

#ifdef	FAN_PIN
	#ifdef	FAN_PWM
		#define	enable_fan()				do { TCCR0A |=  MASK(COM0B1); } while (0)
		#define	disable_fan()				do { TCCR0A &= ~MASK(COM0B1); } while (0)
	#else
		#define	enable_fan()				WRITE(FAN_PIN, 1)
		#define	disable_fan()				WRITE(FAN_PIN, 0);
	#endif
#else
	#define	enable_fan()				if (0) {}
	#define	disable_fan()				if (0) {}
#endif

#define F_CPU 16000000L
#define PID_SCALE 1024L

