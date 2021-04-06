global _start

[bits 32]

_start:
  [extern main] ; this tells the assembler that main won't
                ; be found in this source file
  call main ; calls c function
  jmp $
