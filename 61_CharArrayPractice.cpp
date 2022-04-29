#include <bits/stdc++.h>

using namespace std;
// If solution not found => Too easy.

void compressing() {
    string str;
    cin >> str;

    int count = 1, i = 1;
    for(; i < (int) str.size(); i++) {
        if(str[i - 1] != str[i]) {
            cout << str[i - 1] << count << '_';
            count = 1;
        }
        else 
            count++;
    }
    cout << str[i - 1] << count; // for the last one.
}

// Abstracting it to adding to strings, saves the hassle.
void add5555() {
    string first;
    string second;
    string ans = "";
    cin >> first >> second;

    if(first.size() < second.size())
        swap(first, second);
    
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
    int first_index = 0, carry = 0;
    for(int i = 0; i < (int) first.size(); i++, first_index++) {
        if(i < (int) second.size())
            carry += second[i] - '0';
        
        if(first_index < (int) first.size())
            carry += first[first_index] - '0';

        if(carry > 9) {
            ans += (carry - 10) + '0';
            carry = 1;
        } else {
            ans += carry + '0';
            carry = 0;
        }
    }
    if(carry != 0)
        ans += '1';
    reverse(ans.begin(), ans.end());
    cout << ans;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    add5555();

    return 0;
}