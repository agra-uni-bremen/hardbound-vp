export SYSTEMC_DISABLE_COPYRIGHT_MESSAGE = 1

all: main
sim: main
	test "$$(symex-vp --intercept-syscalls $< \
		| awk '/^a6/ { sub("[()]", "", $$5); print $$5 }')" = 2342

main: main.o
	riscv32-unknown-elf-ld -o $@ $<
main.o: main.S
	riscv32-unknown-elf-as -g $(CPPFLAGS) -o $@ $< -march=rv32i -mabi=ilp32

.PHONY: all sim
