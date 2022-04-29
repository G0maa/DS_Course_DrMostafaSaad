#include<iostream>
#include <vector>
#include<cstring>	// memset
#include <cassert>
using namespace std;

class trie {
private:
	static const int MAX_CHAR = 26;
	trie* child[MAX_CHAR];
	bool isLeaf { };

public:
	trie() {
		// set an array to 0s. Here pointers to null
		memset(child, 0, sizeof(child));
	}

	void insert(string str, int idx = 0) {
        trie* node = this;
        int cur = 0; // dummy value
        while(idx != (int) str.size()) {
            cur = str[idx] - 'a';
			if (node->child[cur] == 0)
				node->child[cur] = new trie();

            node = node->child[cur];
            idx++;
        }
        node->isLeaf = 1;
	}

    bool word_exist(string str, int idx = 0) {
        int cur = 0;
        trie* node = this;
        while(idx != (int) str.size()) {
            cur = str[idx] - 'a';
            if (!node->child[cur])
                return false;

            node = node->child[cur];
            idx++;
        }
        return node->isLeaf;
	}

    bool prefix_exist(string str, int idx = 0) {
		int cur = 0;
        trie* node = this;
        while(idx != (int) str.size()) {
            cur = str[idx] - 'a';
            if (!node->child[cur])
                return false;

            node = node->child[cur];
            idx++;
        }
        return true; // only difference.
	}
    friend void list_substrs(const string &str, vector<string> &queries);
};

// I am failing to see the point of using trie, why not just use string + couple of loops?

// O(N + N * Q * L), N size of str, Q number of queries, L length of Query. ~N^3
// Dr's solution is *much* better.
void list_substrs(const string &str, vector<string> &queries) {
    trie root;
    root.insert(str);

    trie* cur = &root;
    bool vis[(int) queries.size()] = {0};
    for(int i = 0; i < (int) str.size(); i++) {
        cur = cur->child[str[i] - 'a'];
        for(int j = 0; j < (int) queries.size(); j++) {
            if(!vis[j] && cur->prefix_exist(queries[j])) {
                vis[j] = 1;
                cout << queries[j] << '\n';
            }
        }
    }
}

// I got no better idea *shrug*
void list_substrs1(const string &str, vector<string> &queries) {
    trie tree;

    // O(QL)
    for(int i = 0; i < (int) queries.size(); i++)
        tree.insert(queries[i]);
    
    // + O(??) The only way comes into my mind is to get every subtstr (which is O(S^2) by it self,
    // and then check if it exists by word_exist(), which is O(L) => TOTAL is: O(QL + S^2 * L),
    // which is much more than normal thinking.
    for (int i = 0; i < (int)str.size(); i++) {
        for(int j = 0; j <= (int)str.size() - i; j++) {
            string test = str.substr(i, j);
            if(tree.word_exist(test))
                cout << test << '\n';
        }
    }		
}

// Insights from Dr's code:
// In the first solution you created every suffix of the *big* string S, although you might not need them,
// in the second solution you iterated on every suffix of string S, but you always stop at length L, because queries are
// much shorter than S, in conclusion, he kind of swappewd the two for-loops, taking advantage of L being small.

int main() {
    string str = "heyabcdtwxyw";
    vector<string> queries = {"xy", "ab", "t", "yz", "xyw", "hey"};
    list_substrs1(str, queries);

    cout << "\n NO RTE \n";
	return 0;
}
