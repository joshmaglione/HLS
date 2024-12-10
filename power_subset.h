#ifndef HLS_POWER_SUBSET_H_
#define HLS_POWER_SUBSET_H_

#include <array>
#include <vector>
#include "polynomial.h"


/*
	PowerSubset encodes a subset of 2^{[n]} \ {[9], emptyset}, where n <= 9.

	Attributes:
	    n_sets : an unsigned short equal to the cardinality of the subset. Since
	    	[9] and emptyset are not possible members, the maximum value is 
			510 = 2^9 - 2.
	    subsets : an array of arrays each of which correspond to a subset.
	    	Since [9] is not a possible subset, the maximal cardinality is 8. 
*/
class PowerSubset
{
public:
std::array<std::array<unsigned short int, 8>, 510> subsets;
unsigned short int n_sets = 0;

PowerSubset() {}
PowerSubset(unsigned short int n, std::array<std::array<unsigned short int, 8>, 510> a)
{
	n_sets = n;
	subsets = a;
}

void print() const;
void print_term() const;
bool is_sorted() const;
bool is_tableau() const;
void sort();
PowerSubset subset(unsigned int s) const;
Polynomial leg_polynomial() const;
Polynomial extended_leg_polynomial() const;
};

#endif  // HLS_POWER_SUBSET_H_