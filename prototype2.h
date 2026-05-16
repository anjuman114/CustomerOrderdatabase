#ifndef PROTOTYPE2_H
#define PROTOTYPE2_H

#define HASH_SIZE 1009 //copilot has been used for this part 

typedef struct OrderAVLNode {
    int orderID;
    int height;
    struct OrderAVLNode* left;
    struct OrderAVLNode* right;
} OrderAVLNode;

typedef struct CustomerHashNode {
    int customerID;
    OrderAVLNode* orders;
    struct CustomerHashNode* next;
} CustomerHashNode;

int height(OrderAVLNode* node);
int maxInt(int a, int b);
OrderAVLNode* createAVLOrder(int orderID);
OrderAVLNode* rotateRight(OrderAVLNode* y);
OrderAVLNode* rotateLeft(OrderAVLNode* x);
int getBalance(OrderAVLNode* node);
OrderAVLNode* insertAVLOrder(OrderAVLNode* root, int orderID);
void printAVLOrders(OrderAVLNode* root);

int hashFunction(int customerID);
CustomerHashNode* createCustomerHashNode(int customerID);
CustomerHashNode* findCustomerPrototype2(int customerID);
void insertOrderPrototype2(int customerID, int orderID);
void printCustomersPrototype2();
void printOrdersForCustomerPrototype2(int customerID);

#endif#pragma once
