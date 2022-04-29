#include<iostream>
#include <vector>
#include<cstring>	// memset
#include <cassert>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;


// O(~s^3) for generating only + time of hashing + time of inserting.
// All I can think of is tries.
int count_unique_substrings(const string &s) {
    unordered_set<string> test;
        
    for(int i = 0; i < (int) s.size(); i++) {
        string temp = "";
        for(int j = 1; j <= (int) s.size() - i; j++) {
            temp = s.substr(i, j); // I considered this O(L)
            cout << temp << ' ';
            test.insert(temp);
        }
        cout << '\n';
    }
    cout << '\n';
    return test.size();
}



int main() {

    // string s = "abcdef";
    // cout << count_unique_substrings(s);
    return 0;
}