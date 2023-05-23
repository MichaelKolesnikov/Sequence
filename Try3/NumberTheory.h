#pragma once

#include "ArraySequence.h"

class EratosthenesSieve {
private:
	ArraySequence<bool>* prime_;
	// all_primes = ArraySequence<int>
public:
	EratosthenesSieve(size_t n) {
		this->prime_ = new ArraySequence<bool>(new bool[n], n);
		for (size_t i = 0; i < this->prime_->get_length(); ++i) {
			this->prime_->operator[](i) = true;
		}
		this->prime_->operator[](0) = this->prime_->operator[](1) = false;
		for (size_t i = 2; i < n; ++i) {
			if (this->prime_->get(i)) {
				for (size_t j = 2 * i; j < n; j += i) {
					this->prime_->operator[](j) = false;
				}
			}
		}
	}

	bool is_prime(size_t num) const {
		return this->prime_->get(num);
	}

	~EratosthenesSieve() {
		delete this->prime_;
	}

	/*static bool _prime(int n) {
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
	}*/
};

bool prime(int n) {
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

	ArraySequence<int>& factorize(int n) const {
		ArraySequence<int>* prime_factors = new ArraySequence<int>((size_t)0);

		while (n > 1) {
			prime_factors->append(this->get_minimal_prime_divisor(n));
			n /= this->get_minimal_prime_divisor(n);
		}
		return *prime_factors;
	}

	ArraySequence<int>& get_all_prime_divisors(int n) const {
		ArraySequence<int>* prime_divisors = new ArraySequence<int>((size_t)0);
		int divisor = this->get_minimal_prime_divisor(n);
		while (n > 1) {
			if (prime_divisors->get_length() > 0 && (*prime_divisors)[prime_divisors->get_length() - 1] != divisor) {
				prime_divisors->append(divisor);
			}
			n /= this->get_minimal_prime_divisor(n);
			divisor = this->get_minimal_prime_divisor(n);
		}
		return *prime_divisors;
	}

	~Factorizer() {
		delete this->minimal_prime_divisors;
	}
};