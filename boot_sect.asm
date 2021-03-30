[org 0x7c00] ; bootsector code offset

mov bp, 0x8000 ; intialize stack away from boot sector (remember it grows downwards)
mov sp, bp ; stack pointer = base pointer

mov bx, 0x9000 ; ex:bx = 0x0000:0x9000 = 0x09000
mov dh, 2 ; read 2 sectors
;call disk_load

mov dx, [0x9000] ; first word from 1st sector
call print_hex

call print_nl

mov dx, [0x9000 + 512] ; first word from 2n sector
call print_hex

jmp $

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"
%include "boot_sect_disk.asm"

times 510-($-$$) db 0
dw 0xaa55

; initialize 2 sectors after boot sector
times 256 dw 0xdada ; sector 2 = 512 bytes
times 256 dw 0xface ; sector 3 = 512 bytes
