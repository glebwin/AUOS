#include "serialout.h"

static void qemu_gdb_hang(void)
{
#ifdef DEBUG
    static volatile int wait = 1;

    while (wait);
#endif
}

#include <desc.h>
#include <ints.h>

void main(void)
{
    qemu_gdb_hang();

    init_serial();

    struct desc_table_ptr ptr = {0, 0};

    write_idtr(&ptr);

    putstring("System starts");

    while (1);
}
