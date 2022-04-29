#include<iostream>
#include <vector>
#include<cstring>	// memset
#include <cassert>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// few edits.
// I don't understand the Trie idea.
int count_unique_substrings(unordered_set<string> &list, const string &s) {
    for(int i = 0; i < (int) s.size(); i++) {
        string temp = "";
        for(int j = 1; j <= (int) s.size() - i; j++) {
            temp = s.substr(i, j);
            cout << temp << ' ';
            list.insert(temp);
        }
        cout << '\n';
    }
    return list.size();
}

int count_substrings_match(const string &str1, const string &str2) {
    int ans = 0;

    unordered_map<string, int> map;

    for(int i = 0; i < (int) str1.size(); i++) {
        string temp = "";
        for(int j = 1; j <= (int) str1.size() - i; j++) {
            temp = str1.substr(i, j);
            map[temp] = 1;
        }
    }
    // O(L^3 + L^3)
    // I don't know the "proper" way to solve this.
    // we can stick to the problem statement by creating a second map, but I found it rather not needed.
    // Could have made it without maps.
    for(int i = 0; i < (int) str2.size(); i++) {
        string temp = "";
        for(int j = 1; j <= (int) str2.size() - i; j++) {
            temp = str2.substr(i, j);
            if(map[temp] == 1) {
                cout << temp << " ";
                ans++, map[temp]++;
            }
                
        }
    }

    return ans;
}


int main() {

    string s = "abca";
    unordered_set<string> test;
    cout << count_unique_substrings(test, s);

    // string str1 = "ab", str2 = "aaaab";

    // unordered_set<string> s1;
    // unordered_set<string> s2;
    // cout << count_substrings_match(str1, str2);
    return 0;
}