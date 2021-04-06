#include "../drivers/screen.h"
#include "utils.h"

void main() {
  clear_screen();
  char line;
  for (int i = 1; i <= 35; i++) {
    int_to_string(i, line);
    print_string(line);
    print_nl();
  }
}

