#include "bit.h"
#include "interrupt.h"
#include "ioport.h"
#include "pit.h"

#define COMMAND_PORT 0x43
#define DATA_PORT 0x40

void init_pit()
{
    out8(COMMAND_PORT, BIT(5) | BIT(4) | BIT(2));
    out8(DATA_PORT, 0xff);
    out8(DATA_PORT, 0xff);

    unmask_inputs_master(BIT(0));
}
