#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "prototype2.h"

CustomerHashNode* hashTable[HASH_SIZE] = { NULL };

//AVL tree functions

int height(OrderAVLNode* node) {
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

OrderAVLNode* createAVLOrder(int orderID) {
    OrderAVLNode* node = (OrderAVLNode*)malloc(sizeof(OrderAVLNode));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    node->orderID = orderID;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

OrderAVLNode* rotateRight(OrderAVLNode* y) {
    OrderAVLNode* x = y->left;
    OrderAVLNode* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = maxInt(height(y->left), height(y->right)) + 1;
    x->height = maxInt(height(x->left), height(x->right)) + 1;

    return x;
}

OrderAVLNode* rotateLeft(OrderAVLNode* x) {
    OrderAVLNode* y = x->right;
    OrderAVLNode* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = maxInt(height(x->left), height(x->right)) + 1;
    y->height = maxInt(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(OrderAVLNode* node) {
    if (node == NULL) {
        return 0;
    }

    return height(node->left) - height(node->right);
}

OrderAVLNode* insertAVLOrder(OrderAVLNode* root, int orderID) {
    if (root == NULL) {
        return createAVLOrder(orderID);
    }

    if (orderID < root->orderID) {
        root->left = insertAVLOrder(root->left, orderID);
    }
    else if (orderID > root->orderID) {
        root->right = insertAVLOrder(root->right, orderID);
    }
    else {
        return root;
    }

    root->height = 1 + maxInt(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && orderID < root->left->orderID) {
        return rotateRight(root);
    }

    if (balance < -1 && orderID > root->right->orderID) {
        return rotateLeft(root);
    }

    if (balance > 1 && orderID > root->left->orderID) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && orderID < root->right->orderID) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void printAVLOrders(OrderAVLNode* root) {
    if (root != NULL) {
        printAVLOrders(root->left);
        printf("%d ", root->orderID);
        printAVLOrders(root->right);
    }
}

//customer has table function 
int hashFunction(int customerID) {
    return customerID % HASH_SIZE;
}

CustomerHashNode* createCustomerHashNode(int customerID) {
    CustomerHashNode* node = (CustomerHashNode*)malloc(sizeof(CustomerHashNode));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    node->customerID = customerID;
    node->orders = NULL;
    node->next = NULL;

    return node;
}

CustomerHashNode* findCustomerPrototype2(int customerID) {
    int index = hashFunction(customerID);
    CustomerHashNode* current = hashTable[index];

    while (current != NULL) {
        if (current->customerID == customerID) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void insertOrderPrototype2(int customerID, int orderID) {
    int index = hashFunction(customerID);
    CustomerHashNode* customer = findCustomerPrototype2(customerID);

    if (customer == NULL) {
        customer = createCustomerHashNode(customerID);
        customer->next = hashTable[index];
        hashTable[index] = customer;
    }

    customer->orders = insertAVLOrder(customer->orders, orderID);
}

void printCustomersPrototype2() {
    printf("Prototype 2 Customers:\n");

    for (int i = 0; i < HASH_SIZE; i++) {
        CustomerHashNode* current = hashTable[i];

        while (current != NULL) {
            printf("Customer %d\n", current->customerID);
            current = current->next;
        }
    }
}

void printOrdersForCustomerPrototype2(int customerID) {
    CustomerHashNode* customer = findCustomerPrototype2(customerID);

    printf("Prototype 2 Orders for Customer %d: ", customerID);

    if (customer == NULL) {
        printf("Customer not found\n");
        return;
    }

    printAVLOrders(customer->orders);
    printf("\n");
}