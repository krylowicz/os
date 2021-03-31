[bits 32]

; defining some constants
VIDEO_MEMORY equ 0xb8000 ; 80x25
WHITE_ON_BLACK equ 0x0f

print_string_pm:
  pusha
  mov edx, VIDEO_MEMORY ; set edx register to the start of video memory

print_string_pm_loop:
  mov al, [ebx] ; store the char at ebx to in al
  mov ah, WHITE_ON_BLACK ; store the attribute in ah

  cmp ah, 0 ; if al == 0 happens and the end of string
  je print_string_pm_done

  mov [edx], ax ; store char and atributes at current char cell
  add ebx, 1 ; move to the next char in the string
  add edx, 2 ; move to next char in cell in vid mem

  jmp print_string_pm_loop

print_string_pm_done:
  popa
  ret
