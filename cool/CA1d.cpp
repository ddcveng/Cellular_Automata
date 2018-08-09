#include "CA1d.h"
#include <iostream>


CA1d::CA1d(const std::bitset<8>& b, int init_size)
	: generation(0)
	, ruleset(b)
	, cells(init_size, false)
	, next_gen(init_size)
{
	cells[init_size / 2] = true;
}

void CA1d::generate()
{
	std::cout << "\n";
	if (generation != 0) {
		cells.resize(cells.size() + 1);
		cells[cells.size() - 1] = rules(cells.size() - 1);
		next_gen.push_back(cells.size()-1);
	}
	for (size_t it = 0; it != cells.size(); ++it) {
		if (!cells[it])		std::cout << ' ';
		else				std::cout << 'O';
		next_gen[it] = rules(it);
	}
	cells = next_gen;
	++generation;
}

bool CA1d::rules(int index)
{
	int triplet;

	if (index == 0) triplet = convert(1, cells.size() - 1);
	else			triplet = convert(1, index - 1);

	triplet += convert(2, index);

	if (index == cells.size() - 1) triplet += convert(3, 0);
	else			  triplet += convert(3, index + 1);

	return ruleset[triplet] == 1 ? true : false;
}

int CA1d::convert(int position, int index)
{
	switch (position)
	{
	case 1:
		return cells[index] == false ? 0 : 4;
	case 2:
		return cells[index] == false ? 0 : 2;
	case 3:
		return cells[index] == false ? 0 : 1;
	}
}