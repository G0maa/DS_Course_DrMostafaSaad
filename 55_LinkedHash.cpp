// Load factor only makes sense if they elemts in the hash table
// are uniformally distributed, therefore, if you have bad has function, you can have
// 30 elements in one bucket, although you have 40 buckets, the load factor is 3/4, but the result is still shit.
// In other words, is viable only if you have good hashing function to begin with :)

#include<iostream>
#include <vector>
#include<cassert>
using namespace std;

int hash_string(string str, int n) {
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
    // Neat way of changing implementation, first it was vector of PhoneEntry,
    // when we changed, we just added this struct.
    struct LinkedHashEntry {
        PhoneEntry item;
        LinkedHashEntry* next { };

        LinkedHashEntry(PhoneEntry item) : item(item) { }
    };

	int table_size { };
	// vector<LinkedHashEntry*> table;
	LinkedHashEntry **table;
	// mhm should know how to use pointers of pointers I guess.
    // ^ figured it out after trying the vecotr version.
public:
	PhoneHashTable(int table_size = 10) : table_size(table_size) {
        table = new LinkedHashEntry*[table_size](); // Weird syntax.
	}
    
	void put(PhoneEntry phone) {
		int idx = phone.hash() % table_size;

        if(!table[idx]) {
            table[idx] = new LinkedHashEntry(phone);
            return;
        }

        LinkedHashEntry *cur = table[idx];
		while(cur) {
            if(cur->item.name == phone.name) {
                cur->item.phone_number = phone.phone_number;
                return;
            }

            if(!cur->next)
                break;

            cur = cur->next;
        }

		cur->next = new LinkedHashEntry(phone);
	}

	void print_all() {
		for (int hash = 0; hash < table_size; ++hash) {
			if (!table[hash])
				continue;
            LinkedHashEntry *cur = table[hash];
			cout << "Hash " << hash << ": ";
			while(cur) {
                cur->item.print();
                cur = cur->next;
            }
			cout << "\n";
		}
	}

};

int main() {

	PhoneHashTable table(3);
	table.put(PhoneEntry("mostafa", "604-401-120"));
	table.put(PhoneEntry("mostafa", "604-401-777"));	// update
	table.put(PhoneEntry("ali", "604-401-343"));
	table.put(PhoneEntry("ziad", "604-401-17"));
	table.put(PhoneEntry("hany", "604-401-758"));
	table.put(PhoneEntry("belal", "604-401-550"));
	table.put(PhoneEntry("john", "604-401-223"));

	table.print_all();
	// Hash 0: (ali, 604-401-343)  (hany, 604-401-758)  (john, 604-401-223)
	// Hash 1: (mostafa, 604-401-777)  (ziad, 604-401-17)
	// Hash 2: (belal, 604-401-550)

	return 0;
}
