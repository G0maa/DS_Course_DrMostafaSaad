#include<iostream>
#include<cstring>	// memset
using namespace std;

// My thought process went into 3 levels:
// 1. Can I just do it with the original code? = Visit each child,
//    check if it has the first letter of str,
//    then continue with remaining letters, and other nodes = Very inefficient.
// 2. Mhm.... Add another trie, to be children but backwards, aka links every last letter with that new trie
//    = Very complicated, similar to double linked list, also that's basically memory x2,
//     where the data structure is already memory inefficent.
// 3. Finally, looked at the problem statement, it will just have the two mentioned functions,
//    so I'll just insert all words backwards with no-way to traverse them from the beginning.
//    aka it can only be used for suffix.
// = Still dr's code is better ._.
class trie {
private:
	static const int MAX_CHAR = 26;
	trie* child[MAX_CHAR];
	bool isLeaf { };

    void insert(string str, int idx) {
		if (idx == -1)
			isLeaf = 1; // here
		else {
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new trie();
			child[cur]->insert(str, idx - 1); // here
		}
	}

public:
	trie() {
		// set an array to 0s. Here pointers to null
		memset(child, 0, sizeof(child));
	}

    // clean code u_u
	void insert(string str) {
		insert(str, str.size() - 1);
	}

    // Check if any of the inserted words has suffix str.
    // Changed design of data structure, it now inserts words in a... backwards way?
	bool suffix_exist(const string &str) {
        int cur = 0;
        int idx = (int) str.size() - 1;
        trie* node = this;
        while(idx != -1) {
            cur = str[idx] - 'a';
            if (!node->child[cur])
                return false;

            node = node->child[cur];
            idx--;
        }
        return true;
    }
};

int main() {
	trie root;
    root.insert("test");
    root.insert("bacd");
    root.insert("catrepillar");

    cout << root.suffix_exist("t") << '\n';
    cout << root.suffix_exist("st") << '\n';
    cout << root.suffix_exist("est") << '\n';
    cout << root.suffix_exist("test") << '\n';

    cout << root.suffix_exist("tt") << '\n';
    cout << root.suffix_exist("et") << '\n';

    cout << root.suffix_exist("d") << '\n';
    cout << root.suffix_exist("cd") << '\n';
    cout << root.suffix_exist("acd") << '\n';
    cout << root.suffix_exist("bacd") << '\n';

    cout << root.suffix_exist("ba") << '\n';
    cout << root.suffix_exist("ad") << '\n';
	return 0;
}
