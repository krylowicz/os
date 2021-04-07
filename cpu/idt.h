#pragma once
#include <stdint.h>

#define KERNEL_CS 0x08

typedef struct {
  uint16_t low_offset;
  uint16_t selector;
  uint8_t unused;
  uint8_t flags;
  uint16_t high_offset;
} __attribute__((packed)) idt_gate_t; // keeps it aligned

// points to interript descriptor array
typedef struct {
  uint16_t limit; // len of idt - 1
  uint32_t base; // address of idt
} __attribute__((packed)) idtr_t;

void set_idt_gate(int n, uint32_t handler);
void load_idt();

