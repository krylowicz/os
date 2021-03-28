print:
  pusha ; pushes all register to the stack

; while (string[i] != 0) { print(string[i] i++ }
start:
  ; comparison  
  mov al, [bx] ; bx is base address of string
  cmp al, 0
  je done

  ; print
  mov ah, 0x0e ; tty mode
  int 0x10

  ; pointer increment
  add bx, 1
  jmp start

done:
  popa ; pops all registers from the stack
  ret

print_nl:
  pusha
  mov ah, 0x0e
  mov al, 0x0a ; new line character
  int 0x10
  mov al, 0x0d ; cariage return
  int 0x10
  popa
  ret
