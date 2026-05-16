#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include "prototype1.h"
#include "prototype2.h"

//testing 

void runUnitTests() {
    printf(" UNIT TESTS \n");

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

   //PERFORMANCE EVALUATION
  

void runPerformanceTest(int numberOfCustomers, int ordersPerCustomer) {
    clock_t start, end;
    double timePrototype1;
    double timePrototype2;

    printf("\n PERFORMANCE TEST\n");
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

   //MAIN

int main() {
    printf("Customer Order Database Project\n");
    printf("One-to-many relationship: One customer can have many orders.\n\n");

    runUnitTests();

    runPerformanceTest(1000, 20);

    printf("\nProgram finished successfully.\n");

    return 0;
}