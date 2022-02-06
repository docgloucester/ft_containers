#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <map.hpp>
#include <stack.hpp>
#include <vector.hpp>

#ifndef NS
# define NS ft
#endif

#define STR(X) #X
#define ASSTR(X) STR(X)

#include <stdlib.h>

#define COUNT 5000000


int main(int argc, char** argv) {

	std::cout <<
	std::endl << "*****************************************************************" <<std::endl
			  << "This is the " << ASSTR(NS) << " binary" << std::endl 
			  << "*****************************************************************" << std::endl;
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	NS::vector<int> vector_buffer;
	for (int i = 0; i < COUNT; i++)
		vector_buffer.push_back(rand());

	int sum = 0;
	for (int i = 0; i < COUNT; i++)
	{
		const int pos = rand() % COUNT;
		sum += vector_buffer[pos];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl << std::endl;

	NS::map<int, int> map_int;
	for (int i = 0; i < COUNT; ++i)
		map_int.insert(NS::make_pair(rand(), rand()));

	sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl << std::endl;
	return (0);
}