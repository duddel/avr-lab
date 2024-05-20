/*
Copyright (c) 2024 Alexander Scholz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <avr/interrupt.h>

volatile uint32_t timemeas_now = 0;

void timemeas_init(void)
{
    // Activate CTC (Clear Timer on Compare) mode
    TCCR0A |= (1 << WGM01); // Timer/Counter Control Register A (TCCR0A)

    // Set Clock Select: I/O Clock divided by 8.
    // The I/O Clock is the "base clock" (e.g. the internal crystal),
    // divided by the System Clock Prescaler (e.g. set via fuse)
    TCCR0B |= (1 << CS01); // Timer/Counter Control Register B (TCCR0B)

    // Set output compare value.
    // The value of the Timer/Counter Register (TCNT0) is continuously
    // compared to OCR0A (CTC mode), generating an interrupt on overflow
    // (TIMER0_COMPA_vect). Assumption:
    //  - Internal clock: 8MHz
    //  - System Clock Prescaler: 8
    //  - Clock Select: I/O Clock divided by 8 (s. above, CS01 in TCCR0B)
    // -> 8MHz/8/8 = 125kHz -> 125 ticks take 1ms.
    // -> Setting OCR0A to 125-1 = 124 generates an overflow every 1ms.
    OCR0A = 124; // Output Compare Register A (OCR0A)

#if F_CPU != 1000000
#error OCR0A is set assuming an I/O Clock of 1MHz
#endif

    // Enable Timer/Counter0 Compare Match A interrupt
    TIMSK |= (1 << OCIE0A); // Timer/Counter Interrupt Mask Register (TIMSK)
}

ISR(TIMER0_COMPA_vect)
{
    timemeas_now++;
}
