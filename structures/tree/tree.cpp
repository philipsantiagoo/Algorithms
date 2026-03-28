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