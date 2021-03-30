disk_load:
  pusha
  push dx

  mov ah, 0x02 ; BIOS read sector function
  mov al, dh ; dh = number of sectors to read
  mov cl, 0x02 ; 0x01 is boot sector so 0x02 is first available sector
  mov ch, 0x00 ; ch = cylinder
  mov dh, 0x00 ; dh = head number
  int 0x13
  jc disk_error

  pop dx
  cmp al, dh ; if al (sectors read) != dh (sectors expected)
  jne sectors_error ; display error message
  popa
  ret

disk_error:
  mov bx, DISK_ERROR
  call print 
  call print_nl
  mov dh, ah ; ah = error code, dl = disk drive
  call print_hex
  jmp disk_loop

sectors_error:
  mov bx, SECTORS_ERROR
  call print

disk_loop:
  jmp $

DISK_ERROR db "Disk read error",0
SECTORS_ERROR db "Incorrect number of sectors read",0
