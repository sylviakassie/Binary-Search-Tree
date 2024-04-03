#include <stdio.h>
#include <stdlib.h>

// Structure for BST node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
struct Node *insert(struct Node *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Function to create a BST from array
struct Node *createBSTFromArray(int array[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node *root = createNode(array[mid]);

    root->left = createBSTFromArray(array, start, mid - 1);
    root->right = createBSTFromArray(array, mid + 1, end);

    return root;
}

// Function to perform inorder traversal of BST
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to find minimum value node in a subtree
struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from BST
struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct Node *temp = minValueNode(root->right);
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate height of BST
int height(struct Node *root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to print level and height of a node
void printLevelAndHeight(struct Node *root, int key, int level) {
    if (root == NULL)
        return;
    if (root->data == key) {
        printf("Level of node %d: %d\n", key, level); // Increment level by 1 to start from 1
        printf("Height of node %d: %d\n", key, height(root));
    }
    printLevelAndHeight(root->left, key, level + 1);
    printLevelAndHeight(root->right, key, level + 1);
}

int main() {
    int array[] = {5, 10, 15, 20, 25, 30, 35, 40, 45};
    int n = sizeof(array) / sizeof(array[0]);

    // Create BST from sorted array
    struct Node *root = createBSTFromArray(array, 0, n - 1);

    // Print inorder traversal of BST
    printf("Inorder traversal of BST: ");
    inorder(root);
    printf("\n");

    // Delete node with value 20
    root = deleteNode(root, 20);
    printf("BST after deleting node 20: ");
    inorder(root);
    printf("\n");

    // Print height of BST
    printf("Height of BST: %d\n", height(root));

    // Print level and height of node 30
    printLevelAndHeight(root, 30, 0);

    return 0;
}

