gdt_start:
  dd 0x0 ; 4 byte
  dd 0x0 ; 4 byte

; gdt code segment base = 0x00000000, len = 0xffffffff
gdt_code:
  dw 0xffff ; segment len, bits 0-15
  dw 0x0 ; segment base, bits 0-15
  db 0x0 ; segment base, bits 16-23
  db 10011010b ; flags (8bits)
  db 11001111b ; flags (4bits) + segment len, bits 16-19
  db 0x0

gdt_data:
  dw 0xffff 
  dw 0x0
  db 0x0 
  db 10010010b 
  db 11001111b 
  db 0x0

gdt_end:
  
gdt_descriptor:
  dw gdt_end - gdt_start - 1 ; size 16-bit, one less than actual size
  dd gdt_start ; 32 bit

; consts
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
