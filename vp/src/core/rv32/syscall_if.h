#pragma once

#include <clover/clover.h>
#include <stdint.h>

namespace rv32 {

struct UnsupportedSyscall : public std::runtime_error {
	  using runtime_error::runtime_error;
};

/* The syscall handler is using this interface to access and control the ISS. */
struct iss_syscall_if {
	virtual ~iss_syscall_if() {}

	virtual void sys_exit() = 0;
	// virtual void sys_break() = 0;

	virtual unsigned get_syscall_register_index() = 0;

	virtual uint64_t read_register(unsigned idx) = 0;
	virtual void write_register(unsigned idx, uint64_t value) = 0;

	virtual void make_symbolic(size_t index) = 0;
	virtual void make_symbolic(uint32_t addr, size_t size) = 0;

	virtual void set_register_bound(size_t index, uint64_t base, size_t bound) = 0;
	virtual void set_memory_bound(uint64_t addr, uint64_t base, size_t bound) = 0;

	// virtual uint32_t get_hart_id() = 0;
};

/* Using this interface, the ISS supports to intercept and delegate syscalls. */
struct syscall_emulator_if {
	virtual ~syscall_emulator_if() {}

	virtual void execute_syscall(iss_syscall_if *core) = 0;
};

}  // namespace rv32
