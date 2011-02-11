// Thermistor lookup table for RepRap Temperature Sensor Boards (http://make.rrrf.org/ts)
// Made with createTemperatureLookup.py (http://svn.reprap.org/trunk/reprap/firmware/Arduino/utilities/createTemperatureLookup.py)
// ./createTemperatureLookup.py --r0=100000 --t0=25 --r1=0 --r2=4580 --beta=4066 --max-adc=1023
// r0: 100000
// t0: 25
// r1: 0
// r2: 4580
// beta: 4066
// max adc: 1023
#define NUMTEMPS 20
// {ADC, Temp in 1/4 degrees C above 0}, // temp
uint16_t temptable[NUMTEMPS][2] PROGMEM = {
   {1, 3395}, // 848.980376954 C
   {41, 1112}, // 278.028347711 C
   {61, 993}, // 248.481137009 C
   {81, 915}, // 228.866058241 C
   {101, 857}, // 214.295174709 C
   {121, 810}, // 202.737974286 C
   {141, 772}, // 193.166793151 C
   {181, 711}, // 177.851568559 C
   {221, 663}, // 165.764291185 C
   {241, 642}, // 160.527806944 C
   {261, 622}, // 155.697673331 C
   {301, 587}, // 146.99285634 C
   {341, 557}, // 139.250526683 C
   {381, 528}, // 132.209022278 C
   {461, 478}, // 119.545513807 C
   {581, 409}, // 102.457129907 C
   {621, 387}, // 96.9454786672 C
   {881, 221}, // 55.490742511 C
   {981, 96}, // 24.0432854283 C
   {1010, 3} // 0.975765549111 C
};
