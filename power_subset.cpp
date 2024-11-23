#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include "power_subset.h"

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