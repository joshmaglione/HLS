#ifndef HLS_LEG_POLYNOMIAL_H_
#define HLS_LEG_POLYNOMIAL_H_

#include <array>
#include "polynomial.h"
#include "power_subset.h"

std::array<unsigned short int, 8> get_leg_set(const PowerSubset& PS);
Polynomial binomial_poly(int d, int e);

#endif  // HLS_LEG_POLYNOMIAL_H_