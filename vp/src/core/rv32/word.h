#ifndef RISCV_VP_WORD_H
#define RISCV_VP_WORD_H

#include <stdbool.h>
#include <stddef.h>
#include <tuple>
#include <memory>

#include <clover/clover.h>

class Word {
private:
	std::shared_ptr<clover::ConcolicValue> value;
	uint64_t base;
	size_t bound;

public:
	Word() : value(nullptr), base(0), bound(0) {
		return; // TODO
	}

	Word(std::shared_ptr<clover::ConcolicValue> _value)
	  : value(_value), base(0), bound(0) {
		return;
	}

	Word(std::shared_ptr<clover::ConcolicValue> _value, uint64_t _base, size_t _bound)
	  : value(_value), base(_base), bound(_bound) {
		return;
	}

	bool is_pointer(void) const {
		return bound != 0 && base != 0;
	}

	/**
	 * Accessor functions.
	 */

	std::tuple<uint64_t, size_t> metadata(void) const {
		return std::make_tuple(base, bound);
	}

	void set_metadata(uint64_t base, size_t bound) {
		this->base  = base;
		this->bound = bound;
	}

	void set_metadata(Word other) {
		set_metadata(other.base, other.bound);
	}

	/**
	 * Operator overloading for Hardbound propagation.
	 */

	Word zext(klee::Expr::Width width) {
		return Word(value->zext(width), base, bound);
	}

	Word add(const std::shared_ptr<clover::ConcolicValue> other) const {
		return Word(value->add(other), base, bound);
	}

	Word add(const Word other) const {
		auto base = this->base;
		auto bound = this->bound;
		if (other.is_pointer())
			std::tie(base, bound) = other.metadata();

		return Word(value->add(other), base, bound);
	}

	Word sub(const std::shared_ptr<clover::ConcolicValue> other) const {
		return Word(value->sub(other), base, bound);
	}

	Word sub(const Word other) const {
		auto base = this->base;
		auto bound = this->bound;
		if (other.is_pointer())
			std::tie(base, bound) = other.metadata();

		return Word(value->sub(other), base, bound);
	}

	/**
	 * Implicit type conversions
	 */

	// implicit conversion to underlying ConcolicValue
	operator std::shared_ptr<clover::ConcolicValue>(void) const {
		return value;
	}

	std::shared_ptr<clover::ConcolicValue> operator->() const {
		return value;
	}
};

#endif
