#include <iostream>
using namespace std;

// ===== Lecture 1 baseline: Node outside, explicit constructors =====
class Node {
public:
    int data;
    Node* next;

    // explicit constructor (no initializer list)
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

// ===== From Lecture 2 =====
    void print_recursive_impl(Node* node) {
        if (node == nullptr) {
            cout << endl;
            return;
        }
        cout << node->data << " ";
        print_recursive_impl(node->next);
    }

public:
    // explicit constructor (no initializer list)
    LinkedList() {
        head = nullptr; // start empty
    }

    ~LinkedList() {
        // Free all nodes safely (no leaks)
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // ===== From Lecture 1 =====
    // Simple space-separated print (read-only traversal)
    void print() {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }

    void push_front(int value) {
        Node* n = new Node(value);
        n->next = head;  // link first
        head = n;        // then move head
    }

    // ===== Lecture 2 additions =====

    // Pretty output: 10 -> 20 -> 30 -> NULL
    void print_with_arrows() {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "NULL" << endl;
    }

    bool empty() {
        return head == nullptr;
    }

    // Count nodes by traversal
    int size() {
        int count = 0;
        Node* cur = head;
        while (cur != nullptr) {
            count++;
            cur = cur->next;
        }
        return count;
    }

    // Return pointer to first node with matching data, else nullptr
    Node* find_first(int value) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == value) {
                return cur;
            }
            cur = cur->next;
        }
        return nullptr;
    }

    // Return 0-based index of first match, or -1 if not found
    int find_index(int value) {
        int idx = 0;
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == value) {
                return idx;
            }
            idx++;
            cur = cur->next;
        }
        return -1;
    }

    // Optional: recursive print (nice for teaching; iterative is safer for long lists)
    void print_recursive() {
        print_recursive_impl(head);
    }

    // Helper to build examples in natural order (without a tail pointer)
    void push_back(int value) {
        Node* n = new Node(value);
        if (head == nullptr) {
            head = n;
            return;
        }
        Node* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = n;
    }
};

// ===== Demo / quick tests (Lecture 2) =====
int main() {
    LinkedList list;

    // Build: 10 -> 20 -> 30 -> NULL
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    cout << "print(): ";
    list.print();                 // 10 20 30

    cout << "print_with_arrows(): ";
    list.print_with_arrows();     // 10 -> 20 -> 30 -> NULL

    cout << boolalpha;
    cout << "empty()? " << list.empty() << "\n";  // false
    cout << "size(): " << list.size() << "\n";    // 3

    Node* p = list.find_first(20);
    cout << "find_first(20): " << (p ? "found" : "not found") << "\n";
    cout << "find_index(30): " << list.find_index(30) << "\n";  // 2
    cout << "find_index(77): " << list.find_index(77) << "\n";  // -1

    list.push_front(5); // 5 -> 10 -> 20 -> 30
    cout << "after push_front(5): ";
    list.print_with_arrows();

    cout << "print_recursive(): ";
    list.print_recursive();       // 5 10 20 30

    return 0; // destructor frees all nodes
}
