#ifndef HLS_POLYNOMIAL_H_
#define HLS_POLYNOMIAL_H_

#include <vector>
#include <gmp.h>
#include <gmpxx.h>

class Polynomial
{
public:
unsigned short int deg;
std::vector<mpz_class> coeffs;

Polynomial() 
{
	deg = 0;
	coeffs = {0};
}
Polynomial(unsigned short int d, const std::vector<mpz_class>& C)
{
	deg = d;
	coeffs = C;
}
Polynomial(const std::vector<mpz_class>& C)
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
mpz_class coefficient(int i) const;
Polynomial add(const Polynomial& other) const;
Polynomial operator+(const Polynomial& other) const;
Polynomial sub(const Polynomial& other) const;
Polynomial operator-(const Polynomial& other) const;
Polynomial mult(const Polynomial& other) const;
Polynomial operator*(const Polynomial& other) const;
};

#endif  // HLS_POLYNOMIAL_H_