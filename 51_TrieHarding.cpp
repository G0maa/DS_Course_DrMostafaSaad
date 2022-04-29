// I came from here https://www.udemy.com/course/dscpp-skills
#include<iostream>
#include <vector>
#include<cstring>	// memset
#include <cassert>
#include <algorithm>
#include <set>
using namespace std;

class trie {
private:
	static const int MAX_CHAR = 26;
    
	trie* prefix[MAX_CHAR];
	trie* suffix[MAX_CHAR];
	bool isLeaf { };

public:
    vector<int> words; // every inserted words, for each letter in int, it pushes back its index to this dictionary.
	trie() {
		// set an array to 0s. Here pointers to null
		memset(prefix, 0, sizeof(prefix));
		memset(suffix, 0, sizeof(suffix));
	}

    // words is inserted 2 times, 2nd time is reversed.
	void insert(string str, int dic_idx, int idx = 0) {
        trie* node = this;
        int cur = 0; // dummy value
        while(idx != (int) str.size()) {
            
            node->words.push_back(dic_idx); // adding word to the vector

            cur = str[idx] - 'a';
			if (node->prefix[cur] == 0)
				node->prefix[cur] = new trie();


            node = node->prefix[cur];
            idx++;
        }
        node->isLeaf = 1;
        rev_insert(str, dic_idx);
	}

    void rev_insert(string str, int dic_idx, int idx = 0) {
        reverse(str.begin(), str.end()); // I think this might take some time should just traverse backwards.

        trie* node = this;
        int cur = 0; // dummy value
        while(idx != (int) str.size()) {
            
            node->words.push_back(dic_idx); // adding word to the vector

            cur = str[idx] - 'a';
            if (node->suffix[cur] == 0)
                node->suffix[cur] = new trie();


            node = node->suffix[cur];
            idx++;
        }
        node->isLeaf = 1;
    }

    trie* prefix_exist(string str, int idx = 0) {
		int cur = 0;
        trie* node = this;
        while(idx != (int) str.size()) {
            cur = str[idx] - 'a';
            if (!node->prefix[cur])
                return nullptr;

            node = node->prefix[cur];
            idx++;
        }
        return node; // only difference.
	}

    trie* suffix_exist(string str, int idx = 0) {
        reverse(str.begin(), str.end());

		int cur = 0;
        trie* node = this;
        while(idx != (int) str.size()) {
            cur = str[idx] - 'a';
            if (!node->suffix[cur])
                return nullptr;

            node = node->suffix[cur];
            idx++;
        }
        return node; // only difference.
	}
};

class WordFilter {
public:
    trie prefix_tree;
    WordFilter(vector<string>& words) {
        set<string> words_set;
        for (int i = (int) words.size() - 1; i >= 0; --i) {
			if (words_set.insert(words[i]).second) {
				// Insert the word (normal prefix)
				prefix_tree.insert(words[i], i);
			}
		}
    }
    
    int f(string prefix, string suffix) {
        trie* prefix_node = prefix_tree.prefix_exist(prefix);
        trie* suffix_node = prefix_tree.suffix_exist(suffix);

        if(!prefix_node || !suffix_node)
            return -1;

        vector<int> prefix_vec = prefix_node->words;
        vector<int> suffix_vec = suffix_node->words;

        int prefix_idx = (int) prefix_vec.size() - 1;
        int suffix_idx = (int) suffix_vec.size() - 1;

        while(prefix_idx >= 0 && suffix_idx >= 0) {
            if(prefix_vec[prefix_idx] == suffix_vec[suffix_idx])
                return prefix_vec[prefix_idx];
            
            if(prefix_vec[prefix_idx] > suffix_vec[suffix_idx])
                prefix_idx--;
            else
                suffix_idx--;
        }
        return -1;
    }
};



int main() {
    freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
    // somewhat tested.
    vector<string> dic = {"WordFilter","f","f","f","f","f","f","f","f","f","f", "cabaabaaaa","ccbcababac","bacaabccba","bcbbcbacaa","abcaccbcaa","accabaccaa","cabcbbbcca","ababccabcb","caccbbcbab","bccbacbcba"};
    WordFilter *wordfilter = new WordFilter(dic);
    


    string prefix, suffix;
    while(cin >> prefix >> suffix)
        cout << wordfilter->f(prefix, suffix) << ' ';
    cout << "\n NO RTE \n";
	return 0;
}
