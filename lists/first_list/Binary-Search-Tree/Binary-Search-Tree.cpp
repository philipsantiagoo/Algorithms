#include <iostream>

// Custom type representing a BST node: stores a value and pointers to left and right subtrees.
struct Node {
    int value;
    Node* left_subtree;
    Node* right_subtree;
};


// Allocates a new node in memory with the given value and no children (nullptr).
Node* newNode(int value) {
    Node* node = new Node;

    node -> value = value;
    node -> left_subtree = nullptr;
    node -> right_subtree = nullptr;
    return node;
}


// Insertion logic: if the current position is null, creates a new node; if the value is smaller, moves left; if larger, moves right.
Node* insert(Node* root, int value) {
    if(root == nullptr) {
        return newNode(value);
    }
    
    if(value < root -> value) {
        root -> left_subtree = insert(root -> left_subtree, value);
    } else {
        root -> right_subtree = insert(root -> right_subtree, value);
    }

    return root;
}


// Preorder traversal: visits root, then left subtree, then right subtree.
void preOrder(Node* root) {
    if (root == nullptr) return;

    std::cout << root->value << std::endl;
    preOrder(root->left_subtree);
    preOrder(root->right_subtree);
}


// Inorder traversal: visits left subtree, then root, then right subtree. Returns values in ascending order.
void inOrder(Node* root) {
    if (root == nullptr) return;

    inOrder(root->left_subtree);
    std::cout << root->value << std::endl;
    inOrder(root->right_subtree);
}


// Postorder traversal: visits left subtree, then right subtree, then root.
void postOrder(Node* root) {
    if (root == nullptr) return;

    postOrder(root->left_subtree);
    postOrder(root->right_subtree);
    std::cout << root->value << std::endl;
}


int main() {
    Node* root = nullptr;
    int input;

    while (std::cin >> input) {
        root = insert(root, input);
    }

    postOrder(root);

    return 0;
}

