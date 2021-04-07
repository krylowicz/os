#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "utils.h"

void main() {
  clear_screen();
  print_string("installing ISRs\n");
  isr_install();

  print_string("enabling external interrupts\n");
  asm volatile("sti");
}

