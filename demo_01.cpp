#include <iostream>
#include <vector>
#include <chrono>
using namespace std;


class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};


class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr; // start empty
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* t = head;
            head = head->next;
            delete t;
        }
    }

    void push_front(int value) {
        Node* n = new Node(value);
        n->next = head;
        head = n;
    }
};

int main() {

    int N = 500000;

    // --- vector/array, front insert ---
    {
        vector<int> a;
        a.reserve(N); //create a vector with N memory slot reserved

        auto t0 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            a.insert(a.begin(), i); // insert at front
        }
        auto t1 = chrono::high_resolution_clock::now();
        cout << "Vector: insert " << N << " records at the front. Process takes "
             << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
             << " milliseconds \n";
    }

    // --- LinkedList, front insert ---
    {
        LinkedList lst;

        auto t0 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            lst.push_front(i);
        }
            lst.push_front(N+1);
        auto t1 = chrono::high_resolution_clock::now();
        cout << "Linked_list: insert " << N << " records at the front. Process takes "
             << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
                << " milliseconds \n";
    }

    return 0;
}
