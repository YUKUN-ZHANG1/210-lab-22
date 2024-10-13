// COMSC-210 | Lab 22: Upgrade the DLL Class | Yukun Zhang
// IDE used: Visual Studio Code

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() { //delete a node from front
        if (!head) return; //is empty
        Node* temp = head;
        head = head->next;
        if(head) head->prev = nullptr;
        else tail = nullptr; 
        delete temp;
    }

    void pop_back() { //delete a node from back
        if (!tail) return; //is empty
        Node* temp = tail;
        tail = tail->prev;
        if(tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) { //delete a node by search value
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void delete_pos(int pos) { //delete a node by position
        if (!head||pos<0) return; // Empty list or illegal position

        Node* temp = head;
        for (;temp && pos>0; pos--)
            temp = temp->next;

        if (!temp) return; // position not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }


    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    bool is_empty() {
        return head == nullptr;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
// Driver program
int main() {
    DoublyLinkedList list;

    // Randomly generate a list of a certain size
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);

    cout << "Initial list (forward): ";
    list.print();

    cout << "Initial list (backward): ";
    list.print_reverse();

    // Test push_front()
    cout << "\nPushing 55 to the front of the list...\n";
    list.push_front(55);
    list.print();

    // Test pop_front()
    cout << "\nPopping front node...\n";
    list.pop_front();
    list.print();

    // Test pop_back()
    cout << "\nPopping back node...\n";
    list.pop_back();
    list.print();

    // Test insert_after() to insert 88 after position 3
    cout << "\nInserting 88 after position 3...\n";
    list.insert_after(88, 3);
    list.print();

    // Test delete_pos() to delete the node at position 2
    cout << "\nDeleting node at position 2...\n";
    list.delete_pos(2);
    list.print();

    // Test delete_val() to delete the node with value 88
    cout << "\nDeleting node with value 88...\n";
    list.delete_val(88);
    list.print();

    // Test pop_front() and pop_back() again
    cout << "\nPopping front and back nodes...\n";
    list.pop_front();
    list.pop_back();
    list.print();

    // Test behavior when the list is empty
    cout << "\nClearing the list...\n";
    while (!list.is_empty()) {
        list.pop_front(); // Gradually remove all nodes from the list
    }
    list.print();

    cout << "Trying to delete from an empty list...\n";
    list.pop_back(); // Test deleting the tail node from an empty list
    list.delete_pos(0); // Test deleting a node at a specific position from an empty list
    list.delete_val(10); // Test deleting a node by value from an empty list

    return 0;
}

