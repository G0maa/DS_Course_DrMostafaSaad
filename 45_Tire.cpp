#include<iostream>
#include<cstring>	// memset
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

    // find full word in trie that is a prefix of str.
    string first_word_prefix(const string &str) {
        int cur = 0;
        int idx = 0;
        
        trie* node = this;
        string word = "";

        while(idx != (int) str.size() && !node->isLeaf) {
            cur = str[idx] - 'a';
            if (!node->child[cur])
                return str;
            
            word += str[idx];
            node = node->child[cur];
            idx++;
        }

        return node->isLeaf ? word : str;
    }
};

void problem1();
void problem2();

int main() {
    problem1();
	
    cout << "\n NO RTE \n";
	return 0;
}








void problem1() {
    trie root;
    root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("ab");
	root.insert("bcd");


	cout << root.word_exist("xyz") << "\n";
	cout << root.word_exist("abf") << "\n";
	cout << root.word_exist("abcd") << "\n";
	cout << root.word_exist("xy") << "\n";
	cout << root.prefix_exist("xy") << "\n";
}

void problem2() {
    trie root;

    root.insert("xyz");
    root.insert("xyzea");
    root.insert("dc");
    root.insert("a");
    root.insert("bc");

    cout << root.first_word_prefix("x") << '\n';
    cout << root.first_word_prefix("xyzabc") << '\n';
    cout << root.first_word_prefix("daaa") << '\n';
}