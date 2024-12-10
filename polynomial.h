#ifndef HLS_POLYNOMIAL_H_
#define HLS_POLYNOMIAL_H_

#include <array>
#include <gmp.h>
#include <gmpxx.h>

class Polynomial
{
public:
unsigned short int deg;
std::array<mpz_class, 37> coeffs;		// 37 = \binom{9}{2} + 1

Polynomial() 
{
	deg = 0;
	coeffs = {0};
}
Polynomial(unsigned short int d, const std::array<mpz_class, 37>& C)
{
	deg = d;
	coeffs = C;
}
Polynomial(const std::array<mpz_class, 37>& C)
{
	deg = C.size() - 1;
	coeffs = C;
}
Polynomial(int c)
{
	deg = 0;
	coeffs = {c};
}

void print() const;
bool operator==(const Polynomial& other) const;
bool operator!=(const Polynomial& other) const;
mpz_class coefficient(int i) const;
Polynomial add(const Polynomial& other) const;
Polynomial operator+(const Polynomial& other) const;
Polynomial sub(const Polynomial& other) const;
Polynomial operator-(const Polynomial& other) const;
Polynomial mult(const Polynomial& other) const;
Polynomial operator*(const Polynomial& other) const;
};

#endif  // HLS_POLYNOMIAL_H_