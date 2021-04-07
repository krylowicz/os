#pragma once
#include <stdint.h>
#include <stdbool.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

void mem_copy(uint8_t *src, uint8_t *dst, uint32_t bytes);
void int_to_string(int n, char str[]);
int len(char s[]);
void reverse(char s[]);
void append(char s[], char n);
int compare_string(char s1[], char s2[]);
bool backspace(char buffer[]);

