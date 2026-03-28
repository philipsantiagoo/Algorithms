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


// Finds and returns the smallest node in the BST.
Node* smallestNode(Node* root) {
    while (root -> left_subtree != nullptr) {
        root = root -> left_subtree;
    }

    return root;
}


// Insertion logic: if the current position is null, creates a new node; if the value is smaller, moves left; if larger, moves right.
Node* insert(Node* root, int value) {
    if   (root == nullptr) {
        return newNode(value);
    }
    
    if (value < root -> value) {
        root -> left_subtree = insert(root -> left_subtree, value);
    } else {
        root -> right_subtree = insert(root -> right_subtree, value);
    }

    return root;
}



// Removes a node with the given value from the BST.
// Handles three cases: no children, one child, and two children.
Node* remove(Node* root, int value) {
    // Value not found in the tree.
    if (root == nullptr) {
        return nullptr;
    }


    // Value is smaller: move to the left subtree.
    if (value < root->value) {
        root->left_subtree = remove(root->left_subtree, value);


    // Value is larger: move to the right subtree.
    } else if (value > root->value) {
        root->right_subtree = remove(root->right_subtree, value);


    // Found the node to remove.
    } else {

        // Case 1: no children — just delete the node.
        if (root->left_subtree == nullptr && root->right_subtree == nullptr) {
            delete root;
            return nullptr;

        // Case 2a: no left child — replace with right child.
        } else if (root->left_subtree == nullptr) {
            Node* temp = root->right_subtree;
            delete root;
            return temp;

        // Case 2b: no right child — replace with left child.
        } else if (root->right_subtree == nullptr) {
            Node* temp = root->left_subtree;
            delete root;
            return temp;

        // Case 3: two children — replace with inorder successor (smallest in right subtree),
        // then remove the successor from the right subtree.
        } else {
            Node* temp = smallestNode(root->right_subtree);
            root->value = temp->value;
            root->right_subtree = remove(root->right_subtree, temp->value);
        }
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

