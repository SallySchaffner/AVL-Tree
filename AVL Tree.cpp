#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

// Get height of the node
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Update height of a node
int updateHeight(Node* node) {
    return max(getHeight(node->left), getHeight(node->right)) + 1;
}

// Calculate balance factor of a node
int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Right rotate to fix LL imbalance
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = updateHeight(y);
    x->height = updateHeight(x);

    return x;
}

// Left rotate to fix RR imbalance
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = updateHeight(x);
    y->height = updateHeight(y);

    return y;
}

// Insert a node into AVL tree and return new root
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = updateHeight(node);

    int balance = getBalanceFactor(node);

    // Left-Left (LL) Case
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // Right-Right (RR) Case
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // Left-Right (LR) Case
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left (RL) Case
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// In-order traversal for displaying the AVL tree
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    // Insert nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "In-order traversal of AVL tree: ";
    inOrder(root);

    return 0;
}
