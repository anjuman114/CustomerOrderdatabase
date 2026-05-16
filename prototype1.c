#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "prototype1.h"

CustomerListNode* prototype1Head = NULL;
//Order BST function

OrderBSTNode* createBSTOrder(int orderID) {
    OrderBSTNode* node = (OrderBSTNode*)malloc(sizeof(OrderBSTNode));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    node->orderID = orderID;
    node->left = NULL;
    node->right = NULL;

    return node;
}

OrderBSTNode* insertBSTOrder(OrderBSTNode* root, int orderID) {
    if (root == NULL) {
        return createBSTOrder(orderID);
    }

    if (orderID < root->orderID) {
        root->left = insertBSTOrder(root->left, orderID);
    }
    else if (orderID > root->orderID) {
        root->right = insertBSTOrder(root->right, orderID);
    }

    return root;
}

void printBSTOrders(OrderBSTNode* root) {
    if (root != NULL) {
        printBSTOrders(root->left);
        printf("%d ", root->orderID);
        printBSTOrders(root->right);
    }
}

  // CUSTOMER LINKED LIST FUNCTIONS
  

CustomerListNode* createCustomerListNode(int customerID) {
    CustomerListNode* node = (CustomerListNode*)malloc(sizeof(CustomerListNode));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    node->customerID = customerID;
    node->orders = NULL;
    node->next = NULL;

    return node;
}

CustomerListNode* findCustomerPrototype1(int customerID) {
    CustomerListNode* current = prototype1Head;

    while (current != NULL) {
        if (current->customerID == customerID) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void insertOrderPrototype1(int customerID, int orderID) {
    CustomerListNode* customer = findCustomerPrototype1(customerID);

    if (customer == NULL) {
        customer = createCustomerListNode(customerID);
        customer->next = prototype1Head;
        prototype1Head = customer;
    }

    customer->orders = insertBSTOrder(customer->orders, orderID);
}

void printCustomersPrototype1() {
    CustomerListNode* current = prototype1Head;

    printf("Prototype 1 Customers:\n");

    while (current != NULL) {
        printf("Customer %d\n", current->customerID);
        current = current->next;
    }
}

void printOrdersForCustomerPrototype1(int customerID) {
    CustomerListNode* customer = findCustomerPrototype1(customerID);

    printf("Prototype 1 Orders for Customer %d: ", customerID);

    if (customer == NULL) {
        printf("Customer not found\n");
        return;
    }

    printBSTOrders(customer->orders);
    printf("\n");
}