#include "bit.h"
#include "ioport.h"
#include "serialout.h"

#define SERIAL_PORT 0x3f8

void init_serial()
{
    out8(SERIAL_PORT + 3, BIT(7));
    out8(SERIAL_PORT + 0, 1);
    out8(SERIAL_PORT + 1, 0);

    out8(SERIAL_PORT + 3, BIT(1) | BIT(0));

    out8(SERIAL_PORT + 1, 0);
}

void putchar(char c)
{
    while (!(in8(SERIAL_PORT + 5) & BIT(5)));
    out8(SERIAL_PORT + 0, c);
}

void putstring(const char *s)
{
    while (*s)
    {
        putchar(*s);
        s++;
    }
}

void putdec(uint64_t d)
{
    if (!d)
    {
        putchar('0');
        return;
    }

    static char stack[20];
    static int8_t top = 0;
    for (; d; d /= 10)
        stack[top++] = d % 10;
    for (top--; top >= 0; top--)
        putchar('0' + stack[top]);
}
