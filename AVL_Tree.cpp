#include <iostream>
using namespace std;

// Khai báo cấu struct cây AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Hàm tính chiều cao của một node
int getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Hàm cập nhật chiều cao của một node
void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Hàm xoay phải (right rotate)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Hàm xoay trái (left rotate)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Hàm xoay trái rồi xoay phải (left-right rotate)
Node* leftRightRotate(Node* node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

// Hàm xoay phải rồi xoay trái (right-left rotate)
Node* rightLeftRotate(Node* node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

// Hàm thêm node
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    else {
        return root; // Node đã tồn tại trong cây
    }

    updateHeight(root);

    int balance = getHeight(root->left) - getHeight(root->right);

    // Cân bằng cây sau khi thêm node mới
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    if (balance > 1 && key > root->left->key) {
        return leftRightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        return rightLeftRotate(root);
    }

    return root;
}

int main() {
    Node* root = nullptr;
    int arr[7] = { 10, 5, 15, 3, 7, 12, 20 };
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < arrSize; ++i) {
        cout << arr[i] << " ";
    }

    for (int i = 0; i < arrSize; ++i) {
        root = insert(root, arr[i]);
        cout << "\nCay AVL sau khi them phan tu: " << arr[i] << "\n";
    }

    return 0;
}
