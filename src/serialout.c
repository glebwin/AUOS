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
