#pragma once
#include <vector>
#include <bitset>

class CA1d
{
	size_t generation;
	const std::bitset<8>& ruleset;
	std::vector<bool> cells;
	std::vector<bool> next_gen;
public:
	CA1d(const std::bitset<8>& b, int init_size);

	void generate();
	bool rules(int index);
	int convert(int position, int index);
};