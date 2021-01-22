.macro SYS_EXIT, exit_code
li   a7, 93 /* SYS_exit */
li   a0, \exit_code
ecall
.endm

.macro SYS_SETBOUND_REG, reg, base, bound
li a7, 97 /* SYS_setbound_reg */
li a0, \reg
li a1, \base
li a2, \bound
ecall
.endm

irq_handler:
	li a6, 0x2342 /* success pattern */
	SYS_EXIT 1

.globl _start
_start:

/* setup trap handler for load fault */
la t0, irq_handler
csrw mtvec, t0

SYS_SETBOUND_REG 2, 0x1000, 4 /* R2 ⟵ {0x1000; 0x1000; 4} */

li t0, 0xff
sb t0, 2(x2)                  /* write address 0x1002, check passes */
sb t0, 4(x2)                  /* write address 0x1004, check fails */

/* unreachable */
SYS_EXIT 0
