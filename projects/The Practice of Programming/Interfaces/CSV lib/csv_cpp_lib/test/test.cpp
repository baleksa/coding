#include <iostream>

#include "../src/csv.hpp"

int main(int argc, char *argv[])
{
	Csv testcsvparse = Csv();
	string tmp;
	while (testcsvparse.getline(tmp)) {
		int nfield = testcsvparse.getnfield();
		// cout << nfield << endl;
		for (int i = 0; i < nfield; ++i) {
			// cout << "field[" << i << "] = '" << testcsvparse[i]
			//      << "'" << endl;
			testcsvparse.getfield(i);
		}
	}
	return 0;
}
