#include "../drivers/ports.h"

void main() {
  port_byte_out(0x3d4, 14);
  int pos = port_byte_in(0x3d5);
  pos = pos << 8;

  port_byte_out(0x3d4, 15);
  pos += port_byte_in(0x3d5);

  int vga_offset = pos * 2;

  char *vga = 0xb8000;
  vga[vga_offset] = 'X';
  vga[vga_offset + 1] = 0x0f; // white text on black
}

