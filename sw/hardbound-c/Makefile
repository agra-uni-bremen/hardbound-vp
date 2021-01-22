CFLAGS += -march=rv32i -mabi=ilp32

all: main
sim: main
	test "$$(symex-vp --intercept-syscalls $< \
		| awk '/^a6/ { sub("[()]", "", $$5); print $$5 }')" = 2342

main: bootstrap.o main.o
	riscv32-unknown-elf-ld -o $@ $^
bootstrap.o: bootstrap.S
	riscv32-unknown-elf-as -c -g $(CPPFLAGS) -o $@ $< $(CFLAGS)
main.o: main.c
	riscv32-unknown-elf-gcc -c -g $(CPPFLAGS) -o $@ $< $(CFLAGS) -nostartfiles

.PHONY: all sim
