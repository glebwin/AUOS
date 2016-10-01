#ifndef SERIALOUT_H
#define SERIALOUT_H

#include <stdint.h>

void init_serial();
void putchar(char c);
void putstring(const char *s);
void putdec(uint64_t d);

#endif
