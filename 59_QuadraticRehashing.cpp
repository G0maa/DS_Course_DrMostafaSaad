#include<iostream>
#include <vector>
#include<cassert>
#include<unordered_set>
using namespace std;

int hash_string(string str, int n = 65407) {
	long long nn = n;
	long long sum = 0;
	for (int i = 0; i < (int) str.size(); ++i)
		sum = (sum * 26 + str[i] - 'a') % nn;
	return sum % nn;
}

struct PhoneEntry {
	const static int INTERNAL_LIMIT = 65407;
	string name;			// key
	string phone_number;	// data

	int hash() {
		return hash_string(name, INTERNAL_LIMIT);
	}

	PhoneEntry(string name, string phone_number) :
			name(name), phone_number(phone_number) {
	}

	void print() {
		cout << "(" << name << ", " << phone_number << ")  ";
	}
};


class PhoneHashTable {
private:
	int table_size;
	vector<PhoneEntry*> table;
	// to mark a cell as deleted
	PhoneEntry *deleted {};
public:
	PhoneHashTable(int table_size) :
			table_size(table_size) {
		table.resize(table_size);
		deleted = new PhoneEntry("", "");
	} //  needs a destructor


	// Obviously not efficient.
	void put(PhoneEntry phone) {
		int idx = phone.hash() % table_size;
		unordered_set<int> isRepated; 
		// We max move table_size steps
		for (int step = 1; isRepated.count(idx) != 1; ++step) {

			if (table[idx] == deleted || !table[idx]) {
				table[idx] = new PhoneEntry(phone.name, phone.phone_number);
				return;
			}
			else if (table[idx]->name == phone.name) {
				table[idx]->phone_number = phone.phone_number;
				return;
			}

			isRepated.insert(idx);
			idx = (idx + (step * step)) % table_size;	// move next
		}
		rehashing();
		put(phone); // since it failed before.
	}

	bool remove(PhoneEntry phone) {
		int idx = phone.hash() % table_size;
		unordered_set<int> isRepated; 
		for (int step = 0; isRepated.count(idx) != 1; ++step) {
			if(!table[idx])
				break;
			if (table[idx] != deleted && table[idx]->name == phone.name) {
				delete table[idx];
				table[idx] = deleted;
				return true;
			}

			isRepated.insert(idx);
			idx = (idx + (step * step)) % table_size;	// move next
		}
		return false;
	}
	
	bool get(PhoneEntry &phone) {
		int idx = phone.hash() % table_size;

		for (int step = 0; step < table_size; ++step) {
			if(!table[idx])
				break;
			if (table[idx] != deleted && table[idx]->name == phone.name) {
				phone.phone_number = table[idx]->phone_number;
				return true;
			}
			idx = (idx + 1) % table_size;	// move next
		}
		return false;
	}

	void print_all() {
		for (int hash = 0; hash < table_size; ++hash) {
			cout << hash << " ";
			if (table[hash] == deleted)
				cout << " X ";
			else if (!table[hash])
				cout << " E ";
			else
				table[hash]->print();
			cout << "\n";
		}
		cout << "******************\n";
	}

    void rehashing() {
		vector<PhoneEntry*> old_table;
		swap(table, old_table);
		table.resize(table_size * 2);
		table_size *= 2;
		for(auto element: old_table)
			if(element)
				put(*element);
    }
};

int main() {

	PhoneHashTable table(3);
	table.put(PhoneEntry("mostafa", "604-401-120"));
	table.put(PhoneEntry("mostafa", "604-401-777"));
	table.put(PhoneEntry("ali", "604-401-343"));
	table.put(PhoneEntry("ziad", "604-401-17"));
	table.put(PhoneEntry("hany", "604-401-758"));
	table.put(PhoneEntry("belal", "604-401-550"));
	table.put(PhoneEntry("john", "604-401-223"));

	table.print_all();

	/*
	 0  E
	 1  E
	 2  E
	 3 (john, 604-401-223)
	 4  E
	 5  E
	 6 (mostafa, 604-401-120)
	 7 (hany, 604-401-758)
	 8 (ali, 604-401-343)
	 9 (ziad, 604-401-17)
	 10 (belal, 604-401-550)
	 */

	// cout << table.remove(PhoneEntry("smith", "")) << "\n"; // 0
	// cout << table.remove(PhoneEntry("hany", "")) << "\n";  // 1
	// cout << table.remove(PhoneEntry("john", "")) << "\n";  // 1
	// table.print_all();
	/*
	 0  E
	 1  E
	 2  E
	 3  X
	 4  E
	 5  E
	 6 (mostafa, 604-401-120)
	 7  X
	 8 (ali, 604-401-343)
	 9 (ziad, 604-401-17)
	 10 (belal, 604-401-550)
	 */

	// PhoneEntry e("belal", "");
	// if (table.get(e))
	// 	cout << e.phone_number << "\n";	// 604-401-550

	// table.put(PhoneEntry("hany", "604-401-555"));
	// table.print_all();
	/*
	 0  E
	 1  E
	 2  E
	 3  X
	 4  E
	 5  E
	 6 (mostafa, 604-401-120)
	 7 (hany, 604-401-555)
	 8 (ali, 604-401-343)
	 9 (ziad, 604-401-17)
	 10 (belal, 604-401-550)
	 */
	return 0;
}
