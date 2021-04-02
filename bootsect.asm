[org 0x7c00]
KERNEL_OFFSET equ 0x1000
  mov [BOOT_DRIVE], dl 
  mov bp, 0x9000
  mov sp, bp

  mov bx, MSG_REAL_MODE 
  call print
  call print_nl

  call load_kernel ; read the kernel from disk
  call switch_to_pm ; disable interrupts, load GDT,  etc. Finally jumps to 'BEGIN_PM'
  jmp $ ; Never executed

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"
%include "boot_sect_disk.asm"
%include "32-bit_gdt.asm"
%include "32-bit_print.asm"
%include "32-bit_switch.asm"

[bits 16]
load_kernel:
  mov bx, MSG_LOAD_KERNEL
  call print
  call print_nl

  mov bx, KERNEL_OFFSET ; read from disk and store in 0x1000
  mov dh, 2
  mov dl, [BOOT_DRIVE]
  call disk_load
  ret

[bits 32]
BEGIN_PM:
  mov ebx, MSG_PROT_MODE
  call print_string_pm
  call KERNEL_OFFSET ; hand control to the kernel
  jmp $ ; stay here when kernel returns (if ever)


BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

times 510-($-$$) db 0
dw 0xaa55
