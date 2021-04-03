#include "screen.h"
#include "ports.h"

// private functions declaration
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

// public functions
void kprint_at() {
  // TODO - print message on specific location
}

void kprint(char *msg) {
  kprint_at(msg, -1, -1);
}

// private functions
/*
  if col and rows < 0, print at cursor position
  if attr == 0, use white on black
  returns offset of the next char
  sets the cursor to the returned offset
*/
int print_char(char c, int col, int row, char attr) {
  unsigned char *vidmem = VIDEO_ADDRESS;
  if (!attr) attr = WHITE_ON_BLACK;

  int offset;
  if (col >= 0 && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
  }

  if (c == '\n') {
    row = get_offset_row(offset);
    offset = get_offset(0, row + 1);
  } else {
    vidmem[offset] = c;
    vidmem[offset + 1] = attr;
    offset += 2;
  }

  set_cursor_offset(offset);
  return offset;
}

// use VGA ports to get current cursor pos
int get_cursor_offset() {
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2; // pos * size
}

void set_cursor_offset() {

}

void clear_screen() {
  int screen_size = MAX_COLS * MAX_ROWS;
  char *screen = VIDEO_ADDRESS;

  for (int i = 0; i < screen_size; i++) {
    screen[i*2] = '';
    screen[i*2+1] = WHITE_ON_BLACK;
  }

  set_cursor_offset(get_offset(0,0));
}

int get_offset(int col, int row) {
  return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset) {
  return offset / (2 * MAX_COLS);
}

int get_offset_cols(int offset) {
  return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}
