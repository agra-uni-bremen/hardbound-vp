#include <stddef.h>
#include <stdint.h>

/**
 * Set bounds for a pointer variable.
 *
 * @param ptr Pointer to location where pointer value is stored.
 * @param base Base address of the pointer value.
 * @param bound Bound of the pointer value (i.e. size).
 */
static void
setbound(volatile void *ptr, uintptr_t base, size_t bound)
{
	__asm__ volatile ("li a7, 98\n" /* SYS_setbound_mem */
	                  "mv a0, %0\n"
	                  "mv a1, %1\n"
	                  "mv a2, %2\n"
	                  "ecall\n"
	                  : /* no output operands */
	                  : "r" (ptr), "r" (base), "r" (bound)
	                  : "a7", "a0", "a1", "a2");
}

void *
getbuf(size_t size)
{
	static char buf[4096];
	char *retbuf = buf;

	setbound(&retbuf, (uintptr_t)retbuf, size);
	return retbuf;
}

int
main(void)
{
	char *buf = getbuf(10);
	if (buf[10] >= '0') {
		return 1;
	} else {
		return 0;
	}
}
