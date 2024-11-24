#include <iostream>
#include <string>
#include <vector>
#include <gmp.h>
#include <gmpxx.h>
#include "polynomial.h"
#include "power_subset.h"

// Function to print a Polynomial in the variable Y.
void Polynomial::print() const
{
	std::string opp;
	if (deg == 0)
		std::cout << coeffs[0] << std::endl;
	else
	{	
		int k = 0;
		while (coeffs[k] == 0)
			k++;
		if (k == 0)
			std::cout << coeffs[k];
		else
			std::cout << coeffs[k] << "Y^" << k;
		for (int i = k + 1; i <= deg; i++)
		{
			if (coeffs[i] == 0)
				continue;
			if (coeffs[i] > 0)
			{
				if (coeffs[i] == 1)
					std::cout << " + Y^" << i;
				else
					std::cout << " + " << coeffs[i] << "Y^" << i;
			}
			else
			{
				if (coeffs[i] == -1)
					std::cout << " - Y^" << i;
				else
					std::cout << " - " << -coeffs[i] << "Y^" << i;
			}
		}
		std::cout << std::endl;
	}
}

// Function to get the coefficient of Y^i for any integer i.
mpz_class Polynomial::coefficient(int i) const
{
	if ((i >= 0) && (i <= deg))
		return coeffs[i];
	return 0;
}

// Function to add two Polynomials to each other.
Polynomial Polynomial::add(const Polynomial& other) const
{
	unsigned short int d;
	// Determine the (potential) degree of the sum
	if (deg >= other.deg)
		d = deg;
	else
		d = other.deg;
	// Build coefficient vector
	std::vector<mpz_class> C;
	C.reserve(d + 1);
	for (int i = 0; i <= d; i++)
		C.emplace_back(this->coefficient(i) + other.coefficient(i));
	// Verify the degree is correct
	while ((C[d] == 0) && (d > 0))
		d--;
	return Polynomial(d, C);
}

// Function to add two Polynomials to each other via +.
Polynomial Polynomial::operator+(const Polynomial& other) const
{
	return add(other);
}

// Function to multiply two Polynomials to each other.
Polynomial Polynomial::mult(const Polynomial& other) const
{
	// Get the degree of the new polynomial
	unsigned short int d = deg + other.deg;
	// Build coefficient vector
	std::vector<mpz_class> C;
	mpz_class ci;
	C.reserve(d + 1);
	for (int i = 0; i <= d; i++)
	{
		ci = 0;
		for (int j = 0; j <= i; j++)
			ci += this->coefficient(j) * other.coefficient(i - j);
		C.push_back(ci);
	}
	return Polynomial(d, C);
}

// Function to multiply two Polynomials to each other via *.
Polynomial Polynomial::operator*(const Polynomial& other) const
{
	return mult(other);
}