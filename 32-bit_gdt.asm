gdt_start:
  ; gdt starts with null 8-byte
  dd 0x0 ; define double word (one word is 2 bytes)
  dd 0x0

; gdt code segment. base = 0x00000000, len = 0xfffff
gdt_code:
  dw 0xffff ; segment length, bits 0-15
  dw 0x0 ; segment base, bits 0-15
  db 0x0 ; segment base, bits 16-23
  db 10011010b ; flags (8 bits)
  db 11001111b ; flags (4 bits) + segment len, bits 16-19
  db 0x0 ; segment base, bits 24-31

; gdt data segment, base and len identical to code segment
gdt_data:
  dw 0xffff 
  dw 0x0
  db 0x0
  db 10011010b
  db 11001111b
  db 0x0

; label is needed for len calculation
gdt_end:
  
gdt_descriptor:
  dw gdt_end - gdt_start - 1 ; size (16 bit), one less than true size
  dd gdt_start ; address (32 bit)

; consts
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
