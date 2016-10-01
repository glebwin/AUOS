#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

void init_idt();
void init_pic();
void mask_inputs_master(uint8_t);
void unmask_inputs_master(uint8_t);
void mask_inputs_slave(uint8_t);
void unmask_inputs_slave(uint8_t);

#endif
