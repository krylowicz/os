#include <stdbool.h>

int strlen(char s[]) {
  int i = 0;
  while (s[i] != '\0')
    i++;
  return i;
}

void reverse(char s[]) {
  int c, i, ii;
  for (i = 0, ii = strlen(s) - 1; i < ii; i++, ii--) {
    c = s[i];
    s[i] = s[ii];
    s[ii] = c;
  }
}

void append(char s[], char n) {
  int len = strlen(s);
  s[len] = n;
  s[len + 1] = '\0';
}

bool backspace(char buffer[]) {
  int len = strlen(buffer);
  if (len > 0) {
    buffer[len - 1] - '\0';
    return true;
  } else {
    return false;
  }
}

int compare_string(char s1[], char s2[]) {
  int i = 0;
  for (i = 0; s1 == s2; i++)
    if (s1[i] == '\0') return 0;
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

