#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HASH_SIZE 1009
//Order bst- used in prototype one

typedef struct OrderBSTNode {
    int orderID;
    struct OrderBSTNode* left;
    struct OrderBSTNode* right;
} OrderBSTNode;

OrderBSTNode* createBSTOrder(int orderID) {
    OrderBSTNode* node = (OrderBSTNode*)malloc(sizeof(OrderBSTNode));
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

int countBSTOrders(OrderBSTNode* root) {
    if (root == NULL) return 0;
    return 1 + countBSTOrders(root->left) + countBSTOrders(root->right);
}

  // PROTOTYPE 1: Linked List of Customers + BST of Orders
  

typedef struct CustomerListNode {
    int customerID;
    OrderBSTNode* orders;
    struct CustomerListNode* next;
} CustomerListNode;

CustomerListNode* prototype1Head = NULL;

CustomerListNode* createCustomerListNode(int customerID) {
    CustomerListNode* node = (CustomerListNode*)malloc(sizeof(CustomerListNode));
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

   //AVL TREE - used in Prototype 2

typedef struct OrderAVLNode {
    int orderID;
    int height;
    struct OrderAVLNode* left;
    struct OrderAVLNode* right;
} OrderAVLNode;

int height(OrderAVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

OrderAVLNode* createAVLOrder(int orderID) {
    OrderAVLNode* node = (OrderAVLNode*)malloc(sizeof(OrderAVLNode));
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
    if (node == NULL) return 0;
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

   //PROTOTYPE 2: Hash Table of Customers + AVL Tree of Orders
  
typedef struct CustomerHashNode {
    int customerID;
    OrderAVLNode* orders;
    struct CustomerHashNode* next;
} CustomerHashNode;

CustomerHashNode* hashTable[HASH_SIZE];

int hashFunction(int customerID) {
    return customerID % HASH_SIZE;
}

CustomerHashNode* createCustomerHashNode(int customerID) {
    CustomerHashNode* node = (CustomerHashNode*)malloc(sizeof(CustomerHashNode));
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

   //TESTING
  
void runUnitTests() {
    printf(" UNIT TESTS\n");

    insertOrderPrototype1(101, 5003);
    insertOrderPrototype1(101, 5001);
    insertOrderPrototype1(101, 5002);
    insertOrderPrototype1(102, 6001);

    insertOrderPrototype2(101, 5003);
    insertOrderPrototype2(101, 5001);
    insertOrderPrototype2(101, 5002);
    insertOrderPrototype2(102, 6001);

    printf("\nTest 1: Insert and print orders for customer 101\n");
    printOrdersForCustomerPrototype1(101);
    printOrdersForCustomerPrototype2(101);

    printf("\nTest 2: Search missing customer\n");
    printOrdersForCustomerPrototype1(999);
    printOrdersForCustomerPrototype2(999);

    printf("\nTest 3: Print customers\n");
    printCustomersPrototype1();
    printCustomersPrototype2();

    printf("\nUnit tests completed.\n");
}

  // PERFORMANCE EVALUATION
void runPerformanceTest(int numberOfCustomers, int ordersPerCustomer) {
    clock_t start, end;
    double timePrototype1;
    double timePrototype2;

    printf("\n PERFORMANCE TEST \n");
    printf("Customers: %d\n", numberOfCustomers);
    printf("Orders per customer: %d\n", ordersPerCustomer);

    start = clock();

    for (int c = 1; c <= numberOfCustomers; c++) {
        for (int o = 1; o <= ordersPerCustomer; o++) {
            insertOrderPrototype1(c + 1000, (c * 100000) + o);
        }
    }

    end = clock();
    timePrototype1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();

    for (int c = 1; c <= numberOfCustomers; c++) {
        for (int o = 1; o <= ordersPerCustomer; o++) {
            insertOrderPrototype2(c + 1000, (c * 100000) + o);
        }
    }

    end = clock();
    timePrototype2 = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nResults:\n");
    printf("Prototype 1 Linked List + BST time: %.4f seconds\n", timePrototype1);
    printf("Prototype 2 Hash Table + AVL time: %.4f seconds\n", timePrototype2);

    if (timePrototype2 < timePrototype1) {
        printf("Prototype 2 was faster.\n");
    }
    else {
        printf("Prototype 1 was faster or similar for this dataset.\n");
    }
}

   //Main function 

int main() {
    printf("Customer Order Database Project\n");
    printf("One-to-many relationship: One customer can have many orders.\n\n");

    runUnitTests();

    runPerformanceTest(1000, 20);

    printf("\nProgram finished successfully.\n");

    return 0;
}