print_hex:
  pusha
  mov cx, 0

hex_loop:
  cmp cx, 4
  je end

  ; convert last digit of dx to ascii
  mov ax, dx ; ax is working register
  and ax, 0x000f ; 0x1234 -> 0x0004
  add al, 0x30 ; add 0x30 to convert to ascii
  cmp al, 0x39 ; if > 9 add extra 8 for 'A' to 'F'
  jle step2
  add al, 7

step2:
  mov bx, HEX_OUT + 5
  sub bx, cx
  mov [bx], al
  ror dx, 4

  add cx, 1
  jmp hex_loop

end:
  mov bx, HEX_OUT
  call print
  popa
  ret

HEX_OUT: db '0x0000',0
