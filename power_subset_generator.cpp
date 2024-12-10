#include <iostream>
#include <array>
#include "power_subset.h"

static std::array<std::array<unsigned short int, 8>, 30> singletons2()
{
	return {
		std::array<unsigned short int, 8> {1}, 
		std::array<unsigned short int, 8> {2}
	};
}

static std::array<std::array<unsigned short int, 8>, 30> singletons3()
{
	return {
		std::array<unsigned short int, 8> {1, 2}, 
		std::array<unsigned short int, 8> {1, 3},
		std::array<unsigned short int, 8> {2, 3},
		std::array<unsigned short int, 8> {1}, 
		std::array<unsigned short int, 8> {2},
		std::array<unsigned short int, 8> {3},
	};
}

static std::array<std::array<unsigned short int, 8>, 30> singletons4()
{
	return {
		std::array<unsigned short int, 8> {1, 2, 3},
		std::array<unsigned short int, 8> {1, 2, 4},
		std::array<unsigned short int, 8> {1, 3, 4},
		std::array<unsigned short int, 8> {2, 3, 4},
		std::array<unsigned short int, 8> {1, 2}, 
		std::array<unsigned short int, 8> {1, 3},
		std::array<unsigned short int, 8> {1, 4},
		std::array<unsigned short int, 8> {2, 3}, 
		std::array<unsigned short int, 8> {2, 4},
		std::array<unsigned short int, 8> {3, 4},
		std::array<unsigned short int, 8> {1}, 
		std::array<unsigned short int, 8> {2},
		std::array<unsigned short int, 8> {3},
		std::array<unsigned short int, 8> {4},
	};
}

static std::array<std::array<unsigned short int, 8>, 30> singletons5()
{
	return {
		std::array<unsigned short int, 8> {1, 2, 3, 4},
		std::array<unsigned short int, 8> {1, 2, 3, 5},
		std::array<unsigned short int, 8> {1, 2, 4, 5},
		std::array<unsigned short int, 8> {1, 3, 4, 5},
		std::array<unsigned short int, 8> {2, 3, 4, 5},
		std::array<unsigned short int, 8> {1, 2, 3},
		std::array<unsigned short int, 8> {1, 2, 4},
		std::array<unsigned short int, 8> {1, 2, 5},
		std::array<unsigned short int, 8> {1, 3, 4},
		std::array<unsigned short int, 8> {1, 3, 5},
		std::array<unsigned short int, 8> {1, 4, 5},
		std::array<unsigned short int, 8> {2, 3, 4},
		std::array<unsigned short int, 8> {2, 3, 5},
		std::array<unsigned short int, 8> {3, 4, 5},
		std::array<unsigned short int, 8> {1, 2}, 
		std::array<unsigned short int, 8> {1, 3},
		std::array<unsigned short int, 8> {1, 4},
		std::array<unsigned short int, 8> {1, 5},
		std::array<unsigned short int, 8> {2, 3}, 
		std::array<unsigned short int, 8> {2, 4},
		std::array<unsigned short int, 8> {2, 5},
		std::array<unsigned short int, 8> {3, 4}, 
		std::array<unsigned short int, 8> {3, 5},
		std::array<unsigned short int, 8> {4, 5},
		std::array<unsigned short int, 8> {1}, 
		std::array<unsigned short int, 8> {2},
		std::array<unsigned short int, 8> {3},
		std::array<unsigned short int, 8> {4},
		std::array<unsigned short int, 8> {5},
	};
}

PowerSubset int_to_PS(unsigned int S, int n)
{
	std::array<std::array<unsigned short int, 8>, 510> subsets;
	unsigned short int idx = 0;
	std::array<std::array<unsigned short int, 8>, 30> a;
	switch (n)
	{
		case 2:
			a = singletons2();
			break;
		case 3: 
			a = singletons3();
			break;
		case 4:
			a = singletons4();
			break;
		case 5: 
			a = singletons5();
			break;
	}
	for (unsigned int i = 0; i < ((1 << n) - 2); i++)
	{
		if (S & (1 << i))
		{
			subsets[idx] = a[i];
			idx++;
		}
	}
	PowerSubset PS = PowerSubset(idx, subsets);
	return PS;
}