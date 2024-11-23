#ifndef HLS_POLYNOMIAL_H_
#define HLS_POLYNOMIAL_H_

#include <vector>
#include <array>
#include <gmp.h>
#include <gmpxx.h>
#include "power_subset.h"

class Polynomial
{
public:
unsigned short int deg;
std::vector<mpz_class> coeffs;

Polynomial() {}
Polynomial(unsigned short int d, const std::vector<mpz_class>& C)
{
	deg = d;
	coeffs = C;
}

void print() const;
mpz_class operator[](int i) const;
Polynomial add(const Polynomial& other) const;
Polynomial operator+(const Polynomial& other) const;
Polynomial mult(const Polynomial& other) const;
Polynomial operator*(const Polynomial& other) const;
};

#endif  // HLS_POLYNOMIAL_H_

std::array<unsigned short int, 8> get_leg_set(PowerSubset& PS);