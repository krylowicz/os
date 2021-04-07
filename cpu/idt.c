#include "idt.h"
#include "../kernel/utils.h"

idt_gate_t idt_desc[256];
idtr_t idtr;

void set_idt_gate(int n, uint32_t handler) {
  idt_desc[n].low_offset = low_16(handler);
  idt_desc[n].selector = KERNEL_CS;
  idt_desc[n].unused = 0;
  idt_desc[n].flags = 0x8E;
  idt_desc[n].high_offset = high_16(handler);
}

void load_idt() {
  idtr.base = &idt_desc;
  idtr.limit = 256 * sizeof(idt_desc) - 1;
  asm volatile("lidt (%0)" : : "r" (&idtr));
}
