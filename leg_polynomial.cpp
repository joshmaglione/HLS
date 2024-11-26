#include <array>
#include <gmp.h>
#include <gmpxx.h>
#include "power_subset.h"
#include "polynomial.h"

// Function to decide whether or not x is contained in the array a.
bool is_in(std::array<unsigned short int, 8>& a, unsigned short int x)
{
	for (int i = 0; i < 8; i++)
	{
		if (a[i] == x)
			return true;
	}
	return false;
}

// Function to compute the pairs (d_i, e_i) associated to the leg polynomial of
// a tableau, where the leg polynomial is given as 
//		Phi_T(Y) = \prod_i (1 - Y^{d_i})^{e_i} . 
// An array of the e_i are returned such that the ith entry of the array
// corresponds to the degree i + 1.
std::array<unsigned short int, 8> get_leg_set(const PowerSubset& PS)
{
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

// Simple factorial function.
mpz_class factorial(int n) 
{
    mpz_class f = 1;
    for(int k = 2; k <= n; k++)
        f *= k;
    return f;
}

// Simple falling factorial function.
mpz_class falling_factorial(int n, int k) 
{
    mpz_class f = 1;
    for(int m = 0; m < k; m++)
        f *= n - m;
    return f;
}

// Simple binomial coefficient function.
mpz_class binomial(int n, int k) 
{
    return falling_factorial(n, k)/factorial(k);
}

// Given integers d and e, the function returns the expansion of (1 - Y^d)^e.
Polynomial binomial_poly(int d, int e)
{
	unsigned short int deg = d*e;
	std::vector<mpz_class> C;
	C.reserve(deg + 1);
	for (unsigned int i = 0; i <= e; i++)
	{
		if (i & 1)
			C.emplace_back(-binomial(e, i));
		else 
			C.emplace_back(binomial(e, i));
		for (int j = 0; j < d - 1; j++)
			C.push_back(0);
	}
	return Polynomial(deg, C);
}