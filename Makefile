hls: hls.o string_manip.o power_subset.o power_subset_generator.o polynomial.o leg_polynomial.o
	g++ hls.o string_manip.o power_subset.o power_subset_generator.o polynomial.o leg_polynomial.o -o hls -std=c++20 -I/opt/homebrew/Cellar/gmp/6.3.0/include/ -lgmp -lgmpxx

hls.o: hls.cpp
	g++ -c hls.cpp -std=c++20

string_manip.o: string_manip.cpp string_manip.h
	g++ -c string_manip.cpp -std=c++20

power_subset.o: power_subset.cpp power_subset.h
	g++ -c power_subset.cpp -std=c++20

power_subset_generator.o: power_subset_generator.cpp power_subset_generator.h
	g++ -c power_subset_generator.cpp -std=c++20

polynomial.o: polynomial.cpp polynomial.h
	g++ -c polynomial.cpp -std=c++20

leg_polynomial.o: leg_polynomial.cpp leg_polynomial.h
	g++ -c leg_polynomial.cpp -std=c++20

clean: 
	rm *.o
	rm hls