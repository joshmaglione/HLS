#include <iostream>
#include <string>
#include <array>
#include <gmp.h>
#include <gmpxx.h>
#include "polynomial.h"
#include "power_subset.h"

// nonnegative c and positive d
void print_term(mpz_class c, int d)
{
	if (c != 0)
	{
		if (c == 1)
		{
			if (d == 1)
				std::cout << "Y";
			else 
				std::cout << "Y^" << d;
		}
		else
		{
			if (d == 1)
				std::cout << c << "Y";
			else 
				std::cout << c << "Y^" << d;
		}
	}
}

// Function to print a Polynomial in the variable Y.
void Polynomial::print() const
{
	std::string opp;
	if (deg == 0)
		std::cout << coeffs[0];
	else
	{	
		int k = 0;
		while (coeffs[k] == 0)
			k++;
		if (k == 0)
			std::cout << coeffs[k];
		else 
		{
			if (coeffs[k] < 0)
			{
				std::cout << "- ";
				print_term(-coeffs[k], k);
			}
			else
				print_term(coeffs[k], k);
		}
		for (int i = k + 1; i <= deg; i++)
		{
			if (coeffs[i] < 0)
			{
				std::cout << " - ";
				print_term(-coeffs[i], i);
			}
			else if (coeffs[i] > 0)
			{
				std::cout << " + ";
				print_term(coeffs[i], i);
			}
		}
	}
}

bool Polynomial::operator==(const Polynomial& other) const
{
	if (deg != other.deg)
		return false;
	for (int i = 0; i <= deg; i++)
	{
		if (coeffs[i] != other.coeffs[i])
			return false;
	}
	return true;
}

bool Polynomial::operator!=(const Polynomial& other) const
{
	return !(*this == other);	
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
	// Build coefficient array
	std::array<mpz_class, 37> C;
	for (int i = 0; i <= d; i++)
		C[i] = this->coefficient(i) + other.coefficient(i);
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

// Function to subtract two Polynomials.
Polynomial Polynomial::sub(const Polynomial& other) const
{
	unsigned short int d;
	// Determine the (potential) degree of the sum
	if (deg >= other.deg)
		d = deg;
	else
		d = other.deg;
	// Build coefficient array
	std::array<mpz_class, 37> C;
	for (int i = 0; i <= d; i++)
		C[i] = this->coefficient(i) - other.coefficient(i);
	// Verify the degree is correct
	while ((C[d] == 0) && (d > 0))
		d--;
	return Polynomial(d, C);
}

// Function to subtract two Polynomials via -.
Polynomial Polynomial::operator-(const Polynomial& other) const
{
	return sub(other);
}

// Function to multiply two Polynomials to each other.
Polynomial Polynomial::mult(const Polynomial& other) const
{
	// Get the degree of the new polynomial
	unsigned short int d = deg + other.deg;
	// Build coefficient array
	std::array<mpz_class, 37> C;
	mpz_class ci;
	for (int i = 0; i <= d; i++)
	{
		ci = 0;
		for (int j = 0; j <= i; j++)
			ci += this->coefficient(j) * other.coefficient(i - j);
		C[i] = ci;
	}
	return Polynomial(d, C);
}

// Function to multiply two Polynomials to each other via *.
Polynomial Polynomial::operator*(const Polynomial& other) const
{
	return mult(other);
}