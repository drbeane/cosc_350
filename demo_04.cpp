#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int value) { data = value; prev = nullptr; next = nullptr; }
};

class DoublyList {
private:
    Node* head;
    Node* tail;

public:
    DoublyList() { head = nullptr; tail = nullptr; }

    ~DoublyList() {
        Node* cur = head;
        while (cur != nullptr) { Node* nxt = cur->next; delete cur; cur = nxt; }
        head = tail = nullptr;
    }

    bool empty() const { return head == nullptr; }

    Node* find_first(int value) const {
        Node* cur = head;
        while (cur != nullptr) { if (cur->data == value) return cur; cur = cur->next; }
        return nullptr;
    }

    void push_front(int value) {
        Node* n = new Node(value);
        n->next = head;
        if (head != nullptr) head->prev = n; else tail = n;
        head = n;
    }

    void push_back(int value) {
        Node* n = new Node(value);
        n->prev = tail;
        if (tail != nullptr) tail->next = n; else head = n;
        tail = n;
    }

    bool insert_after(Node* pos, int value) {
        if (pos == nullptr) return false;
        Node* n = new Node(value);
        n->prev = pos;
        n->next = pos->next;
        if (pos->next != nullptr) pos->next->prev = n; else tail = n;
        pos->next = n;
        return true;
    }

    bool insert_before(Node* pos, int value) {
        if (pos == nullptr) return false;
        Node* n = new Node(value);
        n->next = pos;
        n->prev = pos->prev;
        if (pos->prev != nullptr) pos->prev->next = n; else head = n;
        pos->prev = n;
        return true;
    }

    bool erase_node(Node* x) {
        if (x == nullptr) return false;
        if (x->prev != nullptr) x->prev->next = x->next; else head = x->next;
        if (x->next != nullptr) x->next->prev = x->prev; else tail = x->prev;
        delete x;
        return true;
    }

    bool erase_first(int value) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == value) return erase_node(cur);
            cur = cur->next;
        }
        return false;
    }

    bool pop_front() { return head ? erase_node(head) : false; }
    bool pop_back()  { return tail ? erase_node(tail) : false; }

    void print_forward() const {
        Node* cur = head;
        while (cur != nullptr) { cout << cur->data << " -> "; cur = cur->next; }
        cout << "NULL\n";
    }
    void print_backward() const {
        Node* cur = tail;
        while (cur != nullptr) { cout << cur->data << " <- "; cur = cur->prev; }
        cout << "NULL\n";
    }
};

int main() {
    DoublyList L;

    // Build 10 <-> 20 <-> 30
    L.push_back(10);
    L.push_back(20);
    L.push_back(30);
    cout << "Start (F): "; L.print_forward();   // 10 -> 20 -> 30 -> NULL
    cout << "Start (B): "; L.print_backward();  // 30 <- 20 <- 10 <- NULL

    // Ends
    L.push_front(5);    // 5 <-> 10 <-> 20 <-> 30
    L.push_back(40);    // 5 <-> 10 <-> 20 <-> 30 <-> 40
    cout << "After pushes (F): "; L.print_forward();

    // Insert around 20
    Node* n20 = L.find_first(20);
    L.insert_after(n20, 25);         // 5 <-> 10 <-> 20 <-> 25 <-> 30 <-> 40
    cout << "After insert_after(20,25): "; L.print_forward();

    n20 = L.find_first(20);
    L.insert_before(n20, 15);        // 5 <-> 10 <-> 15 <-> 20 <-> 25 <-> 30 <-> 40
    cout << "After insert_before(20,15): "; L.print_forward();

    // Erase + pops
    L.erase_first(25);               // 5 <-> 10 <-> 15 <-> 20 <-> 30 <-> 40
    cout << "After erase_first(25): "; L.print_forward();

    L.pop_front();                   // remove 5
    L.pop_back();                    // remove 40
    cout << "After pop_front & pop_back: "; L.print_forward();

    // Final backward check
    cout << "Backward check: "; L.print_backward();
    return 0;
}
