#pragma once
#include <vector>
#include <bitset>

class CA
{
	size_t generation;
	size_t m_rows;
	size_t m_cols;
	char m_type;
	std::vector<std::vector<bool>> cells2D;
	std::vector<std::vector<bool>> next_gen2D;

public:
	CA(char type, int rows, int cols);

	int neighborhood2D(int X, int Y);
	void generate2Dboard();
	void tick();
	bool Conway_rules(int live_neighbors, bool my_state);
	int constrain(int index, int max);
};