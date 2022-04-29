#include<iostream>
#include <vector>
#include <map>
#include<cstring>	// memset
using namespace std;

// 5/5 for the easy ones... makes me worried of what's going to come.
class trie {
private:
	map<string, trie*> child;
	bool isLeaf { };

    
public:
	trie() { }

    void insert(const vector<string> &path, int idx = 0) {
		trie* node = this;
        string cur = ""; // dummy value
        while(idx != (int) path.size()) {
            cur = path[idx];
			if (node->child.find(cur) == node->child.end())
				node->child.insert({cur, new trie()});

            node = node->child[cur]; // <<<
            idx++;
        }
        node->isLeaf = 1;
	}
	
	bool subpath_exist(vector<string> &path, int idx = 0) {
		string cur = "";
        trie* node = this;
        while(idx != (int) path.size()) {
            cur = path[idx];
            if (node->child.find(cur) == node->child.end())
                return false;

            node = node->child[cur];
            idx++;
        }
        return true;
	}
};

int main() {
trie tree;

	vector<string> path;

	path = {"home", "software", "eclipse"};
	tree.insert(path);

	path = {"home", "software", "eclipse", "bin"};
	tree.insert(path);

	path = {"home", "installed", "gnu"};
	tree.insert(path);

	path = {"user", "mostafa", "tmp"};
	tree.insert(path);

	path = {"user", "mostafa", "tmp"};
	cout << tree.subpath_exist(path) << "\n"; // 1

	path = {"user", "mostafa"};
	cout << tree.subpath_exist(path) << "\n"; // 1

	path = {"user", "most"};
	cout << tree.subpath_exist(path) << "\n"; // 0

	path = {"user", "mostafa", "private"};
	cout << tree.subpath_exist(path) << "\n"; // 0
    cout << "\n NO RTE \n";
	return 0;
}
