#include<iostream>
#include <map>
#include<cstring>	// memset
using namespace std;


// map can be implemented by a self-balancing tree => find/search O(logn)
// with normal arrays access is O(1), memory is O(K) where K is tree children, regardless of them existing or not.
// with map access is O(logn), memory is O(K), where K is tree children that already exist.
class trie {
private:
	map<char, trie*> child;
	bool isLeaf { };

public:
	trie() { }

	void insert(string str, int idx = 0) { // stopped here, how to deal with map in these cases for this function
		trie* node = this;
        int cur = 0; // dummy value
        while(idx != (int) str.size()) {
            cur = str[idx] - 'a';
			if (node->child.find(cur) == node->child.end())
				node->child.insert({cur, new trie()});

            node = node->child[cur]; // <<<
            idx++;
        }
        node->isLeaf = 1;
	}
	

	bool word_exist(string str, int idx = 0) {
		int cur = 0;
        trie* node = this;
        while(idx != (int) str.size()) {
            cur = str[idx] - 'a';
            if (node->child.find(cur) == node->child.end())
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
            if (node->child.find(cur) == node->child.end())
                return false;

            node = node->child[cur];
            idx++;
        }
        return true;
	}
};

int main() {
	trie root;

	root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("ab");
	root.insert("bcd");

	cout << root.word_exist("xyz") << "\n";
	cout << root.word_exist("xy") << "\n";
	cout << root.prefix_exist("xy") << "\n";

	return 0;
}
