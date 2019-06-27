#include "CA.h"
#include <sstream>
#include <ctime>



CA::CA(char type, int rows, int cols)
	:generation(0)
	,m_rows(rows)
	,m_cols(cols)
	,m_type(type)
	,cells2D(m_rows)
	,next_gen2D(m_rows)
{
	generate2Dboard();
}

int CA::neighborhood2D(int X, int Y)
{
	int count = 0;

	int tempX;
	int tempY;
	
	for (tempX = X - 1; tempX != X + 2; ++tempX) {
		for (tempY = Y - 1; tempY != Y + 2; ++tempY) {
			if (tempX == X && tempY == Y) continue;
			if (cells2D[constrain(tempX, m_rows)][constrain(tempY, m_cols)]) ++count;
		}
	}

	return count;
}

void CA::generate2Dboard()
{
	srand((unsigned)time(0));

	for (size_t j = 0; j != m_rows; ++j) {
		for (size_t q = 0; q != m_cols; ++q) {
			cells2D[j].push_back(rand() % 2 == 1 ? true : false);
		}
	}
}

void CA::tick()
{
	std::stringstream ss;
	unsigned long x = 0;
	unsigned long length = 0;

	switch (m_type)
	{
	case 'C':
		for (size_t j = 0; j != m_rows; ++j) {
			ss << "\n";
			for (size_t q = 0; q != m_cols; ++q) {
				if (!cells2D[j][q])		ss << ' ';
				else					ss << 'O';
				next_gen2D[j].push_back(Conway_rules(neighborhood2D(j, q), cells2D[j][q]));
			}
		}
		cells2D = next_gen2D;
		length = ss.str().length();
		
		puts(ss.str().c_str());
		
		break;
	default:
		break;
	}
	for (size_t i = 0; i != next_gen2D.size(); ++i) next_gen2D[i].clear();
	++generation;
}

bool CA::Conway_rules(int live_neighbors, bool my_state)
{
    if (live_neighbors == 2) return my_state;
    return live_neighbors == 3;
}

int CA::constrain(int index, int max){
	if 		(index < 0)	   return index+max;
	else if (index >= max) return index-max;
	else				   return index;
}