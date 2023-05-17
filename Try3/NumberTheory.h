#pragma once

#include "ArraySequence.h"

class EratosthenesSieve {
private:
	ArraySequence<bool>* prime;
public:
	EratosthenesSieve(size_t n) {
		this->prime = new ArraySequence<bool>(new bool[n], n);
		for (size_t i = 0; i < this->prime->get_length(); ++i) {
			this->prime->operator[](i) = true;
		}
		this->prime->operator[](0) = this->prime->operator[](1) = false;
		for (size_t i = 2; i < n; ++i) {
			if (this->prime->get(i)) {
				for (size_t j = 2 * i; j < n; j += i) {
					this->prime->operator[](j) = false;
				}
			}
		}
	}

	bool is_prime(size_t num) const {
		return this->prime->get(num);
	}

	EratosthenesSieve() {
		delete this->prime;
	}
};

bool is_prime(int n) {
	if (n < 2) {
		return false;
	}
	int sq = sqrt(n);
	for (int i = 2; i <= sq; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

class Factorizer {
private:
	ArraySequence<int>* minimal_prime_divisors;
public:
	Factorizer(size_t n) {
		this->minimal_prime_divisors = new ArraySequence<int>(n);
		for (size_t i = 0; i < this->minimal_prime_divisors->get_length(); ++i) {
			this->minimal_prime_divisors->operator[](i) = -1;
		}
		for (int i = 2; i < n; ++i) {
			if (minimal_prime_divisors->get(i) == -1) {
				minimal_prime_divisors->operator[](i) = i;
				for (int j = 2 * i; j < n; j += i) {
					if (minimal_prime_divisors->get(j) == -1) {
						minimal_prime_divisors->operator[](j) = i;
					}
				}
			}
		}
	}

	int get_minimal_prime_divisor(int n) const {
		return minimal_prime_divisors->get(n);
	}

	ArraySequence<int>* factorize(int n) const {
		ArraySequence<int>* prime_factors = new ArraySequence<int>((size_t)0);

		while (n > 1) {
			prime_factors->append(this->get_minimal_prime_divisor(n));
			n /= this->get_minimal_prime_divisor(n);
		}
		return prime_factors;
	}

	~Factorizer() {
		delete this->minimal_prime_divisors;
	}
};