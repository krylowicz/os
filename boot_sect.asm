mov ah, 0x0e ; tty mode

mov bp, 0x8000 ; initializing the stack far away fom 0x7c00
mov sp, bp ; if the stack is empty then sp points to bp

push 'A'
push 'B'
push 'C'

mov al, [0x7ffe] ; 0x8000 - 0x2 (the stack grows downwards)
int 0x10

mov al, [0x8000]
int 0x10 ; this won't work, only accessing stack top is valid

; we can pop only full words (unit of data used by cpu)
; so we need aux register to set the lower bytes
pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

; data that has been popped from the stack is garbage now
mov al, [0x8000]
int 0x10

jmp $

; zero padding and boot sector number
times 510-($-$$) db 0
dw 0xaa55
