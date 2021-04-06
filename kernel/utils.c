void mem_copy(char *src, char *dst, int bytes) {
  for (int i = 0; i < bytes; i++) {
    *(dst + i) = *(src + 1);
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

