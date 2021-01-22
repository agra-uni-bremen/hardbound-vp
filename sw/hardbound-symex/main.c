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


static void
make_symbolic(volatile void *ptr, size_t size)
{
	__asm__ volatile ("li a7, 96\n"
			  "mv a0, %0\n"
			  "mv a1, %1\n"
			  "ecall\n"
			  : /* no output operands */
			  : "r" (ptr), "r" (size)
			  : "a7", "a0", "a1");
}

int
main(void)
{
	int a;
	char buf[10];
	char *bufptr = &buf[0];

	setbound(&bufptr, (uintptr_t)&buf[0], 10);
	make_symbolic(&a, sizeof(a));

	if (a == 82798235) {
		*(bufptr + 10) = '\0';
	} else {
		*(bufptr) = '\0';
	}

	return 0;
}
