#include "CA.h"
#include "CA1d.h"
#include "unistd.h"

int main()
{
	
	std::bitset<8> r30  = 0b00011110; // rule 30
	std::bitset<8> r122 = 0b01111010; // rule 122
	std::bitset<8> r126 = 0b01111110; // rule 126
	
	//CA test(r30);
	//CA1d test(r122, 3);
	//CA1d test(r126, 3);
	CA Conway_test('C',50, 120);

	while(true){
		Conway_test.tick();
		//test.generate();
		usleep(500000);
	}
	return 0;
}