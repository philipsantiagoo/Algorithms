#include <iostream>

// Recursively calculates the height of a node at index i in the array-based tree.
// Returns -1 if the node is null or out of bounds.
int height(int array[], int array_size, int i) {
    if (i >= array_size || array[i] == -1) {
        return -1;
    }

    int left_subtree = height(array, array_size, 2*i + 1);
    int right_subtree = height(array, array_size, 2*i + 2);

    if (left_subtree > right_subtree) {
        return 1 + left_subtree;
    } else {
        return 1 + right_subtree;
    }
}

// Checks if the array-based tree is a valid AVL tree.
// A tree is AVL if every node has a balance factor (left height - right height) between -1 and 1.
bool isAVL(int array[], int array_size) {
    int balancing;

    for (int i = 0; i < array_size; i++) {
        if (array[i] != -1) {
            int left = height(array, array_size, 2*i + 1);
            int right = height(array, array_size, 2*i + 2);
            balancing = left - right;

            if (balancing < -1 || balancing > 1) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int test_cases;
    std::cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        int array_size;
        std::cin >> array_size;

        // Max size is 100 as per problem constraints
        int array[100];
        for (int j = 0; j < array_size; j++) {
            std::cin >> array[j];
        }

        if (isAVL(array, array_size)) {
            std::cout << "T" << std::endl;
        } else {
            std::cout << "F" << std::endl;
        }
    }

    return 0;
}