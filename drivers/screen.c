#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "stdint.h"

void set_cursor(int offset) {
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_cursor() {
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2;
}

int get_offset(int col, int row) {
  return 2 * (row * MAX_COLS + col);
}

int get_row_from_offset(int offset) {
  return offset / (2 * MAX_COLS);
}

int move_offset_nl(int offset) {
  return get_offset(0, get_row_from_offset(offset) + 1);
}

void print_char_at(char character, int offset) {
  uint8_t *vidmem = VIDEO_ADDRESS;
  vidmem[offset] = character;
  vidmem[offset + 1] = WHITE_ON_BLACK;
}

int scroll_ln(int offset) {
  mem_copy(get_offset(0,1) + VIDEO_ADDRESS,
           get_offset(0,0) + VIDEO_ADDRESS,
           MAX_COLS * (MAX_ROWS - 1) * 2
  );

  for (int i = 0; i < MAX_COLS; i++) {
    print_char_at(' ', get_offset(i, MAX_ROWS - 1));
  }

  return offset - 2 * MAX_COLS;
}

void print_string(char *string) {
  int offset = get_cursor();
  int i = 0;
  while (string[i] != 0) {
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
      offset = scroll_ln(offset);
    }

    if (string[i] == '\n') {
      offset = move_offset_nl(offset);
    } else {
      print_char_at(string[i], offset);
      offset += 2;
    }
    i++;
  }
  set_cursor(offset);
}

void print_nl() {
  int offset = move_offset_nl(get_cursor());
  if (offset >= MAX_ROWS * MAX_COLS * 2)
    offset = scroll_ln(offset);

  set_cursor(offset);
}

void clear_screen() {
  int screen_size = MAX_COLS * MAX_ROWS;
  for (int i = 0; i < screen_size; i++) 
    print_char_at(' ', i * 2);

  set_cursor(get_offset(0, 0));
}

void print_backspace() {
  set_cursor(get_cursor() - 2);
  print_string(" ");
  set_cursor(get_cursor() - 2);
}

