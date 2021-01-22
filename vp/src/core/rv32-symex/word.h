#ifndef RISCV_VP_WORD_H
#define RISCV_VP_WORD_H

#include <stdbool.h>
#include <stddef.h>
#include <tuple>

template <typename T>
class Word {
private:
	T value;
	uint64_t base;
	size_t bound;

public:
	Word(void)
	  : value(0), base(0), bound(0) {
		return;
	}

	Word(T _value)
	  : value(_value), base(0), bound(0) {
		return;
	}

	Word(T _value, uint64_t _base, size_t _bound)
	  : value(_value), base(_base), bound(_bound) {
		return;
	}

	bool is_pointer(void) {
		return bound != 0 && base != 0;
	}

	/**
	 * Accessor functions.
	 */

	std::tuple<uint64_t, size_t> metadata(void) {
		return std::make_tuple(base, bound);
	}

	void set_metadata(uint64_t base, size_t bound) {
		this->base  = base;
		this->bound = bound;
	}

	void set_metadata(Word<T> other) {
		set_metadata(other.base, other.bound);
	}

	/**
	 * Operator overloading for Hardbound propagation.
	 */

	Word<T> operator+(const T& other) {
		return Word<T>(value + other, base, bound);
	}

	Word<T> operator+(Word<T>& other) {
		auto base = this->base;
		auto bound = this->bound;
		if (other.is_pointer())
			std::tie(base, bound) = other.metadata();

		return Word<T>(value + other, base, bound);
	}

	Word<T> operator-(const T& other) {
		return Word<T>(value - other, base, bound);
	}

	Word<T> operator-(Word<T>& other) {
		auto base = this->base;
		auto bound = this->bound;
		if (other.is_pointer())
			std::tie(base, bound) = other.metadata();

		return Word<T>(value - other, base, bound);
	}

	/**
	 * Implicit type conversions
	 */

	// implicit conversion to underlying type T
	operator T(void) const {
		return value;
	}

	// implicit type conversion to change integer widths
	template <typename N>
	operator Word<N>() const {
		return Word<N>((N)value, base, bound);
	}
};

#endif
