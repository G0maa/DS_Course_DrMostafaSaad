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

    // O(26^n) ... oof. WRONG it is O(NL), N = Words, L = Word Length
    void get_all_strings(vector<string> &res, string word = "") {
        if(this->isLeaf)
            res.push_back(word);

        for(int i = 0; i < 26; i++)
            if(this->child[i])
                this->child[i]->get_all_strings(res, word + char(i + 'a'));  
    }

    void auto_complete(const string &str, vector<string> &res) {
        trie* cur = this;
        for(int i = 0; i < (int) str.size(); i++) { // normal search
            if(cur->child[str[i] - 'a'])
                cur = cur->child[str[i] - 'a'];
            else
                return; // if letter not found -> no words.
        }
        cur->get_all_strings(res, str);
    }

    bool word_exist_with_1_change(const string &str) {
        trie* cur = this;
        for(int i = 0; i < (int) str.size(); i++) {
            if(cur->child[str[i] - 'a'])
                cur = cur->child[str[i] - 'a'];
            else {
                for(int j = 0; j < 26; j++) {
                    if(cur->child[j])
                        if(cur->child[j]->word_exist(str, i + 1))
                            return true;
                }
                return false;
            }
        }
        return false;
    }
};

void problem1();
void problem2();
void problem3();

int main() {

    // problem3();

    cout << "\n NO RTE \n";
	return 0;
}

void problem3() {
    trie tree;

    tree.insert("hello");
    tree.insert("leetcode");

    assert(tree.word_exist_with_1_change("hello") == false);
    assert(tree.word_exist_with_1_change("xello") == true);
    assert(tree.word_exist_with_1_change("xyllo") == false);

    assert(tree.word_exist_with_1_change("leetcode") == false);
    assert(tree.word_exist_with_1_change("xeetcode") == true);
    assert(tree.word_exist_with_1_change("lxetcode") == true);
    assert(tree.word_exist_with_1_change("lextcode") == true);
    assert(tree.word_exist_with_1_change("leexcode") == true);
    assert(tree.word_exist_with_1_change("leetxode") == true);
    assert(tree.word_exist_with_1_change("leetcxde") == true);
    assert(tree.word_exist_with_1_change("leetcoxe") == true);
    assert(tree.word_exist_with_1_change("leetcodx") == true);

    // added 1 more letter.
    assert(tree.word_exist_with_1_change("leettcode") == false);
    assert(tree.word_exist_with_1_change("leetcodee") == false);
    assert(tree.word_exist_with_1_change("leetcoode") == false);

    assert(tree.word_exist_with_1_change("hello") == false);
    assert(tree.word_exist_with_1_change("hhllo") == true);
    assert(tree.word_exist_with_1_change("hell") == false);
    assert(tree.word_exist_with_1_change("leetcoded") == false);
}

void problem2() {
    trie tree;

	tree.insert("abcd");
    tree.insert("ab");
	tree.insert("abx");
	tree.insert("abyz");
	tree.insert("xyz");
    tree.insert("a");
	tree.insert("bcd");

	vector<string> res;
	tree.auto_complete("ab", res);
	for (int i = 0; i < (int) res.size(); ++i)
		cout << res[i] << "\n";
}

void problem1() {
    trie tree;

	tree.insert("abcd");
	tree.insert("xyz");
	tree.insert("a");
	tree.insert("ab");
	tree.insert("xyzw");
	tree.insert("bcd");

	vector<string> res;
	tree.get_all_strings(res);
	for (int i = 0; i < (int) res.size(); ++i)
		cout << res[i] << "\n";
}