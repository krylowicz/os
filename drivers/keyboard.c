#include <stdint.h>
#include "ports.h"
#include "screen.h"
#include "../kernel/utils.h"
#include "../cpu/isr.h"

#define SC_MAX 57
#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

const char sc_ascii[] = {
  '?', '?', '1', '2', '3', '4', '5', '6',
  '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
  'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
  'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
  'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};

static void keyboard_callback(registers_t *r) {
  uint8_t scancode = port_byte_in(0x60);

  if (scancode > SC_MAX) return;

  if (scancode == BACKSPACE) {
    if (backspace(key_buffer)) {
      print_backspace();
    }
  } else if (scancode == ENTER) {
    print_nl();
    execute(key_buffer);
    key_buffer[0] = '\0';
  } else {
    char letter = sc_ascii[(int)scancode];
    append(key_buffer, letter);
    char s[2] = {letter, '\0'};
    print_string(s);
  }
}

void init_keyboard() {
  register_interrupt_handler(IRQ1, keyboard_callback);
}

