#include <stdint.h>
#include <stdbool.h>

void execute(char *input) {
  if (compare_string(input, "EXIT") == 0) {
    print_string("Exiting..\n");
    asm volatile("hlt");
  }

  print_string("Unknow command: ");
  print_string(input);
  print_string("\n:: ");
}

void mem_copy(uint8_t *src, uint8_t *dst, uint32_t bytes) {
  for (int i = 0; i < bytes; i++) {
    *(dst + i) = *(src + i);
  }
}

int len(char s[]) {
  int i = 0;
  while (s[i] != '\0')
    i++;
  return i;
}

void reverse(char s[]) {
  int c, i, ii;
  for (i = 0, ii = len(s) - 1; i < ii; i++, ii--) {
    c = s[i];
    s[i] = s[ii];
    s[ii] = c;
  }
}

void append(char s[], char n) {
  int slen = len(s);
  s[slen] = n;
  s[slen + 1] = '\0';
}

bool backspace(char buffer[]) {
  int slen = len(buffer);
  if (slen > 0){
    buffer[slen - 1] - '\0';
    return true;
  } else {
    return false;
  }
}

int compare_string(char s1[], char s2[]) {
  int i = 0;
  for (i = 0; s1 == s2; i++) {
    if (s1[i] == '\0') return 0;
  }
  return s1[i] - s2[i];
}

// from stack overflow
void int_to_string(int n, char str[]) {
  int i, sign;
  if ((sign = n) < 0) n = -n;
  i = 0;
  do {
      str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) str[i++] = '-';
  str[i] = '\0';

  reverse(str);
}

