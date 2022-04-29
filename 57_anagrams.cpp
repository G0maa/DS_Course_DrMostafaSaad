#include<iostream>
#include <vector>
#include<cstring>	// memset
#include <cassert>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int hash_string(string str, int n = 2147483647) {
	long long nn = n;
	long long sum = 0;

	for (int i = 0; i < (int) str.size(); ++i)
		sum = (sum + str[i] - 'a' + 1) % nn;

	return sum;
}

// L^2 for substrings, L for substr(), L log L for sort, L for hashing.
// L^5 Log L
// I had the frequency idea but wasn't too sure about it, also for sure didn't know how to hash it :)
int count_anagram_substrings(const string &str) {
    unordered_set<string> list;
    for(int i = 0; i < (int) str.size(); i++) {
        for(int j = 1; j <= (int) str.size() - i; j++) {
            string temp = str.substr(i, j);
            sort(temp.begin(), temp.end());
            cout << temp << ' ';
            list.insert(temp);
        }
        cout << '\n';
    }
    return (int) list.size();
}

int main() {
    // freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);

    string s = "aabade";
    cout << count_anagram_substrings(s);
    // cout << hash_string(s);
    return 0;
}