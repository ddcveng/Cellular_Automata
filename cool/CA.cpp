#include "CA.h"
#include <iostream>
#include <sstream>
#include <ctime>



CA::CA(char type, int rows, int cols)
	:generation(0)
	,m_rows(rows)
	,m_cols(cols)
	,m_type(type)
	,cells2D(m_rows)
	,next_gen2D(m_rows)
	,secatt()
	,console(CreateFileA("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE,&secatt,OPEN_EXISTING, NULL, NULL))
		//CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL))

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
			if (tempX == X && tempY == Y) {
				continue;
			}
			else if (tempX == -1 && tempY == -1) {
				if (cells2D[m_rows -1][m_cols -1]) ++count;
			}
			else if (tempX == m_rows && tempY == m_cols) {
				if (cells2D[0][0] == 1) ++count;
			}
			else if (tempX == -1 && tempY == m_cols) {
				if (cells2D[m_rows -1][0]) ++count;
			}
			else if (tempX == m_rows && tempY == -1) {
				if (cells2D[0][m_cols -1]) ++count;
			}
			else if (tempX == -1 && tempY != -1) {
				if (cells2D[m_rows - 1][tempY]) ++count;
			}
			else if (tempX == m_rows && tempY != m_cols) {
				if (cells2D[0][tempY]) ++count;
			}
			else if (tempY == -1 && tempX != -1) {
				if (cells2D[tempX][m_cols - 1]) ++count;
			}
			else if (tempY == m_cols && tempX != m_rows) {
				if (cells2D[tempX][0]) ++count;
			}
			else {
				if (cells2D[tempX][tempY]) ++count;
			}
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
	clear_screen();
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
		//std::cout << ss.str().c_str();
		WriteConsole(console, ss.str().c_str(), length, &x, NULL);
		break;
	default:
		break;
	}
	for (size_t i = 0; i != next_gen2D.size(); ++i) next_gen2D[i].clear();
	++generation;
}

bool CA::Conway_rules(int live_neighbors, bool my_state)
{
	switch (my_state)
	{
	case false:
		return live_neighbors == 3 ? true : false;
		break;
	case true:
		if		(live_neighbors >  3) return false;
		else if (live_neighbors >= 2) return true;
		else						  return false;
		break;
	}
}

void CA::clear_screen()
{
	char fill = ' ';
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}
