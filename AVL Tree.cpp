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

    cout << "\nRight rotate before rotation: " << "y =  " << y->data << " " << "x = " << y->left->data;
    if (x->right)
        cout << " T2 = " << x->right->data << endl;
    else
        cout << endl;

    x->right = y;
    y->left = T2;

    cout << "After rotation: x-right= " << x->right->data;
    if (y->left)
        cout << " y->left = " << y->left->data << endl;
    else
        cout << endl;

    y->height = updateHeight(y);
    x->height = updateHeight(x);

    return x;
}

// Left rotate to fix RR imbalance
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    cout << "\nLeft rotate before rotation: " << "x =  " << x->data << " " << "y = " << x->right->data;
    if (y->left)
        cout << " T2 = " << y->left->data << endl;
    else
        cout << endl;

    y->left = x;
    x->right = T2;

    cout << "After rotation: y-left= " << y->left->data;
    if (x->right)
        cout << " x->right = " << T2->data << endl;
    else
        cout << endl;

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
    cout << "height: " << node->height << " balance: " << balance << endl;

    // Left-Left (LL) Case
    if (balance > 1 && key < node->left->data) {
        cout << "+++++ LL imbalance\n";
        return rightRotate(node);
    }
   
    // Right-Right (RR) Case
    if (balance < -1 && key > node->right->data) {
        cout << "+++++ RR imbalance\n";
        return leftRotate(node);
    }

    // Left-Right (LR) Case
    if (balance > 1 && key > node->left->data) {
        cout << "+++++ LR imbalance\n";
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left (RL) Case
    if (balance < -1 && key < node->right->data) {
        cout << "+++++ RL imbalance\m";
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

// Pre-order traversal for displaying the AVL tree
void preOrder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void traversals(Node* root)
{
    inOrder(root);
    cout << endl;
    preOrder(root);
    cout << endl << endl;
}

int main() {
    Node* root = nullptr;

    // Insert nodes
    cout << "-------Inserting 10\n";
    cout << "Before: ";
    traversals(root);
    root = insert(root, 10);
    cout << "After: \n";
    traversals(root);
    cout << "-------Inserting 20\n";
    root = insert(root, 20);
    traversals(root);
    cout <<  "-------Inserting 30\n";
    root = insert(root, 30);
    traversals(root);
    cout << "-------Inserting 40\n";
    root = insert(root, 40);
    traversals(root);
    cout << "-------Inserting 50\n";
    root = insert(root, 50);
    traversals(root);
    cout << "-------Inserting 25\n";
    root = insert(root, 25);
    traversals(root);

    return 0;
}
