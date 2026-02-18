#include <iostream>
using namespace std;

// ===== Node (outside), explicit constructor =====
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// ===== LinkedList with tail pointer & O(1) size =====
class LinkedList {
private:
    Node* head;
    Node* tail;
    int   count;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~LinkedList() {
        clear();
    }

    bool empty() const { return head == nullptr; }
    int  size()  const { return count; }

    // ---- Output helpers ----
    void print() const {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }

    void print_with_arrows() const {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "NULL" << endl;
    }

    // ---- Builders ----
    void push_front(int value) {
        Node* n = new Node(value);
        n->next = head;
        head = n;
        if (tail == nullptr) tail = n;
        count++;
    }

    void push_back(int value) {
        Node* n = new Node(value);
        if (tail == nullptr) {     // empty list
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        count++;
    }

    // insert before position index (0..count)
    bool insert_at(int index, int value) {
        if (index < 0 || index > count) return false;
        if (index == 0)     { push_front(value); return true; }
        if (index == count) { push_back(value);  return true; }

        Node* prev = head;
        for (int i = 1; i < index; ++i) prev = prev->next;
        Node* n = new Node(value);
        n->next = prev->next;
        prev->next = n;
        count++;
        return true;
    }

    // ---- Deletions ----
    bool pop_front() {
        if (head == nullptr) return false;
        Node* t = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete t;
        count--;
        return true;
    }

    bool pop_back() {
        if (head == nullptr) return false;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            count = 0;
            return true;
        }
        Node* prev = head;
        while (prev->next != tail) prev = prev->next;
        delete tail;
        tail = prev;
        tail->next = nullptr;
        count--;
        return true;
    }

    bool erase_first(int value) {
        if (head == nullptr) return false;
        if (head->data == value) return pop_front();

        Node* prev = head;
        Node* cur  = head->next;
        while (cur != nullptr) {
            if (cur->data == value) {
                prev->next = cur->next;
                if (cur == tail) tail = prev;
                delete cur;
                count--;
                return true;
            }
            prev = cur;
            cur  = cur->next;
        }
        return false;
    }

    bool erase_at(int index) {
        if (index < 0 || index >= count) return false;
        if (index == 0) return pop_front();

        Node* prev = head;
        for (int i = 1; i < index; ++i) prev = prev->next;
        Node* cur = prev->next;
        prev->next = cur->next;
        if (cur == tail) tail = prev;
        delete cur;
        count--;
        return true;
    }

    void clear() {
        while (head != nullptr) {
            Node* t = head;
            head = head->next;
            delete t;
        }
        tail = nullptr;
        count = 0;
    }
};

// ===== Demo =====
int main() {
    LinkedList L;

    // Build 10 -> 20 -> 30
    L.push_back(10);
    L.push_back(20);
    L.push_back(30);
    cout << "Start: "; L.print_with_arrows();
    cout << "size=" << L.size() << ", empty=" << boolalpha << L.empty() << "\n\n";

    // Insert 25 at index 2: 10 -> 20 -> 25 -> 30
    L.insert_at(2, 25);
    cout << "After insert_at(2, 25): "; L.print_with_arrows();

    // Push at both ends: 5 -> 10 -> 20 -> 25 -> 30 -> 40
    L.push_front(5);
    L.push_back(40);
    cout << "After push_front(5) & push_back(40): "; L.print_with_arrows();
    cout << "size=" << L.size() << "\n\n";

    // Remove by value (first match): remove 25
    L.erase_first(25);
    cout << "After erase_first(25): "; L.print_with_arrows();

    // Pop back: remove 40
    L.pop_back();
    cout << "After pop_back(): "; L.print_with_arrows();
    cout << "size=" << L.size() << "\n\n";

    // Erase at index 0: remove 5 → back to 10 -> 20 -> 30
    L.erase_at(0);
    cout << "After erase_at(0): "; L.print_with_arrows();

    // Clear all
    L.clear();
    cout << "After clear(): "; L.print_with_arrows();
    cout << "size=" << L.size() << ", empty=" << L.empty() << "\n";
    return 0;
}
