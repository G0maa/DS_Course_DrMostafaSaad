// Main "mistakes" for first part of the project:
// I'd say all solutions are correct but, they're not as clean,
// and some solutions have different approaches than mine, also I didn't think of
// array_length variable, and using the dummy node, which I guess resulted in *few* more lines.
// in the add function I made sure to use the same nodes, which wasn't a constrain.


// Main "mistakes" for second part of the project:
// I was *lost* for a very long time thinking about how should I implement it.
// Code produces correct results and efficint (I think), but with the wrong approach,
// Dr's code -> Struct for colomn node that is similar to the normal node we have, and another struct for row node,
// of which its data is an ArrayLinkedList, therefore, ArrayLinkedList -> deals with column nodes,
// SparseMatrix -> deals with row nodes, and the rest is repeated/shared code.
// Lesson learned -> divide as much as you can, instead, again make a code suitable for the problem,
// not change the old code to be suitable for the problem.

#include <bits/stdc++.h>
using namespace std;

struct Node {
	int data { };
    int idx { };
	Node* next { };
	Node* prev { };

	Node(int data, int idx) : data(data), idx(idx) {}

};

class ArrayLinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;
    int array_length { };
    // didn't think of array_length as in the solution.


    // I think normal user shouldn't be able to call these functions.

    void link(Node* first, Node*second) {
		if(first)
			first->next = second;
		if(second)
			second->prev = first;
	}

    void insert_front(Node *new_member) {
        link(new_member, head);
        head = new_member;
        length++;
    }

    void insert_back(Node *new_member) {
        link(tail, new_member);
        tail = new_member;
        length++;
    }

    void insert_middle(Node *new_member) {
        Node *after, *prev;
        for(Node* cur = head; cur; cur = cur -> next) {
            if(new_member->idx == cur->idx) {
                cur->data = new_member->data;
                delete new_member;
                return;
            }
            else if (new_member->idx < cur->idx) {
                prev = cur->prev;
                break;
            }
        }
        after = prev->next;
        link(prev, new_member);
        link(new_member, after);
        length++;
    }

public:
    // REVISE.
    ArrayLinkedList* next { };
    ArrayLinkedList* prev { };
    int idx = { };

    ArrayLinkedList(int array_length, int idx) : array_length(array_length), idx(idx) {
        assert(array_length >= 0 && idx >= -1);
     } // I'll just ignore the dummy node part.
	ArrayLinkedList(const ArrayLinkedList&) = delete;
	ArrayLinkedList &operator=(const ArrayLinkedList &another) = delete;
    
    ~ArrayLinkedList() { // O(n) time O(1) memory.. RTE if embty? REVISE
        if(head) {
            Node *prev;
            for(Node *cur = head -> next; cur;) {
                prev = cur;
                cur = cur -> next; // because can't maintain for nullptr.
                delete prev;
            }
        }
        head = tail = nullptr;
		length = 0; // ??
	}

    // my only debugging function :D
    void check() {
        cout << length << '\n';
    }

    // START OF FUNCTIONS:

    void print_array_nonzero() { // Correct
        for(Node *cur = head; cur; cur = cur->next) {
            cout << cur->data << ' ';
        }
        cout << '\n';
    }

    void set_value(int val, int idx) { // Again my code isn't as clean.
        assert(idx < array_length && idx >= 0);

        Node *new_member = new Node(val, idx);
        if(!head) {
            head = tail = new_member;
        }
        else if (new_member->idx < head->idx) {
            insert_front(new_member);
        }
        else if(new_member->idx > tail->idx) {
            insert_back(new_member);
        }
        else {
            insert_middle(new_member);
        }   
    }

    void print_array() { // Correct
        if(!head) {
            cout << "Embty list\n";
            return;
        }

        Node* cur = head;
        for(int i = 0; i < array_length; i++) {
            if(cur && cur->idx == i) {
                cout << cur->data << ' ';
                cur = cur->next;
            }
            else
                cout << 0 << ' ';
        }
        cout << '\n';
    }

    int get_value(int index) { // I'd say correct, doctor's code might be a bit more clean : )
        assert(index >= 0 && index < array_length);
        for(Node* cur = head; cur; cur = cur -> next) {
            if(cur->idx == index)
                return cur->data;
            else if(cur->idx > index) // slighly more efficient.
                return 0;
        }
        return 0;
    }

    void add(ArrayLinkedList &other) { // Very different, this is one is more efficeint but not simple I suppose, 
        assert(array_length == other.array_length);
        // Same solution as the one doctor used in the DLL homework 2, but with very little change.
        if (!other.head)
			return;
        else if(!head) {
            head = other.head;
            tail = other.tail;
            return;
        }

        Node *cur_this = head, *cur_other = other.head, *last { };
        while(cur_this && cur_other) {
            Node *next { };
            if(cur_this->idx == cur_other->idx) { // here
                next = cur_this;
                next->data += cur_other->data;
                cur_this = cur_this->next, cur_other = cur_other->next;
            } else if(cur_this->idx < cur_other->idx) {
                next = cur_this;
                cur_this = cur_this->next;
            } else {
                next = cur_other;
                cur_other = cur_other->next;
            }
            link(last, next);
            last = next;
            if(!head)
                head = last;
        }

        if(cur_other) {
            tail = other.tail;
            link(last, cur_other);
        }
        else if(cur_this) {
            link(last, cur_this);
        }
        other.head = other.tail = nullptr;
        other.length = 0;
    }

    void share_info(ArrayLinkedList &other) {
        head = other.head;
        tail = other.tail;
        length = other.length;
    }
};


