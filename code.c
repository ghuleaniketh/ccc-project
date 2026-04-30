#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node *newNode(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance(struct Node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct Node *insert(struct Node *node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node *deleteNode(struct Node *root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int search(struct Node *root, int data) {
    if (root == NULL)
        return 0;
    if (root->data == data)
        return 1;
    if (data < root->data)
        return search(root->left, data);
    return search(root->right, data);
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void printTree(struct Node *root, int space) {
    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d (h=%d, bf=%d)\n", root->data, root->height, getBalance(root));

    printTree(root->left, space);
}

void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void displayMenu() {
    printf("\n=============================\n");
    printf("   AVL Tree Operations Menu  \n");
    printf("=============================\n");
    printf("1. Insert a node\n");
    printf("2. Delete a node\n");
    printf("3. Search a value\n");
    printf("4. Inorder Traversal\n");
    printf("5. Preorder Traversal\n");
    printf("6. Postorder Traversal\n");
    printf("7. Display Tree Structure\n");
    printf("8. Exit\n");
    printf("=============================\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node *root = NULL;
    int choice, value;

    printf("\n*** AVL Tree Project in C ***\n");

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Inserted %d successfully.\n", value);
                break;

            case 2:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                    break;
                }
                printf("Enter value to delete: ");
                scanf("%d", &value);
                if (search(root, value)) {
                    root = deleteNode(root, value);
                    printf("Deleted %d successfully.\n", value);
                } else {
                    printf("Value %d not found in tree.\n", value);
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                    break;
                }
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value))
                    printf("Value %d FOUND in the AVL tree.\n", value);
                else
                    printf("Value %d NOT FOUND in the AVL tree.\n", value);
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                    break;
                }
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                    break;
                }
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                    break;
                }
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                    break;
                }
                printf("\nTree Structure (rotated 90 degrees, h=height, bf=balance factor):\n");
                printTree(root, 0);
                printf("\n");
                break;

            case 8:
                printf("Freeing memory and exiting...\n");
                freeTree(root);
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}