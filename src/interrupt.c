#include "bit.h"
#include "desc.h"
#include "interrupt.h"
#include "ioport.h"
#include "memory.h"
#include "serialout.h"

#define MASTER_COMMAND 0x20
#define MASTER_DATA 0x21
#define SLAVE_COMMAND 0xA0
#define SLAVE_DATA 0xA1

#define MASTERS_IDT_BIND 0x20

#define DESCR_NUM 48

struct desc_table_entry
{
    uint16_t offset1;
    uint16_t selector;
    uint16_t attr;
    uint16_t offset2;
    uint32_t offset3;
    uint32_t zero;
} __attribute__((packed));

extern uint64_t handlers[];
static struct desc_table_entry idt[DESCR_NUM];

void init_idt()
{
    for (int i = 0; i < DESCR_NUM; i++)
    {
        uint64_t handler = handlers[i];
        idt[i].offset1 = handler & 0xFFFF;
        idt[i].selector = KERNEL_CS;
        idt[i].attr = BIT(15) | (14 << 8);
        idt[i].offset2 = (handler >> 16) & 0xFFFF;
        idt[i].offset3 = (handler >> 32) & 0xFFFFFFFF;
        idt[i].zero = 0;
    }

    struct desc_table_ptr idtptr = {.size = sizeof(idt) - 1, .addr = (uint64_t)idt};
    write_idtr(&idtptr);
}

void init_pic()
{
    out8(MASTER_COMMAND, BIT(4) | BIT(0));
    out8(SLAVE_COMMAND, BIT(4) | BIT(0));

    out8(MASTER_DATA, MASTERS_IDT_BIND);
    out8(SLAVE_DATA, MASTERS_IDT_BIND + 8);

    out8(MASTER_DATA, BIT(2));
    out8(SLAVE_DATA, 2);

    out8(MASTER_DATA, BIT(0));
    out8(SLAVE_DATA, BIT(0));

    mask_inputs_master(0xff ^ BIT(2));
    mask_inputs_slave(0xff);
}

static uint8_t master_mask = 0;

void mask_inputs_master(uint8_t mask)
{
    master_mask |= mask;
    out8(MASTER_DATA, master_mask);
}

void unmask_inputs_master(uint8_t mask)
{
    master_mask &= 0xff ^ mask;
    out8(MASTER_DATA, master_mask);
}

static uint8_t slave_mask = 0;

void mask_inputs_slave(uint8_t mask)
{
    slave_mask |= mask;
    out8(SLAVE_DATA, slave_mask);
}

void unmask_inputs_slave(uint8_t mask)
{
    slave_mask &= 0xff ^ mask;
    out8(SLAVE_DATA, slave_mask);
}

void handle_interrupt(uint64_t index, uint64_t error)
{
    putstring("Interrupt ");
    putdec(index);
    if (index == 8 || (index >= 10 && index <= 14) || index == 17)
    {
        putstring(" with error ");
        putdec(error);
    }
    putchar('\n');

    if (index >= MASTERS_IDT_BIND && index < MASTERS_IDT_BIND + 8)
        out8(MASTER_COMMAND, BIT(5));
    else if (index >= MASTERS_IDT_BIND + 8 && index < MASTERS_IDT_BIND + 16)
    {
        out8(MASTER_COMMAND, BIT(5));
        out8(SLAVE_COMMAND, BIT(5));
    }
}
