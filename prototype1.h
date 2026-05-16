#ifndef PROTOTYPE1_H
#define PROTOTYPE1_H

typedef struct OrderBSTNode {
    int orderID;
    struct OrderBSTNode* left;
    struct OrderBSTNode* right;
} OrderBSTNode;

typedef struct CustomerListNode {
    int customerID;
    OrderBSTNode* orders;
    struct CustomerListNode* next;
} CustomerListNode;

OrderBSTNode* createBSTOrder(int orderID);
OrderBSTNode* insertBSTOrder(OrderBSTNode* root, int orderID);
void printBSTOrders(OrderBSTNode* root);

CustomerListNode* createCustomerListNode(int customerID);
CustomerListNode* findCustomerPrototype1(int customerID);
void insertOrderPrototype1(int customerID, int orderID);
void printCustomersPrototype1();
void printOrdersForCustomerPrototype1(int customerID);

#endif#pragma once
