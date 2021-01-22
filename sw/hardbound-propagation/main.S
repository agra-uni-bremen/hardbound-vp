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
	/* Check mcause for hardbound exception */
	csrr t0, mcause
	li t1, 24  /* hardbound exception */
	beq t0, t1, succ
	SYS_EXIT 0 /* fail */
succ:
	li a6, 0x2342 /* success pattern */
	SYS_EXIT 1

.globl _start
_start:

/* setup trap handler for load fault */
la t0, irq_handler
csrw mtvec, t0

/* configure x2 to hold a pointer to 0x1000 */
SYS_SETBOUND_REG 2, 0x1000, 4 /* R2 ⟵ {0x1000; 0x1000; 4} */

/* increment and decrement x2, propagating bounds to x4 */
li x1, 1
add x3, x2, x1
sub x4, x3, x1

/* move x4 to x5 (value should be propagated) */
mv x5, x4

li x6, 0xff
sb x6, 2(x5)                  /* write address 0x1002, check passes */
sb x6, 4(x5)                  /* write address 0x1004, check fails */

/* unreachable */
SYS_EXIT 0
