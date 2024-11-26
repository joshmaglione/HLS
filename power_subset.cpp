#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <vector>
#include "power_subset.h"
#include "leg_polynomial.h"

int pos_size(const std::array<unsigned short int, 8>& a)
{
	int i = 0;
	while (a[i] > 0 && a[i] < 10)
		i++;
	return i;
}

bool ps_ord_le(
	const std::array<unsigned short int, 8>& X, 
	const std::array<unsigned short int, 8>& Y
)
{
	int a = pos_size(X);
	int b = pos_size(Y);
	if (a != b) 
		return b < a;
	int i = 0;
	while (i < b && X[i] == Y[i]) 
		i++;
	if (i == b) 
		return true;
	return X[i] < Y[i];
}

bool tab_ord_le(
	const std::array<unsigned short int, 8>& X, 
	const std::array<unsigned short int, 8>& Y
)
{
	int a = pos_size(X);
	int b = pos_size(Y);
	if (b > a) 
		return false;
	for (int i = 0; i < b; i++)
	{
		if (X[i] > Y[i])
			return false;
	}
	return true;
}

// -----------------------------------------------------------------------------
// 		PowerSubset Methods
// -----------------------------------------------------------------------------
void PowerSubset::print() const
{
	int cutoff;
	std::cout << "{" << std::endl;
	for (int i = 0; i < n_sets; i++)
	{
		cutoff = 0;
		while (cutoff < 8 && subsets[i][cutoff] != 0)
			cutoff++;
		std::cout << "  {";
		for (int j = 0; j < cutoff - 1; j++)
		{
			std::cout << subsets[i][j] << ", ";
		}
		std::cout << subsets[i][cutoff - 1] << "}" << std::endl;
	}
	std::cout << "}" << std::endl;
}

bool PowerSubset::is_sorted() const
{
	if (n_sets <= 1)
		return true;
	for (int i = 0; i < n_sets - 1; i++)
	{
		if (!ps_ord_le(subsets[i], subsets[i + 1])) 
		{
			std::cout << "subset " << i << " > subset " << i + 1 << std::endl;
			return false;
		}
	}
	return true;
}

bool PowerSubset::is_tableau() const
{
	if (n_sets <= 1)
		return true;
	for (int i = 0; i < n_sets - 1; i++)
	{
		if (!tab_ord_le(subsets[i], subsets[i + 1])) 
			return false;
	}
	return true;
}

void PowerSubset::sort() 
{
	std::sort(subsets.begin(), subsets.begin() + n_sets, ps_ord_le);
}

PowerSubset PowerSubset::subset(unsigned int s) const
{
	unsigned short int new_n_set = __builtin_popcount(s);
	unsigned short int count = 0;
	unsigned int i = 1;
	int j = 0;
	std::array<std::array<unsigned short int, 8>, 510> S;
	while (count < new_n_set)
	{
		if (s & i)
		{
			S[count] = subsets[j];
			count++;
		}
		i <<= 1;
		j++;
	}
	return PowerSubset(new_n_set, S);
}

// Given a tableau, return the expanded leg polynomial.
Polynomial PowerSubset::leg_polynomial() const
{
	// assert(this->is_tableau());
	std::array<unsigned short int, 8> a = get_leg_set(*this);
	std::vector<mpz_class> C = {1};
	Polynomial Phi = Polynomial(0, C);
	for (int i = 0; i < 7; i++)
	{
		if (a[i] != 0)
			Phi = Phi * binomial_poly(i + 1, a[i]);
	}
	return Phi;
}

Polynomial PowerSubset::extended_leg_polynomial() const
{
	Polynomial ext_Phi;
	if (n_sets & 1)
		ext_Phi = Polynomial(-1);
	else
		ext_Phi = Polynomial(1);

	if (n_sets <= 32)
	{
		unsigned int a = 1 << n_sets;				// a == 2^{n_sets}
		unsigned int masker = (1 << n_sets) - 1;
		for (unsigned int i = a - 1; i > 0; i--)
		{
			PowerSubset sub_PS = this->subset(i);
			if (sub_PS.is_tableau())
			{
				// We decide if we have an odd number of subsets excluded from
				// our subset sub_PS.
				if ((n_sets - __builtin_popcount(i & masker)) & 1)
				{
					ext_Phi = ext_Phi - sub_PS.leg_polynomial();
				}
				else
				{
					ext_Phi = ext_Phi + sub_PS.leg_polynomial();
				}
			}
		}
	}
	return ext_Phi;
}