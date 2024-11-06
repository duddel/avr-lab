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
#include <avr/io.h>
#include <stdint.h>

// 0x18 = PORTB
void ws2812b_bang_byte(const uint8_t portb_pin, const uint8_t data)
{
    const uint8_t pb = PORTB;
    const uint8_t pb_hi = (pb | (1 << portb_pin));
    const uint8_t pb_lo = (pb & ~(1 << portb_pin));

    __asm__ volatile(
        // Prepare first bit
        "ldi r17,0x80\n"
        "mov r16,%[data]\n"
        "and r16,r17\n"
        "brne .send_one\n"
        "rjmp .send_zero\n"

        ".send_one:\n"
        "out 0x18,%[pb_hi]\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "out 0x18,%[pb_lo]\n"
        "nop\n"

        // Prepare next bit
        "lsr r17\n"
        "brcs .done\n"
        "mov r16,%[data]\n"
        "and r16,r17\n"
        "brne .send_one\n"
        // "rjmp .send_zero\n"

        ".send_zero:\n"
        "out 0x18,%[pb_hi]\n"
        "nop\n"
        "nop\n"
        "out 0x18,%[pb_lo]\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"

        // Prepare next bit
        "lsr r17\n"
        "brcs .done\n"
        "mov r16,%[data]\n"
        "and r16,r17\n"
        "brne .send_one\n"
        "rjmp .send_zero\n"

        ".done:\n"

        :                                                          // outputs
        : [pb_hi] "r"(pb_hi), [pb_lo] "r"(pb_lo), [data] "r"(data) // inputs
        : "r16", "r17");                                           // clobbered registers
}
