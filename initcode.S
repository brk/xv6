# Initial process execs /init.

#include "syscall.h"
#include "traps.h"

# proc.c copies this file's code and puts it in virtual memory address 0,
# and begins executing the first bytes (regardless of symbol name, etc).

# exec(init, argv)
.globl init_start
init_start:
  pushl $argv
  pushl $init
  pushl $0  // where caller pc would be
  movl $SYS_exec, %eax
  int $T_SYSCALL

# for(;;) exit();
exit:
  movl $SYS_exit, %eax
  int $T_SYSCALL
  jmp exit

# char init[] = "/init\0";
init:
  .string "/init\0"

# char *argv[] = { init, 0 };
.p2align 2
argv:
  .long init
  .long 0

