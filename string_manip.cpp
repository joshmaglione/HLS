#include <string>
#include <array>
#include "string_manip.h"
#include "power_subset.h"

int count_char(const std::string& s, char c)
{
	int count = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == c)
			count++;
	}
	return count;
}

int str_to_tab_size(std::string s){
	std::string t = s;
	int found = s.find('|');
	if (found != std::string::npos)
		t = s.substr(0, found);
	return count_char(t, ',') + 1;
}

PowerSubset set_str_to_ps(std::string s)
{
	std::array<std::array<unsigned short int, 8>, 510> subs;
	int s_ind = 0;
	int a_ind = 0;
	int subs_ind = 0;
	unsigned short int N = 1;
	std::array<unsigned short int, 8> a {0};
	while (s_ind < s.length())
	{
		if (s[s_ind] == '|')
		{
			subs[subs_ind] = a;
			subs_ind++;
			a.fill(0);
			a_ind = 0;
			N++;
		}
		else if (s[s_ind] != ',')
		{
			a[a_ind] = s[s_ind] - 48;
			a_ind++;
		}
		s_ind++;
	}
	subs[subs_ind] = a;
	PowerSubset PS;
	PS.subsets = subs;
	PS.n_sets = N;
	return PS;
}