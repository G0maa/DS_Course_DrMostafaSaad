#include<iostream>
#include <vector>
#include<cstring>	// memset
#include <cassert>
#include <algorithm>
#include <set>
using namespace std;

// Both first & second problem
int hash_string(string str, int n) {
	long long nn = n;
	long long sum = 0;
    long long partial_sum = 0;
    // We now have 26 + 26 + 10 = 62 
    // a-z => 0-25, A-Z is 27-52, 0-9 is 53-62.
	for (int i = 0; i < (int) str.size(); ++i) {

        if(str[i] <= 57)
            partial_sum = (partial_sum * 62 + str[i] - '0' + 53) % nn;
        else if(str[i] <= 90)
            partial_sum = (partial_sum * 62 + str[i] - 'A' + 27) % nn;
        else
		    partial_sum = (partial_sum * 62 + str[i] - 'a') % nn;
        
        if(i + 1 % 4 == 0)
            sum = (sum + partial_sum) % nn, partial_sum = 0;
    }
    sum = (sum + partial_sum) % nn; // if we exist before end of last group.
	return sum;
}

int main() {

    
}