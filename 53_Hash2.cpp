#include<iostream>
#include <vector>
#include<cstring>	// memset
#include <cassert>
#include <algorithm>
#include <set>
using namespace std;

int hash_num(int value, int n_ = 65407) {
	long long n = n_;
	return (value % n + n) % n;
}

int hash_string(string str, int n = 65407) {
	long long nn = n;
	long long sum = 0;

	for (int i = 0; i < (int) str.size(); ++i) {

        if(str[i] <= 57)
            sum = (sum * 62 + str[i] - '0' + 53) % nn;
        else if(str[i] <= 90)
            sum = (sum * 62 + str[i] - 'A' + 27) % nn;
        else
		    sum = (sum * 62 + str[i] - 'a') % nn;
    }
	return sum;
}

class SomeObject {
    const static int INTERNAL_LIMIT = 2147483647;
    string str1, str2;
    int number;

    // Convert all 3 elemnts as a hash value
    int hash() { 
        // should have used INTERNAL_LIMIT as an argument in the functions + use long long in case of overflow from summing them.
        return (hash_string(str1) + hash_string(str2) + hash_num(number)) % INTERNAL_LIMIT;
    }
};


int main() {

    
}