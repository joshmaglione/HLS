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

	std::cout << "What do you want to do?\n  [0] : input a set of subsets of {1, 2, ..., 9},\n  [1] : compute numerator of HLS_n." << std::endl;
	std::cin >> decision;
	if (decision == 0)
	{
		std::cout << "Please input the set as follows. The set{ {1,2}, {3} } should be input as\n    '12|3'." << std::endl;
		std::cin >> input;
		PowerSubset PS = set_str_to_ps(input);
		std::cout << "\nReceived a set of " << PS.n_sets << " subsets:" << std::endl;
		PS.sort();
		PS.print();
		std::cout << "The given set is ";
		if (PS.is_tableau())
		{
			std::cout << "a tableau." << std::endl;
			std::cout << "Now I want to compute its leg set" << std::endl;
			print_array(get_leg_set(PS), true, false);
			std::cout << "Now I want to compute the leg polynomial" << std::endl;
			Polynomial Phi = PS.leg_polynomial();
			Phi.print();
		}
		else
			std::cout << "not a tableau." << std::endl;
			std::cout << "Now I want to compute the extended leg polynomial" << std::endl;
			Polynomial ext_Phi = PS.extended_leg_polynomial();
			ext_Phi.print();
		return 0;
	} 
	std::cout << "For which n in {1, 2, ..., 5} do you want to compute HLS_n?" << std::endl;
	std::cin >> input;
	int inp_int = stoi(input);
	if ((inp_int <= 0) || (inp_int >= 6))
	{
		std::cout << "Cannot compute HLS_n for that n." << std::endl;
		return 0;
	}
	if (inp_int == 1)
		std::cout << 1 << std::endl;
		return 0;
	
}