; there are 16-bits address segments that are shifted 4 bits left
; and then the memory value is added to this segement resulting in absolute address
; we can now access 2^20

mov ah, 0x0e ; tty mode

mov al, [data] 
int 0x10

mov bx, 0x7c0
mov ds, bx ; from now all memory referenced will be offseted by ds
mov al, [data]
int 0x10

mov al, [es:data]
int 0x10

mov bx, 0x7c0
mov es, bx
mov al, [es:data]
int 0x10

jml $

data:
  db "X"

times 510-($-$$) db 0
dw 0xaa55
