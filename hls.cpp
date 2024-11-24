#include <iostream>
#include <chrono>
#include <string>
#include "string_manip.h"
#include "power_subset.h"
#include "polynomial.h"
#include "leg_polynomial.h"

void print_array(
	const std::array<unsigned short int, 8>& a, 
	bool tab, 
	bool skip
)
{
	std::string s = "";
	std::string e = "";
	if (tab)
		s = "\t";
	if (skip)
		e = "\n";
	std::cout << s << "[";
	for (int i = 0; i < 7; i++)
		std::cout << a[i] << ", " << e;
	std::cout << a[7] << "]" << std::endl;
}

int main() 
{
	int decision;
	std::string input;

	std::cout << "What do you want to do?\n  0 : input a set of finite subsets of N,\n  1 : compute HLS_n,\n  2 : other." << std::endl;
	std::cin >> decision;
	if (decision == 0)
	{
		std::cout << "Please input the set as follows. The set{ {1,2}, {3} } should be input as\n    '1,2|3'." << std::endl;
		std::cin >> input;
		PowerSubset PS = set_str_to_ps(input);
		std::cout << "\nReceived a set of " << PS.n_sets << " subsets:" << std::endl;
		PS.print();
		std::cout << "The given set is ";
		if (PS.is_sorted())
		{
			std::cout << "sorted";
			if (PS.is_tableau())
			{
				std::cout << " and is a tableau." << std::endl;
				std::cout << "Now I want to compute its leg set" << std::endl;
				print_array(get_leg_set(PS), true, false);
				std::cout << "Now I want to compute the leg polynomial" << std::endl;
				Polynomial Phi = get_leg_polynomial(PS);
				Phi.print();
			}
			else
				std::cout << " but is not a tableau." << std::endl;
		}
		else
			std::cout << "not sorted." << std::endl;
	} 
	else 
	{
		std::cout << "Not implemented." << std::endl;
	}
}