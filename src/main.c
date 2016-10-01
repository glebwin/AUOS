#include "interrupt.h"
#include "ints.h"
#include "serialout.h"

static void qemu_gdb_hang(void)
{
#ifdef DEBUG
    static volatile int wait = 1;

    while (wait);
#endif
}

void main(void)
{
    qemu_gdb_hang();

    disable_ints();
    init_serial();
    init_idt();
    init_pic();
    enable_ints();

    putstring("System starts\n");
    __asm__ volatile("int $37");

    while (1);
}
