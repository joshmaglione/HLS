#ifndef HLS_POWER_SUBSET_H_
#define HLS_POWER_SUBSET_H_

#include <array>
#include <vector>


/*
	The main data is subsets which we assume to be a subset of 
		2^{[9]} \ {[9], empty-set}.
	Therefore we write this as an array of (maximal) length 2^9 - 2 = 510
	made up from arrays of (maximal) length 8.
*/
class PowerSubset
{
public:
std::array<std::array<unsigned short int, 8>, 510> subsets;
unsigned short int n_sets = 0;

void print() const;
bool is_sorted() const;
bool is_tableau() const;
};

#endif  // HLS_POWER_SUBSET_H_