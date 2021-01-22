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

/**
 * Set bounds for register and ensure that this information
 * is propagated when writting and reading from the memory.
 */
SYS_SETBOUND_REG 2, 0x1000, 4 /* R2 ⟵ {0x1000; 0x1000; 4} */
la t0, bound
sw x2, 0(t0)
lw x4, 0(t0)

lb x4,2(x2)                   /* read address 0x1002, check passes */
lb x4,5(x2)                   /* read address 0x1005, check fails */

/* unreachable */
SYS_EXIT 0

.data

.align 4
bound:
.word 0xffffffff
