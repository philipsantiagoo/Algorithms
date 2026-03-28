struct Node {
    int value;
    Node* left_subtree;
    Node* right_subtree;
};


Node* newNode(int value) {
    Node* node = new Node;

    node -> value = value;
    node -> left_subtree = nullptr;
    node -> right_subtree = nullptr;
    return node;
}


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