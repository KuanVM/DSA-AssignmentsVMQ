#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Hàm thêm node vào đầu danh sách
void insertAtBeginning(Node*& head, int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

// Hàm in danh sách liên kết
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Hàm xoá node đầu danh sách
void deleteFirstNode(Node*& head) {
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

// Hàm xoá node cuối danh sách
void deleteLastNode(Node*& head) {
    if (head == nullptr || head->next == nullptr) {
        deleteFirstNode(head);
        return;
    }
    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}

// Hàm xoá node sau một node cho trước
void deleteNodeAfter(Node* node) {
    if (node == nullptr || node->next == nullptr) {
        return;
    }
    Node* temp = node->next;
    node->next = temp->next;
    delete temp;
}

int main() {
    Node* head = nullptr;

    // Thêm các node vào đầu danh sách
    insertAtBeginning(head, 3);
    insertAtBeginning(head, 2);
    insertAtBeginning(head, 1);

    cout << "Danh sach ban dau: ";
    printList(head);

    // Xoá node đầu danh sách
    deleteFirstNode(head);
    cout << "Danh sach sau khi xoa node dau: ";
    printList(head);

    // Xoá node cuối danh sách
    deleteLastNode(head);
    cout << "Danh sach sau khi xoa node cuoi ";
    printList(head);

    // Xoá node sau node đầu tiên
    if (head != nullptr) {
        deleteNodeAfter(head);
        cout << "Danh sach sau khi xoa node sau node dau: ";
        printList(head);
    }

    return 0;
}