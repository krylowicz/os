mov bx, 20

cmp bx, 4
jle first_block
cmp bx, 40
jl second_block
mov al, 'C'
jmp end

first_block:
  mov al, 'A'

second_block:
  mov al, 'B'
end:
  mov ah, 0x0e
  int 0x10

jmp $

times 510-($-$$) db 0
dw 0xaa55
