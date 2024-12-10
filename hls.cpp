#include <iostream>
#include <chrono>
#include <string>
#include "string_manip.h"
#include "power_subset.h"
#include "power_subset_generator.h"
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

void print_HLS_numerator(unsigned short int n)
{
	std::cout << "Computing HLS_" << n << std::endl;
	unsigned int S = 1 << ((1 << n) - 2);
	PowerSubset PS;
	Polynomial Phi;
	Polynomial zero = Polynomial(0);
	std::cout << '1';
	for (unsigned int i = 1; i < S; i++)
	{
		PS = int_to_PS(i, n);
		Phi = PS.extended_leg_polynomial();
		if (Phi != zero)
		{
			std::cout << " + (";
			Phi.print();
			std::cout << ")*";
			PS.print_term();
		}
	}
	std::cout << std::endl;
}

int interpret(char decision)
{
	std::string input;
	if (decision == '0')
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
			std::cout << std::endl;
		}
		else
			std::cout << "not a tableau." << std::endl;
		std::cout << "Now I want to compute the extended leg polynomial" << std::endl;
		Polynomial ext_Phi = PS.extended_leg_polynomial();
		ext_Phi.print();
		std::cout << std::endl;
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
	{
		std::cout << '1' << std::endl;
		return 0;
	}
	auto start = std::chrono::steady_clock::now();
	print_HLS_numerator(inp_int);
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds{end - start};
	std::cout << "Computation took: " << elapsed_seconds << std::endl;
	return 0;
}

int main() 
{
	char decision;
	bool running = true;

	while (running)
	{
		std::cout << "What do you want to do?" << std::endl;
		std::cout << "  [0] : compute (extended) leg polynomial," << std::endl;
		std::cout << "  [1] : compute numerator of HLS_n," << std::endl;
		std::cout << "  [q] : quit." << std::endl;
		std::cin >> decision;
		if (decision == 'q')
			running = false;
		else
			{
			interpret(decision);
			std::cout << std::endl;
			}
	}
}