// I'll use the dummy ~~Node~~ ArrayLinkedList here and use the old (correct) solutions.
class SparceMatrix {
    private:
        ArrayLinkedList *head { };
        ArrayLinkedList *tail { };
        int rows = 0; // not updated btw
        int cols = 0; // this too ^
        int array_rows { };
        int array_cols { };

        void link(ArrayLinkedList* first, ArrayLinkedList *second) {
            if(first)
                first->next = second;
            if(second)
                second->prev = first;
        }

        ArrayLinkedList* get_index(int idx, bool is_create) {
            ArrayLinkedList *prev_index = head;
            while (prev_index->next && prev_index->next->idx < idx)
			    prev_index = prev_index->next;
            
            bool found = prev_index->next && prev_index->next->idx == idx;

            if(found)
                return prev_index->next;
            
            if(!is_create)
                return nullptr;
            
            return embed_after(prev_index, 0, idx);
        }

        ArrayLinkedList* embed_after(ArrayLinkedList* list_before, int data, int idx) {
            ArrayLinkedList *middle = new ArrayLinkedList(array_cols, idx);

            ArrayLinkedList* list_after = list_before->next;

            link(list_before, middle);

            if (!list_after)
                tail = middle;
            else
                link(middle, list_after);

            return middle;
        }

    public:

    SparceMatrix(int array_rows, int array_cols) : array_rows(array_rows), array_cols(array_cols) {
        assert(array_cols > 0 && array_rows > 0);
        head = tail = new ArrayLinkedList(0, -1);
     }
	SparceMatrix(const SparceMatrix&) = delete;
	SparceMatrix &operator=(const SparceMatrix &another) = delete;


    void print_matrix_nonzero() {
        cout << "Print Matrix 10 x 10 non-zero:\n";
		for (ArrayLinkedList* cur = head->next; cur; cur = cur->next) {
            (*cur).print_array_nonzero();
        }	
		cout << "\n";
	}

    void print_matrix() {
        cout << "Print Matrix " << array_rows << " x " << array_cols << ":\n";
		ArrayLinkedList* cur = head->next;
		for (int c = 0; c < array_rows; ++c) {
			if (cur && cur->idx == c) {
				(*cur).print_array();
				cur = cur->next;
			} else {
				for(int i = 0; i < array_cols; i++)
                    cout << "0 ";
                cout << '\n';
            }
		}
		cout << "\n";
	}

    void set_value(int val, int row, int col) {
        assert(row < array_rows && row >= 0);

        ArrayLinkedList *cur = get_index(row, true);
        (*cur).set_value(val, col); // revise
    }

    int get_value(int row, int col) {
		ArrayLinkedList* alist = get_index(row, false);
		if (!alist)
			return 0;
		return (*alist).get_value(col); // revise
	}

    void add(SparceMatrix &other) { // REVISE VERY MUCH
		assert(array_cols = other.array_cols && array_rows == other.array_rows);

        if (!other.head)
			return;
        else if(!head) {
            head = other.head;
            tail = other.tail;
            return;
        }

        // Notice that snetinel node is only created in SparceMatrix.
		ArrayLinkedList *cur_list = head->next;
		for (ArrayLinkedList* other_list = other.head->next; other_list; other_list = other_list->next) {
			if(cur_list->idx == other_list->idx) {
                (*cur_list).add(*other_list);
                cur_list = cur_list -> next;
            }
            else {
                ArrayLinkedList *middle = get_index(other_list->idx, true);
                (*middle).share_info(*other_list);
                cur_list = middle->next; // what if tail?
            }
		}
		other.head = other.tail = nullptr;
        other.array_rows = other.array_cols = 0;
	}
};

void test_sparse() {
	SparceMatrix mat(10, 10);
	mat.set_value(5, 3, 5);
	mat.set_value(7, 3, 7);
	mat.set_value(2, 3, 2);
	mat.set_value(0, 3, 2);
	mat.set_value(6, 5, 6);
	mat.set_value(4, 5, 4);
	mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	//mat.set_value(1, 70, 1);
	mat.print_matrix();
	mat.print_matrix_nonzero();

	SparceMatrix mat2(10, 10);
	mat2.set_value(5, 1, 9);
	mat2.set_value(6, 3, 8);
	mat2.set_value(9, 9, 9);
	mat.add(mat2);
	mat.print_matrix_nonzero();
}

int main() {
    test_sparse();

    cout << "\n\n NO R T E \n\n";
}