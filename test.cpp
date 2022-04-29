#include <bits/stdc++.h>

using namespace std;

int main() {
	int idx = 0;
	for(int dep = 0; dep < 3; dep++)
		for(int row = 0; row < 4; row++)
			for(int col = 0; col < 5; col++)
				cout << idx++ << " = "
					 << dep << " " << row << " " << col << "\n";
	
	return 0;
}
