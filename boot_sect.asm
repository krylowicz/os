[org 0x7c00] 
; defining global offset 
; without this 3rd attempt works and with this set now the 2nd one works
; because it now calculates offstet from the beginning of the boot sector

mov ah, 0x0e ; tty mode

; fails because it tries to print memory addres of secret (pointer)
mov al, secret
int 0x10

; this dereferences secret (like *pointer in c)
mov al, [secret]
int 0x10

; add the BIOS starting offset 0x7c00 to the memory addres of secret
mov bx, secret
add bx, 0x7c00
mov al, [bx]
int 0x10

jmp $ ; infinite loop

secret:
  db 'X' ; ASCII 'X' is stored just before zero padding

; zero padding and boot sector number
times 510-($-$$) db 0
dw 0xaa55
