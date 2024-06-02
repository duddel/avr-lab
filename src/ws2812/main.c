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
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "../ws2812b_attiny13.h"

#define NUM_LED 24

const uint8_t palette[6][3] = {
    {63, 0, 0},
    {63, 11, 0},
    {63, 63, 0},
    {0, 63, 0},
    {6, 17, 36},
    {16, 0, 39}};

const uint8_t sequence[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
const uint8_t len_sequence = 12;

// Used by ws2812b_set_color_no_reset() to set DDRB and
// the actual data bit values in PORTB
const uint8_t led_pin_mask = (1 << PB1);

int main(void)
{
    uint8_t sequence0 = 0;
    while (1)
    {
        // Bit-Banging. No fancy calculations in this loop!
        for (uint8_t i = 0; i < NUM_LED; i++)
        {
            ws2812b_set_color_no_reset(led_pin_mask,
                                       palette[sequence[(sequence0 + i) % len_sequence]][0],
                                       palette[sequence[(sequence0 + i) % len_sequence]][1],
                                       palette[sequence[(sequence0 + i) % len_sequence]][2]);
        }

        sequence0 = (sequence0 + 1) % len_sequence;
        _delay_ms(100);
    }
}
