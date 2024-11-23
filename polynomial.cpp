#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <gmp.h>
#include <gmpxx.h>
#include "polynomial.h"
#include "power_subset.h"

// -I/opt/homebrew/Cellar/gmp/6.3.0/include/ -L/usr/local/lib 

// Function to print a Polynomial in the variable Y.
void Polynomial::print() const
{
	std::string opp;
	if (coeffs[0] != 0)
		std::cout << coeffs[0];
	for (int i = 1; i <= deg; i++)
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

// Function to get the ith coefficient of a Polynomial via [].
mpz_class Polynomial::operator[](int i) const
{
	return coeffs.at(i);
}

// Function to add two Polynomials to each other.
Polynomial Polynomial::add(const Polynomial& other) const
{
	unsigned short int df = deg;
	unsigned short int dg = other.deg;
	unsigned short int d, min;
	// Determine the (potential) degree of the sum
	if (df >= dg)
	{
		d = df;
		min = dg;
	}
	else
	{
		d = dg;
		min = df;
	}
	// Build coefficient vector
	std::vector<mpz_class> C;
	C.reserve(d + 1);
	for (int i = 0; i <= min; i++)
		C.emplace_back(coeffs[i] + other[i]);
	if (df >= dg)
	{
		for (int i = min + 1; i < d + 1; i++)
			C.emplace_back(coeffs[i]);
	}
	else
	{
		for (int i = min + 1; i < d + 1; i++)
			C.emplace_back(other[i]);
	}
	// Verify the degree is correct
	while (C[d] == 0)
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
	unsigned short int d = deg + other.deg;
	
}

bool is_in(std::array<unsigned short int, 8>& a, unsigned short int x)
{
	for (int i = 0; i < 8; i++)
	{
		if (a[i] == x)
			return true;
	}
	return false;
}

std::array<unsigned short int, 8> get_leg_set(PowerSubset& PS)
{
	assert(PS.is_tableau());
	std::array<unsigned short int, 8> counts {0};
	for (int i = 0; i < PS.n_sets - 1; i++)
	{
		std::array<unsigned short int, 8> A = PS.subsets[i];
		std::array<unsigned short int, 8> B = PS.subsets[i+1];
		int j = 0;
		while (B[j] > 0)
		{
			if (!is_in(A, B[j]))
			{
				int k = j + 1;
				while ((A[k] > 0) && (A[k] < B[j]))
					k++;
				counts[k - j - 1] += 1;
			}
			j++;
		}
	}
	return counts;
}

mpz_class factorial(int n) {
    mpz_class f = 1;
    for(int k = 2; k <= n; k++){
        f *= k;
    }
    return f;
}

// Polynomial get_leg_polynomial(const PowerSubset& PS)
// {
// 	Polynomial Phi;
// 	return Phi;
// }